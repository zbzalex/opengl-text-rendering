#ifndef RENDERER_H
#define RENDERER_H

class Game;

#include "Game.h"

class Renderer
{
public:
    Renderer();
    virtual void Init();
    
    virtual void Render( Game *pGame );
};

#endif