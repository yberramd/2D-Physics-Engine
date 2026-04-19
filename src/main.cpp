#include <SFML/Graphics.hpp>

//Math Collision Invisible construct 

struct AABB
{
	sf::Vector2f min;
	sf::Vector2f max;
};

int main()
{
	//Window
	sf::RenderWindow window( sf::VideoMode( { 640, 480 } ), "SFML works!");

	//Shape
	sf::VertexArray rectangle(sf::PrimitiveType::TriangleStrip, 4);
	//Define the position of the rectangle point
	rectangle[0].position = sf::Vector2f(10.f, 10.f);
	rectangle[1].position = sf::Vector2f(500.f, 10.f);
	rectangle[2].position = sf::Vector2f(10.f, 200.f);
	rectangle[3].position = sf::Vector2f(500.f, 200.f);

	// Define the color of the triangle's points
	rectangle[0].color = sf::Color::Red;
	rectangle[1].color = sf::Color::Blue;
	rectangle[2].color = sf::Color::Magenta;
	rectangle[3].color = sf::Color::Green;

	// Transform (Used to move the visual of the Shape)
	sf::Transform transform;

	transform.translate({0.f, 0.f});

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
		transform.translate({0.f, 0.01f});

		//Render
		window.clear(); // Clear old Frame

		// Draw the game
		window.draw(rectangle, transform);
		
		window.display(); // Tell app that window is done drawing
	}

	//End of application
	return 0;
}
