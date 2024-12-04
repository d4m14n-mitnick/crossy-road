#include <SFML/Graphics.hpp>
#include <Jugador.hpp>
#include <BandaTransportadora.hpp>

double velocidadJugador = 0.2;
double velocidadObstaculos = 0.15;

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Crossy-Road");
    
    Jugador jugador(sf::Vector2f(400,500), sf::Color::Blue);
    
    BandaTransportadora banda1(sf::Vector2f(0,100),5,sf::Color::Green,120,true);
    BandaTransportadora banda2(sf::Vector2f(0,200),5,sf::Color::Green,120,false);
    BandaTransportadora banda3(sf::Vector2f(0,300),5,sf::Color::Green,120,true);
    BandaTransportadora banda4(sf::Vector2f(0,400),5,sf::Color::Green,120,false);
    std::vector<BandaTransportadora> bandas = {banda1, banda2, banda3, banda4};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            jugador.move(velocidadJugador * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            jugador.move(velocidadJugador, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            jugador.move(0, velocidadJugador * -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            jugador.move(0, velocidadJugador);
        }

        window.clear();

        for (auto& banda : bandas) {
            banda.move(velocidadObstaculos);
            banda.update();
            banda.draw(window);
            banda.reiniciarPosicionesObstaculos();
        }
        
        jugador.draw(window);
        window.display();
    }
    return 0;
}