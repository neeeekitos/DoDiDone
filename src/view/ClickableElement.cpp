/*
 * ---------------------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <edouembe@ensea.fr> and <showok@showok.info> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Edouard Emberger and Théo Segonds
 * ---------------------------------------------------------------------------------------------------
 */
#include "../../include/view/ClickableElement.h"

ClickableElement::ClickableElement(){}

void ClickableElement::action(){}

void ClickableElement::setStartPoint(Point2I p){
	pointDebut = p;
}

void ClickableElement::setEndPoint(Point2I p){
	pointFin = p;
}

ClickableElement::ClickableElement(Point2I d, Point2I f){
	pointFin = f;
	pointDebut = d;
}

ClickableElement::~ClickableElement(){

}

bool ClickableElement::isInside(sf::Event event){
	if(event.type == sf::Event::MouseButtonPressed ){
		if(checkPosition(event.mouseButton.x, event.mouseButton.y)){
			action();
			return true;
		}
	}
	return false;
}

Point2I ClickableElement::getEndPoint(){
	return pointFin;
}

Point2I ClickableElement::getStartPoint(){
	return pointDebut;
}

bool ClickableElement::checkPosition(int x, int y){
	if( x>pointDebut.getX() && y>pointDebut.getY() && x<pointFin.getX() && y<pointFin.getY() )
		return true;
	else 
		return false;
}


