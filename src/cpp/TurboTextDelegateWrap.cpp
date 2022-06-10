#include "TurboTextDelegateWrap.h"

#include "Extras/Utils/nutils.h"
#include "QtGui/QColor/qcolor_wrap.h"
#include "QtGui/QFont/qfont_wrap.h"


Napi::FunctionReference TurboTextDelegateWrap::constructor;

Napi::Object TurboTextDelegateWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "TurboTextDelegate";
  Napi::Function func = DefineClass(
      env, CLASSNAME, {QABSTRACTITEMDELEGATE_WRAPPED_METHODS_EXPORT_DEFINE(TurboTextDelegateWrap)
      InstanceMethod("setColor", &TurboTextDelegateWrap::setColor),
      InstanceMethod("setFont", &TurboTextDelegateWrap::setFont)
  });
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(TurboTextDelegate, TurboTextDelegateWrap);
  return exports;
}

QAbstractItemDelegate* TurboTextDelegateWrap::getInternalInstance() { return this->instance; }

TurboTextDelegateWrap::~TurboTextDelegateWrap() { extrautils::safeDelete(this->instance); }

TurboTextDelegateWrap::TurboTextDelegateWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<TurboTextDelegateWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 0) {
    // --- Construct a new instance
    this->instance = new TurboTextDelegate();
  } else if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<TurboTextDelegate>>().Data();
    } else {
      // --- Construct a new instance and pass a parent
      Napi::Object parentObject = info[0].As<Napi::Object>();
      QObjectWrap* parentObjectWrap =
          Napi::ObjectWrap<QObjectWrap>::Unwrap(parentObject);
      this->instance = new TurboTextDelegate(parentObjectWrap->getInternalInstance());
    }
  } else {
    Napi::TypeError::New(
        env, "TurboTextDelegate: TurboTextDelegateWrap: Wrong number of arguments to constructor")
        .ThrowAsJavaScriptException();
  }
}

Napi::Value TurboTextDelegateWrap::setColor(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int slot = info[0].As<Napi::Number>().Int32Value();
  QColor* color =Napi::ObjectWrap<QColorWrap>::Unwrap(info[1].As<Napi::Object>())->getInternalInstance();
  this->instance->setColor(slot, *color);
  return env.Null();
}

Napi::Value TurboTextDelegateWrap::setFont(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int slot = info[0].As<Napi::Number>().Int32Value();
  QFont* font =Napi::ObjectWrap<QFontWrap>::Unwrap(info[1].As<Napi::Object>())->getInternalInstance();
  this->instance->setFont(slot, *font);
  return env.Null();
}
