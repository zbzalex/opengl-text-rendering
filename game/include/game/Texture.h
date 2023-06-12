#ifndef TEXTURE_H
#define TEXTURE_H

#include <game/Precompiled.h>
#include <string>
#include "bitmap.h"

class Texture
{
public:
  Texture(unsigned int id);
  bool LoadFromBitmap(BITMAP_t *bitmap_);
  void Unload();
  void SetActive();

  BITMAP_t *bitmap;

protected:
  GLuint m_ID;
};

#endif // TEXTURE_H