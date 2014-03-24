#include "KeyboardInterface.h"
#include "Game.h"

KeyboardInterface::KeyboardInterface () {
}

KeyboardInterface::~KeyboardInterface () {
}

int KeyboardInterface::inputHandle (Keyboard::Key key, bool isPressed, int state, PlayerController * playerController) {
	if (key == Keyboard::Escape)		//GameState::State::EXIT the game
		return Game::State::EXIT;						//#TEMP

	switch (state) {						//controls the game state
		case Game::State::IN_MENU:
			if (key == Keyboard::Return)		//#TEMP
				return Game::State::PLAYING;						//pseudo-start of the game
			break;
		case Game::State::PLAYING: {						//all events in the actual game
			playerController->preparePlayerMove (key, isPressed);
			return Game::State::PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}