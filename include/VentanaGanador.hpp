#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Jugador.hpp>
#include <iostream>

using namespace std;

class VentanaGanador {
private:
    bool isMouseOverText(const sf::Text& text, const sf::RenderWindow& window) {
        sf::FloatRect textBounds = text.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
    
public:
    bool ejecutar(sf::RenderWindow& window){

        sf::Font font;
        if (!font.loadFromFile("assets/fonts/Oswald-Regular.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente.");
        }

        sf::Text textoGanaste("Felicidades Ganaste!", font, 50);
        textoGanaste.setFillColor(sf::Color::Green);
        textoGanaste.setPosition(250, 200);

        sf::Text textoReintentar("Volver a jugar", font, 30);
        textoReintentar.setFillColor(sf::Color::White);
        textoReintentar.setPosition(320, 300);

        sf::Text textoMenu("Regresar al menu", font, 30);
        textoMenu.setFillColor(sf::Color::White);
        textoMenu.setPosition(280, 400);


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                // Cambiar el color al pasar el mouse sobre una opcion
                if (isMouseOverText(textoReintentar, window)) textoReintentar.setFillColor(sf::Color::Yellow);
                else textoReintentar.setFillColor(sf::Color::White);

                if (isMouseOverText(textoMenu, window)) textoMenu.setFillColor(sf::Color::Yellow);
                else textoMenu.setFillColor(sf::Color::White);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Si se presiona Reintentar retorna false
                    if (isMouseOverText(textoReintentar, window)) {
                        cout << "Reintentar" << endl;
                        return false;
                    // Si se presiona Menu retorna true
                    } else if (isMouseOverText(textoMenu, window)) {
                        cout << "Regresar" << endl;
                        return true;
                    }
                }
            }
            window.clear();
            window.draw(textoGanaste);
            window.draw(textoReintentar);
            window.draw(textoMenu);
            window.display();
        }
        return false;
    }
};