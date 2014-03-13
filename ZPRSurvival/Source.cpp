#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"
#include "MidpointDisplacementNoise.h"
#include "MapGenerator.h"

int main() {
	Game * game;
	game = new Game ();

	game->initialize ();
	game->run();
	game->terminate ();

	delete game;

}