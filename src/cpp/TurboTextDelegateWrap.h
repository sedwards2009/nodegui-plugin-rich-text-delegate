#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Utils/nutils.h"
#include "QtWidgets/QAbstractItemDelegate/qabstractitemdelegate_macro.h"
#include "TurboTextDelegate.h"

class TurboTextDelegateWrap : public Napi::ObjectWrap<TurboTextDelegateWrap> {
  QABSTRACTITEMDELEGATE_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<TurboTextDelegate> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  TurboTextDelegateWrap(const Napi::CallbackInfo& info);
  ~TurboTextDelegateWrap();
  QAbstractItemDelegate* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  Napi::Value setColor(const Napi::CallbackInfo& info);
  Napi::Value setFont(const Napi::CallbackInfo& info);
};
