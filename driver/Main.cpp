#include<iostream>
#include<algorithm>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"GameState.h"
#include"Snake.h"
#include"Food.h"
#include"Menu.h"

void drawSnake(snake a, sf::RectangleShape* s);
void drawMask( snake& a, sf::RectangleShape* s,
			   const sf::Time& time, sf::RenderWindow& window);

constexpr double kSpeed = 0.075;

int main()
{
	int i = 0;
	snake Player;
	Food food;
	gameState state;
	Menu menu;

	Player.reset();
	food.setCoordinates();
	state.setState("menu");
	menu.setPointer(0);

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SnakeGame", sf::Style::Fullscreen);
	sf::RectangleShape shape[64];
	window.setFramerateLimit(60);
	sf::Clock clock;
	sf::Time time;

	// Load the background texture
	sf::Texture background_tex;
	sf::Sprite background;

	if (background_tex.loadFromFile("resources/res/background.jpeg"))
		background.setTexture(background_tex);

	// Load the main menu font and set its properties
	sf::Font font;
	font.loadFromFile("resources/fonts/BAHNSCHRIFT.ttf");
	sf::Text text_play, text_exit, text_score;

	// -> Set font
	text_play.setFont(font);
	text_exit.setFont(font);
	text_score.setFont(font);

	// -> Set character size
	text_play.setCharacterSize(100);
	text_exit.setCharacterSize(100);
	text_score.setCharacterSize(25);

	// -> Set character string
	text_play.setString("Play");
	text_exit.setString("Exit");

	// -> Fill color
	text_play.setFillColor(sf::Color::White);
	text_exit.setFillColor(sf::Color::White);
	text_score.setFillColor(sf::Color::White);
	
	// -> Position
	text_play.setPosition(sf::Vector2f(200, 390));
	text_exit.setPosition(sf::Vector2f(200, 590));
	text_score.setPosition(sf::Vector2f(900, 25));
	
	// Pointer
	sf::CircleShape pointer(30, 3);
	pointer.setRotation(90);

	// Food
	sf::RectangleShape shapeFood(sf::Vector2f(40, 40));
	shapeFood.setFillColor(sf::Color::Red);
	
	while (window.isOpen())
	{
		sf::Event close;
		while (window.pollEvent(close))
			if (close.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::Black);
		time = clock.getElapsedTime();

		if(state.getState() == 0)
		{
			window.draw(background);
			window.draw(text_play);
			window.draw(text_exit);

			if (time.asSeconds() > kSpeed)
			{
				menu.navigateMenu();
				clock.restart();
			}

			// Draw the pointer
			pointer.setPosition(sf::Vector2f(150, 430 + (200 * menu.getPointer())));
			window.draw(pointer);

			if (menu.confirmOption())
			{
				if (menu.getPointer() == 0)
				{
					state.setState("game");
					clock.restart();
				}

				else window.close();
			}
		}
		else
		{
				Player.setDirection();
				if (time.asSeconds() > kSpeed)
				{
					if (abs(Player.getCoordinates(0).x - food.getCoordinates().x) <= 0.8 && abs(Player.getCoordinates(0).y - food.getCoordinates().y) <= 0.8)
					{
						Player.setLength(Player.getLength() + 1);
						food.setCoordinates();
						if (Player.getLength() == 64)
						{
							Player.reset();
							state.setState("menu");
						}
					}
					else if (Player.deathCondition())
					{
						Player.reset();
						state.setState("menu");
					}

					Player.setCoordinates();
					clock.restart();
				}
				
			shapeFood.setPosition(sf::Vector2f((food.getCoordinates().x - 1) * 40, (food.getCoordinates().y - 1) * 40));
			window.draw(shapeFood);

			drawSnake(Player, shape);
			for (int i = 0; i < Player.getLength(); i++)
				window.draw(shape[i]);

			drawMask(Player, shape, time, window);

			// Display the score
			text_score.setString("Score: " + std::to_string(Player.getLength()));
			window.draw(text_score);
			
			if (menu.pauseCheck())
				state.setState("menu");
		}
		window.display();
	}
	return 0;
}

void drawSnake(snake a, sf::RectangleShape* s)
{
	for (int i = 0; i < a.getLength(); i++)
	{
		s[i].setSize(sf::Vector2f(40, 40));
		s[i].setPosition(sf::Vector2f(40 * (a.getCoordinates(i).x - 1), 40 * (a.getCoordinates(i).y - 1)));
		s[i].setFillColor(sf::Color::Green);
	}
}

void drawMask( snake& a, sf::RectangleShape* s,
			   const sf::Time& time, sf::RenderWindow& window)
{
	// Ternary operator, dt is the interpolation constant
	const auto dt = time.asSeconds() <= kSpeed ? std::min(time.asSeconds() / kSpeed, 1.0) : 0;

	// We add a virtual mask for head to expand and tail to contract
	sf::RectangleShape head_mask, tail_mask;
	
	// Head becomes longer
	auto dir = a.getDirection();
	double width, height, dx, dy;

	const auto head_x = a.getCoordinates(0).x - 1.0;
	const auto head_y = a.getCoordinates(0).y - 1.0;

	// -> If moving in the x direction
	if (abs(dir.x) > abs(dir.y))
	{
		width = abs(dir.x * dt);
		height = 1;

		dy = head_y;
		// If right
		if (dir.x > 0)
		{
			dx = head_x + 1.0;
		}
		// If left
		else
		{
			dx = head_x - width;
		}
	}
	// -> If moving in the y direction
	else
	{
		width = 1;
		height = abs(dir.y * dt);

		dx = head_x;
		// If down
		if (dir.y > 0)
		{
			dy = head_y + 1.0;
		}
		// If up
		else
		{
			dy = head_y - height;
		}
	}

	head_mask.setSize(sf::Vector2f(40 * width, 40 * height));	
	head_mask.setPosition(sf::Vector2f( 40 * dx, 40 * dy));
	head_mask.setFillColor(sf::Color::Green);
	
	// Tail becomes shorter
	const auto snake_length = a.getLength();
	
	if (snake_length > 1)
	{
		dir = a.getCoordinates(snake_length - 1) - a.getCoordinates(snake_length - 2);
	}
	else
	{
		// Reverse the direction for tail
		dir.x *= -1;
		dir.y *= -1;
	}

	const auto tail_x = a.getCoordinates(snake_length - 1).x - 1.0;
	const auto tail_y = a.getCoordinates(snake_length - 1).y - 1.0;
	
	// -> If moving in the x direction
	if (abs(dir.x) > abs(dir.y))
	{
		width = abs(dir.x * dt);
		height = 1;

		dy = tail_y;
		// If right
		if (dir.x > 0)
		{
			dx = tail_x + 1.0 - width;
		}
		// If left
		else
		{
			dx = tail_x;
		}
	}
	// -> If moving in the y direction
	else
	{
		width = 1;
		height = abs(dir.y * dt);

		dx = tail_x;
		// If down
		if (dir.y > 0)
		{
			dy = tail_y + 1.0 - height;
		}
		// If up
		else
		{
			dy = tail_y;
		}
	}

	tail_mask.setSize(sf::Vector2f(40 * width, 40 * height));
	tail_mask.setPosition(sf::Vector2f(40 * dx, 40 * dy));
	tail_mask.setFillColor(sf::Color::Black);
	
	window.draw(head_mask);
	window.draw(tail_mask);
}
