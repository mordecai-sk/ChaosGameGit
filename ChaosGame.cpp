// John Tripp & Mordecai Solomon
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    sf::Font font;
    sf::Text text;
    sf::Text text1;
    if (!font.loadFromFile("arial.ttf"))
    {
        // error..
    }

  
    while (window.isOpen())
    {

        text.setFont(font);
        text.setString("Please click three points on the screen!");
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Yellow);
        text1.setFont(font);
        text1.setString("\n Please pick the first point between the triangle!");
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Yellow);

        /*
		****************************************
		Handle the players input
		****************************************
		*/

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        /*
        ****************************************
        Update
        ****************************************
        */

        if (points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.

            int maxPoints = 3;               
            for (int i = 0; i < maxPoints; i++)
            {
                int randomIndex = rand() % vertices.size(); 
                Vector2f randomPoint = vertices[randomIndex];

                Vector2f lastPoint = points.back();
                Vector2f midPoint;
                midPoint.x = (randomPoint.x + lastPoint.x) / 2; 
                midPoint.y = (randomPoint.y + lastPoint.y) / 2;
            
                points.push_back(midPoint);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
        window.draw(text);

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
            if (i == 2) { window.draw(text1); }
        }
        
        for (int j = 0; j < points.size(); j++)
        { 
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(points[j].x, points[j].y));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }
        
        ///TODO:  Draw points
        window.display();
    }
}