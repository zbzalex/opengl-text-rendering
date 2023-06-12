#include <game/Precompiled.h>
#include <game/Texture.h>
#include <game/bitmap.h>
#include <iostream>

//------------------------------------------------------------------------------
// Texture constructor
//------------------------------------------------------------------------------
Texture::Texture(unsigned int id) : m_ID(id)
{
}

//------------------------------------------------------------------------------
// Load texture from bitmap
//------------------------------------------------------------------------------
bool Texture::LoadFromBitmap(BITMAP_t *bitmap_)
{
  glGenTextures(1, &m_ID);
  glBindTexture(GL_TEXTURE_2D, m_ID);
  glTexImage2D(
      GL_TEXTURE_2D,
      0,
      bitmap_->Components == 4 ? GL_RGBA : GL_RGB,
      bitmap_->Width,
      bitmap_->Height,
      0,
      bitmap_->Components == 4 ? GL_RGBA : GL_RGB,
      GL_UNSIGNED_BYTE,
      bitmap_->Buffer);

  bitmap = bitmap_;

  return true;
}

//------------------------------------------------------------------------------
// Unload texture
//------------------------------------------------------------------------------
void Texture::Unload()
{
  glDeleteTextures(1, &m_ID);
}

//------------------------------------------------------------------------------
// Bind texture for use
//------------------------------------------------------------------------------
void Texture::SetActive()
{
  glBindTexture(GL_TEXTURE_2D, m_ID);
}
