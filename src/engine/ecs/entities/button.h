#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "common.h"

#include "ecs/entity.h"
#include "texture.h"

const int BUTTON_WIDTH = 400;
const int BUTTON_HEIGHT = 300;
const int TOTAL_BUTTONS= 4;

enum LButtonSprite{
	BUTTON_SPRITE_MOUSE_OUT, BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_MOUSE_DOWN, BUTTON_SPRITE_MOUSE_UP, 
	BUTTON_SPRITE_TOTAL
};

class LButton : public Entity{
public:
    //! Initialise internal variables
    /*!
    *
    */
    LButton();
    LButton( string name, string path = string( "../media/buttonSpriteSheet.png" ));

    //! Close down the button
    /*!
    *
    */
    ~LButton();

    //! Load the button clips
    /*!
    */
    bool loadButtonSprites( string path );

    //! Set top left position
    /*!
    *
    */
    void setPosition( int x, int y );

    //! Init the button
    virtual void init();

    //! Load the button spritesheet
    virtual void loadMedia() override;

    //! Handle mouse events
    /*!
    *
    */
    virtual void handleEvents( SDL_Event* e ) override;

    //! Shows button sprite
    /*!
    *
    */
    virtual void render() override;

    //! Shutdown the button
    virtual void shutdown() override;

private:

    //! Path to media
    string mediaPath;

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