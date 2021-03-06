/**
    @date	15.05.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "State.h"
#include "../Game.h"
#include <set>

class GameState : public State {
public:
    // Constructor.
    GameState (StateStack & stack, Game * game);

    virtual void draw ();
    virtual bool update (sf::Time dt);
    virtual bool handleEvent (const Command * command);

    virtual void onActivate ();
    virtual void onDestroy ();

private:
    std::set <std::pair <Entities::ID, Entities::ID> > collisionMatches;
    std::set <b2Body*> entitiesScheduledForRemoval;
    void collisionHandle ();
    bool checkCollisionMatch (Entities::ID entityA, Entities::ID entityB);

    void applyPendingEntitiesRemoval ();
};

