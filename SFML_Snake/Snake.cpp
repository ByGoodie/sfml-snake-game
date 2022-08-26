#include "Snake.h"

#ifdef ALLOW_TEXTURES
Snake::Snake(sf::Vector2f windowSize, sf::Texture* head_textures, sf::Texture* body_texture) : Snake(windowSize) {
	_head_textures = head_textures;
	_body_texture = body_texture;
}
#endif

Snake::Snake(sf::Vector2f windowSize) : RectangleShape(sf::Vector2f(windowSize.x / 35.0, windowSize.y / 25.0)) {
#ifndef ALLOW_TEXTURES
	this->setFillColor(sf::Color(0, 255, 0));
#endif
	this->setOutlineColor(sf::Color(0, 0, 0));
	this->setOutlineThickness(2.0);
}

void Snake::Rotate(Directions direction) {
	if (direction != _head.direction) {
		if (_head.direction == Directions::RIGHT && direction == Directions::LEFT) {
			return;
		}
		else if (_head.direction == Directions::LEFT && direction == Directions::RIGHT) {
			return;
		}
		else if (_head.direction == Directions::UP && direction == Directions::DOWN) {
			return;
		}
		else if (_head.direction == Directions::DOWN && direction == Directions::UP) {
			return;
		}
		_head.direction = direction;
		_points.push(Point{_head.cords, _head.direction});
	}
}

void Snake::Move() {
	if (_head.direction == Directions::RIGHT) {
		_head.cords.x += 1;
	}
	else if (_head.direction == Directions::LEFT) {
		_head.cords.x -= 1;
	}
	else if (_head.direction == Directions::UP) {
		_head.cords.y -= 1;
	}
	else if (_head.direction == Directions::DOWN) {
		_head.cords.y += 1;
	}

	for (auto &i: _body_parts) {
		if (i.direction == Directions::RIGHT) {
			i.cords.x += 1;
		}
		else if (i.direction == Directions::LEFT) {
			i.cords.x -= 1;
		}
		else if (i.direction == Directions::UP) {
			i.cords.y -= 1;
		}
		else if (i.direction == Directions::DOWN) {
			i.cords.y += 1;
		}
	}
}

void Snake::CheckPoints() {
	for (auto& i: _body_parts) {
		for (auto j = _points; !j.empty(); j.pop()) {
			if (i.cords.x == j.front().cords.x && i.cords.y == j.front().cords.y) {
				i.direction = j.front().direction;
				
				if (i.direction == (*(_body_parts.end() - 1)).direction && i.cords == (*(_body_parts.end() - 1)).cords) {
					_points.pop();
				}
			}
		}
	}
}

bool Snake::CheckHit() {
	if ((_head.cords.x < 0 || _head.cords.x > 34) || (_head.cords.y < 0 || _head.cords.y > 24)) {
		return true;
	}
	
	for (auto &i: _body_parts) {
		if (_head.cords == i.cords) {
			return true;
		}
	}
	
	return false;
}

bool Snake::Eat(const Apple& apple) {
	if (apple.getCords() == _head.cords) {
		if ((*(_body_parts.end() - 1)).direction == Directions::RIGHT) {
			_body_parts.push_back(BodyPart{ {(*(_body_parts.end() - 1)).cords.x - 1, (*(_body_parts.end() - 1)).cords.y}, Directions::RIGHT });
		}
		else if ((*(_body_parts.end() - 1)).direction == Directions::LEFT) {
			_body_parts.push_back(BodyPart{ {(*(_body_parts.end() - 1)).cords.x + 1, (*(_body_parts.end() - 1)).cords.y}, Directions::LEFT });
		}
		else if ((*(_body_parts.end() - 1)).direction == Directions::UP) {
			_body_parts.push_back(BodyPart{ {(*(_body_parts.end() - 1)).cords.x, (*(_body_parts.end() - 1)).cords.y + 1}, Directions::UP});
		}
		else if ((*(_body_parts.end() - 1)).direction == Directions::DOWN) {
			_body_parts.push_back(BodyPart{ {(*(_body_parts.end() - 1)).cords.x, (*(_body_parts.end() - 1)).cords.y - 1}, Directions::DOWN});
		}
		return true;
	}
	return false;
}

void Snake::Draw(sf::RenderWindow& window) {
	const sf::Vector2f shapeSize = this->getSize();

	this->setPosition(_head.cords.x * shapeSize.x, _head.cords.y * shapeSize.y);

#ifdef ALLOW_TEXTURES
	if (_head.direction == Directions::RIGHT) {
		this->setTexture(_head_textures, true);
	}
	else if (_head.direction == Directions::UP) {
		this->setTexture(_head_textures + 1, true);
	}
	else if (_head.direction == Directions::LEFT) {
		this->setTexture(_head_textures + 2, true);
	}
	else {
		this->setTexture(_head_textures + 3, true);
	}
	window.draw(*this);
	this->setTexture(_body_texture, true);
#else
	window.draw(*this);
#endif
	for (auto i: _body_parts) {
		this->setPosition(i.cords.x * shapeSize.x, i.cords.y * shapeSize.y);
		window.draw(*this);
	}
}