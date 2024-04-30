#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

const int Win_width = 1280;
const int Win_height = 800;

//구조체
typedef struct {
    SDL_Rect rect;
    bool hovered;
    bool pressed;
} Button;

typedef struct {
    SDL_Rect rect;
} Img;

typedef struct {
    bool game;
    bool info;
} Status;


//함수 선언
bool check_in_xy(int x, int y, Button button);
void hovered(Button button, SDL_Texture** tp_texture, SDL_Texture** texture, SDL_Texture** texture_hovered);
void initial_Button(Button *button, int x, int y, int width, int height, bool hovered, bool pressed);
void free_buttons(Button* buttons);
void initial_img(Img *img, int x, int y, int width, int height);
void free_Imgs(Img* imgs);

void startmain(SDL_Renderer** renderer, SDL_Event* e, int* status, bool* quit);
void select_player_num(SDL_Renderer** renderer, SDL_Event* e, bool* quit, int* total_player);
void gamemain(SDL_Renderer** renderer, SDL_Event* e, int* status,int* player_num, bool* quit);
//함수 구현
bool check_in_xy(int x, int y, Button button) {
    if (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
        y >= button.rect.y && y <= button.rect.y + button.rect.h) 
        {
            return true;
    }
    return false;
}


void hovered(Button button, SDL_Texture** tp_texture, SDL_Texture** texture, SDL_Texture** texture_hovered) {
    if (button.hovered) {
            *tp_texture = *texture_hovered;
        }
    else *tp_texture = *texture;
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
void initial_img(Img * img, int x, int y, int width, int height) {
    if(img!= NULL) {
        img->rect.x = x;
        img->rect.y = y;
        img->rect.w = width;
        img->rect.h = height;
    }
}

void free_Imgs(Img* imgs) {
    free(imgs);
}

//*시작초기 함수*/
void startmain(SDL_Renderer** renderer, SDL_Event* e,int* status, bool* quit) 
{   
    SDL_Surface* startButton = IMG_Load("img/button/startbutton.jpg");
    SDL_Surface* startButton_hovered = IMG_Load("img/button/startbutton_hovered.jpg");
    SDL_Surface* infoButton = IMG_Load("img/button/infobutton.jpg");
    SDL_Surface* infoButton_hovered = IMG_Load("img/button/infobutton_hovered.jpg");
    SDL_Surface* backButton = IMG_Load("img/button/backbutton.jpg");
    SDL_Surface* backButton_hovered = IMG_Load("img/button/backbutton_hovered.jpg");

    SDL_Surface* infomain_button = IMG_Load("img/button/infomainbutton.jpg");
    SDL_Surface* infomain_button_hovered = IMG_Load("img/button/infomainbutton_hovered.jpg");
    SDL_Surface* win_button = IMG_Load("img/button/winbutton.jpg");
    SDL_Surface* win_button_hovered = IMG_Load("img/button/winbutton_hovered.jpg");
    SDL_Surface* gametuto_button = IMG_Load("img/button/gametuto.jpg");
    SDL_Surface* gametuto_button_hovered = IMG_Load("img/button/gametuto_hovered.jpg");
    
    SDL_Surface* number_1_button = IMG_Load("img/num/1.jpg");
    SDL_Surface* number_1_button_hovered = IMG_Load("img/num/1_hovered.jpg");
    SDL_Surface* number_2_button = IMG_Load("img/num/2.jpg");
    SDL_Surface* number_2_button_hovered = IMG_Load("img/num/2_hovered.jpg");
    SDL_Surface* number_3_button = IMG_Load("img/num/3.jpg");
    SDL_Surface* number_3_button_hovered = IMG_Load("img/num/3_hovered.jpg");

    SDL_Surface* infomain_img = IMG_Load("img/tutorial/infomain.jpg");
    SDL_Surface* win_img = IMG_Load("img/tutorial/win.jpg");
    SDL_Surface* rule_img1 = IMG_Load("img/tutorial/rule1.jpg");
    SDL_Surface* rule_img2 = IMG_Load("img/tutorial/rule2.jpg");
    SDL_Surface* rule_img3 = IMG_Load("img/tutorial/rule3.jpg");

    SDL_Texture* texture_startbutton = SDL_CreateTextureFromSurface(*renderer, startButton);
    SDL_Texture* texture_startbutton_hovered = SDL_CreateTextureFromSurface(*renderer, startButton_hovered);
    SDL_Texture* texture_infobutton = SDL_CreateTextureFromSurface(*renderer, infoButton);
    SDL_Texture* texture_infobutton_hovered = SDL_CreateTextureFromSurface(*renderer, infoButton_hovered);
    SDL_Texture* texture_backbutton = SDL_CreateTextureFromSurface(*renderer, backButton);
    SDL_Texture* texture_backbutton_hovered = SDL_CreateTextureFromSurface(*renderer, backButton_hovered);

    SDL_Texture* texture_infomain_button = SDL_CreateTextureFromSurface(*renderer, infomain_button);
    SDL_Texture* texture_infomain_button_hovered = SDL_CreateTextureFromSurface(*renderer, infomain_button_hovered);
    SDL_Texture* texture_win_button = SDL_CreateTextureFromSurface(*renderer, win_button);
    SDL_Texture* texture_win_button_hovered = SDL_CreateTextureFromSurface(*renderer, win_button_hovered);
    SDL_Texture* texture_gametuto_button = SDL_CreateTextureFromSurface(*renderer, gametuto_button);
    SDL_Texture* texture_gametuto_button_hovered = SDL_CreateTextureFromSurface(*renderer, gametuto_button_hovered);

    SDL_Texture* texture_num_1_button = SDL_CreateTextureFromSurface(*renderer, number_1_button);
    SDL_Texture* texture_num_1_button_hovered = SDL_CreateTextureFromSurface(*renderer, number_1_button_hovered);
    SDL_Texture* texture_num_2_button = SDL_CreateTextureFromSurface(*renderer, number_2_button);
    SDL_Texture* texture_num_2_button_hovered = SDL_CreateTextureFromSurface(*renderer, number_2_button_hovered);
    SDL_Texture* texture_num_3_button = SDL_CreateTextureFromSurface(*renderer, number_3_button);
    SDL_Texture* texture_num_3_button_hovered = SDL_CreateTextureFromSurface(*renderer, number_3_button_hovered);

    SDL_Texture* texture_infomain_Img = SDL_CreateTextureFromSurface(*renderer, infomain_img);
    SDL_Texture* texture_win_Img = SDL_CreateTextureFromSurface(*renderer, win_img);
    SDL_Texture* texture_rule_Img1 = SDL_CreateTextureFromSurface(*renderer, rule_img1);
    SDL_Texture* texture_rule_Img2 = SDL_CreateTextureFromSurface(*renderer, rule_img2);
    SDL_Texture* texture_rule_Img3 = SDL_CreateTextureFromSurface(*renderer, rule_img3);

    SDL_Texture* tp_startbutton = texture_startbutton;
    SDL_Texture* tp_infobutton = texture_infobutton;
    SDL_Texture* tp_backbutton = texture_backbutton;
    SDL_Texture* tp_infomain_button = texture_infomain_button;
    SDL_Texture* tp_win_button = texture_win_button;
    SDL_Texture* tp_gametuto_button = texture_gametuto_button;
    SDL_Texture* tp_num_1_button = texture_num_1_button;
    SDL_Texture* tp_num_2_button = texture_num_2_button;
    SDL_Texture* tp_num_3_button = texture_num_3_button;

    SDL_Texture* tp_rule_img = texture_infomain_Img;
    
    SDL_Surface* startMain = IMG_Load("img/startMain.jpg");
    

    SDL_Texture* texture_startmain = SDL_CreateTextureFromSurface(*renderer,startMain);
    
    SDL_Texture* tp_maindisplay = texture_startmain;

    SDL_Rect mainImg = {0,0,startMain->w, startMain->h};

    Status game_info = {false, false};
    //총 버튼 개수
    int count_button = 9;

    Button* buttons = (Button*)malloc(count_button * sizeof(Button));
    if (buttons == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }

    //g_start_button
    initial_Button(&buttons[0], 490, 360, startButton->w, startButton->h, false, false); 
    //g_rule_button
    initial_Button(&buttons[1], 490, 540, infoButton->w, infoButton->h, false, false);
    //back_button
    initial_Button(&buttons[2], 1100,680, backButton->w, backButton->h, false, false);
    //infomain_button
    initial_Button(&buttons[3], 50, 300, infomain_button->w, infomain_button->h, false, false);
    //win_button
    initial_Button(&buttons[4], 50,350, win_button->w, win_button->h, false, false);
    //gametuto_button
    initial_Button(&buttons[5], 50, 400, gametuto_button->w, gametuto_button->h, false,false);
    //num1 button
    initial_Button(&buttons[6], 150, 680, number_1_button->w, number_1_button->h, false,false);
    //num2 button
    initial_Button(&buttons[7], 201, 680, number_2_button->w, number_2_button->h, false,false);
    //num3 button
    initial_Button(&buttons[8], 251, 680, number_3_button->w, number_3_button->h, false,false);
    Img* imgs = (Img*)malloc(5 * sizeof(Img));
    if (imgs == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    initial_img(&imgs[0], 151,300, infomain_img->w-200, infomain_img->h);
    initial_img(&imgs[1], 151,300, win_img->w, win_img->h);
    initial_img(&imgs[2], 151,300, rule_img1->w, rule_img1->h);
    initial_img(&imgs[3], 151,300, rule_img2->w, rule_img2->h);
    initial_img(&imgs[4], 151,300, rule_img3->w, rule_img3->h);

    bool start_quit = false;
    bool info_rule = false;
    while(!start_quit) {
        SDL_RenderCopy(*renderer, tp_maindisplay, NULL, &mainImg);
        while(SDL_PollEvent(e)) {
            switch (e->type) {
            case SDL_QUIT:
                *quit = true;
                start_quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                
                if(e->button.button == 1) {
                    for (int i=0; i< count_button; i++) {
                        buttons[i].pressed = check_in_xy(e->motion.x, e->motion.y , buttons[i]);
                    }
                    
                }
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                break;
            case SDL_MOUSEMOTION:
                for (int i = 0; i< count_button; i++) {
                    buttons[i].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[i]);
                }
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
        if (!game_info.game && !game_info.info) {
            if (buttons[0].pressed) {
                *status = 1;
                start_quit = true;
            }
            else {
                SDL_RenderCopy(*renderer, tp_startbutton, NULL, &buttons[0].rect);
                SDL_RenderCopy(*renderer, tp_infobutton, NULL, &buttons[1].rect);
                hovered(buttons[0], &tp_startbutton, &texture_startbutton, &texture_startbutton_hovered);
                hovered(buttons[1],&tp_infobutton, &texture_infobutton, &texture_infobutton_hovered);
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
        else {
            if (buttons[2].pressed) {
                game_info.info = false;
                
            }
            else {
                if (buttons[3].pressed) {
                    tp_rule_img = texture_infomain_Img;
                    info_rule = false;
                }
                else if (buttons[4].pressed) {
                    tp_rule_img = texture_win_Img;
                    info_rule = false;
                }
                else if (buttons[5].pressed) {
                    tp_rule_img = texture_rule_Img1;
                    info_rule = true;
                }
                if (info_rule) {
                    if (buttons[6].pressed) {
                        tp_rule_img = texture_rule_Img1;
                    }
                    else if( buttons[7].pressed) {
                        tp_rule_img = texture_rule_Img2;
                    }
                    else if( buttons[8].pressed) {
                        tp_rule_img = texture_rule_Img3;
                    }
                    SDL_RenderCopy(*renderer, tp_num_1_button, NULL, &buttons[6].rect);
                    SDL_RenderCopy(*renderer, tp_num_2_button, NULL, &buttons[7].rect);
                    SDL_RenderCopy(*renderer, tp_num_3_button, NULL, &buttons[8].rect);
                    hovered(buttons[6], &tp_num_1_button, &texture_num_1_button, &texture_num_1_button_hovered);
                    hovered(buttons[7], &tp_num_2_button, &texture_num_2_button, &texture_num_2_button_hovered);
                    hovered(buttons[8], &tp_num_3_button, &texture_num_3_button, &texture_num_3_button_hovered);
                }
                SDL_RenderCopy(*renderer, tp_rule_img, NULL,&imgs[0].rect );

                SDL_RenderCopy(*renderer, tp_backbutton, NULL, &buttons[2].rect);
                SDL_RenderCopy(*renderer, tp_infomain_button, NULL, &buttons[3].rect);
                SDL_RenderCopy(*renderer, tp_win_button,NULL, &buttons[4].rect );
                SDL_RenderCopy(*renderer, tp_gametuto_button, NULL, &buttons[5].rect);

                hovered(buttons[2],&tp_backbutton, &texture_backbutton,&texture_backbutton_hovered);
                hovered(buttons[3],&tp_infomain_button, &texture_infomain_button, &texture_infomain_button_hovered);
                hovered(buttons[4], &tp_win_button, &texture_win_button, &texture_win_button_hovered);
                hovered(buttons[5], &tp_gametuto_button, &texture_gametuto_button, &texture_gametuto_button_hovered);
            }
        }
        SDL_RenderPresent(*renderer);
    }
    

    SDL_DestroyTexture(texture_startbutton);
    SDL_DestroyTexture(texture_startbutton_hovered);
    SDL_DestroyTexture(texture_infobutton);
    SDL_DestroyTexture(texture_infobutton_hovered);
    SDL_DestroyTexture(texture_backbutton);
    SDL_DestroyTexture(texture_backbutton_hovered);

    SDL_DestroyTexture(texture_infomain_button);
    SDL_DestroyTexture(texture_infomain_button_hovered);
    SDL_DestroyTexture(texture_win_button);
    SDL_DestroyTexture(texture_win_button_hovered);
    SDL_DestroyTexture(texture_gametuto_button);
    SDL_DestroyTexture(texture_gametuto_button_hovered);

    SDL_DestroyTexture(texture_num_1_button);
    SDL_DestroyTexture(texture_num_1_button_hovered);
    SDL_DestroyTexture(texture_num_2_button);
    SDL_DestroyTexture(texture_num_2_button_hovered);
    SDL_DestroyTexture(texture_num_3_button);
    SDL_DestroyTexture(texture_num_3_button_hovered);

    SDL_DestroyTexture(texture_infomain_Img);
    SDL_DestroyTexture(texture_win_Img);
    SDL_DestroyTexture(texture_rule_Img1);
    SDL_DestroyTexture(texture_rule_Img2);
    SDL_DestroyTexture(texture_rule_Img3);
    

    SDL_FreeSurface(startButton);
    SDL_FreeSurface(startButton_hovered);
    SDL_FreeSurface(infoButton);
    SDL_FreeSurface(infoButton_hovered);
    SDL_FreeSurface(backButton);
    SDL_FreeSurface(backButton_hovered);

    SDL_FreeSurface(infomain_button);
    SDL_FreeSurface(infomain_button_hovered);
    SDL_FreeSurface(win_button);
    SDL_FreeSurface(win_button_hovered);
    SDL_FreeSurface(gametuto_button);
    SDL_FreeSurface(gametuto_button_hovered);

    SDL_FreeSurface(number_1_button);
    SDL_FreeSurface(number_1_button_hovered);
    SDL_FreeSurface(number_2_button);
    SDL_FreeSurface(number_2_button_hovered);
    SDL_FreeSurface(number_3_button);
    SDL_FreeSurface(number_3_button_hovered);

    SDL_FreeSurface(infomain_img);
    SDL_FreeSurface(win_img);
    SDL_FreeSurface(rule_img1);
    SDL_FreeSurface(rule_img2);
    SDL_FreeSurface(rule_img3);

    SDL_DestroyTexture(texture_startmain);

    SDL_FreeSurface(startMain);

    free_buttons(buttons);
    free_Imgs(imgs);
}

//* 인원선택 화면/
void select_player_num(SDL_Renderer** renderer, SDL_Event* e,  bool* quit, int* total_player) {
    SDL_Surface* startMain = IMG_Load("img/startMain.jpg");
    
    SDL_Surface* num2_img = IMG_Load("img/num/200x200/2.jpg");
    SDL_Surface* num2_hovered_img = IMG_Load("img/num/200x200/2_hovered.jpg");
    SDL_Surface* num3_img = IMG_Load("img/num/200x200/3.jpg");
    SDL_Surface* num3_hovered_img = IMG_Load("img/num/200x200/3_hovered.jpg");
    SDL_Surface* num4_img = IMG_Load("img/num/200x200/4.jpg");
    SDL_Surface* num4_hovered_img = IMG_Load("img/num/200x200/4_hovered.jpg");

    SDL_Texture* texture_startmain = SDL_CreateTextureFromSurface(*renderer,startMain);

    SDL_Texture* texture_num2 = SDL_CreateTextureFromSurface(*renderer, num2_img);
    SDL_Texture* texture_num2_hovered = SDL_CreateTextureFromSurface(*renderer, num2_hovered_img);
    SDL_Texture* texture_num3 = SDL_CreateTextureFromSurface(*renderer, num3_img);
    SDL_Texture* texture_num3_hovered = SDL_CreateTextureFromSurface(*renderer, num3_hovered_img);
    SDL_Texture* texture_num4 = SDL_CreateTextureFromSurface(*renderer, num4_img);
    SDL_Texture* texture_num4_hovered = SDL_CreateTextureFromSurface(*renderer, num4_hovered_img);

    SDL_Texture* tp_num2 = texture_num2;
    SDL_Texture* tp_num3 = texture_num3;
    SDL_Texture* tp_num4 = texture_num4;

    SDL_Texture* tp_maindisplay = texture_startmain;
    
    SDL_Rect mainImg = {0,0,startMain->w, startMain->h};
    
    int count_button = 3;
    Button* buttons = (Button*)malloc(count_button * sizeof(Button));
    if (buttons == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    //num2_button
    initial_Button(&buttons[0], 300,400, num2_img->w, num2_img->h, false, false);
    //num3_button
    initial_Button(&buttons[1], 550,400, num3_img->w, num3_img->h, false, false);
    //num4_button
    initial_Button(&buttons[2], 800,400, num4_img->w, num4_img->h, false, false);

    bool start_quit = false;
    
    while(!start_quit) {
        SDL_RenderCopy(*renderer, tp_maindisplay, NULL, &mainImg);
        while(SDL_PollEvent(e)) {
            switch (e->type) {
            case SDL_QUIT:
                *quit = true;
                start_quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                
                if(e->button.button == 1) {
                    for (int i=0; i< count_button; i++) {
                        buttons[i].pressed = check_in_xy(e->motion.x, e->motion.y, buttons[i]);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                break;
            case SDL_MOUSEMOTION:
                for (int i = 0; i< count_button; i++) {
                    buttons[i].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[i]);
                }
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
        if (buttons[0].pressed) {
            *total_player = 2;
            start_quit = true;
        }
        SDL_RenderCopy(*renderer, tp_num2, NULL, &buttons[0].rect);
        if (buttons[1].pressed) {
            *total_player =3;
            start_quit = true;
        }
        SDL_RenderCopy(*renderer, tp_num3, NULL, &buttons[1].rect);
        if (buttons[2].pressed) {
            *total_player = 4;
            start_quit = true;
        }
        SDL_RenderCopy(*renderer, tp_num4, NULL, &buttons[2].rect);

        hovered(buttons[0], &tp_num2, &texture_num2, &texture_num2_hovered);
        hovered(buttons[1], &tp_num3, &texture_num3, &texture_num3_hovered);
        hovered(buttons[2], &tp_num4, &texture_num4, &texture_num4_hovered);

        SDL_RenderPresent(*renderer);
    }

    SDL_DestroyTexture(texture_num2);
    SDL_DestroyTexture(texture_num2_hovered);
    SDL_DestroyTexture(texture_num3);
    SDL_DestroyTexture(texture_num3_hovered);
    SDL_DestroyTexture(texture_num4);
    SDL_DestroyTexture(texture_num4_hovered);
    
    SDL_FreeSurface(num2_img);
    SDL_FreeSurface(num2_hovered_img);
    SDL_FreeSurface(num3_img);
    SDL_FreeSurface(num3_hovered_img);
    SDL_FreeSurface(num4_img);
    SDL_FreeSurface(num4_hovered_img);

    SDL_DestroyTexture(texture_startmain);

    SDL_FreeSurface(startMain);

    free_buttons(buttons);
}

//* 게임 화면 구성 요소/
//dice image, texture
typedef struct {
    
    SDL_Surface* dice_Img;
    SDL_Surface* dice_Img_hovered;
    SDL_Texture* texture;
    SDL_Texture* texture_hovered;
    int num;
} Dice;
//tp_dice rect texture dice_num
typedef struct {
    SDL_Rect rect;
    SDL_Texture* texture;
    int dice_num;
    bool hovered;
    bool pressed;
} Tp_dice;

typedef struct {
    int ID;
    int max_horse;
    int use_horse;

    SDL_Surface* player_img;
    SDL_Texture* texture;
} Player;

typedef struct {
    int sum1;
    int sum2;
} Combination_dice;


bool check_in_xy_dice(int x, int y, SDL_Rect tp_dice) {
    if (x >= tp_dice.x && x <= tp_dice.x + tp_dice.w &&
        y >= tp_dice.y && y <= tp_dice.y + tp_dice.h) 
        {
            return true;
    }
    return false;
}

void hovered_dice(bool tp_dice_hovered, SDL_Texture** tp_texture, SDL_Texture** texture, SDL_Texture** texture_hovered) {
    if (tp_dice_hovered) {
            *tp_texture = *texture_hovered;
        }
    else *tp_texture = *texture;
}

void initial_Dice(Dice* dice,const char* address,const char* address_hovered,SDL_Renderer** renderer, int num) {
    if(dice !=NULL) {
        dice->dice_Img = IMG_Load(address);
        if (dice->dice_Img != NULL) {
            dice->texture = SDL_CreateTextureFromSurface(*renderer,dice->dice_Img);
        }
        else {fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());}
        dice->dice_Img_hovered = IMG_Load(address_hovered);
        if(dice->dice_Img_hovered != NULL) {
            dice->texture_hovered = SDL_CreateTextureFromSurface(*renderer, dice->dice_Img_hovered);
        }
        else {fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());}
        dice->num = num;
    }
}

void initial_tp_dice_rect(Tp_dice* dice_rect,SDL_Texture** texture,int x, int y,int w, int h, int dice_num, bool hovered, bool pressed) {
    if (dice_rect !=NULL) {
        dice_rect->texture = *texture;
        dice_rect->rect.x = x;
        dice_rect->rect.y = y;
        dice_rect->rect.w = w;
        dice_rect->rect.h = h;
        dice_rect->dice_num = dice_num;
        dice_rect->hovered = hovered;
        dice_rect->pressed = pressed;
    }
}

void initial_Player(Player* player, const char* address, SDL_Renderer** renderer, int id, int max_horse, int use_horse) {
    if(player != NULL) {
        player->ID = id;
        player->max_horse = max_horse;
        player->use_horse = use_horse;
        player->player_img = IMG_Load(address);
        if (player->player_img != NULL) {
            player->texture = SDL_CreateTextureFromSurface(*renderer, player->player_img);
        }
        else {fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());}
    }
}

void free_Dice(Dice* dice) {
    SDL_DestroyTexture(dice->texture);
    SDL_DestroyTexture(dice->texture_hovered);

    SDL_FreeSurface(dice->dice_Img);
    SDL_FreeSurface(dice->dice_Img_hovered);
    free(dice);
}

void free_tp_dice_rect(Tp_dice* dice_rect) {
    SDL_DestroyTexture(dice_rect->texture);
    free(dice_rect);
}

void free_player(Player* player) {
    free(player);
}

//* 게임 화면//
void gamemain(SDL_Renderer** renderer, SDL_Event* e, int* status,int* player_num, bool* quit) {
    
    SDL_Surface* Main_img = IMG_Load("img/game.jpg");
    SDL_Surface* throw_button = IMG_Load("img/button/throwdice.jpg");
    SDL_Surface* throw_button_hovered = IMG_Load("img/button/throwdice_hovered.jpg");
    //플레이어 배너 img
    SDL_Surface* player1_banner = IMG_Load("img/player_banner/player1.jpg");
    SDL_Surface* player2_banner = IMG_Load("img/player_banner/player2.jpg");
    SDL_Surface* player3_banner = IMG_Load("img/player_banner/player3.jpg");
    SDL_Surface* player4_banner = IMG_Load("img/player_banner/player4.jpg");
    
    SDL_Texture* texture_Main_img = SDL_CreateTextureFromSurface(*renderer, Main_img);
    SDL_Texture* texture_throw_button = SDL_CreateTextureFromSurface(*renderer, throw_button);
    SDL_Texture* texture_throw_button_hovered = SDL_CreateTextureFromSurface(*renderer, throw_button_hovered);

    //플레이어 텍스쳐
    SDL_Texture* texture_player1_banner = SDL_CreateTextureFromSurface(*renderer, player1_banner);
    SDL_Texture* texture_player2_banner = SDL_CreateTextureFromSurface(*renderer, player2_banner);
    SDL_Texture* texture_player3_banner = SDL_CreateTextureFromSurface(*renderer, player3_banner);
    SDL_Texture* texture_player4_banner = SDL_CreateTextureFromSurface(*renderer, player4_banner);

    SDL_Texture* tp_maindisplay = texture_Main_img;
    SDL_Texture* tp_throw_button = texture_throw_button;
    
    SDL_Texture* tp_player_banner = texture_player1_banner;

    SDL_Rect game_img = {0,0, Main_img->w, Main_img->h};

    SDL_Rect player_banner_rect = {1300, 5, player1_banner->w, player1_banner->h};

    int count_button = 1;
    Button* buttons = (Button*)malloc(count_button*sizeof(Button));
    if (buttons == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    initial_Button(&buttons[0], 1330, 510, throw_button->w, throw_button->h, false, false);

    //주사위 이미지 동적할당 저장
    Dice* diceses = (Dice*)malloc(6*sizeof(Dice));
    if (diceses == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    initial_Dice(&diceses[0], "img/dice/100Dice1.jpg","img/dice/100Dice1_hovered.jpg", renderer, 1);
    initial_Dice(&diceses[1], "img/dice/100Dice2.jpg","img/dice/100Dice2_hovered.jpg", renderer, 2);
    initial_Dice(&diceses[2], "img/dice/100Dice3.jpg","img/dice/100Dice3_hovered.jpg", renderer, 3);
    initial_Dice(&diceses[3], "img/dice/100Dice4.jpg","img/dice/100Dice4_hovered.jpg", renderer, 4);
    initial_Dice(&diceses[4], "img/dice/100Dice5.jpg","img/dice/100Dice5_hovered.jpg", renderer, 5);
    initial_Dice(&diceses[5], "img/dice/100Dice6.jpg","img/dice/100Dice6_hovered.jpg", renderer, 6);

    int x_dice = 1350;
    int y_dice = 300;
    int main_dice_num = 4;
    //화면에 4개 주사위만 출력을 위해 임시 주사위 동적할당
    Tp_dice* tp_dice_rects = (Tp_dice*)malloc(main_dice_num*sizeof(Tp_dice));
    if (tp_dice_rects == NULL) {
        perror("Failed to allocate memory for buttons");
        exit(1);
    }
    initial_tp_dice_rect(&tp_dice_rects[0], &diceses[0].texture, x_dice,y_dice,diceses[0].dice_Img->w,diceses[0].dice_Img->h,diceses[0].num,false,false);
    initial_tp_dice_rect(&tp_dice_rects[1], &diceses[1].texture, x_dice + 100 + 10, y_dice, diceses[1].dice_Img->w,diceses[1].dice_Img->h, diceses[1].num,false,false);
    initial_tp_dice_rect(&tp_dice_rects[2], &diceses[2].texture, x_dice, y_dice + 100 + 10, diceses[2].dice_Img->w,diceses[2].dice_Img->h, diceses[2].num,false,false);
    initial_tp_dice_rect(&tp_dice_rects[3], &diceses[3].texture, x_dice + 100 + 10, y_dice + 100 +10, diceses[3].dice_Img->w,diceses[3].dice_Img->h, diceses[3].num,false,false);
    
    
    //플레이어 동적할당
    //Player* players = (Player*)malloc(*player_num* sizeof(Player));
    

    bool start_quit = false;
    
    while(!start_quit) {
        SDL_RenderCopy(*renderer, tp_maindisplay, NULL, &game_img);
        SDL_RenderCopy(*renderer, tp_player_banner, NULL, &player_banner_rect);
        while(SDL_PollEvent(e)) {
            switch (e->type) {
            case SDL_QUIT:
                *quit = true;
                start_quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("Mouse Button Pressed: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                for(int i=0; i< count_button; i++) {
                    buttons[i].pressed = check_in_xy(e->motion.x, e->motion.y, buttons[i]);
                    
                }
                break;
            case SDL_MOUSEBUTTONUP:
                printf("Mouse Button Released: %d at (%d, %d)\n", e->button.button, e->button.x, e->button.y);
                break;
            case SDL_MOUSEMOTION:
                for (int i = 0; i< count_button; i++) {
                    buttons[i].hovered = check_in_xy(e->motion.x, e->motion.y, buttons[i]);
                }
                for (int i = 0; i< main_dice_num; i++) {
                    tp_dice_rects[i].hovered = check_in_xy_dice(e->motion.x, e->motion.y, tp_dice_rects[i].rect);
                }
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
        if (buttons[0].pressed) {
            for (int i= 0; i<4; i++) {
                int random = rand()%6;
                tp_dice_rects[i].texture =diceses[random].texture;
                tp_dice_rects[i].dice_num = diceses[random].num;
            }
            printf("dice_num %d\n", tp_dice_rects[0].dice_num);
            printf("dice_num %d\n", tp_dice_rects[1].dice_num);
            printf("dice_num %d\n", tp_dice_rects[2].dice_num);
            printf("dice_num %d\n", tp_dice_rects[3].dice_num);
            buttons[0].pressed = false;
        }
        else {
            SDL_RenderCopy(*renderer, tp_dice_rects[0].texture, NULL, &tp_dice_rects[0].rect);
            SDL_RenderCopy(*renderer, tp_dice_rects[1].texture, NULL, &tp_dice_rects[1].rect);
            SDL_RenderCopy(*renderer, tp_dice_rects[2].texture, NULL, &tp_dice_rects[2].rect);
            SDL_RenderCopy(*renderer, tp_dice_rects[3].texture, NULL, &tp_dice_rects[3].rect);
            for (int i = 0; i<4; i++) {
                hovered_dice(tp_dice_rects[i].hovered, &tp_dice_rects[i].texture, &diceses[tp_dice_rects[i].dice_num-1].texture, &diceses[tp_dice_rects[i].dice_num-1].texture_hovered);   
            }

        }

        SDL_RenderCopy(*renderer, tp_throw_button, NULL, &buttons[0].rect);
        hovered(buttons[0], &tp_throw_button, &texture_throw_button, &texture_throw_button_hovered);
        SDL_RenderPresent(*renderer);
    }

    SDL_DestroyTexture(texture_Main_img);
    SDL_DestroyTexture(tp_maindisplay);
    SDL_DestroyTexture(texture_throw_button);
    SDL_DestroyTexture(texture_throw_button_hovered);

    SDL_FreeSurface(Main_img);
    SDL_FreeSurface(throw_button);
    SDL_FreeSurface(throw_button_hovered);

    free_buttons(buttons);
    free_Dice(diceses);
    free_tp_dice_rect(tp_dice_rects);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
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

    SDL_Event e;

    int status = 0;
    int player_num = 0;
    bool quit = false;

    while (!quit) {
        switch (status)
        {
        case 0:
            startmain(&renderer,&e, &status, &quit );
            break;
        case 1:
            select_player_num(&renderer, &e,  &quit, &player_num);
            SDL_SetWindowSize(window, 1600,800);
            gamemain(&renderer,&e, &status,&player_num, &quit);
            break;
        default:
            break;
        }
    }

    IMG_Quit();
}