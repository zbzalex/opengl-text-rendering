#include <game/SDLRenderer.h>
#include <game/Game.h>
#include <game/Input.h>
#include <iostream>
#include <sstream>

SDLRenderer::SDLRenderer() : Renderer()
{
}

void SDLRenderer::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    m_Window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!m_Window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(m_Window);
    SDL_GL_MakeCurrent(m_Window, glContext);
    SDL_GL_SetSwapInterval(0); // Disable vsync

    // SDL_ShowCursor(SDL_DISABLE);
    // SDL_CaptureMouse(SDL_TRUE);

    // SDL_SetWindowBordered(app.window, SDL_FALSE);
}

void SDLRenderer::Render(Game *pGame)
{
    float ticks = SDL_GetTicks();

    SDL_Event e;
    while (pGame->IsRunning())
    {

        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
            {
                pGame->Stop();
            }
            break;
            case SDL_MOUSEMOTION:
            {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;

                POINT p;
                p.x = mouseX < 0 ? 0 : (mouseX > 640 ? 640 : mouseX);
                p.y = mouseY < 0 ? 0 : (mouseY > 480 ? 480 : mouseY);

                std::stringstream ss;
                ss << "X: " << p.x << " Y: " << p.y;
                SDL_SetWindowTitle(m_Window, ss.str().c_str());
                
                Input::Instance().SetCursorPos(p);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    SDL_Log("mouse button down");
                }
                else
                {
                    SDL_Log("mouse button up");
                }
            }
            break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                SDL_KeyboardEvent *key = &e.key;
                Input::Instance().SetKeyState(e.key.keysym.sym, key->type == SDL_KEYUP ? 0 : 1);
            }
            break;
            case SDL_MOUSEWHEEL:
            {
                if (e.wheel.y > 0) // scroll up
                {
                    SDL_Log("Scroll up");
                }
                else if (e.wheel.y < 0) // scroll down
                {
                    SDL_Log("Scroll down");
                }
            }
            break;
            }
        }

        float deltaTime = (SDL_GetTicks() - ticks) / 1000.0f;
        if (deltaTime > 0.05f)
        {
            deltaTime = 0.05f;
        }

        pGame->Update(deltaTime);
        
        SDL_GL_SwapWindow(m_Window);
    }

    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}
