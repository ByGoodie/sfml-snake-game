#ifndef APPLE_H
#define APPLE_H

#include <cstdlib>
#include <SFML\Graphics.hpp>

class Apple : public sf::RectangleShape {
private:
	sf::Vector2i _cur_cords;

public:
	Apple(sf::Vector2f windowSize);
	void Ate();
	sf::Vector2i getCords() const;
	void Draw(sf::RenderWindow& window);
};

#endif