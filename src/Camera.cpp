#include "Camera.hpp"

Camera::Camera(const sf::Vector2f& position, const sf::Vector2f& size)
    : ZOOM_FACTOR(0.1f)
    , START_POSITION(position)
    , START_SIZE(size)
    , m_HasBounds(false)
    , m_MoveAmount(1.f)
{
    m_View.setCenter(position.x + size.x / 2.f, position.y + size.y / 2.f);
    m_View.setSize(size);
}

void Camera::moveLeft()
{
    if (inBounds()) m_View.move(-m_MoveAmount, 0.f);
}

void Camera::moveRight()
{
    if (inBounds()) m_View.move(m_MoveAmount, 0.f);
}

void Camera::moveUp()
{
    if (inBounds()) m_View.move(0.f, -m_MoveAmount);
}

void Camera::moveDown()
{
    if (inBounds()) m_View.move(0.f, m_MoveAmount);
}

void Camera::zoomIn()
{
    m_View.zoom(1.f + ZOOM_FACTOR);
}

void Camera::zoomOut()
{
    m_View.zoom(1.f - ZOOM_FACTOR);
}

void Camera::reset()
{
    m_View.setCenter(START_POSITION.x + START_SIZE.x / 2.f, START_POSITION.y + START_SIZE.y / 2.f);
    m_View.setSize(START_SIZE);
}

void Camera::setBounds(const sf::FloatRect& bounds)
{
    m_Bounds = bounds;
    m_HasBounds = true;
}

void Camera::setMoveAmount(float moveAmount)
{
    m_MoveAmount = moveAmount;
}

bool Camera::pointInView(float x, float y) const
{
    sf::Vector2f topLeft = { m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f };
    sf::Vector2f size = m_View.getSize();

    return x >= topLeft.x
        && x <= topLeft.x + size.x
        && y >= topLeft.y
        && y <= topLeft.y + size.y;
}

bool Camera::inBounds() const
{
    if (!m_HasBounds) return true;

    sf::Vector2f topLeft = { m_View.getCenter().x - m_View.getSize().x / 2.f, m_View.getCenter().y - m_View.getSize().y / 2.f };

    return topLeft.x >= m_Bounds.left
        && topLeft.x <= m_Bounds.left + m_Bounds.width
        && topLeft.y >= m_Bounds.top
        && topLeft.y <= m_Bounds.top + m_Bounds.height;
}
