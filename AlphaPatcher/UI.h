#pragma once
#include <iostream>
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <map>

class Button
{
private:
	int id = 0;
	sf::Sprite sprite;
	bool hover = false;

public:

	Button(int id, sf::Vector2f size, sf::Vector2f pos, sf::Texture& tx)
	{
		this->sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		this->sprite.setTexture(tx);
		this->sprite.setPosition(pos);
	};

	void Draw(sf::RenderWindow& window) { window.draw(this->sprite); }

	bool hoverCheck(sf::Vector2f pos)
	{
		bool contains = this->sprite.getGlobalBounds().contains(pos);
		
		if (contains == this->hover)
			return contains;

		this->hover = contains;
		int height = this->sprite.getTexture()->getSize().y;
		int width = this->sprite.getTexture()->getSize().x;

		int shift = contains ? width / 2 : 0;

		this->sprite.setTextureRect(sf::IntRect(shift, height, width / 2, height));

		return contains;
	}
};
class UI
{

private:
	
	unsigned int windowX = 400;
	unsigned int windowY = 400;
	std::string windowName = "Alpha Patcher 0.0.1";
	sf::Font font;

	std::string hostIP = "209.141.40.127";
	
	std::map<int, sf::Texture> textures;
	sf::Sprite background;
	std::vector<Button*> buttons;
	

	bool running = true;

	void Log(std::string msg);
	void Run();
	void CursorMove(sf::Vector2i pos);

	enum States {
		PRECHECK = 0,
		CHECKING = 1,
		DOWNLOADING = 2,
		READY = 3
	};
	States state;

public:

	UI();
	~UI();
};

