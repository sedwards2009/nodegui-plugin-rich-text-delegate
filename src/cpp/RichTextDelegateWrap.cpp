#include "RichTextDelegateWrap.h"

#include "Extras/Utils/nutils.h"

Napi::FunctionReference RichTextDelegateWrap::constructor;

Napi::Object RichTextDelegateWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "RichTextDelegate";
  Napi::Function func = DefineClass(
      env, CLASSNAME, {QABSTRACTITEMDELEGATE_WRAPPED_METHODS_EXPORT_DEFINE(RichTextDelegateWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(RichTextDelegate, RichTextDelegateWrap);
  return exports;
}

QAbstractItemDelegate* RichTextDelegateWrap::getInternalInstance() { return this->instance; }

RichTextDelegateWrap::~RichTextDelegateWrap() { extrautils::safeDelete(this->instance); }

RichTextDelegateWrap::RichTextDelegateWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<RichTextDelegateWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 0) {
    // --- Construct a new instance
    this->instance = new RichTextDelegate();
  } else if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<RichTextDelegate>>().Data();
    } else {
      // --- Construct a new instance and pass a parent
      Napi::Object parentObject = info[0].As<Napi::Object>();
      QObjectWrap* parentObjectWrap =
          Napi::ObjectWrap<QObjectWrap>::Unwrap(parentObject);
      this->instance = new RichTextDelegate(parentObjectWrap->getInternalInstance());
    }
  } else {
    Napi::TypeError::New(
        env, "RichTextDelegate: RichTextDelegateWrap: Wrong number of arguments to constructor")
        .ThrowAsJavaScriptException();
  }
}
