#include <SFML/Graphics.hpp>
#include <Jugador.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>
double velocidadJugador = 0.2;
double velocidadObstaculos = 0.15;
int main()

{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Crossy-Road");

    Jugador jugador(sf::Vector2f(400, 500), sf::Color::Blue);

    BandaTransportadora banda1(sf::Vector2f(0, 100), 5, sf::Color::Green, 120, true);
    BandaTransportadora banda2(sf::Vector2f(0, 200), 5, sf::Color::Green, 120, false);
    BandaTransportadora banda3(sf::Vector2f(0, 300), 5, sf::Color::Green, 120, true);
    BandaTransportadora banda4(sf::Vector2f(0, 400), 5, sf::Color::Green, 120, false);

    Obstaculo obstaculo1(sf::Vector2f(300, 500), sf::Color::Magenta);
    std::vector<Obstaculo> obstaculos = {obstaculo1};
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (jugador.senalColision(banda1) || jugador.senalColision(banda2) || jugador.senalColision(banda3) || jugador.senalColision(banda4))
        {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            jugador.move(velocidadJugador * -1, 0, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            jugador.move(velocidadJugador, 0, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            jugador.move(0, velocidadJugador * -1, obstaculos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            jugador.move(0, velocidadJugador, obstaculos);
        }
        window.clear();

        banda1.move(velocidadObstaculos);
        banda1.update();
        banda1.draw(window);
        banda1.reiniciarPosicionesObstaculos();
        banda2.move(velocidadObstaculos);
        banda2.update();
        banda2.draw(window);
        banda2.reiniciarPosicionesObstaculos();
        banda3.move(velocidadObstaculos);
        banda3.update();
        banda3.draw(window);
        banda3.reiniciarPosicionesObstaculos();
        banda4.move(velocidadObstaculos);
        banda4.update();
        banda4.draw(window);
        banda4.reiniciarPosicionesObstaculos();
        obstaculo1.draw(window);
        jugador.draw(window);
        window.display();
    }
    return 0;
}