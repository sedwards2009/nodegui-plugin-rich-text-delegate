# nodegui-plugin-rich-text-delegate

Render rich text with Qt's Model/View framework from [NodeGui](https://github.com/nodegui/nodegui).

This package contains 2 `QAbstractItemDelegate` subclasses for rendering rich text. One is based on `QTextDocument` and can render a subset of HTML, the other takes a string with embedded "command" characters which can modify the presentation of the characters. This later version is designed to be fast.

## RichTextDelegate

TypeScript example of the HTML based delegate:

```typescript
  //...

  const listView = new QListView();
  const delegate = new RichTextDelegate();
  listView.setItemDelegateForColumn(0, delegate);

  // All strings in column 0 will be treated as HTML.
```

It has no configuration. It just treats the strings to format as HTML.


## TurboTextDelegate

This delegate is designed for run-time speed. It has a fairly low-level API. You may want to build some comfort layers on top of it first. It takes a string which contains embedded special unicode characters from the private use area which are interpretted as formatting commands. Like terminal escape codes, colors, fonts, and font styles can be turned on and off.

**Basic Commands**

These enum values are all strings which can be embedded in input strings.

* `CommandChar.BoldOn` - Turn bold on
* `CommandChar.BoldOff` - Turn bold off
* `CommandChar.ItalicOn` - Turn italic on
* `CommandChar.ItalicOff` - Turn italic off
* `CommandChar.StrikeOutOn` - Turn strike out on
* `CommandChar.StrikeOutOff` - Turn strike out off
* `CommandChar.UnderlineOn` - Turn underline on
* `CommandChar.UnderlineOff` - Turn underline off
* `CommandChar.OverlineOn` - Turn overline on
* `CommandChar.OverlineOff` - Turn overline off

**Color Commands**

`QColor` instances can be loaded into 1 of 15 slots. Color commands can be used inside the string to load a color from a slot. The commands and slots are available in the `ColorSlot` enum and are `n0`-`n14` and `default`. The `default` command resets the color back to the default.

```typescript
const delegate = new TurboTextDelete();
const myColor = new QColor(255, 0, 0);
delegate.setColor(ColorSlot.n0, myColor);

// ...

const myString = `A ${ColorSlot.n0}colorful${ColorSlot.default} word`;
```

**Font Commands**

`QFont` instances can be loaded into 1 of 15 slots. Font commands can be used inside the string to load a font from a slot. The commands and slots are
available in the `FontSlot` enum and are named `n0`-`n14` and `default`. The `default` command resets the font back to the default.

```typescript
const delegate = new TurboTextDelete();
delegate.setFont(FontSlot.n0, myFont);
```

# Install via NPM:

```
npm install nodegui-plugin-rich-text-delegate
```

For the API see [src/index.ts](src/index.ts)

For a complete demo see [src/demo.ts](src/demo.ts)

# Maintainer

Simon Edwards <simon@simonzone.com>

# License

MIT

# Release Process (for maintainers)

* Make sure the version in `package.json` is correct.
* Tag the version with git (format: v1.2.3).
* Push the tag to origin.
* Wait for GitHub Action to build and release to NPM.
