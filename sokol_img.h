/* sokol_input.h -- https://github.com/takeiteasy/sokol_helpers
 
 Simple wrapper for loading textures using `stb_image.h` and `qoi.h` into and
 sokol sg_image object
 
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

#ifndef SOKOL_HELPER_IMG
#define SOKOL_HELPER_IMG
#if defined(__cplusplus)
extern "C" {
#endif

#include "sokol_gfx.h"

sg_image sokol_empty_texture(int width, int height);
sg_image sokol_load_texture_path(const char *path);
sg_image sokol_load_texture_memory(unsigned char *data, int data_size);

#if defined(__cplusplus)
}
#endif
#endif // SOKOL_HELPER_INPUT

#ifdef SOKOL_HELPER_IMG
#ifdef _WIN32
#include <io.h>
#include <dirent.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "deps/stb_image.h"
#define QOI_IMPLEMENTATION
#include "deps/qoi.h"

sg_image sokol_empty_texture(int width, int height) {
    assert(width && height);
    sg_image_desc desc = {
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .usage = SG_USAGE_STREAM
    };
    return sg_make_image(&desc);
}

static int does_file_exist(const char *path) {
    return !access(path, F_OK);
}

static const char* file_extension(const char *path) {
    const char *dot = strrchr(path, '.');
    return !dot || dot == path ? NULL : dot + 1;
}

sg_image sokol_load_texture_path(const char *path) {
    assert(does_file_exist(path));
#define VALID_EXTS_SZ 11
    static const char *valid_extensions[VALID_EXTS_SZ] = {
        "jpg", "jpeg", "png", "bmp", "psd", "tga", "hdr", "pic", "ppm", "pgm", "qoi"
    };
    const char *ext = file_extension(path);
    unsigned long ext_length = strlen(ext);
    char *dup = strdup(ext);
    for (int i = 0; i < ext_length; i++)
        if (dup[i] >= 'A' && dup[i] <= 'Z')
            dup[i] += 32;
    int found = 0;
    for (int i = 0; i < VALID_EXTS_SZ; i++) {
        if (!strncmp(dup, valid_extensions[i], ext_length)) {
            found = 1;
            break;
        }
    }
    free(dup);
    if (!found)
        return (sg_image){.id=SG_INVALID_ID};
    
    size_t sz = -1;
    FILE *fh = fopen(path, "rb");
    assert(fh);
    fseek(fh, 0, SEEK_END);
    sz = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    
    unsigned char *data = malloc(sz * sizeof(unsigned char));
    fread(data, sz, 1, fh);
    fclose(fh);
    sg_image result = sokol_load_texture_memory(data, (int)sz);
    free(data);
    return result;
}

#define QOI_MAGIC (((unsigned int)'q') << 24 | ((unsigned int)'o') << 16 | ((unsigned int)'i') <<  8 | ((unsigned int)'f'))

static int check_if_qoi(unsigned char *data) {
    return (data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3]) == QOI_MAGIC;
}

#define RGBA(R, G, B, A) (((unsigned int)(A) << 24) | ((unsigned int)(R) << 16) | ((unsigned int)(G) << 8) | (B))

static int* load_texture_data(unsigned char *data, int data_size, int *w, int *h) {
    assert(data && data_size);
    int _w, _h, c;
    unsigned char *in = NULL;
    if (check_if_qoi(data)) {
        qoi_desc desc;
        in = qoi_decode(data, data_size, &desc, 4);
        _w = desc.width;
        _h = desc.height;
    } else
        in = stbi_load_from_memory(data, data_size, &_w, &_h, &c, 4);
    assert(in && _w && _h);
    
    int *buf = malloc(_w * _h * sizeof(int));
    for (int x = 0; x < _w; x++)
        for (int y = 0; y < _h; y++) {
            unsigned char *p = in + (x + _w * y) * 4;
            buf[y * _w + x] = RGBA(p[0], p[1], p[2], p[3]);
        }
    free(in);
    if (w)
        *w = _w;
    if (h)
        *h = _h;
    return buf;
}

sg_image sokol_load_texture_memory(unsigned char *data, int data_size) {
    assert(data && data_size);
    int w, h;
    int *tmp = load_texture_data(data, data_size, &w, &h);
    assert(tmp && w && h);
    sg_image texture = sokol_empty_texture(w, h);
    sg_image_data desc = {
        .subimage[0][0] = (sg_range) {
            .ptr = tmp,
            .size = w * h * sizeof(int)
        }
    };
    sg_update_image(texture, &desc);
    free(tmp);
    return texture;
}
#endif
