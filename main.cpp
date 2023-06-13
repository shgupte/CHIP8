#include <iostream>
#include <SDL.h>
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(512, 256, 0, &window, &renderer);
	SDL_RenderSetScale(renderer, 8, 8);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.y = 256/2;
	rect.x = 512/2;
	SDL_RenderDrawRect(renderer, &rect);


	
	SDL_RenderDrawPoint(renderer, 512 / 2, 256 / 2);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	return 0;
}

