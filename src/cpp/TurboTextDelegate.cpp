#include "TurboTextDelegate.h"

#include <QApplication>
#include <QPainter>
#include <QTextCursor>
#include <QTextDocument>
#include <QDebug>


inline bool isFontSlot(const QChar c) {
  return c.unicode() >= FontSlotBase && c.unicode() <= FontSlotDefault;
}

inline bool isColorSlot(const QChar c) {
  return c.unicode() >= ColorSlotBase && c.unicode() <= ColorSlotDefault;
}

inline bool isCommand(const QChar c) {
  return c.unicode() >= FirstCommand && c.unicode() <= LastCommand;
}

TurboTextDelegate::TurboTextDelegate(QObject* parent) : QStyledItemDelegate(parent),
    m_fontSlots(FontSlotDefault - FontSlotBase),
    m_colorSlots(ColorSlotDefault - ColorSlotBase),
    m_colorSelectedSlots(ColorSlotDefault - ColorSlotBase) {}

TurboTextDelegate::~TurboTextDelegate() {
}

void TurboTextDelegate::setFont(int slot, QFont &font) {
  m_fontSlots[slot - FontSlotBase] = font;
}

void TurboTextDelegate::setColor(int slot, QColor &color, QColor &colorSelected) {
  m_colorSlots[slot - ColorSlotBase] = color;
  m_colorSelectedSlots[slot - ColorSlotBase] = colorSelected;
}

void TurboTextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &inOption,
                              const QModelIndex &index) const {

  QStyleOptionViewItem option = inOption;
  initStyleOption(&option, index);

  if (option.text.isEmpty()) {
    QStyledItemDelegate::paint(painter, inOption, index);
    return;
  }

  // Let QStyle paint any highlights and backgrounds.
  QString text = option.text;
  option.text = QString();
  QStyle *style = option.widget ? option.widget->style() : QApplication::style();
  style->drawControl(QStyle::CE_ItemViewItem, &option, painter, inOption.widget);

  // Get QStyle to handle text alignment and draw box position.
  QRect textAreaRect = style->subElementRect(QStyle::SE_ItemViewItemText, &option);
  QFontMetrics fm(painter->font());
  QSize lineSize(fm.horizontalAdvance(text), fm.height());
  QRect textRect = QStyle::alignedRect(Qt::LayoutDirectionAuto, option.displayAlignment, lineSize, textAreaRect);
  textRect.setWidth(textAreaRect.width());
  // ^ Make the rect full width again. Yes, this breaks horizontal alignment I know.

  painter->save();

  // Set up colors
  QPalette::ColorGroup cg = option.state & QStyle::State_Enabled ? QPalette::Normal
                                                                 : QPalette::Disabled;
  if (cg == QPalette::Normal && !(option.state & QStyle::State_Active)) {
      cg = QPalette::Inactive;
  }
  const bool isSelected = option.state & QStyle::State_Selected;
  QPalette::ColorRole colorRole = isSelected ? QPalette::HighlightedText : QPalette::Text;
  QColor defaultColor = QColor(option.palette.color(cg, colorRole));
  painter->setPen(defaultColor);

  const QWidget *widget = option.widget;
  const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, widget) + 1;
  textRect = textRect.adjusted(textMargin, 0, -textMargin, 0); // remove width padding

  QFont defaultFont = painter->font();

  const int len = text.length();
  int rangeStart = 0;
  int x = 0;
  for (int i = 0; i <= len; i++) {
    QChar c;
    if (i == len) {
      c = '\0';
    } else {
      c = text[i];
    }

    if (c == QChar('\0') || isFontSlot(c) || isColorSlot(c) || isCommand(c)) {
      if (rangeStart != i) {
        QString drawText = text.mid(rangeStart, i-rangeStart);
        painter->drawText(textRect.translated(x, 0), drawText);

        QFontMetrics metric(painter->font());
        x += metric.horizontalAdvance(drawText);
      }
      rangeStart = i + 1;

      if (isFontSlot(c)) {
        if (c.unicode() == FontSlotDefault) {
          painter->setFont(defaultFont);
        } else {
          painter->setFont(m_fontSlots.at(c.unicode() - FontSlotBase));
        }
      } else if (isColorSlot(c)) {
        if (c.unicode() == ColorSlotDefault) {
          painter->setPen(defaultColor);
        } else {
          if (isSelected) {
            painter->setPen(m_colorSelectedSlots.at(c.unicode() - ColorSlotBase));
          } else {
            painter->setPen(m_colorSlots.at(c.unicode() - ColorSlotBase));
          }
        }
      } else if (isCommand(c)) {
        QFont newFont = painter->font();
        switch (c.unicode()) {
          case 0xf8d6: // BoldOn
            newFont.setBold(true);
            break;
          case 0xf8d7: // BoldOff
            newFont.setBold(false);
            break;
          case 0xf8d8: // ItalicOn
            newFont.setItalic(true);
            break;
          case 0xf8d9: // ItalicOff
            newFont.setItalic(false);
            break;
          case 0xf8da: // StrikeOutOn
            newFont.setStrikeOut(true);
            break;
          case 0xf8db: // StrikeOutOff
            newFont.setStrikeOut(false);
            break;
          case 0xf8dc: // UnderlineOn
            newFont.setUnderline(true);
            break;
          case 0xf8dd: // UnderlineOff
            newFont.setUnderline(false);
            break;
          case 0xf8de: // OverlineOn
            newFont.setOverline(true);
            break;
          case 0xf8df: // OverlineOff
            newFont.setOverline(false);
            break;
          default:
            break;
        }
        painter->setFont(newFont);
      }
    }
  }

  painter->restore();
}
