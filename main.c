#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 200
#define PADDLE_HEIGHT 30
#define PADDLE_MARGIN 20
#define PLAY_BALL_WIDTH 20
#define PLAY_BALL_HEIGHT 20

int main(int argc, char** argv) {
    // Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
            "SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    // create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // aktuelle Ballgeschwindigkeit
    int speed_x = -1; // Variablendefinition mit Initialisierung
    int speed_y = -1;

    // Zeitpunkt des letzten Updates
    Uint32 last_update_ticks = SDL_GetTicks();

    // Rechteck definieren
    SDL_Rect paddle; // Variablendefinition ohne Initialisierung
    paddle.x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    paddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN;
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    SDL_Rect play_ball;
    play_ball.x = (SCREEN_WIDTH - PLAY_BALL_WIDTH) / 2;
    play_ball.y = SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN - PLAY_BALL_HEIGHT;
    play_ball.w = PLAY_BALL_WIDTH;
    play_ball.h = PLAY_BALL_HEIGHT;

    // Run the main loop
    bool quit = false;
    while (!quit) {

        // event handling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) {
                    printf("Die Taste 'A' wurde gedrückt. \n");
                    paddle.x = paddle.x - 10;
                    if (paddle.x < 0) {
                        paddle.x = 0;
                    }
                }
                if (event.key.keysym.sym == SDLK_d) {
                    printf("Die Taste 'D' wurde gedrückt. \n");
                    paddle.x = paddle.x + 10;
                    if (paddle.x > SCREEN_WIDTH - PADDLE_WIDTH) {
                        paddle.x = SCREEN_WIDTH - PADDLE_WIDTH;
                    }
                }
            }
        }

        // update
        // Ist seit dem letzten Update "genug" Zeit vergangen?
        //  1. Wie ist die aktuelle Zeit?
        //  2. Wie viel Zeit ist seit dem letzten Mal vergangen?
        //  3. Ist die vergangene Zeit "groß genug"?
        //  4. Falls ja: Ball bewegen
        //  5. aktuelle Uhrzeit als letzte Zeit speichern
        Uint32 update_ticks = SDL_GetTicks();                    // die aktuelle "Uhrzeit" (in ms)
        Uint32 elapsed_ticks = update_ticks - last_update_ticks; // Wie viel Zeit (in ms) ist vergangen, seitdem ich
                                                                 // zum letzten Mal den Ball bewegt habe?
        if (elapsed_ticks > 10) {
            // Die letzte Ballbewegung ist mehr als 10 ms her.
            play_ball.x = play_ball.x - 1;
            play_ball.y = play_ball.y - 1;

            // Ich merke mir, dass ich den Ball JETZT GERADE bewegt habe.
            last_update_ticks = update_ticks; // Zuweisung in eine bestehende Variable hinein.
        }


        // rendering

        // 1. Farbe setzen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 2. Hintergrund mit der Farbe "clearen"
        SDL_RenderClear(renderer);

        // Rechteck zeichnen
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &paddle);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &play_ball);

        // 3. alles anzeigen (Backbuffer und Frontbuffer tauschen)
        SDL_RenderPresent(renderer);
    }

    // destroy the renderer
    SDL_DestroyRenderer(renderer);
    // Destroy the window and quit SDL2
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/*

Uhrzeit         Aktion
0               last_update_ticks = 0
1               Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
2               Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
3               Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
4               Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
5               Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
6               ...
7
8
9
10
11              Wie spät ist es? Sind schon mehr als 10 ms vergangen? Ja! => Ball bewegen und last_update_ticks = 11
12              Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
13              Wie spät ist es? Sind schon mehr als 10 ms vergangen? Nein
14              ...
15
16
17
18
19
20
21
22              Wie spät ist es? Sind schon mehr als 10 ms vergangen? Ja! => Ball bewegen und last_update_ticks = 22

*/