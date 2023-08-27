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

// Engine globals
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;

// Game globals
enum KeyPressSurfaces{KPS_DEFAULT, KPS_UP, KPS_DOWN, KPS_LEFT, KPS_RIGHT, KPS_TOTAL};
SDL_Surface* gKeyPressSurfaces[KPS_TOTAL];

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
			gCurrentSurface = gKeyPressSurfaces[KPS_DEFAULT];

			// Update the surface
			SDL_UpdateWindowSurface(gWindow);

			// Create an event handler
			SDL_Event e;

			// Create an exit flag
			bool quit = false;
			// -- Game loop --
			while(!quit){
				// Poll hardware events
				while(SDL_PollEvent(&e)){
					// Exit event
					if(e.type == SDL_QUIT){
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KPS_UP];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KPS_DOWN];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KPS_LEFT];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KPS_RIGHT];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[KPS_DEFAULT];
							break;
						}
					}
				}

				// Apply the current image
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

				// Update the surface
				SDL_UpdateWindowSurface(gWindow);
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

	string filePath;

	// Load splash image
	gKeyPressSurfaces[KPS_DEFAULT]  = loadSurface("../media/image.bmp");
	if(gKeyPressSurfaces[KPS_DEFAULT] == NULL){
		cout << "Unable to load image ../media/image.bmp. SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	gKeyPressSurfaces[KPS_UP]  = loadSurface("../media/up.bmp");
	if(gKeyPressSurfaces[KPS_UP] == NULL){
		cout << "Unable to load image ../media/up.bmp. SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	gKeyPressSurfaces[KPS_DOWN]  = loadSurface("../media/down.bmp");
	if(gKeyPressSurfaces[KPS_DOWN] == NULL){
		cout << "Unable to load image ../media/down.bmp. SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	gKeyPressSurfaces[KPS_LEFT]  = loadSurface("../media/left.bmp");
	if(gKeyPressSurfaces[KPS_LEFT] == NULL){
		cout << "Unable to load image ../media/left.bmp. SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	gKeyPressSurfaces[KPS_RIGHT]  = loadSurface("../media/right.bmp");
	if(gKeyPressSurfaces[KPS_RIGHT] == NULL){
		cout << "Unable to load image ../media/right.bmp. SDL Error : " << SDL_GetError() << endl;
		success = false;
	}

	return success;
}

void close(){
	// Deallocate the surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	for(auto i = 0; i < KPS_TOTAL; i++){
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}

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

	return loadedSurface;

}
