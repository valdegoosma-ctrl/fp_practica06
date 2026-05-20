#include <stdio.h>  
#include <SDL2/SDL.h>
#include <stdbool.h>  

int main (int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO)==0)
    {
        printf("Error: %s\n", SDL_GetError());
        return 1;
    
    
}

bool running = true;
SDL_Event event;

SDL_Window *window = SDL_CreateWindow(
    "HOLA MUNDO", // TITULO DE LA VENATANA 
    SDL_WINDOWPOS_CENTERED, // POSICION DE LA VENTANA EN X 
    SDL_WINDOWPOS_CENTERED, //POSICION DE LA VENTANA EN Y 
    800, //ANCHO DE LA VENTANA 
    600, //ALTO DE LA VENTANA
    0

);
if(window ==NULL)
{
    printf("Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}
SDL_RaiseWindow(window); //Envia a ventana al frente

while(running)
{
    while(SDL_PollEvent(&event)) //Detecta los eventos
    {
        if(event.type == SDL_QUIT){
            running = false;
        }else if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_x)
            running = false;
        }
    }
    
}
//SDL_Delay(3000);

SDL_DestroyWindow(window);

SDL_Quit();
}

