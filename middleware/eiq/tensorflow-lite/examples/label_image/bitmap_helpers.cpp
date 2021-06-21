/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.
   Copyright 2018-2019 NXP. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* File modified by NXP. Changes are described in file
   /middleware/eiq/tensorflow-lite/readme.txt in section "Release notes" */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

#if !defined(__ICCARM__) && !defined(__ARMCC_VERSION)
#include <unistd.h>  // NOLINT(build/include_order)
#endif

#include "bitmap_helpers.h"

#define LOG(x) std::cerr

namespace tflite {
namespace label_image {

uint8_t* DecodeBmp(const uint8_t* input, int row_size, uint8_t* const output,
                   int width, int height, int channels, bool top_down) {
  for (int i = 0; i < height; i++) {
    int src_pos;
    int dst_pos;

    for (int j = 0; j < width; j++) {
      if (!top_down) {
        src_pos = ((height - 1 - i) * row_size) + j * channels;
      } else {
        src_pos = i * row_size + j * channels;
      }

      dst_pos = (i * width + j) * channels;

      switch (channels) {
        case 1:
          output[dst_pos] = input[src_pos];
          break;
        case 3:
          // BGR -> RGB
          output[dst_pos] = input[src_pos + 2];
          output[dst_pos + 1] = input[src_pos + 1];
          output[dst_pos + 2] = input[src_pos];
          break;
        case 4:
          // BGRA -> RGBA
          output[dst_pos] = input[src_pos + 2];
          output[dst_pos + 1] = input[src_pos + 1];
          output[dst_pos + 2] = input[src_pos];
          output[dst_pos + 3] = input[src_pos + 3];
          break;
        default:
          LOG(FATAL) << "Unexpected number of channels: " << channels;
          break;
      }
    }
  }
  return output;
}

uint8_t* ReadBmp(const char* input_bmp_data, size_t input_bmp_len, int* width, int* height,
                 int* channels, Settings* s) {
  const uint8_t* img_bytes = (const uint8_t*)input_bmp_data;
  const int32_t header_size =
      *(reinterpret_cast<const int32_t*>(img_bytes + 10));
  *width = *(reinterpret_cast<const int32_t*>(img_bytes + 18));
  *height = *(reinterpret_cast<const int32_t*>(img_bytes + 22));
  const int32_t bpp = *(reinterpret_cast<const int32_t*>(img_bytes + 28));
  *channels = bpp / 8;

  if (s->verbose)
    LOG(INFO) << "width, height, channels: " << *width << ", " << *height
              << ", " << *channels << "\n";

  // there may be padding bytes when the width is not a multiple of 4 bytes
  // 8 * channels == bits per pixel
  const int row_size = (8 * *channels * *width + 31) / 32 * 4;

  // if height is negative, data layout is top down
  // otherwise, it's bottom up
  bool top_down = (*height < 0);

  // Decode image, allocating tensor once the image size is known
  uint8_t* output = new uint8_t[abs(*height) * *width * *channels];
  const uint8_t* bmp_pixels = &img_bytes[header_size];
  return DecodeBmp(bmp_pixels, row_size, output, *width, abs(*height),
                   *channels, top_down);
}

}  // namespace label_image
}  // namespace tflite
