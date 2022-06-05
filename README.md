# nodegui-plugin-rich-text-delegate

Render rich text with Qt's Model/View framework from [NodeGui](https://github.com/nodegui/nodegui).

The delegate will render strings as HTML as supported by `QTextDocument`.

TypeScript example:

```typescript
  //...

  const listView = new QListView();
  const delegate = new RichTextDelegate();
  listView.setItemDelegateForColumn(0, delegate);

  // All strings in column 0 will be treated as HTML.
```

Install via NPM:

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
