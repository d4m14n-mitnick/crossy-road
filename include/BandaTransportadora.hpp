#pragma once
#include <SFML/Graphics.hpp>
#include <ObstaculoMovil.hpp>
#include <list>
#include <iostream>

class BandaTransportadora
{

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 6; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;
    float width = 800;
    float height = 50;
    std::list<ObstaculoMovil> obstaculos;

public:
    // Constructor
    BandaTransportadora(sf::Vector2f posicion, int noObstaculos, sf::Color colorObstaculos, float width, float height, float separacionObstaculos, bool sentido, const std::string &rutaImagen)
    {
        sf::Vector2f posicionBanda = posicion;
        // Se crean los obstaculos y se agregan a una lista
        for (size_t i = 0; i < noObstaculos; i++)
        {
            this->obstaculos.emplace_back(posicion, colorObstaculos, width, height, 800, sentido, rutaImagen);
            posicion.x = posicion.x + separacionObstaculos + 50;
        }
        // Caracteristicas para la propia banda transportadora
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(posicionBanda);
        shape.setFillColor(sf::Color::Red);
        // Cargar la imagen desde un archivo
        if (!texture.loadFromFile("assets/images/bandeja_transportadora.jpg"))
        {
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(posicionBanda);
    }

    // Destructor
    virtual ~BandaTransportadora() {}

    // Dibuja la banda transportadora y sus elementos en la ventana
    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(this->sprite);
        // Bucle para dibujar los obstaculos
        for (auto &i : obstaculos)
        {
            i.draw(window);
        }
    }

    // Movimiento de los obstaculos
    void move(float offsetX)
    {
        for (auto &i : obstaculos)
        {
            i.move(offsetX);
        }
    }

    void update()
    {
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect((currentFrame * 64), 133, width, height));
            clock.restart();
        }
    }

    void reiniciarPosicionesObstaculos()
    {
        for (auto &i : obstaculos)
        {
            i.reiniciarPosicion();
        }
    }

    // Metodo para detectar cuando jugador colisione con alguno de los obstaculos
    bool detectarColision(const sf::FloatRect &jugadorBounds) const
    {
        for (const auto &obstaculo : obstaculos)
        {
            if (jugadorBounds.intersects(obstaculo.getBounds()))
            {
                return true; // Colision detectada con un obstáculo
            }
        }
        return false; // No hay colision
    }
};