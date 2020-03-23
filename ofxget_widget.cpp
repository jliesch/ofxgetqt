#include <QDebug>
#include <QTimer>

#include "ofxget_widget.h"
#include "ui_ofxget.h"

#include "download.h"
#include "ofxgetmainwindow.h"
#include "ofxget/ofxhome.h"
#include "ofxhomeworker.h"

using namespace ofx_get;
using std::string;

OfxGet::OfxGet(QWidget *main_window) :
    QWidget(main_window),
    main_window_((OfxGetMainWindow*) main_window),
    ui_(new Ui::OfxGet),
    selected_institution_(nullptr)
{
    ui_->setupUi(this);

    ui_->institutionList->addItem("... loading institutions ...");

    connect(ui_->institutionList,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this,
            SLOT(selectInstitution(QListWidgetItem*, QListWidgetItem*)));
    connect(ui_->institutionNameSearch,
            SIGNAL(textChanged(const QString&)),
            this,
            SLOT(searchInstitution(const QString&)));
    connect(ui_->query,
            SIGNAL(released()),
            this,
            SLOT(query()));

    QTimer::singleShot(200, this, SLOT(loadInstitutions()));
}

OfxGet::~OfxGet()
{
    delete ui_;
}

void OfxGet::loadInstitutions() {
    // Initialize institution list
    try {
        string institution_str = OfxHomeFullDumpString();
        institutions_ = OfxDumpStringToInstitutions(institution_str);
        std::sort(
            institutions_.begin(), institutions_.end(),
            [] (const Institution& a, const Institution& b) {
                return a.name < b.name;
            }
        );
        rebuildList("");
    } catch (const string& err) {
        main_window_->showError(err.c_str());
    }
}

void OfxGet::selectInstitution(QListWidgetItem * current, QListWidgetItem * previous) {
    (void) previous;  // Remove warning.
    selected_institution_ = nullptr;
    if (!current) {
        clearSelection();
        return;
    }
    if (current->text() == "... loading institutions ...") {
        return;
    }

    const Institution* i = FindInstitutionByName(
                institutions_, string(current->text().toStdString()));
    if (!i) {
        main_window_->showError("Could not find institution " + current->text());
        return;
    }
    selected_institution_ = i;

    ui_->nameLabel->setText(current->text());
    ui_->nameLabel->setCursorPosition(0);
    ui_->urlLabel->setText(i->url.c_str());
    ui_->urlLabel->setCursorPosition(0);
    ui_->fidLabel->setText(i->fid.c_str());
    ui_->fidLabel->setCursorPosition(0);
    ui_->orgLabel->setText(i->org.c_str());
    ui_->orgLabel->setCursorPosition(0);
    ui_->brokerIdLabel->setText(i->brokerid.c_str());
    ui_->brokerIdLabel->setCursorPosition(0);
    ui_->bankIdLabel->setText(i->bankid.c_str());
    ui_->bankIdLabel->setCursorPosition(0);
    if (i->ofxfail == 0 && i->sslfail == 0)  {
        ui_->failureLabel->setText("No failures");
        ui_->failureLabel->setStyleSheet("QLineEdit {  }");
    } else if (i->ofxfail != 0 && i->sslfail != 0)  {
        ui_->failureLabel->setText("OFX and SSL fail");
        ui_->failureLabel->setStyleSheet("QLineEdit { font-weight: bold; color:red }");
    } else if (i->ofxfail != 0) {
        ui_->failureLabel->setText("OFX fails");
        ui_->failureLabel->setStyleSheet("QLineEdit { font-weight: bold; color:red }");
    } else {
        ui_->failureLabel->setText("SSL fails");
        ui_->failureLabel->setStyleSheet("QLineEdit { font-weight: bold; color:red }");
    }
    ui_->failureLabel->setCursorPosition(0);
    ui_->notesLabel->setText(i->bankid.c_str());
    ui_->notesLabel->setCursorPosition(0);
    string profile_string;
    for (const auto& p : i->profile) {
        profile_string += p.first + ": " + p.second + "\n";
    }
    ui_->profileLabel->setText(profile_string.c_str());
}

std::string upper_string(const std::string& str)
{
    string upper;
    transform(str.begin(), str.end(), std::back_inserter(upper), toupper);
    return upper;
}

void OfxGet::searchInstitution(const QString& search) {
    rebuildList(upper_string(search.toStdString()));
}

void OfxGet::query() {
    // selected_institution may be null.
    Download* dl = new Download(selected_institution_, main_window_);
    dl->show();
}

void OfxGet::clearSelection() {
    ui_->nameLabel->setText("");
    ui_->urlLabel->setText("");
    ui_->fidLabel->setText("");
    ui_->orgLabel->setText("");
    ui_->brokerIdLabel->setText("");
    ui_->bankIdLabel->setText("");
    ui_->failureLabel->setText("");
    ui_->notesLabel->setText("");
    ui_->profileLabel->setText("");
}

void OfxGet::rebuildList(const string& searchIgnore) {
    ui_->institutionList->clear();
    const string search = upper_string(ui_->institutionNameSearch->text().toStdString());
    int index = 0;
    bool showFialing = main_window_->showFailingInstitutions();
    for (const auto& i: institutions_) {
        bool isFailing = i.ofxfail != 0 || i.sslfail != 0;
        if (!showFialing && isFailing) {
            continue;
        }
        if (search != "" && upper_string(i.name).find(search) == string::npos) {
            continue;
        }
        ui_->institutionList->addItem(QString(i.name.c_str()));
        if (isFailing) {
            ui_->institutionList->item(index)->setForeground(Qt::gray);
        }
        index++;
    }
}
