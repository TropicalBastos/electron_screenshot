
/* cppsrc/main.cpp */
#include <napi.h>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  // TODO
#elif __APPLE__
  #include <CoreGraphics/CoreGraphics.h>
  #include <CoreFoundation/CoreFoundation.h>
  #include <ImageIO/ImageIO.h>
#else
  // TODO
#endif

namespace electron_screenshot
{

void TakeScreenshot() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  // TODO
#elif __APPLE__
  CGImageRef screenShot = CGWindowListCreateImage( CGRectInfinite, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
  CFStringRef file = CFSTR("/Users/ianbastos/Desktop/SC.jpg");
  CFStringRef type = CFSTR("public.jpeg");
  CFURLRef urlRef = CFURLCreateWithFileSystemPath( kCFAllocatorDefault, file, kCFURLPOSIXPathStyle, false );
  CGImageDestinationRef image_destination = CGImageDestinationCreateWithURL( urlRef, type, 1, NULL );
  CGImageDestinationAddImage( image_destination, screenShot, NULL );
  CGImageDestinationFinalize( image_destination );
#else
  // TODO
#endif
}

void TakeScreenshotWrapped(const Napi::CallbackInfo& info) 
{
  TakeScreenshot();
}

}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("takeScreenshot", Napi::Function::New(env, electron_screenshot::TakeScreenshotWrapped));
  return exports;
}

NODE_API_MODULE(electron_screenshot, InitAll)