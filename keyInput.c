#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("SDL2 Keyboard Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                printf("Key pressed: ");
                char str[20];
                SDL_strlcpy(str, SDL_GetKeyName(event.key.keysym.sym), sizeof(str));
                printf("%s", str);
                printf("\n");
            case SDL_KEYUP:
                printf("Key released: ");
                char str2[20];
                SDL_strlcpy(str2, SDL_GetKeyName(event.key.keysym.sym), sizeof(str2));
                printf("%s", str2);
                printf("\n");
            default:
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 255,255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}