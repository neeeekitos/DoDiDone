/*
 * ---------------------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <edouembe@ensea.fr> and <showok@showok.info> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Edouard Emberger and Théo Segonds
 * ---------------------------------------------------------------------------------------------------
 */
#include "../../include/view/GraphicElement.h"

GraphicElement::GraphicElement(const string s){
	setSprite(s, 0);
}

GraphicElement::GraphicElement(){}

GraphicElement::~GraphicElement(){}

void GraphicElement::setSprite(string fileName, int lvl){
	t.loadFromFile(fileName);
	img = sf::Sprite(t);
}

void GraphicElement::draw(sf::RenderWindow & window){
	window.draw(img);
}

sf::Sprite& GraphicElement::getSprite(char state){
    return img;
}

void GraphicElement::setPosition(Point2I p){
	img.setPosition(p.getX(), p.getY());
}

void GraphicElement::setRotation(float angle){
	img.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
	img.setRotation(angle);
}

void GraphicElement::setScale(float size){
	img.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
	img.setScale(size, size);
}

Point2I GraphicElement::getPosition(){
	return p;
}

void GraphicElement::checkPosition(){
	if((p.getX() != img.getPosition().x) && (p.getY() != img.getPosition().y))
		img.setPosition(p.getX(), p.getY());
}	
