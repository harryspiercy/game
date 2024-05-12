#ifndef _LEVEL01_H_
#define _LEVEL01_H_

#include "common.h"
#include "level.h"
#include "texture.h"
#include "ecs/entity.h"

class Player : public Entity{

    int x, y;
    string mediaPath;

public:
    Player( string name, string path = "" );
    shared_ptr< LTexture > sprite;

    virtual void loadMedia() override;
    virtual void init() override;
    virtual void handleEvents( SDL_Event* e ){}
    virtual void tick() override{}
    virtual void render() override;
    virtual void shutdown() override{}
    virtual void closeMedia() override{}

};

class Level01 : public LLevel{

public:
    Level01();
    ~Level01() {}

private:
    shared_ptr< Player > player;

    virtual bool loadMedia() override{ return true; }
    virtual bool init() override;
    virtual void tick() override{}
    virtual void render() override{}
    virtual void shutdown() override{}
    virtual void closeMedia() override{}

};

#endif