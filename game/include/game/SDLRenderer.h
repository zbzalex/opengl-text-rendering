#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include "Precompiled.h"
#include "Renderer.h"

class Game;

#include "Game.h"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer();

    virtual void Init() override;

    virtual void Render(Game *pGame) override;

protected:
    SDL_Window *m_Window;
};

#endif // SDL_RENDERER_H