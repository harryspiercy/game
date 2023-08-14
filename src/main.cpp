#include<iostream>
#include<SDL2/SDL.h>
#include<string>

using std::cout;
using std::endl;
using std::string;

// Globals
const int SCREENWIDTH = 640;
const int SCREENHEIGHT = 480;
const char* MEDIAPATH = "../media/image.bmp";

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;

enum KeyPressSurfaces{KPS_DEFAULT, KPS_UP, KPS_DOWN, KPS_LEFT, KPS_RIGHT, KPS_TOTAL};

// Start up sdl and create a window
bool init();

// load media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Load SDL Surfaces
SDL_Surface* loadSurface(string path);

// ---
int main(int argc, char* args[]){
	// Start up SDL and create window
	if(!init()){
		cout << "Failed to init" << endl;
	}
	else{
		// Load media
		if(!loadMedia()){
			cout << "Failed to load media" << endl;
		}
		else{
			// Apply the image
			SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

			// Update the surface
			SDL_UpdateWindowSurface(gWindow);

			// Hold the window open
			SDL_Event e;
			bool quit = false;
			while(!quit){
				while(SDL_PollEvent(&e)){
					if(e.type == SDL_QUIT){
						quit = true;
					}
				}
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}

bool init(){
	// Inisitialise flag
	bool success = true;

	// Initialise SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL could not initialise! SDL Error :" << SDL_GetError() << endl;
		success = false;
	}
	else{
		// Create window
		gWindow = SDL_CreateWindow(
			"SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN
		);

		if(gWindow == NULL){
			cout << "Window could not be created! SDL Error : " << SDL_GetError() << endl;
			success = false;
		}
		else{
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	// Load splash image
	gHelloWorld = SDL_LoadBMP(MEDIAPATH);
	if(gHelloWorld == NULL){
		cout << "Unable to load image '" << MEDIAPATH << "' SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	return success;
}

void close(){
	// Deallocate the surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL Subsystems
	SDL_Quit();
}

SDL_Surface* loadSurface(string path){
	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL){
		cout << "Unable to load image " << path.c_str() << " SDL Error : " << SDL_GetError() << endl;
	}

	return 0;

}
