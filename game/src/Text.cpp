#include <game/Precompiled.h>
#include <game/Text.h>
#include <iostream>
#include <string>

Text::Text() : m_Text()
{
}

Text::~Text()
{
}

Text &Text::Instance()
{
  static Text s_Text;

  return s_Text;
}

bool Text::Create(float width, float height)
{
  if (FT_Init_FreeType(&m_Ft))
  {
    return false;
  }

  m_ScreenWidth = width;
  m_ScreenHeight = height;

  return true;
}

bool Text::SetFace(const char *filename)
{
  if (FT_New_Face(m_Ft, filename, 0, &m_Face))
  {
    return false;
  }

  m_FontPath = filename;

  return true;
}

bool Text::SetFontSize(int size)
{
  if (FT_Set_Pixel_Sizes(m_Face, 0, size))
  {
    return false;
  }

  m_FontSize = size;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  return true;
}

void Text::SetColor(float r, float g, float b, float a)
{
  m_Color[0] = r;
  m_Color[1] = g;
  m_Color[2] = b;
  m_Color[3] = a;
}

void Text::SetText(const std::string text)
{
  m_Text = text;
}

void Text::SetPosition(float pos[2])
{
  // m_Pos = pos;
  memcpy(m_Pos, pos, sizeof(float) * 2);
}

void Text::SetScale(float scale[2])
{
  // m_Scale = scale;
  memcpy(m_Scale, scale, sizeof(float) * 2);
}

void Text::SetAlign(int align)
{
  m_Align = align;
}

BBOX_t Text::GetBBox()
{
  FT_GlyphSlot slot = m_Face->glyph;

  int x = 0;

  const char *text = m_Text.c_str();

  for (const char *p = text; *p; p++)
  {
    if (FT_Load_Char(m_Face, *p, FT_LOAD_RENDER))
      continue;

    x += (slot->advance.x >> 6);
  }

  BBOX_t bbox;
  bbox.Width = x;
  bbox.Height = m_FontSize;

  return bbox;
}

void Text::Render()
{
  BBOX_t bbox = GetBBox();
  FT_GlyphSlot slot = m_Face->glyph;

  glEnable(GL_TEXTURE_2D);

  const char *text = m_Text.c_str();

  float x = 0;

  switch (m_Align)
  {
  default:
  case ALIGN_LEFT:
  {
    x = m_Pos[0];
  }
  break;
  case ALIGN_CENTER:
  {
    x = m_Pos[0] > (bbox.Width / 2) ? m_Pos[0] - (bbox.Width / 2) : m_Pos[0];
  }
  break;
  case ALIGN_RIGHT:
  {
    x = m_Pos[0] + (bbox.Width / 2);
  }
  break;
  }

  float y = (-m_Pos[1] - (bbox.Height / 2)) + m_ScreenHeight;

  for (const char *p = text; *p; p++)
  {
    if (FT_Load_Char(m_Face, *p, FT_LOAD_RENDER))
      continue;

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_ALPHA,
        slot->bitmap.width,
        slot->bitmap.rows,
        0,
        GL_ALPHA,
        GL_UNSIGNED_BYTE,
        slot->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float x2 = x + slot->bitmap_left * m_Scale[0];
    float y2 = -y - slot->bitmap_top * m_Scale[1];

    float w = slot->bitmap.width * m_Scale[0];
    float h = slot->bitmap.rows * m_Scale[1];

    glColor4f(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(x2, -y2); // left top

    glTexCoord2f(0, 1);
    glVertex2f(x2, -y2 - h); // left bottom

    glTexCoord2f(1, 1);
    glVertex2f(x2 + w, -y2 - h); // right bottom

    glTexCoord2f(1, 0);
    glVertex2f(x2 + w, -y2); // right top

    glEnd();

    x += (slot->advance.x >> 6);
    y += (slot->advance.y >> 6);
  }

  glDisable(GL_TEXTURE_2D);
}
