#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>


class Jugador {
    
private:
    sf::RectangleShape shape;
    float width = 50;
    float height = 50;
    
public:
    // Constructor
    Jugador(sf::Vector2f position, sf::Color color) {
        shape.setSize(sf::Vector2f(width,height));
        shape.setPosition(position);
        shape.setFillColor(color);
    }
    
    // Destructor
    ~Jugador(){}
    
    // Dibuja a jugador en la ventana
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    
    // Movimiento del jugador
    void move(float offsetX, float offsetY) {
        shape.move(offsetX, offsetY);
    }
};