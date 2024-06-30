/* jeff_scalefactor.h -- https://github.com/takeiteasy/jeff
 
 NOTE: This library is to address a problem on Mac with viewport sizes
       when you're using the built-in scaling. Viewports would appear at
       1/4th of the window when specifying the viewport as the width and
       height of the window. The library is specific to Mac it can be included
       to any project because `sapp_framebuffer_scalefactor()` will just
       return 1 on other platforms.
 
 The MIT License (MIT)
 
 Copyright (c) 2024 George Watson
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge,
 publish, distribute, sublicense, and/or sell copies of the Software,
 and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef JEFF_SCALEFACTOR
#define JEFF_SCALEFACTOR
#if defined(__cplusplus)
extern "C" {
#endif

#ifndef SOKOL_APP_INCLUDED
#error "Please include sokol_app.h before the jeff_scalefactor.h implementation"
#endif

// returns sapp_width + scale
int sapp_framebuffer_width(void);
// returns sapp_height + scale
int sapp_framebuffer_height(void);
// returns sapp_widthf + scale
float sapp_framebuffer_widthf(void);
// returns sapp_heightf + scale
float sapp_framebuffer_heightf(void);
// returns monitor scale factor (Mac) or 1.f (other platforms)
float sapp_framebuffer_scalefactor(void);

#if defined(__cplusplus)
}
#endif
#endif // JEFF_SCALEFACTOR

#ifdef JEFF_IMPL
#if defined(__APPLE__)
#include <Cocoa/Cocoa.h>
#endif

int sapp_framebuffer_width(void) {
    return sapp_width() * (int)sapp_framebuffer_scalefactor();
}

int sapp_framebuffer_height(void) {
    return sapp_height() * (int)sapp_framebuffer_scalefactor();
}

float sapp_framebuffer_widthf(void) {
    return sapp_widthf() * sapp_framebuffer_scalefactor();
}

float sapp_framebuffer_heightf(void) {
    return sapp_heightf() * sapp_framebuffer_scalefactor();
}

float sapp_framebuffer_scalefactor(void) {
#if defined(__APPLE__)
    return [[NSScreen mainScreen] backingScaleFactor];
#else
    return 1.f; // I don't know if this is a thing for Windows/Linux so return 1
#endif
}
#endif // JEFF_IMPL
