#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Jugador.hpp>
#include <iostream>

using namespace std;

class VentanaPerdedor
{
private:
    bool isMouseOverText(const sf::Text &text, const sf::RenderWindow &window)
    {
        sf::FloatRect textBounds = text.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }

public:
    bool ejecutar(sf::RenderWindow &window)
    {

        // Fuente
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/Oswald-Regular.ttf"))
        {
            throw std::runtime_error("No se pudo cargar la fuente.");
        }

        // Texturas de los botones
        sf::Texture texturaReintentar;
        if (!texturaReintentar.loadFromFile("assets/images/buttons.png"))
        {
            throw std::runtime_error("No se pudo cargar la textura del boton.");
        }

        sf::Texture texturaMenu;
        if (!texturaMenu.loadFromFile("assets/images/buttons.png"))
        {
            throw std::runtime_error("No se pudo cargar la textura del boton.");
        }

        // Sprites para los botones
        sf::Sprite spriteReintentar(texturaReintentar);
        sf::Sprite spriteMenu(texturaMenu);

        // Textos
        sf::Text textoPerdiste("Perdiste!", font, 50);
        textoPerdiste.setFillColor(sf::Color::Red);
        textoPerdiste.setPosition(300, 200);

        sf::Text textoReintentar("Reintentar", font, 30);
        textoReintentar.setFillColor(sf::Color::White);
        textoReintentar.setPosition(280, 300);

        sf::Text textoMenu("Regresar al menu", font, 30);
        textoMenu.setFillColor(sf::Color::White);
        textoMenu.setPosition(280, 400);

        // Posicion Sprites
        spriteReintentar.setPosition(textoReintentar.getPosition().x - 20, textoReintentar.getPosition().y - 10);
        spriteMenu.setPosition(textoMenu.getPosition().x - 20, textoMenu.getPosition().y - 10);
        spriteReintentar.setTextureRect(sf::IntRect(0, 0, 256, 64));
        spriteMenu.setTextureRect(sf::IntRect(0, 0, 256, 64));

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

            if (event.type == sf::Event::MouseMoved)
            {
                // Cambiar el color al pasar el mouse sobre una opcion
                if (isMouseOverText(textoReintentar, window))
                {
                    textoReintentar.setFillColor(sf::Color::Yellow);
                    spriteReintentar.setTextureRect(sf::IntRect(0, 64, 256, 64));
                }
                else
                {
                    textoReintentar.setFillColor(sf::Color::White);
                    spriteReintentar.setTextureRect(sf::IntRect(0, 0, 256, 64));
                }

                if (isMouseOverText(textoMenu, window))
                {
                    textoMenu.setFillColor(sf::Color::Yellow);
                    spriteMenu.setTextureRect(sf::IntRect(0, 64, 256, 64));
                }
                else
                {
                    textoMenu.setFillColor(sf::Color::White);
                    spriteMenu.setTextureRect(sf::IntRect(0, 0, 256, 64));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Si se presiona Reintentar retorna false
                    if (isMouseOverText(textoReintentar, window))
                    {
                        cout << "Reintentar" << endl;
                        return false;
                        // Si se presiona Menu retorna true
                    }
                    else if (isMouseOverText(textoMenu, window))
                    {
                        cout << "Regresar" << endl;
                        return true;
                    }
                }
            }
            window.clear();
            window.draw(spriteReintentar);
            window.draw(spriteMenu);
            window.draw(textoPerdiste);
            window.draw(textoReintentar);
            window.draw(textoMenu);
            window.display();
        }
        return false;
    }
};