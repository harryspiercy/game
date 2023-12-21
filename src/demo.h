#ifndef _DEMO_H_
#define _DEMO_H_

#include "common.h"
#include "core.h"
#include "texture.h"
#include "timer.h"
#include "button.h"

const int COLOUR_CIRCLE_CLIPS = 4;
const int WALKING_ANIMATION_FRAMES = 4;

class Demo{

    Core* gCore = NULL;
    SDL_Renderer* gRenderer = NULL;
    Resolution* gViewport = NULL;

    //
    // -- Game globals --
    //
    // Texture for the title
    LTexture gTitleTexture;

    // Sprites: the coloured cirles sprite sheet
    LTexture gColourCircleClipSheet;
    SDL_Rect gColourCircleClips[ COLOUR_CIRCLE_CLIPS ];

    // Sprites: the animated man running
    LTexture gSpriteTextureSheet;
    SDL_Rect gAnimSpriteClips[ WALKING_ANIMATION_FRAMES ];

    // Overlay: example of alpha blending
    LTexture gBackground;
    LTexture gFadeTexture;

    // Overlay: example of rotation and flipping the texture
    LTexture gCompassTexture;

    // Overlay: example of using text
    LTexture gSceneGuideText;

    // Overlay: example of some mouse inputs
    LButton* gButtons[ TOTAL_BUTTONS ];

    // Overlay: example of timers
    LTexture gPromptTexture;
    LTexture gUserTimerTexture;
    LTexture gFpsTimerTexture;

    // Modulation components
    Uint8 red = 255;
    Uint8 green = 255;
    Uint8 blue = 255;

    // Fade alpha variable
    Uint8 alpha = 255;

    // Animation frame
    int frame = 0;

    // Scene ids
    int scene = 0;

    // Texture rotational angle
    double angle = 0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

    // Global text colour
    SDL_Color textColour = { 0, 0, 0, 255 };

    // Timer example
    LTimer userTimer;
    std::stringstream userTimerText;

    // FPS timer
    LTimer fpsTimer;
    std::stringstream fpsTimerText;
    bool showFps = true;
    int countedFrames = 0;

    // load media
    bool loadMedia();

public:
    void init( Core* core );
    void tick(); 
    
    void closeMedia();

};

#endif