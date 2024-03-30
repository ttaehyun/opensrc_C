#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Mouse Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                printf("Mouse Moved to (%d, %d) with Motion X: %d, Motion Y: %d\n", event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                break;
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 배경을 검은색으로 설정
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
