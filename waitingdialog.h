#ifndef WAITINGDIALOG_H
#define WAITINGDIALOG_H

#include <QDialog>

namespace Ui {
class WaitingDialog;
}

class WaitingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingDialog(QWidget *parent = 0);
    WaitingDialog(QWidget *parent, const QString& text);
    ~WaitingDialog();

    void setText(const QString& text);

    // Progress between 0 and 1.
    void setProgress(float progress);

private:
    Ui::WaitingDialog *ui_;
};

#endif // WAITINGDIALOG_H
