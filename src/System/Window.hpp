#pragma once

namespace aik
{
    namespace system
    {
        class Window
        {
          public:
            bool createWindow();
            bool setupOpenGL();
            bool isOpen();
            void init();

          private:
            SDL_Window* mWindow;
            SDL_GLContext mGlContext;
            SDL_Renderer* mRenderer;
        }
    } // namespace system
} // namespace aik