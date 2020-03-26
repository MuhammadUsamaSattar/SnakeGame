#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include"GameState.h"
#include"Snake.h"
#include"Food.h"

void drawSnake(snake a, sf::RectangleShape* s);

int main()
{
	snake Player;
	Food food;

	Player.reset();
	food.setCoordinates();

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

		Player.setDirection();
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 0.2)
		{
			if (Player.getCoordinates(0) == food.getCoordinates())
			{
				Player.setLength(Player.getLength() + 1);
				food.setCoordinates();
			}
				
			Player.setCoordinates();
			clock.restart();
		}
			
		window.clear(sf::Color::Black);
		sf::RectangleShape shapeFood(sf::Vector2f(40, 40));
		shapeFood.setPosition(sf::Vector2f((food.getCoordinates().x - 1) * 40, (food.getCoordinates().y - 1) * 40));
		shapeFood.setFillColor(sf::Color::Red);
		window.draw(shapeFood);

		drawSnake(Player, shape);
		for(int i=0; i < Player.getLength();i++)
			window.draw(shape[i]);
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