#pragma once

#include <QStyledItemDelegate>


const int BoldOn = 0xf8d6;
const int BoldOff = 0xf8d7;
const int ItalicOn = 0xf8d8;
const int ItalicOff = 0xf8d9;
const int StrikeOutOn = 0xf8da;
const int StrikeOutOff = 0xf8db;
const int UnderlineOn = 0xf8dc;
const int UnderlineOff = 0xf8dd;
const int OverlineOn = 0xf8de;
const int OverlineOff = 0xf8df;

const int FirstCommand = BoldOn;
const int LastCommand = OverlineOff;

// These ranges correspond to the end of Unicode 16bit private use area.
// This should keep them out of collision range with things like Font Awesome etc.
const int ColorSlotBase = 0xf8e0;
const int ColorSlotLast = 0xf8ee;
const int ColorSlotDefault = 0xf8ef;

const int FontSlotBase = 0xf8f0;
const int FontSlotLast = 0xf8fe;
const int FontSlotDefault = 0xf8ff;


class TurboTextDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit TurboTextDelegate(QObject *parent = nullptr);
  ~TurboTextDelegate();

  void setFont(int slot, QFont &font);
  void setColor(int slot, QColor &color);

 protected:
  void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
 private:
  QVector<QColor> m_colorSlots;
  QVector<QFont> m_fontSlots;
  void viewItemDrawText(QStyle* style, QPainter *p, const QStyleOptionViewItem *option, const QRect &rect) const;
};
