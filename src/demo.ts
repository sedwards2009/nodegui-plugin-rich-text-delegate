import { QWidget, QMainWindow, QListView, QModelIndex, ItemDataRole, QVariant, QAbstractTableModel, QBoxLayout,
  Direction,
  QColor,
  QLabel} from '@nodegui/nodegui';
import { RichTextDelegate, TurboTextDelegate } from './index';
import { ColorSlot, CommandChar } from './TurboTextDelegate';

function main(): void {
  const win = new QMainWindow();
  win.setWindowTitle('Rich Text Delegate Demo');

  const centralWidget = new QWidget();
  centralWidget.setObjectName('myroot');
  const rootLayout = new QBoxLayout(Direction.TopToBottom);
  centralWidget.setLayout(rootLayout);

  const label1 = new QLabel();
  label1.setText("QListView with TurboTextDelegate");
  rootLayout.addWidget(label1);

  const turboTextListView = new QListView();
  const turboTextDelegate = new TurboTextDelegate();
  turboTextDelegate.setColor(ColorSlot.n0, new QColor(255, 0,0 ));
  turboTextDelegate.setColor(ColorSlot.n1, new QColor(255, 255,0 ));

  turboTextListView.setItemDelegateForColumn(0, turboTextDelegate);
  turboTextListView.setModel(new ContentModel([
    "Apple",
    `${ColorSlot.n1}Banana${ColorSlot.default} salad`,
    `Cran${ColorSlot.n0}berry`,
    `${CommandChar.BoldOn}Bold${CommandChar.BoldOff}nana`,
    `Rasp${ColorSlot.n0}berry`,
    "A fruit salid containing raisins, apple, watermelon, and pineapple",
    "Watermelon",
  ]));
  rootLayout.addWidget(turboTextListView);

  const label2 = new QLabel();
  label2.setText("QListView with RichTextDelegate");
  rootLayout.addWidget(label2);

  const richTextListView = new QListView();
  const richTextDelegate = new RichTextDelegate();
  richTextListView.setItemDelegateForColumn(0, richTextDelegate);
  richTextListView.setModel(new ContentModel([
    "Apple",
    "<b>Bold</b>nana",
    "A <i>fruit</i> salid containing raisins, apple, watermelon, and pineapple",
    "Watermelon",
  ]));
  rootLayout.addWidget(richTextListView);

  win.setCentralWidget(centralWidget);

  win.show();

  (global as any).win = win;
}

class ContentModel extends QAbstractTableModel {
  #entries: string[] = [];

  constructor(entries: string[]) {
    super();
    this.#entries = entries;
  }

  rowCount(parent = new QModelIndex()): number {
    return this.#entries.length;
  }

  columnCount(parent = new QModelIndex()): number {
    return 1;
  }

  data(index: QModelIndex, role = ItemDataRole.DisplayRole): QVariant {
    if (role === ItemDataRole.DisplayRole) {
      return new QVariant(this.#entries[index.row()]);
    }
    return new QVariant();
  }
}

main();
