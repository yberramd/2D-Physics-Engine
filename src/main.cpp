#include <SFML/Graphics.hpp>
#include <iostream>

//Math Collision Invisible construct 

struct AABB
{
	sf::Vector2f min;
	sf::Vector2f max;
};

int	ft_sat(AABB box1, AABB box2)
{
	return 0;
}

int main()
{
	//Window
	sf::RenderWindow window( sf::VideoMode( { 640, 480 } ), "SFML works!");

	//Shape
	sf::VertexArray rectangle(sf::PrimitiveType::TriangleStrip, 4);
	//Define the position of the rectangle point
	rectangle[0].position = sf::Vector2f(0.f, 0.f);
	rectangle[1].position = sf::Vector2f(40.f, 0.f);
	rectangle[2].position = sf::Vector2f(0.f, 40.f);
	rectangle[3].position = sf::Vector2f(40.f, 40.f);

	// Define the color of the triangle's points
	rectangle[0].color = sf::Color::Red;
	rectangle[1].color = sf::Color::Blue;
	rectangle[2].color = sf::Color::Magenta;
	rectangle[3].color = sf::Color::Green;

	// Transform (Used to move the visual of the Shape)
	sf::Transform box1, box2;
	const float* matrix_b1 = box1.getMatrix();
	const float* matrix_b2 = box2.getMatrix();
	AABB pos_b1, pos_b2;
	
	box1.translate({0.f, 0.f});
	box2.translate({600.f, 0.f});

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
		/*Inner Update*/

		//Box 1
		pos_b1.min = {matrix_b1[12], matrix_b1[13] + 40};
		pos_b1.max = {matrix_b1[12] + 40, matrix_b1[13]};
		
		if (pos_b1.min.y < 480 && pos_b1.max.x < 640) {
			box1.translate({0.01f, 0.01f});
		}
		//Box 2
		pos_b2.min = {matrix_b2[12], matrix_b2[13] + 40};
		pos_b2.max = {matrix_b2[12] + 40, matrix_b2[13]};

		if (pos_b2.min.y < 480 && pos_b2.max.x > 0) {
			box2.translate({-0.01f, 0.01f});
		}

		/*Render*/
		window.clear(); // Clear old Frame

		// Draw the game
		window.draw(rectangle, box1);
		window.draw(rectangle, box2);
		
		window.display(); // Tell app that window is done drawing
	}

	//End of application
	return 0;
}
