#pragma once

#include <QStyledItemDelegate>
#include <QTextDocument>


class RichTextDelegate : public QStyledItemDelegate {
 public:
  using QStyledItemDelegate::QStyledItemDelegate;

 protected:
  void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
  QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;

 private:
  void prepareTextDocument(QTextDocument &doc, QStyleOptionViewItem &option) const;
};
