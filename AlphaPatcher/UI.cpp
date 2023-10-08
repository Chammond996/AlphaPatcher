#include "UI.h"

UI::UI()
{
	// I don't like these if/else, will change to just check everything after.
	// 
	// Font
	if (!this->font.loadFromFile("data/font.ttf"))
		this->running = false;

	// background
	if (this->textures[0].loadFromFile("data/bg.png"))
		this->background.setTexture(this->textures[0]);
	else
		this->running = false;

	if (this->textures[1].loadFromFile("data/buttons.png"))
	{
		Button* btn = new Button(1, sf::Vector2f(200, 75), sf::Vector2f(100, 300), this->textures[1]);
		this->buttons.emplace_back(btn);
	}
	else this->running = false;



	
	// No point starting a window if resources aint loaded
	if (this->running)
		this->Run();
}

UI::~UI()
{
}


void UI::Log(std::string msg)
{
#ifdef _DEBUG
	std::cout << msg << "\n";
#endif // _DEBUG

}

void UI::Run()
{

	if (!this->running)
		return;

	sf::RenderWindow window(sf::VideoMode(this->windowX,this->windowY), this->windowName, sf::Style::Close);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::MouseMoved)
			{
				for (auto& btn : this->buttons)
				{
					// Handling the hover sprite transition in the function to keep this clean / save a separate function

					btn->hoverCheck(sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));
				}
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (auto& btn : this->buttons)
				{
					if (btn->hoverCheck(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
					{
						switch (this->state)
						{
							// idle, check for updates
						case 0:
							this->Log("Checking for updates");
							break;
							// checked, patched if needed & should be ready
						case 3:
							this->Log("Launching game");
							break;
						default:
							break;
						}
					}
				}
			}
		}



		window.clear(sf::Color(30, 30, 30));
		
		window.draw(this->background);

		for (auto& btn : this->buttons)
			btn->Draw(window);

		window.display();


		// exit
		if (!this->running)
			window.close();
	}
}

void UI::CursorMove(sf::Vector2i pos)
{

	for (auto& btn : this->buttons)
	{
		//if(btn->)
	}
}
