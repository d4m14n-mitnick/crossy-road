#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>
#include <vector>
#include <iostream>


class Jugador {
    
private:
    sf::RectangleShape shape;
    sf::Vector2f posicionInicial;
    float width = 50;
    float height = 50;
    
public:
    // Constructor
    Jugador(sf::Vector2f position, sf::Color color) {
        shape.setSize(sf::Vector2f(width,height));
        shape.setPosition(position);
        shape.setFillColor(color);
        this->posicionInicial=position;
    }
    
    // Destructor
    ~Jugador(){}

    // Regresa al jugador a su posicion original
    void reiniciarPosicion(){
        shape.setPosition(posicionInicial);
    }
    
    // Dibuja a jugador en la ventana
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    
    // Movimiento del jugador tomando en cuenta los obstaculos
    void move(float offsetX, float offsetY, const std::vector<Obstaculo>& obstaculos) {
        sf::Vector2f posicionOriginal = shape.getPosition();
        shape.move(offsetX, offsetY);
        
        // Comprobar colisiones con todos los obstaculos
        for (const auto& obstaculo : obstaculos) {
            if (obstaculo.detectarColision(shape.getGlobalBounds())) {
                shape.setPosition(posicionOriginal);
                break; // Salir del bucle si hay colision
            }
        }
    }

    // Senal de Colisison
    bool detectarColision(const BandaTransportadora& banda) {
        if (banda.detectarColision(shape.getGlobalBounds())) {
            return true; // Colision detectada con un obstaculo en alguna banda
        }
        return false; // No hay colision
    }

    // Obtiene la posicion del jugador
    const sf::Vector2f& getPosition() const {
        return shape.getPosition();
    }
};