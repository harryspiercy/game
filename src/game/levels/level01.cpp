#include "level01.h"
#include "core.h"

Player::Player( string name, string path ) : Entity( name ), mediaPath( path ), sprite( NULL ),
    x( 0 ), y( 0 ){

    sprite = make_shared< LTexture >();
}

void Player::init(){
}

void Player::render(){
    sprite->render( core->getRenderer(), x, y );
}

void Player::loadMedia(){
    
    // Load title page
	sprite->loadFromFile( core->getRenderer(), string( "../media/heady.png" ).c_str() );
}

Level01::Level01() : LLevel() {

}

bool Level01::init(){
    player = makeEntity< Player >( "player" );

    return true;
}