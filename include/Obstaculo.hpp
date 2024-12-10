#pragma once
#include <SFML/Graphics.hpp>


class Obstaculo {

protected:
    sf::RectangleShape shape;
    float width = 50;
    float height = 50;

public:
    // Constructor para Obstaculos estaticos
    Obstaculo(sf::Vector2f posicion, sf::Color color){
        shape.setSize(sf::Vector2f(width,height));
        shape.setPosition(posicion);
        shape.setFillColor(color);
    }

    // Destructor
    ~Obstaculo(){}

    // Dibuja el obstaculo en la ventana
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    // Metodo para detectar cuando jugador colisione con obstaculo
    bool detectarColision(const sf::FloatRect& jugadorBounds) const {
        if (jugadorBounds.intersects(shape.getGlobalBounds())) {
            return true; // Colisión detectada
        }
        return false; // No hay colisión
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    const sf::Vector2f& getPosition() const {
        return shape.getPosition();
    }

};