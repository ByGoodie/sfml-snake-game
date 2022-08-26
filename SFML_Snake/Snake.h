#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include <vector>
#include "Apple.h"
#include <SFML/Graphics.hpp>
#include "Configs.h"

enum class Directions {
	RIGHT = 0,
	LEFT = 1,
	UP = 2,
	DOWN = 3
};

typedef struct Point {
	sf::Vector2i cords;
	Directions direction;
}Point;

typedef struct Point BodyPart;
typedef struct Point Head;

class Snake : sf::RectangleShape {
private:
#ifdef ALLOW_TEXTURES
	sf::Texture* _head_textures{nullptr}, *_body_texture{nullptr};

#endif
	std::queue<Point> _points;
	Head _head{{0, 1}, Directions::DOWN};
	std::vector<BodyPart> _body_parts{ 1, BodyPart{{0, 0}, Directions::DOWN} };

public:
#ifdef ALLOW_TEXTURES
	Snake(sf::Vector2f windowSize ,sf::Texture* head_textures, sf::Texture* body_texture);	
#endif
	Snake(sf::Vector2f windowSize);
	void Rotate(Directions direction);
	void Move();
	void CheckPoints();
	bool CheckHit();
	bool Eat(const Apple& apple);
	void Draw(sf::RenderWindow& window);
};

#endif