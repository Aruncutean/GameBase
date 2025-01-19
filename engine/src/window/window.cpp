//
// Created by arunc on 29/09/2024.
//

#include "window/window.h"

#include "setting/Setting.h"

Window::Window(Game *game) : game(game) {
}

Window::~Window() {
}

void Window::init() {
    initSDL();
    createContext();
    game->init();
}

void Window::start() {
    game->start();
    loop();
}

void Window::stop() {
    game->stop();
    running = false;
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::loop() {
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    int windowWidth, windowHeight;
    SDL_GL_GetDrawableSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    // Schimbă culoarea de fundal
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    bool pPressed = false;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_P]) {
            if (!pPressed) {
                pPressed = true;
                Setting::getInstance().enableLineRender = !Setting::getInstance().enableLineRender;
            }
        } else {
            pPressed = false;
        }
        game->keyPress(state);

        int mouseX, mouseY;
        const Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        game->mouseHandle(mouseX, mouseY, &mouseState);

        glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game->update();

        SDL_GL_SwapWindow(window);
    }
}

void Window::createContext() {
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_Log("Could not create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Initializează GLAD
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }
}

void Window::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

#if defined(__ANDROID__) || defined(__APPLE__)

    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);  // OpenGL ES 2.0
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    window = SDL_CreateWindow("My Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        0, 0,
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
#elif defined(_WIN32)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); // OpenGL 3.3 pentru Windows
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    window = SDL_CreateWindow("My Game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800, 512,
                              SDL_WINDOW_OPENGL);
#endif
    if (!window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
    }
}
