#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class Camera
{
    public:
        Camera(const sf::Vector2f& position, const sf::Vector2f& size);

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void zoomIn();
        void zoomOut();
        void reset();

        void setBounds(const sf::FloatRect& bounds);
        void setMoveAmount(float moveAmount);

        bool pointInView(float x, float y) const;

        operator const sf::View&()
        {
            return m_View;
        }

    private:
        bool inBounds() const;

    private:
        const float ZOOM_FACTOR;

        const sf::Vector2f START_POSITION;
        const sf::Vector2f START_SIZE;

        sf::View m_View;

        sf::FloatRect m_Bounds;
        bool m_HasBounds;

        float m_MoveAmount;
};

#endif
