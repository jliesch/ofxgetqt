#ifndef OFXGETMAINWINDOW_H
#define OFXGETMAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class OfxGetMainWindow;
}

class OfxGetMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OfxGetMainWindow(QWidget *parent = 0);
    ~OfxGetMainWindow();

    bool showFailingInstitutions();
    bool sendInstitutionData();
    void showError(QString err);

    QSettings settings_;

public slots:
    void showPreferences();

private:
    Ui::OfxGetMainWindow *ui;
};

#endif // OFXGETMAINWINDOW_H
