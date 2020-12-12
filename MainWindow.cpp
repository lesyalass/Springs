#include "MainWindow.h"

MainWindow::MainWindow(int width, int height, int sphereNumber)
{
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML Works!");
    model = Model(width, height, sphereNumber, 0.01);
    circles = new sf::CircleShape[sphereNumber];
    texture.loadFromFile("../sphere.png");
    for(int i = 0; i < sphereNumber; i++)
    {
        circles[i].setTexture(&texture);
        circles[i].setFillColor(sf::Color(255, 100, 255));
    }

    lines = new SFLine[model.GetSpringsNumber()];
}

MainWindow::~MainWindow()
{
    delete[] circles;
    delete[] lines;
    delete window;
}

int MainWindow::Start()
{
    int step = 0;
    while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
            {
                window->close();
            }
		}
        UpdateWindow();
        UpdateModel();
        step += 1;
	}
    return 0;
}

void MainWindow::UpdateModel()
{
    model.Update(); 
}

void MainWindow::UpdateWindow()
{
    window->clear(sf::Color(250, 220, 100, 0));
    int spheresNumber = model.GetSpheresNumber();
    int springsNumber = model.GetSpringsNumber();

    for (int i = 0; i < springsNumber; i++)
    {
        Segment pos = model.GetSpringPosition(i);
        lines[i].first = sf::Vertex(sf::Vector2f(pos.first.X, pos.first.Y), sf::Color(0, 0, 0));
        lines[i].second = sf::Vertex(sf::Vector2f(pos.second.X, pos.second.Y), sf::Color(0, 0, 0));
        sf::Vertex line[] = {lines[i].first, lines[i].second};
        window->draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < spheresNumber; i++)
    {
        Vector pos = model.GetSpherePosition(i);
        float radius = model.GetSphereRadius(i);
        circles[i].setRadius(radius);
        circles[i].setPosition(pos.X - radius, pos.Y - radius);
        
        window->draw(circles[i]);
    }
    window->display();
}