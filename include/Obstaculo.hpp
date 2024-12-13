#pragma once
#include <SFML/Graphics.hpp>

class Obstaculo
{

protected:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    float width = 50;
    float height = 50;

public:
    // Construcctor para Obstaculos estaticos
    Obstaculo(sf::Vector2f posicion, sf::Color color, float width, float height, const std::string &rutaImagen)
    {
        this->width = width;
        this->height = height;
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(posicion);
        shape.setFillColor(color);
        // Cargar la imagen desde un archivo
        if (!texture.loadFromFile(rutaImagen))
        {
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(posicion);
        sprite.setTextureRect(sf::IntRect(0, 0, width, height));
    }

    // Destructor
    virtual ~Obstaculo() {}

    // Dibuja el obstaculo en la ventana
    void draw(sf::RenderWindow &window)
    {
        // window.draw(shape);
        window.draw(this->sprite);
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