#include <game/Game.h>
#include <game/SDLRenderer.h>

int main()
{
  Game *pGame = new Game();
  SDLRenderer *pRenderer = new SDLRenderer();

  pRenderer->Init();

  pGame->Init();
  
  pRenderer->Render(pGame);
}