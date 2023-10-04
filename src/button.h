#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "texture.h"

using std::vector;
using std::string;

const int BUTTON_WIDTH = 400;
const int BUTTON_HEIGHT = 300;
const int TOTAL_BUTTONS= 4;

enum LButtonSprite{
	BUTTON_SPRITE_MOUSE_OUT, BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_MOUSE_DOWN, BUTTON_SPRITE_MOUSE_UP, 
	BUTTON_SPRITE_TOTAL
};

class LButton{
public:
    //! Initialise internal variables
    /*!
    *
    */
    LButton();

    //! Load the button clips
    /*!
    */
   bool loadButtonSprites( SDL_Renderer* renderer, string path = string( "media/buttonSpriteSheet.png" ) );

    //! Set top left position
    /*!
    *
    */
   void setPosition( int x, int y );

    //! Handle mouse events
    /*!
    *
    */
   void handleEvent( SDL_Event* e );

    //! Shows button sprite
    /*!
    *
    */
   void render( SDL_Renderer* renderer );

private:

    //! Top left position
    /*!
    *
    */
    SDL_Point mPosition;

    //! Textures to render from
    /*!
    *
    */
    LTexture mButtonSpriteSheet;

    //! Textures to render from
    /*!
    *
    */
    SDL_Rect mButtonSpriteClips[ BUTTON_SPRITE_TOTAL ];

    //! Currently used global sprite
    /*!
    *
    */
    LButtonSprite mCurrentSprite;

};

#endif