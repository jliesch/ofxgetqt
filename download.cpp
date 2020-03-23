#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QKeyEvent>

#include "download.h"
#include "ui_download.h"
#include "ofxget_widget.h"
#include "ofxhomeworker.h"
#include "varswidget.h"

#include "ofxget/ofxget.h"

using namespace ofx_get;
using std::string;
using std::vector;

Download::Download(const Institution* inst, OfxGetMainWindow* main_window,
                   QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Download),
    institution_(inst),
    main_(main_window)
{
    ui_->setupUi(this);
    this->installEventFilter(this);
    ui_->vars->installEventFilter(this);
    connect(ui_->downloadButton,
            SIGNAL(released()),
            this,
            SLOT(DoDownload()));
    connect(ui_->requestTypes,
            SIGNAL(currentTextChanged(const QString&)),
            this,
            SLOT(LoadRequest(const QString&)));

    QStringList request_files = QDir(":/requests/").entryList();
    for (int i = 0; i < request_files.size(); ++i) {
        ui_->requestTypes->addItem(QString(request_files.at(i)).replace(".txt", ""));
    }

    if (institution_) {
       this->setWindowTitle(institution_->name.c_str());
    } else {
        this->setWindowTitle("Download");
    }

    LoadRequest("accounts");
}

Download::~Download()
{
    delete ui_;
}

bool Download::eventFilter(QObject* obj, QEvent* event) {
    (void) obj;  // Remove warning.
    // Filter for enter events.
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Enter ||
            keyEvent->key() == Qt::Key_Return) {
            ui_->downloadButton->animateClick();
            return true;
        }
    }
    return false;
}

void Download::LoadRequest(const QString& req) {
    QFile request(":/requests/" + req + ".txt");
    string request_string;
    if (request.open(QFile::ReadOnly)) {
        QTextStream in(&request);
        request_string = in.readAll().toUtf8().constData();
        QTextEdit* requestLabel = this->findChild<QTextEdit*>("request");
        if (requestLabel) {
            requestLabel->setText(request_string.c_str());
        }
    } else {
        main_->showError("Could not read query file");
    }

    InitVars(&vars_);
    AddApp(&vars_, "Quicken_2011");
    if (institution_ && institution_->bankid != "") {
        vars_["BANKID"] = institution_->bankid;
    }
    if (institution_ && institution_->brokerid != "") {
        vars_["BROKERID"] = institution_->brokerid;
    }
    if (institution_ && institution_->fid != "") {
        vars_["FID"] = institution_->fid;
    }
    if (institution_ && institution_->org != "") {
        vars_["ORG"] = institution_->org;
    }
    vector<string> missing = GetMissingRequestVars(request_string, vars_);
    for (const string& m : missing) {
        vars_[m] = "";
        if (user_vars_.count(m) == 0) {
            user_vars_[m] = "";
        }
    }
    VarsToWidget();

    QLineEdit* urlLabel = this->findChild<QLineEdit*>("url");
    if (urlLabel) {
        if (institution_) {
            urlLabel->setText(institution_->url.c_str());
            urlLabel->setCursorPosition(0);
        } else {
            urlLabel->setText("");
        }
    }
}

void Download::ofxResponse(
    const QString& response, const QString& headers, bool success) {
  response_ = response;
  success_ = success;
  headers_ = headers;
}

void Download::VarsToWidget() {
    VarsWidget* varsTable = this->findChild<VarsWidget*>("vars");
    if (varsTable) {
        varsTable->clearContents();
        varsTable->setRowCount(vars_.size());
        varsTable->setColumnCount(2);
        varsTable->horizontalHeader()->hide();
        varsTable->verticalHeader()->hide();
        varsTable->horizontalHeader()->setStretchLastSection(true);
        // First pass for user vars.
        int i = 0;
        for (const auto& it : vars_) {
            if (it.second.empty() || user_vars_.count(it.first) > 0) {
                if (user_vars_.count(it.first) == 0) {
                    user_vars_[it.first] = "";
                }
                varsTable->setCellWidget(i, 0, new QLabel(it.first.c_str()));
                varsTable->cellWidget(i, 0)->setStyleSheet("padding-left: 5px");
                if (it.first == "ACCTID") {
                    if (!acct_ids_.empty()) {
                        QStringList accts;
                        for (const auto& kv : acct_ids_) {
                            if (kv.second.empty()) {
                                accts.append(kv.first.c_str());
                            } else {
                                accts.append((kv.first + " (" + kv.second + ")").c_str());
                            }
                        }
                        QComboBox* combo = new QComboBox(this);
                        combo->addItems(accts);
                        combo->setFrame(false);
                        combo->setStyleSheet("padding-left: 5px");
                        varsTable->setCellWidget(i, 1, combo);
                    } else {
                        QLineEdit* le = new QLineEdit(user_vars_[it.first].c_str());
                        le->setFrame(false);
                        le->setStyleSheet("padding-left: 5px");
                        varsTable->setCellWidget(i, 1, le);
                    }
                } else {
                    QLineEdit* le = new QLineEdit(user_vars_[it.first].c_str());
                    if (it.first == "USERPASS") {
                        le->setEchoMode(QLineEdit::Password);
                    }
                    le->setFrame(false);
                    le->setStyleSheet("padding-left: 5px");
                    varsTable->setCellWidget(i, 1, le);
                }
                i++;
            }
        }
        // Next fill in non-user vars.
        for (const auto& it : vars_) {
            if (!(it.second.empty() || user_vars_.count(it.first) > 0)) {
                varsTable->setCellWidget(i, 0, new QLabel(it.first.c_str()));
                varsTable->cellWidget(i, 0)->setStyleSheet("padding-left: 5px");
                QLineEdit* le = new QLineEdit(it.second.c_str());
                le->setFrame(false);
                le->setStyleSheet("padding-left: 5px");
                varsTable->setCellWidget(i, 1, le);
                i++;
            }
        }
        varsTable->cellWidget(0, 1)->setFocus();
    }
}

void Download::DoDownload() {
    // Create waiting dialog. Sets result to -1 if aborted.
    WaitingDialog waiting(this, "Downloading OFX data");
    waiting.show();
    connect(
        &waiting, &QDialog::finished,
        [&waiting](int) { waiting.setResult(-1); }
    );
    string request_string = ui_->request->toPlainText().toStdString();

    VarsWidget* varsTable = ui_->vars;
    for (int i = 0; i < varsTable->rowCount(); ++i)
    {
        string var = ((QLabel*) varsTable->cellWidget(i, 0))->text().toStdString();
        string value;
        QWidget* valueWidget = varsTable->cellWidget(i, 1);
        if (!strcmp(valueWidget->metaObject()->className(), "QComboBox")) {
            value = ((QComboBox*) valueWidget)->currentText().toStdString();
            std::size_t parens = value.find(" (");
            if (parens != string::npos) {
                value = value.substr(0, parens);
            }
        } else if (!strcmp(valueWidget->metaObject()->className(), "QLineEdit")) {
            value = ((QLineEdit*) valueWidget)->text().toStdString();
        }
        if (!value.empty()) {
            if (vars_[var] != value) {
                user_vars_[var] = value;
            }
            vars_[var] = value;
        }
    }
    vector<string> missing = GetMissingRequestVars(request_string, vars_);
    for (const string& m : missing) {
        vars_[m] = "";
        user_vars_[m] = "";
    }
    VarsToWidget();

    if (missing.size() != 0) {
        main_->showError("Please fill values for all missing vars.");
        return;
    }

    QLineEdit* urlLabel = this->findChild<QLineEdit*>("url");
    string url = urlLabel->text().toStdString();

    string request;
    response_ = "__waiting__";
    headers_ = "";
    success_ = false;
    OfxHomeController controller;
    try {
        // Build and send request to OfxHomeController. response_ and success_
        // will be set by the ofxResponse slot. We wait until there is a
        // response or until the operation is aborted.
        request = BuildRequest(request_string, vars_);
        controller.ofxRequest(this, request, url);
        QElapsedTimer timer;
        timer.start();
        while (response_ == "__waiting__" && waiting.result() != -1) {
            QThread::msleep(10);
            waiting.setProgress(timer.elapsed() / 1000.0 / REQUEST_TIMEOUT);
            QApplication::processEvents();
        }
    } catch(const string& msg) {
        waiting.done(0);
        main_->showError(msg.c_str());
        return;
    }

    if (waiting.result() == -1) {
        // User aborted. Canceling ofx request will disconnect the
        // ofxRespone signal.
        controller.cancelOfxRequest(this);
        return;
    }

    if (!success_) {
        waiting.done(0);
        main_->showError(response_);
        return;
    }

    // Check for account ids
    QStringList acct_fields;
    acct_fields << "ACCTINFO" << "/ACCTINFO" << "ACCTID" << "DESC" << "USPRODUCTTYPE";
    QList<QPair<QString, QString>> accts = ExtractOfxValues(
                response_, acct_fields);
    QString desc;
    QString acctid;
    QString product;
    for (int i = 0; i < accts.size(); i++) {
        if (accts.at(i).first == "ACCTINFO") {
            desc = "";
            acctid = "";
            product = "";
        } else if (accts.at(i).first == "ACCTID") {
            acctid = accts.at(i).second;
        } else if (accts.at(i).first == "DESC") {
            desc = accts.at(i).second;
        } else if (accts.at(i).first == "USPRODUCTTYPE") {
            product = accts.at(i).second;
        } else if (accts.at(i).first == "/ACCTINFO") {
            if (!acctid.isEmpty()) {
                if (!desc.isEmpty() && !product.isEmpty()) {
                    acct_ids_[acctid.toStdString()] = (product + ": " + desc).toStdString();
                } else if (!desc.isEmpty()) {
                    acct_ids_[acctid.toStdString()] = desc.toStdString();
                } else if (!product.isEmpty()) {
                    acct_ids_[acctid.toStdString()] = product.toStdString();
                } else  {
                    acct_ids_[acctid.toStdString()] = "";
                }
            }
        }
    }

    ui_->response->setText(FormatResponse(response_));
    ui_->headers->setText(headers_);

    if (main_->sendInstitutionData()) {
        QString code = ExtractOfxValue(response_, "code");
        QString severity = ExtractOfxValue(response_, "severity");

        if (code == "0" || code == "2000" || code == "2003" || code == "3000"
            || code == "15500") {
            const string& api_key = "cdc580fb6ac146c8c2c5de82f587d9b4";
            string out;
            try {
              out = UploadSuccessfulRequest(api_key, url, request);
            } catch(const string& msg) {
               main_->showError(msg.c_str());
              return;
            }
        }
    }
}

QString Download::FormatResponse(const QString& response) {
    QString formatted = response;
    formatted.replace(QRegExp("\n?<([^>]*)>"), "\n<\\1>");
    if (formatted[0] == "\n") {
        formatted.remove(0, 1);
    }
    return formatted;
}

QString Download::ExtractOfxValue(const QString& ofx, const QString& value) {
    QRegExp reg("<" + value + ">([^<]*)");
    reg.setCaseSensitivity(Qt::CaseInsensitive);
    if (reg.indexIn(ofx) != -1) {
        return reg.cap(1).trimmed();
    } else {
        return "";
    }
}

QList<QPair<QString, QString>> Download::ExtractOfxValues(
        const QString& ofx, const QStringList& values) {
    QList<QPair<QString, QString>> matches;
    if (values.size() == 0) {
        return matches;
    }
    QString re = "<(" + values.at(0);
    for (int i = 1; i < values.size(); i++) {
        re += "|" + values.at(i);
    }
    re += ")>([^<]*)";
    QRegExp reg(re);
    reg.setCaseSensitivity(Qt::CaseInsensitive);
    int offset = 0;
    while (true)
    {
        if (reg.indexIn(ofx, offset) != -1) {
            offset = reg.pos(1) + reg.matchedLength() - 1;
            matches.append(QPair<QString, QString>(reg.cap(1).trimmed(),
                                                   reg.cap(2).trimmed()));
        } else {
            break;
        }
    }
    return matches;
}

QString Download::SanitizeRequest(const QString& request) {
    QStringList to_sanitize;
    to_sanitize << "USERID" << "USERPASS" << "ACCTID";
    QString s = request;
    for (int i = 0; i < to_sanitize.length(); i++) {
        QString val = ExtractOfxValue(s, to_sanitize.at(i));
        if (!val.isEmpty()) {
            s.replace(val, "XXXXX");
        }
    }
    return s;
}
