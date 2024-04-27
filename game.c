#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

const int Win_width = 1280;
const int Win_height = 800;

typedef struct {
    SDL_Rect rect;
    bool hovered;
} Button;

bool check_hover(int x, int y, Button button) {
    if (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
        y >= button.rect.y && y <= button.rect.y + button.rect.h) {
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("SDL_Image Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Win_width, Win_height,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_JPG );

    //IMG Load
    SDL_Surface* startMain = IMG_Load("startMain.jpg");
    SDL_Surface* mapBackgroud = IMG_Load("test.jpg");
    //SDL_Surface* dice_img = IMG_Load("Dice1.jpg");
    //IMG -> texture
    SDL_Texture* texture_Main = SDL_CreateTextureFromSurface(renderer, startMain);
    SDL_Texture* texture_map = SDL_CreateTextureFromSurface(renderer, mapBackgroud);
    //SDL_Texture* texture_dice = SDL_CreateTextureFromSurface(renderer, dice_img);
    //temp texture
    SDL_Texture* temp_text = texture_Main;
    //printf("%d", imageSurface->w);
    //IMG 크기만큼의 Rect 생성
    SDL_Rect main = {0,0,startMain->w, startMain->h};
    SDL_Rect map = {0,0, mapBackgroud->w, mapBackgroud->h};
    //button 생성
    Button button = {{600, 400, 200, 50}, false};

    //SDL_Rect dice = {1250,700, dice_img->w, dice_img->h };
    bool quit = false;
    SDL_Event event;
    
    while (!quit) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                if (temp_text != texture_map) {
                    temp_text = texture_map;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                button.hovered = check_hover(event.motion.x, event.motion.y, button);
                printf("Mouse Moved to (%d, %d) with Motion X: %d, Motion Y: %d\n", event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            default:
                break;
            }
        }
        SDL_RenderCopy(renderer, temp_text, NULL, &map);

        SDL_SetRenderDrawColor(renderer, 0,0,255,255);
        SDL_RenderFillRect(renderer, &button.rect);

        if (button.hovered) {
            SDL_SetRenderDrawColor(renderer, 255, 0,0,255);
            SDL_RenderFillRect(renderer, &button.rect);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(temp_text);
    //SDL_DestroyTexture(texture_dice);
    SDL_FreeSurface(mapBackgroud);
    //SDL_FreeSurface(dice_img);

    IMG_Quit();

}