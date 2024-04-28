#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

const int Win_width = 1280;
const int Win_height = 800;

//구조체
typedef struct {
    SDL_Rect rect;
    bool hovered;
    bool pressed;
} Button;

typedef struct {
    bool game;
    bool info;
} Status;
//함수 선언
bool check_in_xy(int x, int y, Button button);
void hovered(Button button, SDL_Texture** tp_texture, SDL_Texture* texture, SDL_Texture* texture_hovered);
void initial_Button(Button *button, int x, int y, int width, int height, bool hovered, bool pressed);
void free_buttons(Button* buttons);
void startmain(SDL_Renderer** renderer, SDL_Event* e,SDL_Rect* mainImg, SDL_Texture** tp_maindisplay, int* status, bool* quit);
//함수 구현
bool check_in_xy(int x, int y, Button button) {
    if (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
        y >= button.rect.y && y <= button.rect.y + button.rect.h) 
        {
            return true;
    }
    return false;
}

void hovered(Button button, SDL_Texture** tp_texture, SDL_Texture* texture, SDL_Texture* texture_hovered) {
    if (button.hovered) {
            *tp_texture = texture_hovered;
        }
    else *tp_texture = texture;
}

void initial_Button(Button *button, int x, int y, int width, int height, bool hovered, bool pressed) {
    if (button!= NULL) {
        button->rect.x = x;
        button->rect.y = y;
        button->rect.w = width;
        button->rect.h = height;
        button->hovered = hovered;
        button->pressed = pressed;
    }
}
//메모리 해제
void free_buttons(Button* buttons) {
    free(buttons);
}

//*메인 함수*//
void startmain(SDL_Renderer** renderer, SDL_Event* e, SDL_Rect* mainImg, SDL_Texture** tp_maindisplay,int* status, bool* quit) 
{   
    

    SDL_Surface* startButton = IMG_Load("img/startbutton.jpg");
    SDL_Surface* startButton_hovered = IMG_Load("img/startbutton_hovered.jpg");
    SDL_Surface* infoButton = IMG_Load("img/infobutton.jpg");
    SDL_Surface* infoButton_hovered = IMG_Load("img/infobutton_hovered.jpg");
    SDL_Surface* backButton = IMG_Load("img/backbutton.jpg");
    SDL_Surface* backButton_hovered = IMG_Load("img/backbutton_hovered.jpg");

    

    SDL_Texture* texture_startbutton = SDL_CreateTextureFromSurface(*renderer, startButton);
    SDL_Texture* texture_startbutton_hovered = SDL_CreateTextureFromSurface(*renderer, startButton_hovered);
    SDL_Texture* texture_infobutton = SDL_CreateTextureFromSurface(*renderer, infoButton);
    SDL_Texture* texture_infobutton_hovered = SDL_CreateTextureFromSurface(*renderer, infoButton_hovered);
    SDL_Texture* texture_backbutton = SDL_CreateTextureFromSurface(*renderer, backButton);
    SDL_Texture* texture_backbutton_hovered = SDL_CreateTextureFromSurface(*renderer, backButton_hovered);

    SDL_Texture* tp_startbutton = texture_startbutton;
    SDL_Texture* tp_infobutton = texture_infobutton;
    SDL_Texture* tp_backbutton = texture_backbutton;

    Status game_info = {false, false};

    Button* buttons = (Button*)malloc(3 * sizeof(Button));
    if (buttons == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    //g_start_button
    initial_Button(&buttons[0], 490, 360, startButton->w, startButton->h, false, false); 
    //g_rule_button
    initial_Button(&buttons[1], 490, 540, infoButton->w, infoButton->h, false, false);
    //back_button
    initial_Button(&buttons[2], 1000,650, backButton->w, backButton->h, false, false);

    bool start_quit = false;

    while(!start_quit) {
        SDL_RenderCopy(*renderer, *tp_maindisplay, NULL, mainImg);
        while(SDL_PollEvent(e)) {
            switch (e->type) {
            case SDL_QUIT:
                *quit = true;
                start_quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                
                if(e->button.button == 1) {
                    buttons[0].pressed = check_in_xy(e->motion.x, e->motion.y, buttons[0]);
                    buttons[1].pressed = check_in_xy(e->motion.x, e->motion.y, buttons[1]);
                    buttons[2].pressed = check_in_xy(e->motion.x, e->motion.y, buttons[2]);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                break;
            case SDL_MOUSEMOTION:
                buttons[0].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[0]);
                buttons[1].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[1]);
                buttons[2].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[2]);
                break;
            case SDL_KEYDOWN:
                if (e->key.keysym.sym == SDLK_ESCAPE) {
                    *quit = true;
                    start_quit = true;
                }
            default:
                break;
            }
        }
        //
        
        // Game logic based on events
        if (!game_info.game && !game_info.info) {
            if (buttons[0].pressed) {
                *status = 1;
                start_quit = true;
            }
            else {
                SDL_RenderCopy(*renderer, tp_startbutton, NULL, &buttons[0].rect);
                SDL_RenderCopy(*renderer, tp_infobutton, NULL, &buttons[1].rect);
            }
        }
        if (game_info.info == false) {
            if (buttons[1].pressed) {
                game_info.info = true;
            }
            else {
                if (buttons[2].pressed) {
                    game_info.info = false;
                }
            }
        }
        if (game_info.info) {
            if (buttons[2].pressed) {
                game_info.info = false;
            }
            else SDL_RenderCopy(*renderer, tp_backbutton, NULL, &buttons[2].rect);
        }
        hovered(buttons[0], &tp_startbutton, texture_startbutton, texture_startbutton_hovered);
        hovered(buttons[1],&tp_infobutton, texture_infobutton,texture_infobutton_hovered);
        hovered(buttons[2],&tp_backbutton, texture_backbutton,texture_backbutton_hovered);
        SDL_RenderPresent(*renderer);
    }
    

    SDL_DestroyTexture(texture_startbutton);
    SDL_DestroyTexture(texture_startbutton_hovered);
    SDL_DestroyTexture(texture_infobutton);
    SDL_DestroyTexture(texture_infobutton_hovered);

    

    SDL_FreeSurface(startButton);
    SDL_FreeSurface(startButton_hovered);
    SDL_FreeSurface(infoButton);
    SDL_FreeSurface(infoButton_hovered);

    free_buttons(buttons);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Cant stop!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Win_width, Win_height,0);
    if (!window) {
        printf("Window could not be created: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        return 1;
    }
    IMG_Init(IMG_INIT_JPG);

    SDL_Surface* startMain = IMG_Load("img/startMain.jpg");
    SDL_Surface* gameMain = IMG_Load("img/test.jpg");

    SDL_Texture* texture_startmain = SDL_CreateTextureFromSurface(renderer,startMain);
    SDL_Texture* texture_gamemain = SDL_CreateTextureFromSurface(renderer, gameMain);
    
    SDL_Texture* tp_maindisplay = texture_startmain;

    SDL_Rect mainImg = {0,0,startMain->w, startMain->h};

    SDL_Event e;

    int status = 0;
    bool quit = false;

    while (!quit) {
        switch (status)
        {
        case 0:
            startmain(&renderer,&e, &mainImg, &tp_maindisplay,&status, &quit );
            break;
        case 1:
            while(true) {
                SDL_RenderCopy(renderer, tp_maindisplay, NULL, &mainImg);
                tp_maindisplay = texture_gamemain;
                SDL_RenderPresent(renderer);
            }
            break;
        default:
            break;
        }
    }

    SDL_DestroyTexture(texture_startmain);
    SDL_DestroyTexture(texture_gamemain);

    SDL_FreeSurface(startMain);
    SDL_FreeSurface(gameMain);
    
    IMG_Quit();
}