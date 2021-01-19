#include <iostream>
#include "Collision.hpp"
#include "Ball.hpp"

Collision::Collision(): m_window(sf::VideoMode(1920,1080), "Ma fenêtre", sf::Style::Fullscreen), m_ball(500,500)
{
    TimePerFrame = sf::seconds(1.f/120.f);
}

void Collision::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Collision::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;
        }
    }
}

void Collision::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) { this-> Left = isPressed; }
    if(key == sf::Keyboard::Right) { this-> Right = isPressed; }
}

void Collision::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed; }
    if(mouse == sf::Mouse::Right) { this-> MouseR = isPressed; }
}

void Collision::update(sf::Time deltaTime)
{
    if(Echap) { m_window.close(); }
    if(MouseR) { m_listeBoule.push_back(Ball(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y)); }
    if(MouseL) { m_ball.setVitesse(500,500); }
    if(Left) { m_ball.setVitesse(-300,400);}
    if(Right) { m_ball.setVitesse(300, 400);}

    m_ball.update(deltaTime);
    for(int i=0; i < int(m_listeBoule.size()); i++) {
        m_listeBoule[i].update(deltaTime);
        m_listeBoule[i].afficher();
    }
}

void Collision::render(void)
{
    m_window.clear();
    for(int i=0; i < int(m_listeBoule.size()); i++) {
        m_listeBoule[i].draw(m_window);
    }
    m_ball.draw(m_window);
    m_window.display();
}

Collision::~Collision()
{}
