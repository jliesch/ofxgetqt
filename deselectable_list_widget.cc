#include <QDebug>
#include <QListWidgetItem>
#include <QMouseEvent>

#include "deselectable_list_widget.h"

DeselectableListWidget::DeselectableListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

void DeselectableListWidget::mousePressEvent(QMouseEvent *event) {
  QModelIndex index = indexAt(event->pos());
  QListWidgetItem selected_item(index.data().toString(), this);
  bool selected = selectionModel()->isSelected(index);
  if (selected) {
    selectionModel()->clearSelection();
    emit currentItemChanged(nullptr, &selected_item);
  } else {
      selectionModel()->clearSelection();
      selectionModel()->select(index, QItemSelectionModel::Select);
      selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
      emit currentItemChanged(&selected_item, nullptr);
  }
}
