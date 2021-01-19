#ifndef BALL_HPP_INCLUDED
#define BALL_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Displayable
{
    public:
    virtual void afficher(void) const =0;
};

class Ball : public Displayable
{
    public:
        Ball();
        Ball(const float X,const float Y);
        virtual ~Ball();

        void update(const sf::Time& deltaTime);
        void setPosition(const float X, const float Y);
        void setVitesse(const float X, const float Y);
        void draw(sf::RenderWindow& window);
        void launch(const float X, const float Y, const float vit_X, const float vit_Y);
        void processPhysics(void);
        void processCollision(void);
        float dist(const sf::Vector2f& p1, const sf::Vector2f& p2);
        
        virtual void afficher(void) const {};

    private:
        float m_masse;
        sf::Vector2f m_pos, m_vit;
        sf::Vector2f m_posInit, m_vitInit;
        float m_timeElapsedJump;
        sf::CircleShape m_sprite;
        sf::VertexArray m_vertex;
};

#endif // BALL_HPP_INCLUDED
