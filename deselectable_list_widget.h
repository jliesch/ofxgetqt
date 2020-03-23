#ifndef DESELECTABLE_LIST_WIDGET_H
#define DESELECTABLE_LIST_WIDGET_H

#include <QListWidget>

class DeselectableListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DeselectableListWidget(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // DESELECTABLE_LIST_WIDGET_H
