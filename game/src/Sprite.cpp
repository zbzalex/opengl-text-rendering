#include <game/Precompiled.h>
#include <game/Sprite.h>
#include <game/Texture.h>
#include <iostream>

Sprite::Sprite(
    float fOrgWidth,
    float fOrgHeight,
    Texture *pTexture,
    float fScaleX,
    float fScaleY) : m_fOrgWidth((float)fOrgWidth),
                     m_fOrgHeight((float)fOrgHeight),
                     m_pTexture(pTexture),
                     m_fScaleX(fScaleX),
                     m_fScaleY(fScaleY)
{

  m_fHeight = (float)SCREEN_HEIGHT / fScaleY;

  // left top
  m_VertCoord[LT].fX = 0.0f;
  m_VertCoord[LT].fY = m_fHeight;

  // left bottom
  m_VertCoord[LB].fX = 0.0f;
  m_VertCoord[LB].fY = m_fHeight - m_fOrgHeight;

  // right bottom
  m_VertCoord[RB].fX = m_fOrgWidth;
  m_VertCoord[RB].fY = m_fHeight - m_fOrgHeight;

  // right top
  m_VertCoord[RT].fX = m_fOrgWidth;
  m_VertCoord[RT].fY = m_fHeight;

  m_TexCoord[LT].fU = 0.5f / m_pTexture->bitmap->Width;
  m_TexCoord[LT].fV = 0.5f / m_pTexture->bitmap->Height;
  m_TexCoord[LB].fU = 0.5f / m_pTexture->bitmap->Width;
  m_TexCoord[LB].fV = (m_fOrgHeight - 0.5f) / m_pTexture->bitmap->Height;
  m_TexCoord[RB].fU = (m_fOrgWidth - 0.5f) / m_pTexture->bitmap->Width;
  m_TexCoord[RB].fV = (m_fOrgHeight - 0.5f) / m_pTexture->bitmap->Height;
  m_TexCoord[RT].fU = (m_fOrgWidth - 0.5f) / m_pTexture->bitmap->Width;
  m_TexCoord[RT].fV = 0.5f / m_pTexture->bitmap->Height;
}

void Sprite::Render()
{
  glEnable(GL_TEXTURE_2D);

  m_pTexture->SetActive();

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glBegin(GL_TRIANGLE_FAN);

  glColor4f(1.f, 1.f, 1.f, 1.f);

  for (int i = 0; i < 4; i++)
  {

    glTexCoord2f(
        m_TexCoord[i].fU,
        m_TexCoord[i].fV);

    glVertex2f(
        m_VertCoord[i].fX * m_fScaleX,
        m_VertCoord[i].fY * m_fScaleY);
  }

  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void Sprite::SetPosition(float x, float y)
{
  float fWidth  = m_VertCoord[RT].fX - m_VertCoord[LT].fX; // right top - left top    = w
  float fHeight = m_VertCoord[LT].fY - m_VertCoord[LB].fY; // left top  - left bottom = h 

  m_VertCoord[LT].fX = m_VertCoord[LB].fX = (float)x;
  m_VertCoord[RT].fX = m_VertCoord[RB].fX = m_VertCoord[0].fX + fWidth;

  m_VertCoord[LT].fY = m_VertCoord[RT].fY = m_fHeight - (float)y;
  m_VertCoord[LB].fY = m_VertCoord[RB].fY = m_VertCoord[0].fY - fHeight;
}

void Sprite::SetSize(float width, float height)
{
  m_VertCoord[RT].fX = m_VertCoord[RB].fX = m_VertCoord[LT].fX + (float)width;
  m_VertCoord[LB].fY = m_VertCoord[RB].fY = m_VertCoord[LT].fY - (float)height;
}
