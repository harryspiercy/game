#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include<string>
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

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
	bool loadFromFile( SDL_Renderer* renderer, string path );
	//! Free the hardware texture
	void free();

	//! Draw mTexture at the given point
	/*!
	* \param x x coord to render to
	* \param y y coord to render to
	* \param clip rect to define the area from the loaded texture to render
	*/
	void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL );

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

#endif