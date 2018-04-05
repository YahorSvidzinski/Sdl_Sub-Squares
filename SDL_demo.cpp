//
#include "stdafx.h"
#include "draw.h"

//Screen dimension constants
const int SCREEN_WIDTH  = 760;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(std::string path);
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* loadedSurface = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		/*if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}*/
		gWindow = SDL_CreateWindow("AOKG Lab 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	gTexture = loadTexture("07_texture_loading_and_rendering/texture.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}
	return success;
}

void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	loadedSurface = SDL_CreateRGBSurface(0, 640, 480, 32,
		0x00FF0000,
		0x0000FF00,
		0x000000FF,
		0x00000000);

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: \n", path.c_str());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
	}
	return newTexture;
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			os(loadedSurface);
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					
					unsigned int a = 0;
					if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
						case SDLK_RIGHT:
							SDL_FillRect(loadedSurface, NULL, 0x000000);
							
							draw(loadedSurface,0.1);
							break;
						case SDLK_LEFT:
							SDL_FillRect(loadedSurface, NULL, 0x000000);
							
							draw(loadedSurface, -0.1);
							break;
						}
					}
				}
				
				
				SDL_RenderClear(gRenderer);

				SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}