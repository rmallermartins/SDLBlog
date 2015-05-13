#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGTH 480
#define SPRITE_SIZE 50

SDL_Window* tela;
SDL_Surface* surface;
SDL_Surface* background;
SDL_Surface* sprite;

SDL_Rect rectSrc, rectSprite[18];
SDL_Event event;

int quit;
int key = 0, posX = 0, posY = 0;

SDL_Surface* loadImage(string path)
{
    SDL_Surface* image = IMG_Load(path.c_str());
    if (image == NULL)
    {
        printf("Não foi possível carregar a imagem! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    return image;
}

void close()
{
    SDL_FreeSurface(background);
    SDL_FreeSurface(sprite);
    SDL_DestroyWindow(tela);
    SDL_Quit();
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao ligar o vídeo! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        tela = SDL_CreateWindow("Exemplo Sprite", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);
        if (tela == NULL)
        {
            printf("Erro ao carregar interface gráfica! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            surface = SDL_GetWindowSurface(tela);
            background = loadImage("D:/Codes/SDL/SDLBlog/ExemploSprite/imagem.png");
            sprite = loadImage("D:/Codes/SDL/SDLBlog/ExemploSprite/sprite.png");
            rectSrc.w = SPRITE_SIZE;
            rectSrc.h = SPRITE_SIZE;
            for (int i = 0; i < 18; i++)
            {
                if (i < 9)
                {
                    (i < 5) ? (rectSprite[i].x = i * SPRITE_SIZE) : (rectSprite[i].x = (i - 5) * SPRITE_SIZE);
                    (i < 5) ? (rectSprite[i].y = 0) : (rectSprite[i].y = SPRITE_SIZE);
                }
                else
                {
                    (i < 14) ? (rectSprite[i].x = (13 - i) * SPRITE_SIZE) : (rectSprite[i].x = (18 - i) * SPRITE_SIZE);
                    (i < 14) ? (rectSprite[i].y = 2 * SPRITE_SIZE) : (rectSprite[i].y = 3 * SPRITE_SIZE);
                }
                rectSprite[i].w = SPRITE_SIZE;
                rectSprite[i].h = SPRITE_SIZE;
            }
        }
    }
    return success;
}

void handleEvent(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        quit = 1;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
        case SDLK_q :
            quit = 1;
            break;
        case SDLK_RIGHT :
            key++;
            if (key > 8) { key = 0; }
            posX += 15;
            cout << posX << endl;
            break;
        case SDLK_LEFT:
            key++;
            if (key < 9 || key > 17) { key = 9; }
            posX -= 15;
            cout << posX << endl;
            break;
        case SDLK_DOWN:
            posY += 15;
            break;
        case SDLK_UP:
            posY -= 15;
            break;
        }
        break;
    }
    cout << key << endl;
    if (posX >= (SCREEN_WIDTH - SPRITE_SIZE)) { posX = (SCREEN_WIDTH - SPRITE_SIZE); }
    if (posX < 0) { posX = 0; }
    if (posY >= (SCREEN_HEIGTH - SPRITE_SIZE)) { posY = (SCREEN_HEIGTH - SPRITE_SIZE); }
    if (posY < 0) { posY = 0; }
}

int main(int argc, char* args[])
{
    if (!init()) { printf("Falha ao iniciar SDL!\n"); }
    else
    {
        while (!quit)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                handleEvent(event);
            }
            SDL_BlitSurface(background, 0, surface, 0);
            rectSrc.x = posX;
            rectSrc.y = posY;
            SDL_BlitSurface(sprite, &rectSprite[key], surface, &rectSrc);
            SDL_UpdateWindowSurface(tela);
        }
    }
    close();
    return 0;
}