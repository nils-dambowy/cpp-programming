#include <complex>
#include <iostream>
#include <SDL.h>

using namespace std;

struct color {
	float r, g, b, a;
};

int mandel(complex<double> z, complex<double> c) {
	int n = 0.0;
	while (n < 255) {
		z = z * z + c;
		if (abs(z) > 2.0)
			break;
		++n;
	}
	return n;
}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError();
		return 1;
	}
	
	// Color palette
	color palette[] = { {0,0,0}, {0,24,32}, {26,61,74}, {79,90,100}, {147,167,184}};

	// Create a window
	const int HEIGHT = 720;
	const int WIDTH = 1280;
	SDL_Window *window;


	// Create a renderer
	SDL_Renderer *renderer;
	 

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_OPENGL, &window, &renderer);

	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			complex<double> c(1.0* (x - (WIDTH - HEIGHT) / 2) / HEIGHT * 4.0 - 2.0, 1.0 * y / HEIGHT * 4.0 - 2.0);
			complex<double> z(0.0, 0.0);
			int m = mandel(z, c);

			// choose color based on iteration count when breaking
			color random_color = palette[m % 5];
		
			SDL_SetRenderDrawColor(renderer, random_color.r, random_color.g, random_color.b, 255);
			SDL_RenderDrawPoint(renderer,x, y);
		}
	}

	// Present the renderer
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}