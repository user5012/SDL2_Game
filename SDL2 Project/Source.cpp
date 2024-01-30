#include <iostream>
#include <SDL.h>
#include <Windows.h>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 500;
const int CIRCLE_RADIUS = 50;
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;
const char* K = "[+]";


void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
	for (int i = 0; i <= 360; ++i) {
		double angle = i * 3.1415926535 / 180.0;
		int x = static_cast<int>(centerX + radius * std::cos(angle));
		int y = static_cast<int>(centerY + radius * std::sin(angle));
		SDL_RenderDrawPoint(renderer, x, y);
	}
}

void hideConsole() {
	HWND console = GetConsoleWindow();
	ShowWindow(console, 0);
}

void ShowConsole() {
	HWND console = GetConsoleWindow();
	ShowWindow(console, 1);
}

int main(int argc, char* argv[]) {
	
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error: " << SDL_GetError();
		return 1;
	}

	std::cout << K <<" Initializing\n";

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << K <<" Error trying to create window: " << SDL_GetError();
		SDL_Quit();
		return 1;
	}

	std::cout << K << " Creating window\n";

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << K <<" Error while trying to render: " << SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	std::cout << K << " Rendering circle...\n";



	hideConsole();

	
	bool running = true;
	int circleCentrerY = HEIGHT / 2;
	int circleCentrerX = WIDTH / 2;

	SDL_Event e;

	while (running) {
		Uint32 frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP) {
				if (circleCentrerY != 0) {
					circleCentrerY -= 2;
				}
			}
			if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN) {
				if (circleCentrerY != HEIGHT) {
					circleCentrerY += 2;
				}
			}
			if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) {
				if (circleCentrerX != 0) {
					circleCentrerX -= 2;
				}
			}
			if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) {
				if (circleCentrerX != WIDTH) {
					circleCentrerX += 2;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		DrawCircle(renderer, circleCentrerX, circleCentrerY, CIRCLE_RADIUS);

		SDL_RenderPresent(renderer);



		Uint32 frameTime = SDL_GetTicks() - frameStart;	

		if (frameTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}

	ShowConsole();
	
	SDL_DestroyRenderer(renderer);
	std::cout << K << " Destroying rendered circle\n";
	SDL_DestroyWindow(window);
	std::cout << K << " Destroying Window\n";
	SDL_Quit();
	std::cout << K <<" Bye!\n";

	return 0;
}