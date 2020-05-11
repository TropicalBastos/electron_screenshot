
/* cppsrc/main.cpp */
#include <napi.h>
#include <iostream>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ImageIO/ImageIO.h>
#include <Security/Security.h>
#include <AppKit/AppKit.h>

namespace electron_screenshot
{

static NSData *base64helper(NSData *input, SecTransformRef transform)
{
    NSData *output = nil;

    if (!transform)
        return nil;

    if (SecTransformSetAttribute(transform, kSecTransformInputAttributeName, input, NULL))
        output = (NSData *)SecTransformExecute(transform, NULL);

    CFRelease(transform);

    return [output autorelease];
}

Napi::String TakeScreenshot(const Napi::Env env) {
    CGImageRef screenShot = CGWindowListCreateImage( CGRectInfinite, kCGWindowListOptionOnScreenOnly, kCGNullWindowID, kCGWindowImageDefault);
    NSBitmapImageRep* bitmapImageRep = [[NSBitmapImageRep alloc]initWithCGImage:screenShot];
    NSImage *image = [[NSImage alloc] init];
    [image addRepresentation:bitmapImageRep];
    NSData *imgData = [image TIFFRepresentation];
    SecTransformRef transform = SecEncodeTransformCreate(kSecBase64Encoding, NULL);
    NSString* base64Result = [[NSString alloc] initWithData:base64helper(imgData, transform) encoding:NSASCIIStringEncoding];
    Napi::String ret = Napi::String::New(env, [base64Result UTF8String]);

    // CFRelease(transform);
    CFRelease(screenShot);
    [base64Result release];
    [imgData release];
    [image release];
    [bitmapImageRep release];

    return ret;
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