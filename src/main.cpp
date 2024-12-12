#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <Nivel1.hpp>

bool senalSalirNivel=false;

using namespace std;

// Funcion para comprobar si el mouse esta sobre un texto
bool isMouseOverText(const sf::Text& text, const sf::RenderWindow& window) {
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main() {
    // Crear la ventana para todo el juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu de Inicio");

    // Configurar la fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Oswald-Regular.ttf")) {
        cerr << "No se pudo cargar la fuente." << endl;
        return -1;
    }

    // Crear los textos del menu
    sf::Text titulo("Menu de Inicio", font, 50);
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

    Nivel1 nivel1;

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
                // Cambiar el color al pasar el mouse sobre una opcion
                if (isMouseOverText(jugar, window)) jugar.setFillColor(sf::Color::Yellow);
                else jugar.setFillColor(sf::Color::White);

                if (isMouseOverText(niveles, window)) niveles.setFillColor(sf::Color::Yellow);
                else niveles.setFillColor(sf::Color::White);

                if (isMouseOverText(salir, window)) salir.setFillColor(sf::Color::Yellow);
                else salir.setFillColor(sf::Color::White);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isMouseOverText(jugar, window)) {
                        cout << "Iniciar juego" << endl;
                        // Se ejecuta toda la logica del Nivel 1
                        senalSalirNivel = false;
                        while(senalSalirNivel != true){
                            senalSalirNivel = nivel1.ejecutar(window);
                        }
                    } else if (isMouseOverText(niveles, window)) {
                        cout << "Abrir niveles" << endl;
                        // Mostrar todos los niveles
                    } else if (isMouseOverText(salir, window)) {
                        cout << "Salir del juego" << endl;
                        window.close();
                    }
                }
            }
        }

        // Dibujar la ventana
        window.clear();
        window.draw(titulo);
        window.draw(jugar);
        window.draw(niveles);
        window.draw(salir);
        window.display();
    }

    return 0;
}