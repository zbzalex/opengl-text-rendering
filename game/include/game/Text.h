#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

typedef struct
{
  float Width;
  float Height;
} BBOX_t;

class Text
{
public:
  enum
  {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
  };

  Text();
  ~Text();
  static Text &Instance();
  bool Create(float screenWidth, float screenHeight);

  bool SetFace(const char *filename);
  bool SetFontSize(int size);
  void SetColor(float r, float g, float b, float a);

  void SetText(const std::string text);

  void SetPosition(float pos[2]);

  void SetScale(float scale[2]);

  void SetAlign(int Align);

  BBOX_t GetBBox();

  void Render();

protected:
  const char *m_FontPath;
  FT_Library m_Ft;
  FT_Face m_Face;
  int m_FontSize = 24;
  float m_Color[4];
  float m_ScreenWidth;
  float m_ScreenHeight;
  float m_Pos[2];
  int m_Align;
  float m_Scale[2];
  std::string m_Text;
};

#endif // TEXT_H