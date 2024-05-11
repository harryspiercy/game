#include "button.h"
#include "core.h"

LButton::LButton() : Entity( "button" ), mPosition( SDL_Point({ 0, 0 }) ), 
    mCurrentSprite( BUTTON_SPRITE_MOUSE_OUT ){
}

LButton::LButton(string name ) : Entity( name ), mPosition( SDL_Point({ 0, 0 }) ), 
    mCurrentSprite( BUTTON_SPRITE_MOUSE_OUT ){
}

LButton::~LButton(){
    mButtonSpriteSheet.free();
}

bool LButton::loadButtonSprites( SDL_Renderer* renderer, string path ){
    
    bool success = false;
    
    if( mButtonSpriteSheet.loadFromFile( renderer, path ) ){
        int halfw = mButtonSpriteSheet.getWidth() / 2; 
        int halfh = mButtonSpriteSheet.getHeight() / 2;
        mButtonSpriteClips[ BUTTON_SPRITE_MOUSE_OUT ] = { 0, 0, halfw, halfh };
        mButtonSpriteClips[ BUTTON_SPRITE_MOUSE_OVER_MOTION ] = { 0, halfh, halfw, halfh };
        mButtonSpriteClips[ BUTTON_SPRITE_MOUSE_DOWN ] = { halfw, 0, halfw, halfh };
        mButtonSpriteClips[ BUTTON_SPRITE_MOUSE_UP ] = { halfw, halfh, halfw, halfh };
        success = true;
    }
    return success;
}

void LButton::setPosition( int x, int y ){
    mPosition = { x, y };
}

void LButton::init( int x, int y, string path ){
	setPosition( x, y );
	loadButtonSprites( core->getRenderer(), path );  
}

void LButton::handleEvents( SDL_Event* e ){
    // If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        // Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        // Check if mouse is in button
        bool inside = true;

        // Mouse is not within the bounds of the button
        if( x < mPosition.x || x > mPosition.x + BUTTON_WIDTH 
        || y < mPosition.y || y > mPosition.y + BUTTON_HEIGHT){
            inside = false;
        }

        // Mouse is outside button
        if( !inside ){
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        // Mouse is inside the button
        else{
            // Set mouse over sprites
            switch( e->type ){
                case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

                case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

                case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void LButton::render(){
    // Show current sprite
    mButtonSpriteSheet.render( core->getRenderer(), mPosition.x, mPosition.y, &mButtonSpriteClips[ mCurrentSprite ] );
}