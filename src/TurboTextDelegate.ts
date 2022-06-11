import { checkIfNativeElement, NativeElement, QAbstractItemDelegate, QColor, QFont, QObject, QObjectSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';

export const ColorSlotBase = 0xf8e0;
export const ColorSlotLast = 0xf8ee;
export const ColorSlotDefault = 0xf8ef;
export const FontSlotBase = 0xf8f0;
export const FontSlotLast = 0xf8fe;
export const FontSlotDefault = 0xf8ff;

// export enum ColorSlot {
//     n0 = ColorSlotBase,
//     n1 = ColorSlotBase + 1,
//     n2 = ColorSlotBase + 2,
//     n3 = ColorSlotBase + 3,
//     n4 = ColorSlotBase + 4,
//     n5 = ColorSlotBase + 5,
//     n6 = ColorSlotBase + 6,
//     n7 = ColorSlotBase + 7,
//     n8 = ColorSlotBase + 8,
//     n9 = ColorSlotBase + 9,
//     n10 = ColorSlotBase + 10,
//     n11 = ColorSlotBase + 11,
//     n12 = ColorSlotBase + 12,
//     n13 = ColorSlotBase + 13,
//     n14 = ColorSlotBase + 14,
//     default = ColorSlotDefault
// }

export enum ColorSlot {
    n0 = "\uf8e0",
    n1 = "\uf8e1",
    n2 = "\uf8e2",
    n3 = "\uf8e3",
    n4 = "\uf8e4",
    n5 = "\uf8e5",
    n6 = "\uf8e6",
    n7 = "\uf8e7",
    n8 = "\uf8e8",
    n9 = "\uf8e9",
    n10 = "\uf8ea",
    n11 = "\uf8eb",
    n12 = "\uf8ec",
    n13 = "\uf8ed",
    n14 = "\uf8ee",
    default = "\uf8ef",
}

// export enum FontSlot {
//     n0 = FontSlotBase,
//     n1 = FontSlotBase + 1,
//     n2 = FontSlotBase + 2,
//     n3 = FontSlotBase + 3,
//     n4 = FontSlotBase + 4,
//     n5 = FontSlotBase + 5,
//     n6 = FontSlotBase + 6,
//     n7 = FontSlotBase + 7,
//     n8 = FontSlotBase + 8,
//     n9 = FontSlotBase + 9,
//     n10 = FontSlotBase + 10,
//     n11 = FontSlotBase + 11,
//     n12 = FontSlotBase + 12,
//     n13 = FontSlotBase + 13,
//     n14 = FontSlotBase + 14,
//     default = FontSlotDefault
// }

export enum FontSlot {
    n0 = "\uf8f0",
    n1 = "\uf8f1",
    n2 = "\uf8f2",
    n3 = "\uf8f3",
    n4 = "\uf8f4",
    n5 = "\uf8f5",
    n6 = "\uf8f6",
    n7 = "\uf8f7",
    n8 = "\uf8f8",
    n9 = "\uf8f9",
    n10 = "\uf8fa",
    n11 = "\uf8fb",
    n12 = "\uf8fc",
    n13 = "\uf8fd",
    n14 = "\uf8fe",
    default = "\uf8ff",
}

export const CommandChar = {
    BoldOn: String.fromCodePoint(0xf8d6),
    BoldOff: String.fromCodePoint(0xf8d7),
    ItalicOn: String.fromCodePoint(0xf8d8),
    ItalicOff: String.fromCodePoint(0xf8d9),
    StrikeOutOn: String.fromCodePoint(0xf8da),
    StrikeOutOff: String.fromCodePoint(0xf8db),
    UnderlineOn: String.fromCodePoint(0xf8dc),
    UnderlineOff: String.fromCodePoint(0xf8dd),
    OverlineOn: String.fromCodePoint(0xf8de),
    OverlineOff: String.fromCodePoint(0xf8df),
}

export class TurboTextDelegate extends QAbstractItemDelegate {
    constructor(arg?: QObject<QObjectSignals> | NativeElement) {
        let native: NativeElement;
        if (checkIfNativeElement(arg)) {
            native = arg as NativeElement;
        } else if (arg != null) {
            const parent = arg as QObject;
            native = new addon.TurboTextDelegate(parent.native);
        } else {
            native = new addon.TurboTextDelegate();
        }
        super(native);
    }

    setColor(slot: ColorSlot, color: QColor, colorSelected?: QColor): void {
        this.native.setColor(slot.codePointAt(0), color.native,
            colorSelected === undefined ? color.native : colorSelected.native);
    }

    setFont(slot: FontSlot, font: QFont): void {
        this.native.setFont(slot.codePointAt(0), font.native);
    }
}

wrapperCache.registerWrapper('TurboTextDelegateWrap', TurboTextDelegate);
