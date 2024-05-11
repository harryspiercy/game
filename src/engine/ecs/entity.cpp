#include "entity.h"
    
Entity::Entity( string name ): entityName( name ), visible( true ){

}

void Entity::onInit(){

    cout << entityName << " load entity media" << endl;
    loadMedia();

    cout << entityName << " init entity" << endl;
    init();
}

void Entity::onHandleEvents( SDL_Event* e ){

    handleEvents( e );
}

void Entity::onTick(){
    
    tick();
}

void Entity::onRender(){
    
    if( visible ){

        render();
    }
}

void Entity::onShutdown(){

    cout << entityName << " shutdown entity" << endl;
    shutdown();

    cout << entityName << " close entity media" << endl;


}
