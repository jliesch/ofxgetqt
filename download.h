#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <set>

#include <QWidget>

#include "ofxgetmainwindow.h"
#include "ofxget/ofxget.h"
#include "ofxget/ofxhome.h"
#include "waitingdialog.h"

namespace Ui {
class Download;
}

class OfxGet;

class Download : public QWidget
{
    Q_OBJECT

public:
    explicit Download(const ofxget::Institution* inst,
                      OfxGetMainWindow* main_window, QWidget *parent = 0);
    ~Download();

public slots:
    void DoDownload();
    void LoadRequest(const QString&);
    void ofxResponse(const QString&, const QString&, bool);

private:
    Ui::Download *ui_;
    const ofxget::Institution* institution_;
    OfxGetMainWindow* main_;
    ofxget::OfxGetContext ofxget_context_;
    std::map<std::string, std::string> acct_ids_;
    std::map<std::string, std::string> user_vars_;
    QString response_;
    QString headers_;
    bool success_;

    bool eventFilter(QObject* obj, QEvent* event);
    static QString FormatResponse(const QString& response);
    static QString ExtractOfxValue(const QString& ofx, const QString& value);
    static QList<QPair<QString, QString>> ExtractOfxValues(const QString& ofx, const QStringList& values);
    static QString SanitizeRequest(const QString& request);
    void VarsToWidget();

    friend class Download_test;
};

#endif // DOWNLOAD_H
