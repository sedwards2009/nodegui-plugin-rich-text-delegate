#include <napi.h>

#include "RichTextDelegateWrap.h"


Napi::Object Main(Napi::Env env, Napi::Object exports) {
  RichTextDelegateWrap::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
