#ifndef OFXGET_H
#define OFXGET_H

#include <QWidget>
#include <QSettings>
#include <QListWidget>

#include "ofxgetmainwindow.h"
#include "ofxget/ofxhome.h"

namespace Ui {
class OfxGet;
}

class OfxGet : public QWidget
{
    Q_OBJECT

public:
    explicit OfxGet(QWidget *main_window);
    ~OfxGet();

    void rebuildList(const std::string& search);

public slots:
    void loadInstitutions();
    void selectInstitution(QListWidgetItem * current, QListWidgetItem * previous);
    void searchInstitution(const QString &);
    void query();

private:
    OfxGetMainWindow* main_window_;
    Ui::OfxGet *ui_;
    std::vector<ofx_get::Institution> institutions_;
    const ofx_get::Institution* selected_institution_;

    void clearSelection();
};

#endif // OFXGET_H
