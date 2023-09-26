#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

//! Texture wrapper class.
/*! A class which wraps around the functionailty of the SDL Texture class.
*/
class LTexture{
public:

 	//! Constructor
	LTexture();
 	//! Destructor
	~LTexture();

	//! Write to the hardware mTexture
	/*! Load a texture from a png image at path. set mTexture, mWidth and mHeight
	* \param path path to the png file containing the texture
	* \return was the file successfully loaded
	*/
	bool loadFromFile( string path );
	//! Free the hardware texture
	void free();

	//! Draw mTexture at the given point
	/*!
	* \param x x coord to render to
	* \param y y coord to render to
	* \param clip rect to define the area from the loaded texture to render
	*/
	void render( int x, int y, SDL_Rect* clip = NULL );

	//! Modify texture colour
	void setColour( Uint8 r, Uint8 g, Uint8 b );
	//! Modify the blend mode
	/*!
	* \param blending the SDL_BlendMode to render mTexture with
	*/
	void setBlendMode( SDL_BlendMode blending );
	//! Modify the alpha
	void setAlpha( Uint8 a );

	//! Get width in pixels
	inline int getWidth() { return mWidth; }
	//! Get height in pixels
	inline int getHeight() { return mHeight; }

private:
	//! Hardware texture
	SDL_Texture* mTexture;

	//! Image width
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
LTexture gColourCircleClipSheet;
const int COLOUR_CIRCLE_CLIPS = 4;
SDL_Rect gColourCircleClips[ COLOUR_CIRCLE_CLIPS ];

LTexture gSpriteTextureSheet;
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gAnimSpriteClips[ WALKING_ANIMATION_FRAMES ];

// Other example content
LTexture gFadeTexture;

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

			// Modulation components
			Uint8 red = 255;
			Uint8 green = 255;
			Uint8 blue = 255;

			Uint8 alpha = 255;

			int frame = 0;
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
							if( alpha + 32 > 255 ) alpha = 255;
							else alpha += 32;
							break;

							case SDLK_DOWN:
							if( alpha - 32 < 0 ) alpha = 0;
							else alpha -= 32;
							break;

							case SDLK_LEFT:
							break;

							case SDLK_RIGHT:
							break;

							case SDLK_ESCAPE:
							quit = true;
							break;

							case SDLK_q:
							red += 32;
							break;

							case SDLK_a:
							red -= 32;
							break;

							case SDLK_w:
							green += 32;
							break;

							case SDLK_s:
							green -= 32;
							break;

							case SDLK_e:
							blue += 32;
							break;

							case SDLK_d:
							blue -= 32;
							break;
							default:
							break;
						}
					}
				}

				// Clear the screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				// Draw the modular background
				gColourCircleClipSheet.setColour( red, green, blue );

				gColourCircleClipSheet.render( 0, 0, &gColourCircleClips[0] );
				gColourCircleClipSheet.render( SCREENWIDTH - gColourCircleClips[1].w, 0, &gColourCircleClips[1] );
				gColourCircleClipSheet.render( 0, SCREENHEIGHT - gColourCircleClips[2].h, &gColourCircleClips[2] );
				gColourCircleClipSheet.render( SCREENWIDTH - gColourCircleClips[3].w, SCREENHEIGHT - gColourCircleClips[3].h, &gColourCircleClips[3] );

				// Render the current frame
				SDL_Rect* currentClip = &gAnimSpriteClips[ frame / 4 ];
				gSpriteTextureSheet.render( ( SCREENWIDTH - currentClip->w ) / 2, ( SCREENHEIGHT - currentClip->h) / 2, currentClip );

				// Go te the next frame
				++frame;

				// Cycle Animation
				if ( frame / 4 >= WALKING_ANIMATION_FRAMES ) frame = 0;

				// Draw the fader forground
				gFadeTexture.setAlpha( alpha );
				gFadeTexture.render( 0, 0 );

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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

	string path( "media/SpriteSheetTemplate.png" );
	if( !gSpriteTextureSheet.loadFromFile( path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	path = string( "media/spriteSheet.png" );
	if( !gColourCircleClipSheet.loadFromFile( path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}

	gColourCircleClips[0] = { 0, 0, 200, 200 };
	gColourCircleClips[1] = { 200, 0, 200, 200 };
	gColourCircleClips[2] = { 0, 200, 200, 200 };
	gColourCircleClips[3] = { 200, 200, 200, 200 };

	gAnimSpriteClips[0] = { 0, 0, 100, 200 };
	gAnimSpriteClips[1] = { 100, 0, 100, 200 };
	gAnimSpriteClips[2] = { 200, 0, 100, 200 };
	gAnimSpriteClips[3] = { 300, 0, 100, 200 };

	path = string( "media/fadeIn.png" );
	if( !gFadeTexture.loadFromFile( path.c_str() ) ){
		cout << "loadMedia Failure: Couldn't load " << path.c_str() << endl;
		success = false;
	}
	else{
		// Setup blending
		gFadeTexture.setBlendMode( SDL_BLENDMODE_BLEND );
	}

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

void LTexture::setColour( Uint8 r, Uint8 g, Uint8 b ){
	SDL_SetTextureColorMod( mTexture, r, g, b );
}

void LTexture::setBlendMode( SDL_BlendMode blending ){
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 a ){
	SDL_SetTextureAlphaMod( mTexture, a );
}
