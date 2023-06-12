#ifndef INPUT_H
#define INPUT_H

#include <map>

#include "point.h"

class Input
{
protected:
  POINT m_CursorPos;
  std::map<int, int> m_KeyState;

public:
  Input();
  ~Input();
  static Input &Instance();
  bool Create(float screenWidth, float screenHeight);
  void Update();
  void SetCursorPos(POINT cursorPos);
  POINT GetCursorPos();
  void SetKeyState(int sym, int state);
  int GetKeyState(int sym);
};

#endif // INPUT_H