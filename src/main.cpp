#include <SFML/Graphics.hpp>
#include <iostream>

//constante universel

const float UNIVERSAL_GRAVITY = 6.6743e-11;

const float EARTH_GRAVITY = 9.81;

//Math Collision Invisible construct 

struct AABB //Construct for a rectangle
{
	sf::Vector2f min;
	sf::Vector2f max;
};

//Information about the object

struct OBJECT
{
	AABB pos;
	int element;
	int area;
	int weight;
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
	sf::Transform pos_box1, pos_box2;
	const float* matrix_b1 = pos_box1.getMatrix();
	const float* matrix_b2 = pos_box2.getMatrix();
	OBJECT box1, box2;
	
	// Initialise info about box1 to test Gravity
	box1.weight = 45;

	// Initialise info about box2 to test Gravity
	box2.weight = 60;

	pos_box1.translate({0.f, 0.f});
	pos_box2.translate({600.f, 0.f});

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
		box1.pos.min = {matrix_b1[12], matrix_b1[13] + 40};
		box1.pos.max = {matrix_b1[12] + 40, matrix_b1[13]};
		
		if (box1.pos.min.y < 480 && box1.pos.max.x < 640) {
			pos_box1.translate({0.01f, 0.01f});
		}

		//Box 2
		box2.pos.min = {matrix_b2[12], matrix_b2[13] + 40};
		box2.pos.max = {matrix_b2[12] + 40, matrix_b2[13]};

		if (box2.pos.min.y < 480 && box2.pos.max.x > 0) {
			pos_box2.translate({-0.01f, 0.01f});
		}

		/*Render*/
		window.clear(); // Clear old Frame

		// Draw the game
		window.draw(rectangle, pos_box1);
		window.draw(rectangle, pos_box2);
		
		window.display(); // Tell app that window is done drawing
	}

	//End of application
	return 0;
}
