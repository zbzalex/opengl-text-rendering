#ifndef PRECOMPILED_H
#define PRECOMPILED_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
// #include <GL/glu.h>
#include <GL/glext.h>
#include <SDL2/SDL.h>
#include <jpeglib.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifdef __linux__
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#else
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#endif

#define USE_SHADERS

#endif // PRECOMPILED_H