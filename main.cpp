#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

enum Direction
{
    None,
    North,
    South,
    West,
    East

};

void drawGrid(sf::RenderWindow& win, int rows, int cols){
    // initialize values
    int numLines = rows+cols-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    win.setView(win.getDefaultView());
    auto size = win.getView().getSize();
    float rowH = size.y/rows;
    float colW = size.x/cols;
    // row separators
    for(int i=0; i < rows-1; i++){
        int r = i+1;
        float rowY = rowH*r;
        grid[i*2].position = {0, rowY};
        grid[i*2+1].position = {size.x, rowY};
    }
    // column separators
    for(int i=rows-1; i < numLines; i++){
        int c = i-rows+2;
        float colX = colW*c;
        grid[i*2].position = {colX, 0};
        grid[i*2+1].position = {colX, size.y};
    }
    // draw it
    win.draw(grid);
}
void handleKeyboard(Direction &currentDirection)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currentDirection != East){currentDirection = West;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currentDirection != West){currentDirection = East;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentDirection != South){currentDirection = North;
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentDirection != North){currentDirection = South;}
}

void snakePos(std::vector<sf::RectangleShape> &body, Direction currentDirection, float speed){
//    sf::Vector2f headPos = body[0].getPosition();
    sf::Vector2f movement(0.f, 0.f);

    switch(currentDirection){
        case West:
            movement.x = -speed;
            break;
        case East:
            movement.x = speed;
            break;
        case North:
            movement.y = -speed;
            break;
        case South:
            movement.y = speed;
            break;
        default:
            break;
    }
    body[0].move(movement);
    for(int i = body.size() - 1; i > 0; i--){
        body[i].setPosition(body[i - 1].getPosition());
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML SNAKE");
    window.setFramerateLimit(60);
    std::vector<sf::RectangleShape> body;
    body.push_back(sf::RectangleShape(sf::Vector2f(30.f, 30.f)));
    body[0].setFillColor(sf::Color::Yellow);

    Direction direction = None;

    sf::CircleShape food(15);

    food.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    float speed = 10.f;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> xDist(0, window.getSize().x - 30);
    std::uniform_real_distribution<float> yDist(0, window.getSize().y - 30);


    for (int i = 1; i < 3; i++) {
        body.push_back(sf::RectangleShape(sf::Vector2f(30.f, 30.f)));
//        body[i].setPosition(body[i - 1].getPosition() + sf::Vector2f(40.f, 0.f));
        body[i].setOutlineColor(sf::Color::Red);
        body[i].setOutlineThickness(2);
    }

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        handleKeyboard(direction);

        snakePos(body, direction, speed);
        if(body[0].getGlobalBounds().intersects(food.getGlobalBounds())){
            food.setPosition(xDist(gen), yDist(gen));
            body.push_back(sf::RectangleShape(sf::Vector2f(30.f, 30.f)));
        }

        window.clear();
       drawGrid(window, 20, 20);
        for(int i = 0; i < body.size(); i++){
            window.draw(body[i]);
        }
        window.draw(food);
        window.display();
    }
}
