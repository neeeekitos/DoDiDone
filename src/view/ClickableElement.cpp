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
	startPoint = p;
}

void ClickableElement::setEndPoint(Point2I p){
	endPoint = p;
}

ClickableElement::ClickableElement(Point2I d, Point2I f){
	endPoint = f;
	startPoint = d;
}

ClickableElement::~ClickableElement(){

}

Point2I ClickableElement::getEndPoint(){
	return endPoint;
}

Point2I ClickableElement::getStartPoint(){
	return startPoint;
}

bool ClickableElement::checkPosition(int x, int y){
	if( x>startPoint.getX() && y>startPoint.getY() && x<endPoint.getX() && y<endPoint.getY() )
		return true;
	else 
		return false;
}


