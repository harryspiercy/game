#include "texture.h"

using std::cout;
using std::endl;

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

bool LTexture::loadFromFile( SDL_Renderer* renderer, string path ){
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
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
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

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( SDL_Renderer* renderer, string textureText, SDL_Color textColour ){
	// Remove exisitng texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, textureText.c_str(), textColour );
	if ( textSurface == NULL ){
		cout << "loadFromRenderedText Failure: Didn't load surface. " << SDL_GetError() << endl;
	}
	else {
		// Create texture from the surface
		mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL ){
			cout << "loadFromRenderedText Failure: Didn't load texture. " << SDL_GetError() << endl;
		}
		else{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		
		// Get rid of used surface
		SDL_FreeSurface( textSurface );
	}

	return mTexture != NULL;
}
#endif

void LTexture::free(){
	// free the texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip,  double angle, SDL_Point* centre, SDL_RendererFlip flip ){
	// set the rendering screen space
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL ){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// copy the texture to the renderer
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, centre, flip );
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