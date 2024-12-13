#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <Nivel1.hpp>

bool senalSalirNivel = false;

using namespace std;

// Funcion para comprobar si el mouse esta sobre un texto
bool isMouseOverText(const sf::Text &text, const sf::RenderWindow &window)
{
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main()
{
    // Crear la ventana para todo el juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cruzando la canasta basica");

    // Configuracion Musica
    sf::Music music;
    if (!music.openFromFile("./assets/music/Juhani Junkala [Chiptune Adventures] 4. Stage Select.ogg"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música
    music.play();
    music.setLoop(true);

    // Configurar la fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Oswald-Regular.ttf"))
    {
        cerr << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    // Texturas de los botones
    sf::Texture texturaJugar;
    if (!texturaJugar.loadFromFile("assets/images/buttons.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del boton.");
    }

    sf::Texture texturaNiveles;
    if (!texturaNiveles.loadFromFile("assets/images/buttons.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del boton.");
    }

    sf::Texture texturaSalir;
    if (!texturaSalir.loadFromFile("assets/images/buttons.png"))
    {
        throw std::runtime_error("No se pudo cargar la textura del boton.");
    }

    // Sprites para los botones
    sf::Sprite spriteJugar(texturaJugar);
    sf::Sprite spriteNiveles(texturaNiveles);
    sf::Sprite spriteSalir(texturaSalir);

    // Crear los textos del menu
    sf::Text titulo("Cruzando la canasta basica", font, 50);
    titulo.setPosition(200, 50);
    titulo.setFillColor(sf::Color::White);

    sf::Text jugar("Jugar", font, 30);
    jugar.setPosition(350, 200);
    jugar.setFillColor(sf::Color::White);

    sf::Text niveles("Niveles", font, 30);
    niveles.setPosition(350, 300);
    niveles.setFillColor(sf::Color::White);

    sf::Text salir("Salir", font, 30);
    salir.setPosition(350, 400);
    salir.setFillColor(sf::Color::White);

    // Posicion Sprites
    spriteJugar.setPosition(jugar.getPosition().x - 20, jugar.getPosition().y - 10);
    spriteNiveles.setPosition(niveles.getPosition().x - 20, niveles.getPosition().y - 10);
    spriteSalir.setPosition(salir.getPosition().x - 20, salir.getPosition().y - 10);
    spriteJugar.setTextureRect(sf::IntRect(0, 0, 256, 64));
    spriteNiveles.setTextureRect(sf::IntRect(0, 0, 256, 64));
    spriteSalir.setTextureRect(sf::IntRect(0, 0, 256, 64));

    // Cargar el fondo
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/fondo_verde.png"))
    {
        // Si no se puede cargar la imagen se muestra un error
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    Nivel1 nivel1;

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                // Cambiar el color al pasar el mouse sobre una opcion
                if (isMouseOverText(jugar, window))
                    jugar.setFillColor(sf::Color::Yellow);
                else
                    jugar.setFillColor(sf::Color::White);

                if (isMouseOverText(niveles, window))
                    niveles.setFillColor(sf::Color::Yellow);
                else
                    niveles.setFillColor(sf::Color::White);

                if (isMouseOverText(salir, window))
                    salir.setFillColor(sf::Color::Yellow);
                else
                    salir.setFillColor(sf::Color::White);

                if (isMouseOverText(jugar, window))
                {
                    jugar.setFillColor(sf::Color::Yellow);
                    spriteJugar.setTextureRect(sf::IntRect(0, 64, 256, 64));
                }
                else
                {
                    jugar.setFillColor(sf::Color::White);
                    spriteJugar.setTextureRect(sf::IntRect(0, 0, 256, 64));
                }

                if (isMouseOverText(niveles, window))
                {
                    niveles.setFillColor(sf::Color::Yellow);
                    spriteNiveles.setTextureRect(sf::IntRect(0, 64, 256, 64));
                }
                else
                {
                    niveles.setFillColor(sf::Color::White);
                    spriteNiveles.setTextureRect(sf::IntRect(0, 0, 256, 64));
                }

                if (isMouseOverText(salir, window))
                {
                    salir.setFillColor(sf::Color::Yellow);
                    spriteSalir.setTextureRect(sf::IntRect(0, 64, 256, 64));
                }
                else
                {
                    salir.setFillColor(sf::Color::White);
                    spriteSalir.setTextureRect(sf::IntRect(0, 0, 256, 64));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isMouseOverText(jugar, window))
                    {
                        cout << "Iniciar juego" << endl;
                        // Se ejecuta toda la logica del Nivel 1
                        senalSalirNivel = false;
                        while (senalSalirNivel != true)
                        {
                            music.stop();
                            senalSalirNivel = nivel1.ejecutar(window);
                        }
                        music.play();
                    }
                    else if (isMouseOverText(niveles, window))
                    {
                        cout << "Abrir niveles" << endl;
                        // Mostrar todos los niveles
                    }
                    else if (isMouseOverText(salir, window))
                    {
                        cout << "Salir del juego" << endl;
                        window.close();
                    }
                }
            }
        }

        // Dibujar la ventana
        window.clear();
        window.draw(background);
        window.draw(spriteJugar);
        window.draw(spriteNiveles);
        window.draw(spriteSalir);
        window.draw(titulo);
        window.draw(jugar);
        window.draw(niveles);
        window.draw(salir);
        window.display();
    }

    return 0;
}