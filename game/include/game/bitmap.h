#ifndef BITMAP_H
#define BITMAP_H

struct BITMAP
{
  unsigned int BitmapIndex;
  char Filename[256];
  float Width;
  float Height;
  int Components;
  unsigned char *Buffer;
};

typedef BITMAP BITMAP_t;

#endif // BITMAP_H