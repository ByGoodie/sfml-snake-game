#include "Apple.h"

Apple::Apple(sf::Vector2f windowSize) : RectangleShape(sf::Vector2f(windowSize.x / 35.0, windowSize.y / 25.0)) {
	_cur_cords = sf::Vector2i(rand() % 35, rand() % 25);
	this->setFillColor(sf::Color(255, 0, 0));
	this->setOutlineColor(sf::Color(0, 0, 0));
	this->setOutlineThickness(2.0);
}

void Apple::Ate() {
	sf::Vector2i temp = _cur_cords;

	while (temp == _cur_cords) {
		_cur_cords = sf::Vector2i(rand() % 35, rand() % 25);
	}
}

sf::Vector2i Apple::getCords() const {return _cur_cords;}

void Apple::Draw(sf::RenderWindow& window) {
	this->setPosition(_cur_cords.x * this->getSize().x, _cur_cords.y * this->getSize().y);
	window.draw(*this);
}