#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    //SDL_Init(SDL_INIT_VIDEO);  // SDL 초기화
    int imgFlags = IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    //IMG_Init(IMG_INIT_JPG);  // SDL_image 초기화

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("Image Loading Example",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Surface* surface = IMG_Load("/Users/th/Desktop/오픈소스(c)프로젝트/1.jpg");
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", "/Users/th/Desktop/오픈소스(c)프로젝트/start.jpg", IMG_GetError());
    }  // 이미지 불러오기
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);  // 서페이스를 텍스처로 변환

    SDL_FreeSurface(surface);  // 더 이상 필요 없는 서페이스 해제

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);  // 텍스처 렌더링
    SDL_RenderPresent(renderer);

    SDL_Delay(10000);  // 5초간 유지

    SDL_DestroyTexture(texture);  // 텍스처 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();  // SDL_image 정리
    SDL_Quit();  // SDL 정리

    return 0;
}
