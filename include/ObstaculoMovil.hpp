#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.hpp>


class ObstaculoMovil : public Obstaculo{

private:
    float limitePosicion;
    float posicionInicial;
    bool sentido;

public:
    // Constructor para Obstaculos en movimiento
    ObstaculoMovil(sf::Vector2f posicion, sf::Color color, float limitePosicion, bool sentido) : Obstaculo(posicion,color) {
        this->posicionInicial = posicion.x;
        this->limitePosicion = limitePosicion;
        this->sentido = sentido;
    }

    // Destructor
    ~ObstaculoMovil(){}

    // Movimiento del obstaculo en eje X
    void move(float offsetX) {
        if(sentido==true){
            shape.move(offsetX,0);
        }
        if(sentido==false){
            shape.move(-offsetX,0);
        }
    }

    // Efecto para tener infinitos objetos en moviento
    void reiniciarPosicion(){
        if(sentido==true){
            if(shape.getPosition().x >= limitePosicion){
                shape.setPosition(-width,shape.getPosition().y);
            }
        }
        if(sentido==false){
            if(shape.getPosition().x <= -width){
                shape.setPosition(limitePosicion,shape.getPosition().y);
            }
        }
    }
};