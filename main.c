#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

const int Win_width = 1280;
const int Win_height = 800;

typedef struct {
    SDL_Rect rect;
    bool hovered;
    bool pressed;
} Button;

typedef struct {
    bool game;
    bool info;
} Status;

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

void startmain(SDL_Renderer** renderer, SDL_Event* e, SDL_Surface* img, Status* status, SDL_Texture** tp_maindisplay, SDL_Texture* texture_gamemain, bool* quit) {

    while(SDL_PollEvent(e)) {
        switch (e->type) {
        case SDL_QUIT:
            *quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse Button Pressed: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
            
            if(e->button.button == 1) {
                g_rule_button->pressed = check_in_xy(e->motion.x, e->motion.y, *g_rule_button);
                g_start_button->pressed = check_in_xy(e->motion.x, e->motion.y, *g_start_button);
                back_button->pressed = check_in_xy(e->motion.x, e->motion.y, *back_button);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            printf("Mouse Button Released: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
            break;
        case SDL_MOUSEMOTION:
            g_rule_button->hovered = check_in_xy(e->motion.x, e->motion.y, *g_rule_button);
            g_start_button->hovered = check_in_xy(e->motion.x, e->motion.y, *g_start_button);
            back_button->hovered = check_in_xy(e->motion.x, e->motion.y, *back_button);
            break;
        case SDL_KEYDOWN:
            if (e->key.keysym.sym == SDLK_ESCAPE) {
                *quit = true;
            }
        default:
            break;
        }
    }
    //
    SDL_RenderCopy(renderer, tp_maindisplay, NULL, &main);

        if (status.game == false &&status.info == false ) {
            if (g_start_button.pressed) {
                tp_maindisplay = texture_gamemain;
                status.game = true;
            }
            else {
                SDL_RenderCopy(renderer, tp_startbutton, NULL, &g_start_button.rect);
                SDL_RenderCopy(renderer, tp_infobutton, NULL, &g_rule_button.rect);
            }
        }
    //
    if (status.info == false) {
            if (g_rule_button.pressed) {
                status.info = true;
            }
        }
        else {
            if (back_button.pressed) {
                status.info = false;
            }
            else SDL_RenderCopy(renderer, tp_backbutton, NULL, &back_button.rect);

        }

    // Game logic based on events
    if (!status->game && !status->info) {
        if (g_start_button->pressed) {
            *tp_maindisplay = texture_gamemain;
            status->game = true;
        }
    }

    if (status->info) {
        if (back_button->pressed) {
            status->info = false;
        }
        else SDL_RenderCopy(renderer, tp_backbutton, NULL, &back_button.rect);
    }
    hovered(g_start_button, &tp_startbutton, texture_startbutton, texture_startbutton_hovered);
    hovered(g_rule_button,&tp_infobutton, texture_infobutton,texture_infobutton_hovered);
    hovered(back_button,&tp_backbutton, texture_backbutton,texture_backbutton_hovered);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Cant stop!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Win_width, Win_height,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_JPG);

    SDL_Surface* startMain = IMG_Load("img/startMain.jpg");
    SDL_Surface* gameMain = IMG_Load("img/test.jpg");

    SDL_Surface* startButton = IMG_Load("img/startbutton.jpg");
    SDL_Surface* startButton_hovered = IMG_Load("img/startbutton_hovered.jpg");
    SDL_Surface* infoButton = IMG_Load("img/infobutton.jpg");
    SDL_Surface* infoButton_hovered = IMG_Load("img/infobutton_hovered.jpg");
    SDL_Surface* backButton = IMG_Load("img/backbutton.jpg");
    SDL_Surface* backButton_hovered = IMG_Load("img/backbutton_hovered.jpg");

    SDL_Texture* texture_startmain = SDL_CreateTextureFromSurface(renderer,startMain);
    SDL_Texture* texture_gamemain = SDL_CreateTextureFromSurface(renderer, gameMain);

    SDL_Texture* texture_startbutton = SDL_CreateTextureFromSurface(renderer, startButton);
    SDL_Texture* texture_startbutton_hovered = SDL_CreateTextureFromSurface(renderer, startButton_hovered);
    SDL_Texture* texture_infobutton = SDL_CreateTextureFromSurface(renderer, infoButton);
    SDL_Texture* texture_infobutton_hovered = SDL_CreateTextureFromSurface(renderer, infoButton_hovered);
    SDL_Texture* texture_backbutton = SDL_CreateTextureFromSurface(renderer, backButton);
    SDL_Texture* texture_backbutton_hovered = SDL_CreateTextureFromSurface(renderer, backButton_hovered);

    SDL_Texture* tp_startbutton = texture_startbutton;
    SDL_Texture* tp_infobutton = texture_infobutton;
    SDL_Texture* tp_backbutton = texture_backbutton;
    SDL_Texture* tp_maindisplay = texture_startmain;

    SDL_Rect main = {0,0, startMain->w, startMain->h};

    SDL_Event e;

    Button* buttons = (Button*)malloc(3 * sizeof(Button));
    if (buttons == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    //g_start_button
    buttons[0] = {{490, 360, startButton->w, startButton->h}, false, false};    
    //g_rule_button
    buttons[1] = {{490,540,infoButton->w,infoButton->h}, false, false};
    //back_button
    buttons[2] = {{1000,650, backButton->w, backButton->h},false, false};

    Status status = {false, false};
    bool quit = false;
    
    while(!quit) {
       startmain();
        
        

        

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture_startmain);
    SDL_DestroyTexture(texture_gamemain);
    SDL_DestroyTexture(texture_startbutton);
    SDL_DestroyTexture(texture_startbutton_hovered);
    SDL_DestroyTexture(texture_infobutton);
    SDL_DestroyTexture(texture_infobutton_hovered);

    SDL_FreeSurface(startMain);
    SDL_FreeSurface(gameMain);
    SDL_FreeSurface(startButton);
    SDL_FreeSurface(startButton_hovered);
    SDL_FreeSurface(infoButton);
    SDL_FreeSurface(infoButton_hovered);

    IMG_Quit();
}