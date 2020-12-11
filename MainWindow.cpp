#include "MainWindow.h"

MainWindow::MainWindow(int width, int height, int N)
{
    window = sf::RenderWindow(VideoMode(width, height), "SFML Works!");
}

int MainWindow::Start()
{
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
            {
                window.close(); 
            }			    
		}
        UpdateWindow();
        UpdateModel();
	}
    return 0;
}

void MainWindow::UpdateModel()
{
    model.Update(); 
}

void MainWindow::UpdateWindow()
{
    int spheresNumber = model.GetSpheresNumber();
    int springsNumber = model.GetSpringsNumber();
    for (int i = 0; i < spheresNumber; i++)
    {
        Vector pos = model.GetSpherePosition(i);
        float radius = model.GetSphereRadius(i);
        circles[i].setRadius(radius);
        circles[i].setPosition(pos.X - radius, pos.Y - radius);
        window.draw(circles[i]);
    }
    for (int i = 0; i < springsNumber; i++)
    {
        Segment pos = model.GetSpringPosition(i);
        lines[i].first = sf::Vertex(sf::Vector2f(pos.first.X, pos.first.Y));
        window.draw({lines[i].first, lines[i].second}, 2, sf::Lines);
    }
    window.display();
}