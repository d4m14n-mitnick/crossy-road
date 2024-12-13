#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>
#include <vector>
#include <iostream>

class Jugador
{

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f posicionInicial;
    float width = 43;
    float height = 44;
    // Variabes para intercalar los dibujos del spritesheet
    int frameIzquierda = 1;
    int frameDerecha = 1;
    int frameArriba = 1;
    int frameAbajo = 1;

public:
    // Constructor
    Jugador(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(position);
        shape.setFillColor(color);
        this->posicionInicial = position;
        // Cargar la imagen desde un archivo
        if (!texture.loadFromFile("assets/images/mama_lucha.png"))
        {
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position);
        sprite.setTextureRect(sf::IntRect(50, 163, width, height));
    }

    // Destructor
    ~Jugador() {}

    // Regresa al jugador a su posicion original
    void reiniciarPosicion()
    {
        sprite.setPosition(posicionInicial);
        shape.setPosition(posicionInicial);
    }

    // Dibuja a jugador en la ventana
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(this->sprite);
    }

    // Movimiento del jugador tomando en cuenta los obstaculos
    void move(float offsetX, float offsetY, const std::list<Obstaculo> &obstaculos)
    {
        sf::Vector2f posicionOriginal = shape.getPosition();
        this->sprite.setPosition(posicionOriginal);
        shape.move(offsetX, offsetY);

        // Comprobar colisiones con todos los obstaculos
        for (const auto &obstaculo : obstaculos)
        {
            if (obstaculo.detectarColision(shape.getGlobalBounds()))
            {
                shape.setPosition(posicionOriginal);
                break; // Salir del bucle si hay colision
            }
        }
    }

    // Mueve a jugador y cambia las posiciones del spritesheet de acuerdo al teclado del usuario
    void controlarMovimientos(float velocidadJugador, const std::list<Obstaculo> &obstaculos)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (frameIzquierda == 1)
            {
                sprite.setTextureRect(sf::IntRect(53, 222, width, height));
                frameIzquierda = 2;
            }
            else
            {
                sprite.setTextureRect(sf::IntRect(114, 220, width, height));
                frameIzquierda = 1;
            }
            this->move(velocidadJugador * -1, 0, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (frameDerecha == 1)
            {
                sprite.setTextureRect(sf::IntRect(49, 282, width, height));
                frameDerecha = 2;
            }
            else
            {
                sprite.setTextureRect(sf::IntRect(107, 280, width, height));
                frameDerecha = 1;
            }
            this->move(velocidadJugador, 0, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (frameArriba == 1)
            {
                sprite.setTextureRect(sf::IntRect(50, 341, width, height));
                frameArriba = 2;
            }
            else if (frameArriba == 2)
            {
                sprite.setTextureRect(sf::IntRect(44, 112, width, height));
                frameArriba = 3;
            }
            else
            {
                sprite.setTextureRect(sf::IntRect(110, 341, width, height));
                frameArriba = 1;
            }
            this->move(0, velocidadJugador * -1, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (frameAbajo == 1)
            {
                sprite.setTextureRect(sf::IntRect(50, 163, width, height));
                frameAbajo = 2;
            }
            else if (frameAbajo == 2)
            {
                sprite.setTextureRect(sf::IntRect(44, 57, width, height));
                frameAbajo = 3;
            }
            else
            {
                sprite.setTextureRect(sf::IntRect(109, 164, width, height));
                frameAbajo = 1;
            }
            this->move(0, velocidadJugador, obstaculos);
        }
    }

    // Senal de Colisison
    bool detectarColision(const BandaTransportadora &banda)
    {
        if (banda.detectarColision(shape.getGlobalBounds()))
        {
            return true; // Colision detectada con un obstaculo en alguna banda
        }
        return false; // No hay colision
    }

    // Obtiene la posicion del jugador
    const sf::Vector2f &getPosition() const
    {
        return shape.getPosition();
    }

    // sprite.setTextureRect(sf::IntRect(44, 57, width, height)); // sprite 1
    // sprite.setTextureRect(sf::IntRect(44, 112, width, height)); // srpite 2
    // sprite.setTextureRect(sf::IntRect(50, 163, width, height)); // sprite 3
    // sprite.setTextureRect(sf::IntRect(109, 164, width, height)); // sprite 4
    // sprite.setTextureRect(sf::IntRect(53, 222, width, height)); // sprite 5
    // sprite.setTextureRect(sf::IntRect(114, 220, width, height)); // sprite 6
    // sprite.setTextureRect(sf::IntRect(49, 282, width, height)); // sprite 7
    // sprite.setTextureRect(sf::IntRect(107, 280, width, height)); // sprite 8
    // sprite.setTextureRect(sf::IntRect(50, 341, width, height)); // sprite 9
    // sprite.setTextureRect(sf::IntRect(110, 341, width, height)); // sprite 10
};