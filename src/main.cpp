#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

//
// -- Engine classes --
//
class LTexture{
public:
	// Constructor
	LTexture();
	~LTexture();
	// Write to the hardware texture
	bool loadFromFile( string path );
	// Free the hardware texture
	void free();

	// Draw texture at a given point
	void render( int x, int y, SDL_Rect* clip = NULL );
	// Get image details
	inline int getWidth() { return mWidth; }
	inline int getHeight() { return mHeight; }

private:
	// Hardware texture
	SDL_Texture* mTexture;
	// Image details
	int mWidth;
	int mHeight;
};

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
SDL_Rect gSpriteClips[4];
LTexture gSpriteTextureSheet;

//
// -- Engine methods --
//

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
// --- Program --//
//
int main( int argc, char* args[] ){
	// Start up SDL and create window
	if( !init() ){
		cout << "Failed to init" << endl;
	}
	else{
		// Load media
		if( !loadMedia() ){
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
			while( !quit ){
				// Poll hardware events
				while( SDL_PollEvent( &e )){
					// Exit event
					if( e.type == SDL_QUIT ){
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN ){
						switch( e.key.keysym.sym ){

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
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Render textures
				gSpriteTextureSheet.render( 0, 0, &gSpriteClips[0] );
				gSpriteTextureSheet.render( SCREENWIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1] );
				gSpriteTextureSheet.render( 0, SCREENHEIGHT - gSpriteClips[2].h, &gSpriteClips[2] );
				gSpriteTextureSheet.render( SCREENWIDTH - gSpriteClips[3].w, SCREENHEIGHT - gSpriteClips[3].h, &gSpriteClips[3] );

				// Update screen
				SDL_RenderPresent( gRenderer );
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
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		cout << "SDL could not initialise! SDL Error :" << SDL_GetError() << endl;
		success = false;
	}
	else{
		// Create window
		gWindow = SDL_CreateWindow(
			"SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN
		);

		if( gWindow == NULL ){
			cout << "Window could not be created! SDL Error : " << SDL_GetError() << endl;
			success = false;
		}
		else{
			// create renderer for widow.
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ){
				cout << "Renderer could not be created! SDL Error : " << SDL_GetError() << endl;
				success = false;
			}
			else{
				// Initialise renderer colour to white
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// initialise png loading
				int imgFlags = IMG_INIT_PNG;
				if( !(IMG_Init(imgFlags) & imgFlags) ){
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

	string path( "media/spriteSheet.png" );
	if( !gSpriteTextureSheet.loadFromFile( path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	// Set top left sprite
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 200;
	gSpriteClips[0].h = 200;

	gSpriteClips[1].x = 200;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 200;
	gSpriteClips[1].h = 200;

	gSpriteClips[2].x = 0;
	gSpriteClips[2].y = 200;
	gSpriteClips[2].w = 200;
	gSpriteClips[2].h = 200;

	gSpriteClips[3].x = 200;
	gSpriteClips[3].y = 200;
	gSpriteClips[3].w = 200;
	gSpriteClips[3].h = 200;

	return success;
}

void close(){
	// Free loaded textures
	gSpriteTextureSheet.free();

	// Destroy renderer
	SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	// Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();
}

//
// -- Texture methods --
//
LTexture::LTexture(){
	// Initialise members
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture(){
	// Free the hardware texture
	free();
}

bool LTexture::loadFromFile( string path ){
	// Free an image on hardware
	free();

	// create the fianl texture
	SDL_Texture* newTexture = NULL;
	// load to a surface from the path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		cout << "loadFromFile Failure: " << IMG_GetError() << endl;
	}
	else{
		// Set colour key for the loaded surface to cyan
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		// Create texture from the surface pixels
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ){
			cout << "loadFromFile Failure: " << SDL_GetError() << endl;
		}
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of the old surfce
		SDL_FreeSurface( loadedSurface );
	}

	// Set the texture and return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free(){
	// free the texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( int x, int y, SDL_Rect* clip ){
	// set the rendering screen space
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// copy the texture to the renderer
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}
