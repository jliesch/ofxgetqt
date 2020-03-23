#include <QDebug>
#include <QMessageBox>
#include <preferences.h>

#include "ofxgetmainwindow.h"
#include "ui_ofxgetmainwindow.h"

OfxGetMainWindow::OfxGetMainWindow(QWidget *parent) :
    QMainWindow(parent),
    settings_("OFX Home", "ofxget"),
    ui(new Ui::OfxGetMainWindow)
{
    ui->setupUi(this);

    auto fileMenu = menuBar()->addMenu(tr("&File"));

    auto preferences = new QAction("Preferences", this);
    fileMenu->addAction(preferences);
    connect(preferences, &QAction::triggered,
            this, &OfxGetMainWindow::showPreferences);
}

OfxGetMainWindow::~OfxGetMainWindow()
{
    delete ui;
}

void OfxGetMainWindow::showPreferences() {
    Preferences p(&settings_, ui->centralwidget);
    p.exec();
}

bool OfxGetMainWindow::showFailingInstitutions() {
    return settings_.value("showFailingInstitutions", QVariant(true)).toBool();
}

bool OfxGetMainWindow::sendInstitutionData() {
    return settings_.value("sendInstitutionData", QVariant(false)).toBool();
}

void OfxGetMainWindow::showError(QString err) {
    qDebug() << err;
    QMessageBox::critical(this, "", err, QMessageBox::Ok);
}
