#ifndef VARSWIDGET_H
#define VARSWIDGET_H

#include <QTableWidget>

class VarsWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit VarsWidget(QWidget *parent = nullptr);
    VarsWidget(int rows, int columns, QWidget *parent = nullptr);

    bool focusNextPrevChild(bool next);

private:
    int editable_ = 0;
};

#endif // VARSWIDGET_H
