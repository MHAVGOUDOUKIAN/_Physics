#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.hpp"

class Collision
{
    public:
        Collision();
        ~Collision();

        void run();
        void update(sf::Time deltaTime);
        void processEvents();
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
        void render();

    public: // Normalement privé
        bool MouseL=false, MouseR=false, Echap=false;
        bool Left=false, Right=false;
        sf::RenderWindow m_window;
        Ball m_ball;
        sf::Time TimePerFrame;
        std::vector<Ball> m_listeBoule;
};

#endif // COLLISION_HPP_INCLUDED
