#include "../../include/view/GraphicElement.h"

GraphicElement::GraphicElement(const string s) {
    SetSprite(s, 0);
}

GraphicElement::GraphicElement() {}

GraphicElement::~GraphicElement() {}

void GraphicElement::SetSprite(string fileName, int lvl) {
    t.loadFromFile(fileName);
    img = sf::Sprite(t);
}

void GraphicElement::Draw(sf::RenderWindow &window) {
    window.draw(img);
}

sf::Sprite &GraphicElement::GetSprite(char state) {
    return img;
}

void GraphicElement::SetPosition(Point2I p) {
    img.setPosition(p.GetX(), p.GetY());
}

void GraphicElement::SetRotation(float angle) {
    img.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    img.setRotation(angle);
}

void GraphicElement::SetScale(float size) {
    img.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    img.setScale(size, size);
}

Point2I GraphicElement::GetPosition() {
    return p;
}

