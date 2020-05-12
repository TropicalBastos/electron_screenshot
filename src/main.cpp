
/* src/main.cpp */
#include <napi.h>
#include <iostream>
#include "base64.h"
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  #include "Windows.h"
  #include "wingdi.h"
  #include "Gdiplus.h"
#else
  // TODO
#endif

namespace electron_screenshot
{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
bool BitmapToPng(HBITMAP hbitmap, BYTE* data, int* len)
{
    Gdiplus::Bitmap bmp(hbitmap, nullptr);

    //write to IStream
    IStream* istream = nullptr;
    CreateStreamOnHGlobal(NULL, TRUE, &istream);

    CLSID clsid_png;
    CLSIDFromString(L"{557cf406-1a04-11d3-9a73-0000f81ef32e}", &clsid_png);
    Gdiplus::Status status = bmp.Save(istream, &clsid_png);
    if(status != Gdiplus::Status::Ok)
        return false;

    //get memory handle associated with istream
    HGLOBAL hg = NULL;
    GetHGlobalFromStream(istream, &hg);

    //copy IStream to buffer
    int bufsize = GlobalSize(hg);
    data = (BYTE*) malloc(bufsize);

    //lock & unlock memory
    LPVOID pimage = GlobalLock(hg);
    memcpy(data, pimage, bufsize);
    GlobalUnlock(hg);

    istream->Release();

    *len = bufsize;
    return true;
}
#endif

Napi::String TakeScreenshot(const Napi::Env& env) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  // get the device context of the screen
  HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);     
  // and a device context to put it in
  HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

  int width = GetDeviceCaps(hScreenDC, HORZRES);
  int height = GetDeviceCaps(hScreenDC, VERTRES);

  // maybe worth checking these are positive values
  HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

  // get a new bitmap
  HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);

  BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
  hBitmap = (HBITMAP) SelectObject(hMemoryDC, hOldBitmap);

  BYTE* buffer;
  int len;
  BitmapToPng(hBitmap, buffer, &len);
  std::string result(reinterpret_cast<char*>(buffer), len);

  //cleanup
  DeleteDC(hMemoryDC);
  DeleteDC(hScreenDC);
  DeleteObject(hOldBitmap);
  DeleteObject(hBitmap);
  delete buffer;

  return Napi::String::New(env, macaron::Base64::Encode(result));

#else
  // TODO
#endif
}

Napi::String TakeScreenshotWrapped(const Napi::CallbackInfo& info) 
{
  Napi::Env env = info.Env();
  return TakeScreenshot(env);
}

}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("takeScreenshot", Napi::Function::New(env, electron_screenshot::TakeScreenshotWrapped));
  return exports;
}

NODE_API_MODULE(electron_screenshot, InitAll)