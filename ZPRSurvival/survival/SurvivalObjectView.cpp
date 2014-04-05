/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "SurvivalObjectView.h"

SurvivalObjectView::SurvivalObjectView () {
}

SurvivalObjectView::~SurvivalObjectView () {
}

/*void SurvivalObjectView::draw (sf::RenderWindow& window) const {
	drawAll (window);
}*/


void SurvivalObjectView::attachChild (Ptr & child)
{
	child->parent = this;		//caller is parent for attached child
	children.push_back (std::move (child));		//insert new child
}

SurvivalObjectView::Ptr SurvivalObjectView::detachChild (const SurvivalObjectView& node)
{
	//lambda-expression search for child; return true if found
	auto found = std::find_if (children.begin (), children.end (), [&] (Ptr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
	Ptr result = std::move (*found);		//assign child pointer to 'result'
	result->parent = nullptr;				//erase parent
	children.erase (found);					//erase child
	return result;
}

void SurvivalObjectView::draw (sf::RenderWindow& window) const {
	window.draw (*this);
}

void SurvivalObjectView::drawAll (sf::RenderWindow& window) const {
	this->draw (window);
	for (const Ptr& child : children) {
		child->drawAll (window);
	}
}


void SurvivalObjectView::setTextureByID (int textureID) {

}
