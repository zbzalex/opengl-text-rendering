#ifndef GAME_H
#define GAME_H

class Game
{
public:
  Game();

  void Init() noexcept;
  
  void Update(float dt) noexcept;

  inline bool IsRunning() const { return m_Running; }

  inline void Stop() { m_Running = false; }

protected:
  bool m_Running = true;
};

#endif // GAME_H