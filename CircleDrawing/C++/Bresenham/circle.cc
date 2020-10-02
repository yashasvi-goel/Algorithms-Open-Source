/**
 * Bresenham's Algorithm to draw a circle.
 *
 * @author rhythm1705
 * @version 12 April 2020
 */

#include <iostream>
#include <SDL2/SDL.h>

#define WINDOW_SIZE 640 // the lenght and width of the window
#define RADIUS 150 // the radius of the circle

// Draw point in all octants
void drawPoints(SDL_Renderer *ren, int xc, int yc, int x, int y) {
	SDL_RenderDrawPoint(ren, xc + x, yc + y);
	SDL_RenderDrawPoint(ren, xc - x, yc + y);
	SDL_RenderDrawPoint(ren, xc + x, yc - y);
	SDL_RenderDrawPoint(ren, xc - x, yc - y);
	SDL_RenderDrawPoint(ren, xc + y, yc + x);
	SDL_RenderDrawPoint(ren, xc - y, yc + x);
	SDL_RenderDrawPoint(ren, xc + y, yc - x);
	SDL_RenderDrawPoint(ren, xc - y, yc - x);
	SDL_RenderPresent(ren);
	// delay to show animation
	SDL_Delay(20);
}

// Calculate radius error
int radiusError(int x, int y, int r) {
	return (x * x) + (y * y) - (r * r);
}

// Bresenham's Algorithm to draw a circle
void circleBres(SDL_Renderer *ren, int xc, int yc, int r) {
	int x = r;
	int y = 0;
	while (x >= y) {
		drawPoints(ren, xc, yc, x, y);
		int decision = 2 * (radiusError(x, y, r) + (2 * y) + 1) + (1 - (2 * x));
		y++;
		if (decision > 0) {
			x--;
		}
	}
}

int main() {
	SDL_Event event;
	// initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_INIT Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	// open a window to draw the circle on
	SDL_Window *win = SDL_CreateWindow("Circle using Bresenham's Algorithm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	// create a renderer to render the circle
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	// set center and radius of circle
	int xc = WINDOW_SIZE / 2;
	int yc = WINDOW_SIZE / 2;
	int r = RADIUS;
	// set color of circle
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	// draw circle
	circleBres(ren, xc, yc, r);
	// quit window on close
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
