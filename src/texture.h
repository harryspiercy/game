#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include<string>
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

using std::string;

//! Texture wrapper class.texture.h
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
	* \param renderer Global renderer
	* \param path path to the png file containing the texture
	* \return was the file successfully loaded
	*/
	bool loadFromFile( SDL_Renderer* renderer, string path );

	//! Load the required texture clips from the ttf file for the provided string
	/*! 
	* \param renderer Global renderer
	* \param textureText string of characters to render
	* \param textColour colour of the text to render
	* \return success of loading text
	*/
	bool loadFromRenderedText( SDL_Renderer* renderer, string textureText, SDL_Color textColour );

	//! Free the hardware texture
	void free();

	//! Draw mTexture at the given point
	/*!
	* \param renderer Global renderer
	* \param x x coord to render to
	* \param y y coord to render to
	* \param clip rect to define the area from the loaded texture to render
	* \param angle angle at which to rotate the texture
	* \param centre SDL Point to define the centre of rotation
	* \param flip SDL Flip type, SDL_FLIP_NON, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICLE
	*/
	void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	//! Modify texture colour 0-255
	/*!
	* \param r red value
	* \param g green value
	* \param b blue value
	*/
	void setColour( Uint8 r, Uint8 g, Uint8 b );
	//! Modify the blend mode
	/*!
	* \param blending the SDL_BlendMode to render mTexture with
	*/
	void setBlendMode( SDL_BlendMode blending );
	//! Modify the alpha
	/*!
	* \param a the alpha value of the texture, 0-255
	*/
	void setAlpha( Uint8 a );

	//! Get width in pixels
	/*!
	* \return width of the loading image in pixels
	*/
	inline int getWidth() { return mWidth; }
	//! Get height in pixels
	/*!
	* \return height of the loading image in pixels
	*/
	inline int getHeight() { return mHeight; }

private:
	//! Hardware texture
	SDL_Texture* mTexture;

	//! Image width
	int mWidth;
	//! Image height
	int mHeight;

public:
	//! Font to render all textures.
	TTF_Font* mFont;
};

#endif