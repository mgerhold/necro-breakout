#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800 // Bildschirm-Breite
#define SCREEN_HEIGHT 600 // Bildschirm-Höhe

#define PADDLE_WIDTH 200 // Schläger-Breite
#define PADDLE_HEIGHT 30 // Schläger-Höhe
#define PADDLE_MARGIN 20 // Schläger Abstand zum Rand

#define BALL_WIDTH 20 // Spielball-Breite
#define BALL_HEIGHT 20 // Spielball-Höhe

int main(int argc, char** argv) {
    // Initialisiere SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Erstelle ein Fenster
    SDL_Window* window = SDL_CreateWindow(
            "SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    // Erstelle den Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Zeitpunkt des letzten Updates
    Uint32 last_update_ticks = SDL_GetTicks();

    // Rechteck definieren
    SDL_Rect paddle; // Variablendefinition ohne Initialisierung
    paddle.x = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
    paddle.y = (SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN);
    paddle.w = PADDLE_WIDTH;
    paddle.h = PADDLE_HEIGHT;

    SDL_Rect ball;
    ball.x = (SCREEN_WIDTH - BALL_WIDTH) / 2;
    ball.y = (SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN - BALL_HEIGHT);
    ball.w = BALL_WIDTH;
    ball.h = BALL_HEIGHT;
    int speed_x = -2; // Variablendefinition mit Initialisierung
    int speed_y = -2; // Ball-Geschwindigkeit

    // Spiel-Schleife
    bool quit = false;
    while (!quit) {

        // Ereignisse abfragen
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                
                if (event.key.keysym.sym == SDLK_a) {
                    printf("Die Taste 'A' wurde gedrückt. \n");
                    paddle.x = paddle.x - 20;
                    if (paddle.x < 0) {
                        paddle.x = 0;
                    }
                }
                
                if (event.key.keysym.sym == SDLK_d) {
                    printf("Die Taste 'D' wurde gedrückt. \n");
                    paddle.x = paddle.x + 20;
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
            ball.x = ball.x + speed_x;
            ball.y = ball.y + speed_y;
            if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_WIDTH) { 
                speed_x *= -1;
            }
 
            if (ball.y <= 0 || ball.y >= SCREEN_HEIGHT - PADDLE_HEIGHT - PADDLE_MARGIN - BALL_HEIGHT) { //apprall von der oberfläche
                speed_y *= -1;
            }

            // Ich merke mir, dass ich den Ball JETZT GERADE bewegt habe.
            last_update_ticks = update_ticks; // Zuweisung in eine bestehende Variable hinein.
        }


        // Rendern
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 1. Farbe setzen
        SDL_RenderClear(renderer);                      // 2. Hintergrund mit der Farbe "clearen"

        // Schläger zeichnen
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);       // Schläger-Farbe (R,G,B,A)
        SDL_RenderFillRect(renderer, &paddle);

        // Ball zeichnen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // Ball-Farbe (R,G,B,A)
        SDL_RenderFillRect(renderer, &ball);

        // 3. Inhalt anzeigen (Backbuffer und Frontbuffer tauschen)
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer); // Löschen des Renderers
    SDL_DestroyWindow(window); // Löschen des Fensters
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