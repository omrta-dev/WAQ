#include <functional>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <SDL2/SDL.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#include <glad.h>

std::function< void() > loop;
void main_loop() { loop(); }

int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_OPENGL, &window,
                                &renderer);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    const GLubyte* glVersion = glGetString(GL_VERSION);
    std::cout << "GLVersion:" << glVersion << std::endl;
    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "an error occurred" << std::endl;
        exit(-1);
    }
    std::cout << "OpenGL:" << GLVersion.major << GLVersion.minor << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    loop = [&] {
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#endif
    // main loop here
    SDL_GL_DeleteContext(gl_context);
    return EXIT_SUCCESS;
}
