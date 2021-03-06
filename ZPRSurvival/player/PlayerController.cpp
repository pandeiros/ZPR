/**
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerController.h"

PlayerController::PlayerController () {
    // Set sizes for every animation of the player.
    Player::insertFrameData (Textures::P_IDLE, sf::Vector3<int> (50, 50, 10));
    Player::insertFrameData (Textures::P_WALK, sf::Vector3<int> (50, 50, 10));
    Player::insertFrameData (Textures::P_RUN, sf::Vector3<int> (50, 50, 10));
    
    // Load player textures.
    for (unsigned int i = Textures::P_INIT + 1; i < Textures::P_END; ++i) {
        textureHolder.load (static_cast<Textures::PLAYER>(i), "resources/textures/player.png", sf::IntRect (
            0,
            Player::frameData[static_cast<Textures::PLAYER>(i)].y*(i - Textures::P_INIT - 1),
            Player::frameData[static_cast<Textures::PLAYER>(i)].x*Player::frameData[static_cast<Textures::PLAYER> (i)].z,
            Player::frameData[static_cast<Textures::PLAYER>(i)].y));
    }
}

PlayerController::~PlayerController () {

}

void PlayerController::update () {
    controlStates ();
    controlEffects ();
    updateEntities ();

    entityHolder[0]->update ();
}

void PlayerController::controlStates () {
    Textures::PLAYER textureOld = entityHolder[0]->getCurrentAnimation ();
    Textures::PLAYER textureNew;
    if (entityHolder[0]->getDirection() == 0) {
        if (HYPOTEN_VEC (entityHolder[0]->getBody ()->GetLinearVelocity ()) > 0.1f)	
            textureNew = Textures::P_WALK;
        else
            textureNew = Textures::P_IDLE;
    }
    else if (entityHolder[0]->getIsRunning ()) {
        textureNew = Textures::P_RUN;
    }
    else {
        textureNew = Textures::P_WALK;
    }

    if (textureNew != textureOld)
        entityHolder[0]->changeAnimation (&textureHolder.get (textureNew), textureNew);
}

void PlayerController::controlEffects () {

}