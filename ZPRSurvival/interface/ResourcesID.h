/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

using sf::Texture;

// List of all textures in the game.
namespace Textures {
	enum ID {
		P_BASE = 1,		//P_xxx - player textures
		I_STONE = 100	//I_xxx - item textures
		//C_xxx - creature textures
		//M_xxx - map elements textures
	};
}

// List of all differen font used in the game.
namespace Fonts {
	enum ID {
		F_MENU = 1
	};
}