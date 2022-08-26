#include "Apple.h"
#include "Snake.h"
#include "timer.h"
#include <iostream>

char* set_str(char* str, int n, int buff_size);
constexpr int str_len(char* str);

int main(void) {
	srand(time(NULL));
	sf::Texture *snake_heads, snake_body;

	snake_heads = new sf::Texture[4];
	
	if (!snake_heads[0].loadFromFile("snake_parts\\snake_head_0.png")) {
		std::cerr << "1 cannot opened!\n";
	}
	
	if (!snake_heads[1].loadFromFile("snake_parts\\snake_head_90.png")) {
		std::cerr << "2 cannot opened!\n";
	}
	
	if (!snake_heads[2].loadFromFile("snake_parts\\snake_head_180.png")) {
		std::cerr << "3 cannot opened!\n";
	}

	if (!snake_heads[3].loadFromFile("snake_parts\\snake_head_270.png")) {
		std::cerr << "4 cannot opened!\n";
	}

	if (!snake_body.loadFromFile("snake_parts\\snake_body.png")) {
		std::cerr << "5 cannot opened!\n";
	}
	
	sf::RenderWindow window(sf::VideoMode(700, 500), "Snake Game V1");
	sf::Event evnt;
	sf::Text score_text, game_over_text;
	sf::Font fnt;
	int cur_score = 0;
	Snake* snake = new Snake(sf::Vector2f(700.0, 500.0), snake_heads, &snake_body);
	Apple* apple = new Apple(sf::Vector2f(700.0, 500.0));
	timer move_timer(0.2);	

	fnt.loadFromFile("arial.ttf");
	score_text.setCharacterSize(40);
	score_text.setFont(fnt);
	game_over_text.setFont(fnt);
	game_over_text.setString("GAME OVER\nPRESS SPACE BAR TO PLAY AGAIN");
	game_over_text.setCharacterSize(25);
	game_over_text.setPosition(400.0 - 14 * 25, 400 - 25);
	
	auto change_score = [&score_text](int score) {
		char str[100] = "Score: {}";
		score_text.setString(set_str(str, score, 99));
	};

	while (window.isOpen()) {
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::KeyPressed) {
				if (evnt.key.code == sf::Keyboard::D) {
					snake->Rotate(Directions::RIGHT);
				}
				else if (evnt.key.code == sf::Keyboard::A) {
					snake->Rotate(Directions::LEFT);
				}
				else if (evnt.key.code == sf::Keyboard::W) {
					snake->Rotate(Directions::UP);
				}
				else if (evnt.key.code == sf::Keyboard::S) {
					snake->Rotate(Directions::DOWN);
				}
			}
			else if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (snake->Eat(*apple)) {
			apple->Ate();
			cur_score++;
		}
		
		move_timer.calcTime();
		if (move_timer.isFinish()) {
			snake->Move();
			move_timer.reset();
		}
		
		snake->CheckPoints();

		if (snake->CheckHit()) {
			while (!window.pollEvent(evnt)) {
				window.clear(sf::Color::Black);
				snake->Draw(window);
				apple->Draw(window);
				window.draw(score_text);
				window.draw(game_over_text);
				window.display();	
			}
			
			if (evnt.type == sf::Event::KeyPressed) {
				if (evnt.key.code == sf::Keyboard::Space) {
					delete snake;
					delete apple;

					snake = new Snake(sf::Vector2f(700.0, 500.0), snake_heads, &snake_body);
					apple = new Apple(sf::Vector2f(700.0, 500.0));

					cur_score = 0;
					change_score(cur_score);
					continue;
				}
			}

			window.close();
			continue;
		}

		change_score(cur_score);

		window.clear(sf::Color::Black);
		snake->Draw(window);
		apple->Draw(window);
		window.draw(score_text);
		window.display();
	}

	delete snake; delete apple;
	return 0;
}

constexpr int str_len(char* str) {
	int i = 0;

	while (str[i] != '\0') {
		i++;
	}

	return i;
}

char* set_str(char* buff, int n, int buff_size) {
	int i, j, k, step = 1, temp = n;
	temp /= 10;

	while (temp) {
		temp /= 10;
		step++;
	}

	for (i = 0; i < buff_size; i++) {
		if (buff[i] == '{' && buff[i + 1] == '}') {
			buff[i] = '\0'; buff[i + 1] = '\0';
			for (j = i + step - 1, k = 0; j >= i && k < step; j--, k++) {
				if (j > buff_size) {
					continue;
				}
				buff[j] = 48 + n % 10;
				n /= 10;
			}
			break;
		}
	} 
	
	return buff;
}