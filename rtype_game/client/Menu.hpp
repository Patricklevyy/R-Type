#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

class Menu {
    private:
        bool isOpen;
        sf::Font font;
        sf::RectangleShape menuButton;
        sf::Text buttonText;
        std::vector<sf::Text> roomTexts;
        float padding = 10.f;

    public:
        Menu() : isOpen(false)
        {
            // Chargement de la police
            if (!font.loadFromFile("./assets/fonts/ApercuPro.ttf")) {
                // Gérer l'erreur de chargement de la police
                throw std::runtime_error("Unable to load font");
            }

            // Configuration du bouton
            menuButton.setSize(sf::Vector2f(120.f, 40.f));
            menuButton.setPosition(10.f, 10.f);
            menuButton.setFillColor(sf::Color(100, 100, 100));

            // Configuration du texte du bouton
            buttonText.setFont(font);
            buttonText.setString("Menu");
            buttonText.setCharacterSize(20);
            buttonText.setFillColor(sf::Color::White);

            // Centrage du texte dans le bouton
            sf::FloatRect textBounds = buttonText.getLocalBounds();
            buttonText.setPosition(menuButton.getPosition().x
                    + (menuButton.getSize().x - textBounds.width) / 2.f,
                menuButton.getPosition().y
                    + (menuButton.getSize().y - textBounds.height) / 2.f);
        }

        void add_room(const std::string &room_name)
        {
            sf::Text roomText;
            roomText.setFont(font);
            roomText.setString(room_name);
            roomText.setCharacterSize(18);
            roomText.setFillColor(sf::Color::White);

            // Positionnement du texte sous les précédents
            float yPos =
                menuButton.getPosition().y + menuButton.getSize().y + padding;
            if (!roomTexts.empty()) {
                yPos = roomTexts.back().getPosition().y + 30.f;
            }

            roomText.setPosition(menuButton.getPosition().x, yPos);
            roomTexts.push_back(roomText);
        }

        void toggle_menu()
        {
            isOpen = !isOpen;
        }

        bool is_button_clicked(const sf::Vector2i &mousePos)
        {
            return menuButton.getGlobalBounds().contains(
                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }

        void draw(sf::RenderWindow &window)
        {
            // Toujours afficher le bouton
            window.draw(menuButton);
            window.draw(buttonText);

            // Afficher les rooms uniquement si le menu est ouvert
            if (isOpen) {
                for (const auto &roomText : roomTexts) {
                    window.draw(roomText);
                }
            }
        }

        bool get_is_open() const
        {
            return isOpen;
        }
};