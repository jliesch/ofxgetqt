#include "waitingdialog.h"
#include "ui_waitingdialog.h"

WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent)
{
    ui_->setupUi(this);
}

WaitingDialog::WaitingDialog(QWidget *parent, const QString& text) :
    QDialog(parent),
    ui_(new Ui::WaitingDialog)
{
    ui_->setupUi(this);
    ui_->progress->setRange(0, 100);
    setText(text);
}

WaitingDialog::~WaitingDialog()
{
    delete ui_;
}

void WaitingDialog::setText(const QString& text) {
    ui_->message->setText(text);
}

void WaitingDialog::setProgress(float progress) {
    ui_->progress->setValue(100 * progress);
}
