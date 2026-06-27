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

struct Circle // Construct for a circle
{
	float radius;
	sf::Vector2f position;
};

//Information about the object

struct OBJECT
{
	AABB rectangle;
	Circle circle;
	sf::Vector2f acceleration;
	sf::Vector2f speed;
	float mass;
};


int	ft_sat(AABB box1, AABB box2)
{
	if((box1.min.y > box2.max.y) || (box2.min.y > box1.max.y)) return false;
	if((box1.max.x < box2.min.x) || (box1.min.x > box2.max.x)) return false; 

	return true;
}

int main()
{
	//Window
	sf::RenderWindow window( sf::VideoMode( { 640, 680 } ), "SFML works!");

	//Shape
	// RECTANGLES
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

	//Creating OBJECTS
	OBJECT box1, box2, d_c1, d_c2;
	
	// Initialise info about circle1
	d_c1.circle.radius = 25.f;
	d_c1.circle.position = {0.f, 90.f};
	
	// Initialise info about circle2
	d_c2.circle.radius = 30.f;
	d_c2.circle.position = {580.f, 90.f};

	// CIRCLES
	sf::CircleShape circle1(d_c1.circle.radius), circle2(d_c2.circle.radius);
	circle1.setPosition(d_c1.circle.position);
	circle2.setPosition(d_c2.circle.position);

	// Initialise info about box1 to test Gravity
	box1.mass = 45;

	// Initialise info about box2 to test Gravity
	box2.mass = 60;

	pos_box1.translate({0.f, 0.f});
	pos_box2.translate({600.f, 0.f});

	//Time
	sf::Clock clock;
	sf::Time elapsed;

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
		box1.rectangle.min = {matrix_b1[12], matrix_b1[13]};
		box1.rectangle.max = {matrix_b1[12] + 40, matrix_b1[13] + 40};
		
		if ((box1.rectangle.min.y < 640 && box1.rectangle.max.x < 640) && !ft_sat(box1.rectangle, box2.rectangle)) {
			pos_box1.translate({0.01f, 0.f});
		}

		//Box 2
		box2.rectangle.min = {matrix_b2[12], matrix_b2[13]};
		box2.rectangle.max = {matrix_b2[12] + 40, matrix_b2[13] + 40};

		if ((box2.rectangle.min.y < 640 && box2.rectangle.max.x > 40) && !ft_sat(box1.rectangle, box2.rectangle)){
			pos_box2.translate({-0.01f, 0.f});
		}
		else if ((box2.rectangle.min.y < 640 && box2.rectangle.max.x > 40)) {
			pos_box2.translate({0.f, 0.01f});
		}

		//Circle 1
		d_c1.circle.position = circle1.getPosition();
		if (d_c1.circle.position.y < 640 && d_c1.circle.position.x < 590){
			circle1.move({0.015f, 0.f});
		}

		//Circle 2
		d_c2.circle.position = circle2.getPosition();
		if (d_c2.circle.position.y < 640 && d_c2.circle.position.x > 0){
			circle2.move({-0.015f, 0.f});
		}

		window.clear(); // Clear old Frame
		
		// Draw the game
		window.draw(rectangle, pos_box1);
		window.draw(rectangle, pos_box2);
		window.draw(circle1);
		window.draw(circle2);
		
		
		window.display(); // Tell app that window is done drawing
	}
	//End of application
	return 0;
}