#include <iostream>
#include <math.h>
#include "Ball.hpp"

#define RADIUS 15
#define g 10 * 100
#define h 5

Ball::Ball(): m_masse(10), m_pos(0,0), m_vit(0,0), m_posInit(0,0), m_vitInit(0,0), m_timeElapsedJump(0), m_vertex(sf::Quads , 4) {}

Ball::Ball(const float X,const float Y): m_masse(10), m_pos(sf::Vector2f(X,Y)), m_vit(sf::Vector2f(0,0)), m_posInit(sf::Vector2f(X,Y)), m_vitInit(sf::Vector2f(0,0)), m_timeElapsedJump(0), m_vertex(sf::Quads , 4) {}

void Ball::update(const sf::Time& deltaTime)
{
    m_timeElapsedJump += deltaTime.asSeconds();

    processPhysics();

    processCollision();

    /*m_vertex[0].position = sf::Vector2f(0,m_pos.y);
    m_vertex[1].position = sf::Vector2f(1920,m_pos.y);
    m_vertex[2].position = sf::Vector2f(1920,m_pos.y+1);
    m_vertex[3].position = sf::Vector2f(0,m_pos.y+1);

    m_vertex[0].color = sf::Color::Cyan;
    m_vertex[1].color = sf::Color::Cyan;
    m_vertex[2].color = sf::Color::Cyan;
    m_vertex[3].color = sf::Color::Cyan;*/

}

void Ball::processPhysics(void)
{
    m_pos.y = -((-0.5) * g * m_timeElapsedJump * m_timeElapsedJump + m_vitInit.y * m_timeElapsedJump) + m_posInit.y;    
    //m_pos.x = m_vitInit.x * m_timeElapsedJump + m_posInit.x; // Cas sans frottements
    m_pos.x = (m_masse/h) * m_vitInit.x * (1-exp(-h * m_timeElapsedJump / m_masse)) + m_posInit.x; // Cas avec frottements

    m_vit.y = (-1) * g * m_timeElapsedJump + m_vitInit.y;
    //m_vit.x = m_vitInit.x; // Cas sans frottements
    m_vit.x = m_vitInit.x * exp((-h*m_timeElapsedJump)/m_masse); // Cas avec frottements
    
}

void Ball::processCollision(void)
{
    if(m_pos.y - RADIUS < 0) {
        launch(m_pos.x, RADIUS, m_vit.x, m_vit.y*(-1));
    }
    else if(m_pos.y + RADIUS > 1080) {
        if(m_vit.y > 0 && m_vit.y < 5) // Cas ou la balle ne rebondit plus
        {
            launch(m_pos.x, 1080-RADIUS, m_vit.x, 0);
        }
        else { // Cas du rebond
            launch(m_pos.x, 1080-RADIUS, m_vit.x, m_vit.y*(-1) * 0.65 /* Facteur d'Adhérence du sol */);
        }
    }

    if(m_pos.x - RADIUS < 0) { launch(RADIUS, m_pos.y, m_vit.x * (-1), m_vit.y); } // Rebond sur les cotés 
    else if(m_pos.x + RADIUS > 1920) { launch(1920 - RADIUS, m_pos.y, m_vit.x * (-1), m_vit.y); }
    if(abs(m_vit.x) < 10) { launch(m_pos.x, m_pos.y, 0, m_vit.y); }
}

void Ball::setPosition(const float X, const float Y)
{
    m_pos = sf::Vector2f(X,Y);

    m_posInit = m_pos;

    m_vit = sf::Vector2f(0,0);

    m_vitInit = m_vit;

    m_timeElapsedJump = 0;
}

void Ball::setVitesse(const float X, const float Y)
{
    m_posInit = m_pos;
    
    m_vit = sf::Vector2f(X,Y);

    m_vitInit = m_vit;

    m_timeElapsedJump = 0;
}

void Ball::launch(const float X, const float Y, const float vit_X, const float vit_Y)
{
    m_pos = sf::Vector2f(X,Y);

    m_posInit = m_pos;

    m_vit = sf::Vector2f(vit_X,vit_Y);

    m_vitInit = m_vit;

    m_timeElapsedJump = 0;
}

void Ball::draw(sf::RenderWindow& window)
{ 
    m_sprite.setPosition(m_pos.x - RADIUS , m_pos.y - RADIUS);
    m_sprite.setFillColor(sf::Color::Red);
    m_sprite.setRadius(RADIUS);
    window.draw(m_sprite);
    window.draw(m_vertex);
}

float Ball::dist(const sf::Vector2f& p1, const sf::Vector2f& p2) { return sqrtf((p1.x + p2.x)*(p1.x + p2.x) + (p1.y + p2.y)*(p1.y + p2.y)); }

Ball::~Ball() {}