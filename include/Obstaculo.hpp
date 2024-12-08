#pragma once
#include <SFML/Graphics.hpp>
class Obstaculo
{
private:
    sf::RectangleShape shape;
    float width = 50;
    float height = 50;
    float limitePosicion;
    float posicionInicial;
    bool sentido;

public:
    // Construcctor para Obstaculos en movimiento
    Obstaculo(sf::Vector2f posicion, sf::Color color, float limitePosicion, bool sentido)
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(posicion);
        shape.setFillColor(color);
        this->posicionInicial = posicion.x;
        this->limitePosicion = limitePosicion;
        this->sentido = sentido;
    }
    // Construcctor para Obstaculos estaticos
    Obstaculo(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(position);
        shape.setFillColor(color);
    }
    // Destructor
    ~Obstaculo() {}
    // Dibuja el obstaculo en la ventana
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
    // Movimiento del obstaculo en eje X
    void move(float offsetX)
    {
        if (sentido == true)
        {
            shape.move(offsetX, 0);
        }
        if (sentido == false)
        {
            shape.move(-offsetX, 0);
        }
    }
    // Efecto para tener infinitos objetos en moviento
    void reiniciarPosicion()
    {
        if (sentido == true)
        {
            if (shape.getPosition().x >= limitePosicion)
            {
                shape.setPosition(-width, shape.getPosition().y);
            }
        }
        if (sentido == false)
        {
            if (shape.getPosition().x <= -width)
            {
                shape.setPosition(limitePosicion, shape.getPosition().y);
            }
        }
    }
    // Metodo para detectar cuando jugador colisione con obstaculo
    bool detectarColision(const sf::FloatRect &jugadorBounds) const
    {
        if (jugadorBounds.intersects(shape.getGlobalBounds()))
        {
            return true; // Colisión detectada
        }
        return false; // No hay colisión
    }
    sf::FloatRect getBounds() const
    {
        return shape.getGlobalBounds();
    }
    const sf::Vector2f &getPosition() const
    {
        return shape.getPosition();
    }
};