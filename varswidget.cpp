#include <QDebug>

#include "varswidget.h"

VarsWidget::VarsWidget(QWidget *parent)
    : QTableWidget(parent)
{
}

VarsWidget::VarsWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
}

bool VarsWidget::focusNextPrevChild(bool next) {
  if (next) {
    if (currentRow() <= 0) {
      setCurrentCell(1, 1);
    } else {
      setCurrentCell((currentRow() + 1) % rowCount(), 1);
    }
  } else {
    if (currentRow() <= 0) {
      setCurrentCell(rowCount() - 1, 1);
    } else {
      setCurrentCell(currentRow() - 1 , 1);
    }
  }
  return true;
}
