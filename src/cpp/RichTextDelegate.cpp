#include "RichTextDelegate.h"

#include <QApplication>
#include <QPainter>
#include <QTextCursor>
#include <QTextDocument>


void RichTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &inOption,
                             const QModelIndex &index) const {
  QStyleOptionViewItem option = inOption;
  initStyleOption(&option, index);

  if (option.text.isEmpty()) {
    QStyledItemDelegate::paint(painter, inOption, index);
    return;
  }

  QTextDocument doc;
  prepareTextDocument(doc, option);

  if (doc.size().width() > option.rect.width()) {
    QTextCursor cursor(&doc);
    cursor.movePosition(QTextCursor::End);

    QChar ellipsisChar(0x2026);
    QFontMetrics metric(option.font);
    int ellipsisCharWidth = metric.horizontalAdvance(ellipsisChar);
    while (doc.size().width() > option.rect.width() - ellipsisCharWidth) {
      cursor.deletePreviousChar();
      doc.adjustSize();
    }
    cursor.insertText(ellipsisChar);
  }

  // Let QStyle paint any highlights and backgrounds.
  option.text = QString();
  QStyle *style = option.widget ? option.widget->style() : QApplication::style();
  style->drawControl(QStyle::CE_ItemViewItem, &option, painter, inOption.widget);

  // Get QStyle to handle text alignment and draw box position.
  QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &option);
  QSize documentSize(doc.size().width(), doc.size().height());
  QRect layoutRect = QStyle::alignedRect(Qt::LayoutDirectionAuto, option.displayAlignment, documentSize, textRect);

  // The doc.drawContents() renders with (0,0) as its origin. Translate the painter
  // position doc over the desired text rectangle rendered at the correct position.
  painter->save();
  painter->translate(layoutRect.topLeft());
  doc.drawContents(painter, textRect.translated(-textRect.topLeft()));
  painter->restore();
}

QSize RichTextDelegate::sizeHint(const QStyleOptionViewItem &inOption, const QModelIndex &index) const {
  QStyleOptionViewItem option = inOption;
  initStyleOption(&option, index);

  if (option.text.isEmpty()) {
    return QStyledItemDelegate::sizeHint(inOption, index);
  }

  QTextDocument doc;
  prepareTextDocument(doc, option);
  return QSize(doc.idealWidth(), doc.size().height());
}

void RichTextDelegate::prepareTextDocument(QTextDocument &doc, QStyleOptionViewItem &option) const {
  QTextOption textOption;
  textOption.setWrapMode(option.features & QStyleOptionViewItem::WrapText ? QTextOption::WordWrap
                                                                          : QTextOption::ManualWrap);
  textOption.setTextDirection(option.direction);
  doc.setDefaultFont(option.font);
  doc.setTextWidth(option.rect.width());
  doc.setDocumentMargin(0);
  doc.setDefaultTextOption(textOption);
  doc.setHtml(option.text);
  doc.adjustSize();
}
