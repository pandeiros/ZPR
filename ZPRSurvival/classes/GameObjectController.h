/**	
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Dynamics/b2World.h>
#include "../interface/ResourcesID.h"
#include "../interface/ResourceHolder.h"
#include "../interface/EntityFactory.h"
#define HYPOTEN(a, b) sqrt(a*a + b*b)
#define HYPOTEN_VEC(vec) sqrt(vec.x*vec.x + vec.y*vec.y)

template <class Type, class Identifier>
/** 
    MVC's Controller for GameObject class. 
*/
class GameObjectController {
public:
    // Time for one tick. Initialized in Game::run()
    static sf::Time deltaTime;

    // Default constructor.
    GameObjectController ();

    // Default destructor.
    virtual ~GameObjectController ();

    // Creates entity of given Type
    void createEntity (Entities::ID entityID, Identifier itemTexture, sf::Vector2f position, sf::Vector2i size);

    // Update all data about enitites
    void updateEntities ();
    
    // Overloaded access operator for getting entities.
    Type* operator[](std::size_t index);

    // Deletes entity matching given id.
    void deleteById (const unsigned id);

    // EntityHolder size getter.
    unsigned int getSize () {
        return entityHolder.size ();
    }

    // Cotrol states, update animations, manage effects
    //virtual void update ();

protected:
    ResourceHolder<sf::Texture, Identifier> textureHolder;		// Template for all different texture holders
    std::vector<Type*> entityHolder;			// Holds all entities
};

template <class Type, class Identifier>
sf::Time GameObjectController<Type, Identifier>::deltaTime = sf::Time::Zero;

template <class Type, class Identifier>
GameObjectController<Type, Identifier>::GameObjectController () {
}

template <class Type, class Identifier>
GameObjectController<Type, Identifier>::~GameObjectController () {
    
}
template <class Type, class Identifier>
void GameObjectController<Type, Identifier>::createEntity (Entities::ID entityID, Identifier texture, sf::Vector2f position, sf::Vector2i size) {
    entityHolder.push_back (EntityFactory::createEntity<Type> (entityID,
                                            textureHolder.get (texture),
                                            position,
                                            size));
}

template <class Type, class Identifier>
void GameObjectController<Type, Identifier>::updateEntities () {
    for (auto & entity : entityHolder) {
        entity->animate (deltaTime);

        if (dynamic_cast<Player*>(entity))
            entity->rotateInstantly ();
        else
            entity->rotateEntity ();

        entity->applyForce ();
        entity->updateFromBody ();
    }
}

template <class Type, class Identifier>
Type * GameObjectController<Type, Identifier>::operator[](std::size_t index) {
    assert (index < entityHolder.size ());
    return entityHolder[index];
}

template <class Type, class Identifier>
void GameObjectController<Type, Identifier>::deleteById (const unsigned id) {
    for (auto & x : entityHolder)
        if (x->getEntityInfo().id == id) {
            auto old = x;
            x = entityHolder.back ();
            entityHolder.pop_back ();

            GameObject::boxWorld.DestroyBody (old->getBody ());
            delete old;
            break;
        }
}