#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>dsweqw
#include"GameState.h"
#include"Snake.h"
#include"Food.h"
#include"Menu.h"

void drawSnake(snake a, sf::RectangleShape* s);

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
	
	while (window.isOpen())
	{
		sf::Event close;
		while (window.pollEvent(close))
			if (close.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::Black);

		if(state.getState() == 0)
		{
			sf::Font font;
			font.loadFromFile("BAHNSCHRIFT.ttf");
			sf::Text text_play, text_exit;
			text_play.setFont(font);
			text_exit.setFont(font);
			text_play.setCharacterSize(100);
			text_exit.setCharacterSize(100);
			text_play.setString("Play");
			text_exit.setString("Exit");
			text_play.setFillColor(sf::Color::White);
			text_exit.setFillColor(sf::Color::White);
			text_play.setPosition(sf::Vector2f(900, 540));
			text_exit.setPosition(sf::Vector2f(900, 740));

			window.draw(text_play);
			window.draw(text_exit);

			menu.navigateMenu();

			sf::CircleShape pointer(30, 3);
			pointer.setPosition(sf::Vector2f(800, 580 + (200 * menu.getPointer())));
			pointer.setRotation(90);
			window.draw(pointer);

			if (menu.confirmOption())
			{
				if (menu.getPointer() == 0)
					state.setState("game");
				else window.close();
			}
		}
		else
		{
			time = clock.getElapsedTime();
				Player.setDirection();
				if (time.asSeconds() > 0.075)
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
				

			sf::RectangleShape shapeFood(sf::Vector2f(40, 40));
			shapeFood.setPosition(sf::Vector2f((food.getCoordinates().x - 1) * 40, (food.getCoordinates().y - 1) * 40));
			shapeFood.setFillColor(sf::Color::Red);
			window.draw(shapeFood);

			drawSnake(Player, shape);
			for (int i = 0; i < Player.getLength(); i++)
				window.draw(shape[i]);

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