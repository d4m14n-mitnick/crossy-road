#include <SFML/Graphics.hpp>
#include <Jugador.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>
#include <VentanaPerdedor.hpp>
#include <VentanaGanador.hpp>
#include <string>
#include <iostream>


class Nivel1 {
private:
    double velocidadJugador = 0.2;
    double velocidadObstaculos = 0.15;
    int width = 800;
    int height = 600;
    bool senalColisionBanda;
    bool senalSalir;

public:
    bool ejecutar(sf::RenderWindow& window){

        Jugador jugador(sf::Vector2f(400,500), sf::Color::Blue);

        BandaTransportadora banda1(sf::Vector2f(0,100),5,sf::Color::Green,120,true);
        BandaTransportadora banda2(sf::Vector2f(0,200),5,sf::Color::Green,120,false);
        BandaTransportadora banda3(sf::Vector2f(0,300),5,sf::Color::Green,120,true);
        BandaTransportadora banda4(sf::Vector2f(0,400),5,sf::Color::Green,120,false);

        Obstaculo obstaculo1(sf::Vector2f(300,500),sf::Color::Magenta);

        float posicionPared = 0;

        std::vector<Obstaculo> obstaculos = {obstaculo1};

        for (size_t i = 0; i < width/50; i++){
            obstaculos.emplace_back(sf::Vector2f(posicionPared,0-25),sf::Color::Magenta);
            obstaculos.emplace_back(sf::Vector2f(posicionPared,550+25),sf::Color::Magenta);
            posicionPared = posicionPared+50;
        }

        posicionPared = 0;

        for (size_t i = 0; i < height/50; i++){
            obstaculos.emplace_back(sf::Vector2f(0-25,posicionPared),sf::Color::Magenta);
            obstaculos.emplace_back(sf::Vector2f(750+25,posicionPared),sf::Color::Magenta);
            posicionPared = posicionPared+50;
        }

        VentanaPerdedor ventanaPerdedor;
        VentanaGanador ventanaGanador;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            /* Si jugador colisiona con obstaculos de las bandas transportadoras 
            se ejecuta la logica para el menu de ventana perdedor */
            if (jugador.detectarColision(banda1)||jugador.detectarColision(banda2)||
                jugador.detectarColision(banda3)||jugador.detectarColision(banda4)){
                senalSalir = false;
                senalSalir = ventanaPerdedor.ejecutar(window);
                
                // Si jugador elige salir, regresa al menu principal
                if (senalSalir==true){
                    return senalSalir;
                }
                /* Si jugador eleige volver a intentar, simplemente
                 se mueve el juagador a la posicion original al iniciar el juego */
                else if (senalSalir == false) {
                    jugador.reiniciarPosicion();
                }
            }

            if (jugador.getPosition().y <= 26){
                std::cout<<"Ganaste"<<std::endl;
                senalSalir = false;
                senalSalir = ventanaGanador.ejecutar(window);
                
                // Si jugador elige salir, regresa al menu principal
                if (senalSalir==true){
                    return senalSalir;
                }
                /* Si jugador eleige volver a intentar, simplemente
                 se mueve el juagador a la posicion original al iniciar el juego */
                else if (senalSalir == false) {
                    jugador.reiniciarPosicion();
                }
            }

            // Movimiento para jugador
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                jugador.move(velocidadJugador * -1, 0, obstaculos);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                jugador.move(velocidadJugador, 0, obstaculos);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                jugador.move(0, velocidadJugador * -1, obstaculos);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                jugador.move(0, velocidadJugador, obstaculos);
            }

            // Se dibuja la ventana y los demas componentes

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

            for (auto& i : obstaculos) {
                i.draw(window);
            }

            obstaculo1.draw(window);
            jugador.draw(window);
            window.display();
        }
        return true;
    }
};