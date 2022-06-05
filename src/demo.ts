import { QWidget, QMainWindow, QListView, QModelIndex, ItemDataRole, QVariant, QAbstractTableModel, QBoxLayout,
  Direction } from '@nodegui/nodegui';
import { RichTextDelegate } from './index';

function main(): void {
  const win = new QMainWindow();
  win.setWindowTitle('Rich Text Delegate Demo');

  const centralWidget = new QWidget();
  centralWidget.setObjectName('myroot');
  const rootLayout = new QBoxLayout(Direction.TopToBottom);
  centralWidget.setLayout(rootLayout);

  const listView = new QListView();
  const delegate = new RichTextDelegate();
  listView.setItemDelegateForColumn(0, delegate);
  listView.setModel(new ContentModel([
    "Apple",
    "<i>Banana</i>",
    "Cranberry",
    "<b>Date</b>",
    "Raspberry",
    "A fruit salid containing raisens, apple, watermelon, and pineapple",
    "Watermelon"
  ]));
  rootLayout.addWidget(listView);

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
