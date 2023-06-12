#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"

typedef struct
{
  float fX;
  float fY;
} VertexCoord;

typedef struct
{
  float fU;
  float fV;
} TexCoord;

class Sprite
{
public:
  enum
  {
    LT = 0,
    LB = 1,
    RB = 2,
    RT = 3
  };

  Sprite(
      float fOrgWidth,
      float fOrgHeight,
      Texture *pTexture,
      float fScaleX,
      float fScaleY);

  void Render();
  void SetPosition(
      float x,
      float y);
  void SetSize(float width, float height);

protected:
  float m_fOrgWidth;
  float m_fOrgHeight;
  Texture *m_pTexture;
  float m_fScaleX;
  float m_fScaleY;

  float m_fHeight;

  VertexCoord m_VertCoord[4];
  TexCoord m_TexCoord[4];
};

#endif // SPRITE_H