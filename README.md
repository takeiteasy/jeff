# sokol_helpers

> [!WARNING]
> Work in progres

A small collection of utility libraries for [sokol](https://github.com/floooh/sokol/)

All libraries are single-header, so `SOKOL_HELPER_IMPL` must be defined (***once***) before including any headers.

## Libraries

| File                     | Description                                       |
| ------------------------ | --------------------------------------------------|
| **sokol_generic.h**†     | _Generic wrappers for sokol types                 |
| **sokol_img.h**\*        | Load textures from `stb_image.h` + `qoi.h`        |
| **sokol_input.h**        | Basic input manager (keyboard, mouse, etc)        |
| **sokol_scalefactor.h**§ | Function to return the monitors scale factor      |

* **†** Relies on modern compiler extensions or C11+ features
* **\*** Relies on third-party library (located in `deps/`)
* **§** Platform specific (safe to include on unspecified platforms)

## LICENSE
```
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
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
