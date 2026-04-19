#include <SFML/Graphics.hpp>

int main()
{
	//Window
	sf::RenderWindow window( sf::VideoMode( { 640, 480 } ), "SFML works!");
	sf::RectangleShape shape( {120.f, 100.f} );
	shape.setFillColor( sf::Color::Green );
	shape.setPosition({60.f, 50.f});


	//Game loop
	while ( window.isOpen() )
	{
		//Event polling
		while ( const std::optional event = window.pollEvent() )
		{
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* KeyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (KeyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
		}
		//Update
		shape.move({0.01f, 0.01f});

		//Render
		window.clear(); // Clear old Frame

		window.draw( shape );// Draw the game
		
		window.display(); // Tell app that window is done drawing
	}

	//End of application
	return 0;
}
