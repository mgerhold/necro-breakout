#include <SDL.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
            "SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN
    );

    // Run the main loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Destroy the window and quit SDL2
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
