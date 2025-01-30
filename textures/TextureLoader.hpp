#pragma once

#include <string>
#include <iostream>

struct TextureData {
  unsigned char* image = nullptr;
  int width;
  int height;
  int n_channels;
};

class TextureLoader {
public:
  static TextureData Load(const char* texture_path);
};
