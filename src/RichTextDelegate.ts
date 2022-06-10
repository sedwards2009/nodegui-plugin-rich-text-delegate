import { checkIfNativeElement, NativeElement, QAbstractItemDelegate, QObject, QObjectSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';

export class RichTextDelegate extends QAbstractItemDelegate {
    constructor(arg?: QObject<QObjectSignals> | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.RichTextDelegate(parent.native);
        } else {
            native = new addon.RichTextDelegate();
        }
        super(native);
    }
}

wrapperCache.registerWrapper('RichTextDelegateWrap', RichTextDelegate);
