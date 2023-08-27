#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>
#include<iostream>

using std::cout;
using std::endl;
using std::string;

//
// -- Engine globals --
//
// Engine window
SDL_Window* gWindow = NULL;
const int SCREENWIDTH = 640;
const int SCREENHEIGHT = 480;
// Texture renderer to link to window
SDL_Renderer* gRenderer = NULL;
// Texture to load image to
SDL_Texture* gTexture = NULL;

//
// -- Engine methods --
//
// Load individual image as texture
SDL_Texture* loadTexture(string path);

//
// -- Game globals --
//

//
// -- Game methods --
//
// Start up sdl and create a window
bool init();
// load media
bool loadMedia();
// Frees media and shuts down SDL
void close();

//
// --- Program --
//
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
			//
			// -- Pregame --
			//

			// Load the default state

			// Create an event handler
			SDL_Event e;
			// Create an exit flag
			bool quit = false;

			//
			// -- Game loop --
			//
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
							break;

							case SDLK_DOWN:
							break;

							case SDLK_LEFT:
							break;

							case SDLK_RIGHT:
							break;

							case SDLK_ESCAPE:
							quit = true;
							break;

							default:
							break;
						}
					}
				}

				// Clear the screen
				SDL_RenderClear(gRenderer);

				// Render texture to the screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Update screen
				SDL_RenderPresent(gRenderer);
			}

			//
			// -- Close game --
			//
		}
		//
		// -- Close media --
		//
	}
	//
	// -- Close engine --
	//

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
			// create renderer for widow.
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL){
				cout << "Renderer could not be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else{
				// Initialise renderer colour
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// initialise png loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					cout << "SDL_image could not be initialised! SDL_image error : " << IMG_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(){
	// Loading success flag
	bool success = true;

	// String to hold the file paths
	string filePath;

	// Load a texture
	filePath = string("media/pngs/texture.png");
	gTexture = loadTexture(filePath.c_str());
	if(gTexture == NULL){
		cout << "Failed to load texture image. SDL Error : " << IMG_GetError() << endl;
		success = false;
	}

	return success;
}

void close(){
	// Free loaded textures
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	// Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(string path){
	// the final texture.
	SDL_Texture* newTexture = NULL;

	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL){
		cout << "Unable to load image. SDL_image Error : " << IMG_GetError() << endl;
	}
	else{
		// create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL){
			cout << "Unable to create texture. SDL Error: " << SDL_GetError() << endl;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
