/**    
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../options/GraphicsOptions.h"
#include "../interface/ResourcesID.h"
#include "../interface/Command.h"
#define RAD_TO_DEG 180.0f / b2_pi
#define DEG_TO_RAD b2_pi / 180.0f

/**
    MVC's View for GameObject class. Implements scene graph to draw objects and provides
    Box2D physics engine functionality

    \base class: sf::Sprite
    \derived: Animated, Effectable, Dynamic, Console, Map
*/

class GameObject : public sf::Sprite {
public:
    // Prefab structure defining all in-game object.
    typedef struct Prefab {
        Entities::ID id = Entities::NONE;
        int width = 1;
        int height = 1;
        float originX = 0.f;
        float originY = 0.f;
        float density = 0.f;
        float friction = 0.f;
        float maxSpeed = 0.f;
        float rotation = 0.f;
        float rotationSpeed = 0.f;
        float acceleration = 0.f;
        float linearDamping = 1.f;
        float angularDamping = 1.f;
        float runModifier = 1.f;
        bool isTextureRepeatable = false;
        b2BodyType bodyType = b2_dynamicBody;
        b2PolygonShape * polyShape = nullptr;		// ONLY ONE shape can and should be
        b2CircleShape * circleShape = nullptr;		// nullptr at creation time.
        union texture {
            Textures::PLAYER playerTexture;
            Textures::ITEMS itemTexture;
            Textures::CREATURES creatureTexture;
        } texture;
    };

    // Identificator of an object.
    typedef struct EntityInfo {
        EntityInfo () : type (Entities::NONE), id (0) {
        };

        EntityInfo (Entities::ID type, const unsigned long long id) : type (type), id (id) {
        }

        EntityInfo operator= (const EntityInfo & entityInfo) {
            EntityInfo temp (entityInfo.type, entityInfo.id);
            return temp;
        }

        Entities::ID type;
        unsigned long long id;
    } EntityInfo;

    // EntityInfo getter
    EntityInfo & getEntityInfo ();

    // Used to create scene nodes.
    //typedef std::shared_ptr<GameObject> ObjectPtr;
    typedef GameObject* ObjectPtr;

    // Global id to distribute to entities.
    static unsigned long long GLOBAL_ID;

    // Assigns unique id to entity.
    static unsigned long long getGlobalID () {
        GLOBAL_ID++;
        return (GLOBAL_ID - 1);
    }

    // Box2D World
    static b2World boxWorld;

    // Default constructor.
    GameObject ();

    // Default destructor.
    virtual ~GameObject ();

    // Overloaded sf::Sprite draw method.
    virtual void draw (sf::RenderWindow * window) const;

    // Draw this object and all children.
    virtual void drawAll (sf::RenderWindow* window) const;

    // Check is this command considers this object and pass it deeper.
    virtual void passCommand (Command *command, sf::Time dt);

    // Get updated position and rotation from b2Body and apply it to Sprite.
    void updateFromBody ();

    // Adds child to vector 'children'.
    // Added child has 'parent' set to calling object.
    void attachChild (ObjectPtr child);

    // Removes node from vector.
    void detachChild (const GameObject& node);	//remove child from vector

    // Removes all (if any left) childs.
    void detachAllChilds ();

    // Remove object by searching graph for given ID.
    void detachById (const unsigned long long id);

    // Check if had any childs.
    bool hasChilds ();

    // Create b2Body 
    void createB2Body (Prefab prefab);

    // Get b2Body of that object
    b2Body * getBody ();

protected:
    std::vector<ObjectPtr> children;	// All children to draw after this object is drawn.
    GameObject* parent;			// Pointer ro the parent (one level above).
    b2Body * boxBody;			// Box2D Dynamic object.
    EntityInfo entityInfo;
};

/**
    GameObject has won "The Most Important Class In The Game" award, in particular circles
    known as TMICITG, but no relation. During the ceremony, one of its rivals (taking its Sprite
    issues into consideration) congratulate the winner with following words: Now you're the thirst.
*/

