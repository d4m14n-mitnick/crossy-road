#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.hpp>

class ObstaculoMovil : public Obstaculo
{

private:
    float limitePosicion;
    float posicionInicial;
    bool sentido;

public:
    // Construcctor para Obstaculos en movimiento
    ObstaculoMovil(sf::Vector2f posicion, sf::Color color, float width, float height, float limitePosicion, bool sentido, const std::string &rutaImagen) : Obstaculo(posicion, color, width, height, rutaImagen)
    {
        this->posicionInicial = posicion.x;
        this->limitePosicion = limitePosicion;
        this->sentido = sentido;
        // if (!texture.loadFromFile("assets/images/canasta/refresco naranja3.png")){}
        // this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(posicion);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
        shape.setSize(sf::Vector2f(width, height));
    }

    // Destructor
    virtual ~ObstaculoMovil() {}

    // Movimiento del obstaculo en eje X
    void move(float offsetX)
    {
        if (sentido == true)
        {
            sf::Vector2f posicionActual = shape.getPosition();
            this->sprite.setPosition(posicionActual);
            shape.move(offsetX, 0);
        }
        if (sentido == false)
        {
            sf::Vector2f posicionActual = shape.getPosition();
            this->sprite.setPosition(posicionActual);
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
                this->sprite.setPosition(-width, shape.getPosition().y);
                shape.setPosition(-width, shape.getPosition().y);
            }
        }
        if (sentido == false)
        {
            if (shape.getPosition().x <= -width)
            {
                this->sprite.setPosition(limitePosicion, shape.getPosition().y);
                shape.setPosition(limitePosicion, shape.getPosition().y);
            }
        }
    }
};