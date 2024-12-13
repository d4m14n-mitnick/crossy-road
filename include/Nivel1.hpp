#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Jugador.hpp>
#include <Obstaculo.hpp>
#include <BandaTransportadora.hpp>
#include <VentanaPerdedor.hpp>
#include <VentanaGanador.hpp>
#include <string>
#include <iostream>

class Nivel1
{
private:
    double velocidadJugador = 0.2;
    double velocidadObstaculos = 0.15;
    int width = 800;
    int height = 600;
    bool senalColisionBanda;
    bool senalSalir;

public:
    bool ejecutar(sf::RenderWindow &window)
    {

        Jugador jugador(sf::Vector2f(400, 500), sf::Color::Transparent);

        // Configuracion Musica
        sf::Music music;
        if (!music.openFromFile("./assets/music/Juhani Junkala [Chiptune Adventures] 1. Stage 1.ogg"))
        {
            // Error al cargar el archivo de música
            return -1;
        }

        // Reproducir la música
        music.play();
        music.setLoop(true);

        BandaTransportadora banda1(sf::Vector2f(0, 100), 5, sf::Color::Green, 37, 50, 120, true, "assets/images/canasta/corn flakes.png");
        BandaTransportadora banda2(sf::Vector2f(0, 200), 5, sf::Color::Green, 17, 50, 120, false, "assets/images/canasta/pure de tomate.png");
        BandaTransportadora banda3(sf::Vector2f(0, 300), 5, sf::Color::Green, 19, 49, 120, true, "assets/images/canasta/leche.png");
        BandaTransportadora banda4(sf::Vector2f(0, 400), 5, sf::Color::Green, 76, 50, 120, false, "assets/images/canasta/frijol negro.png");

        Obstaculo obstaculo1(sf::Vector2f(200, 150), sf::Color::Magenta, 46, 50, "assets/images/carro.png");
        Obstaculo obstaculo2(sf::Vector2f(280, 250), sf::Color::Magenta, 46, 50, "assets/images/carro.png");
        Obstaculo obstaculo3(sf::Vector2f(490, 250), sf::Color::Magenta, 46, 50, "assets/images/carro.png");
        Obstaculo obstaculo4(sf::Vector2f(400, 350), sf::Color::Magenta, 46, 50, "assets/images/carro.png");
        Obstaculo obstaculo5(sf::Vector2f(290, 450), sf::Color::Magenta, 46, 50, "assets/images/carro.png");
        std::list<Obstaculo> obstaculos{obstaculo1, obstaculo2, obstaculo3, obstaculo4, obstaculo5};

        float posicionPared = 0;

        for (size_t i = 0; i < width / 50; i++)
        {
            obstaculos.emplace_back(sf::Vector2f(posicionPared, 0), sf::Color::Magenta, 50, 35, "assets/images/estante.png");
            obstaculos.emplace_back(sf::Vector2f(posicionPared, 550 + 25), sf::Color::Magenta, 50, 50, "assets/images/wall50x50.png");
            posicionPared = posicionPared + 50;
        }

        posicionPared = 0;

        for (size_t i = 0; i < height / 50; i++)
        {
            obstaculos.emplace_back(sf::Vector2f(0 - 25, posicionPared), sf::Color::Magenta, 50, 50, "assets/images/wall50x50.png");
            obstaculos.emplace_back(sf::Vector2f(750 + 25, posicionPared), sf::Color::Magenta, 50, 50, "assets/images/wall50x50.png");
            posicionPared = posicionPared + 50;
        }

        // Cargar el fondo
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/images/FloorTileAmbientOcclusion.png"))
        {
            // Si no se puede cargar la imagen se muestra un error
            return -1;
        }
        sf::Sprite background(backgroundTexture);

        VentanaPerdedor ventanaPerdedor;
        VentanaGanador ventanaGanador;

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

            /* Si jugador colisiona con obstaculos de las bandas transportadoras
            se ejecuta la logica para el menu de ventana perdedor */
            if (jugador.detectarColision(banda1) || jugador.detectarColision(banda2) ||
                jugador.detectarColision(banda3) || jugador.detectarColision(banda4))
            {
                senalSalir = false;
                senalSalir = ventanaPerdedor.ejecutar(window);

                // Si jugador elige salir, regresa al menu principal
                if (senalSalir == true)
                {
                    music.stop();
                    return senalSalir;
                }
                /* Si jugador eleige volver a intentar, simplemente
                 se mueve el juagador a la posicion original al iniciar el juego */
                else if (senalSalir == false)
                {
                    jugador.reiniciarPosicion();
                }
            }

            if (jugador.getPosition().y <= 36)
            {
                std::cout << "Ganaste" << std::endl;
                senalSalir = false;
                senalSalir = ventanaGanador.ejecutar(window);

                // Si jugador elige salir, regresa al menu principal
                if (senalSalir == true)
                {
                    return senalSalir;
                }
                /* Si jugador eleige volver a intentar, simplemente
                 se mueve el juagador a la posicion original al iniciar el juego */
                else if (senalSalir == false)
                {
                    jugador.reiniciarPosicion();
                }
            }

            // Movimiento para jugador
            jugador.controlarMovimientos(velocidadJugador, obstaculos);

            // Se dibuja la ventana y los demas componentes

            window.clear();
            window.draw(background);

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

            for (auto &i : obstaculos)
            {
                i.draw(window);
            }

            jugador.draw(window);
            window.display();
        }
        return true;
    }
};