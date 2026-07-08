#include <vulkan/vulkan.h>
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>
/* We will use this renderer to draw into this window every frame. */

struct AppState {
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Computer Graphics Projekt 2026", "1.0", "https://github.com/LaevDaev/CGprojekt2026");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    AppState *state = new AppState();
    state->window = SDL_CreateWindow(
        "OpenGL Renderer",
        1280, 720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!state->window) {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
       SDL_GLContext glContext = SDL_GL_CreateContext(state->window);
    if (!glContext) throw std::runtime_error("SDL_GL_CreateContext failed");
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";

    // Enable vsync (optional but recommended)
    SDL_GL_SetSwapInterval(1);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    if (event->type == SDL_EVENT_WINDOW_RESIZED) {
            glViewport(0, 0, event->window.data1, event->window.data2);
        }
    return SDL_APP_CONTINUE;  /* carry on with the program! */

    
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // --- draw calls go here ---
    SDL_GL_SwapWindow(((AppState*)appstate)->window);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    AppState* state = static_cast<AppState*>(appstate);
    if (state) {
        if (state->glContext) SDL_GL_DestroyContext(state->glContext);
        if (state->window) SDL_DestroyWindow(state->window);
        delete state;
    }
}
