#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Utils/nutils.h"
#include "QtWidgets/QAbstractItemDelegate/qabstractitemdelegate_macro.h"
#include "RichTextDelegate.h"

class RichTextDelegateWrap : public Napi::ObjectWrap<RichTextDelegateWrap> {
  QABSTRACTITEMDELEGATE_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<RichTextDelegate> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  RichTextDelegateWrap(const Napi::CallbackInfo& info);
  ~RichTextDelegateWrap();
  QAbstractItemDelegate* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
};
