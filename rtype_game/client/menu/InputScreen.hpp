
#include <SFML/Graphics.hpp>
#include <iostream>

namespace rtype
{
    class InputScreen {
      public:
        InputScreen(sf::RenderWindow &win);
        ~InputScreen() {};
        void handleEvent(sf::Event &event, bool &isRunning, std::string &playerName);
        void update();
        void render();
        void run(bool &isRunning, std::string &playerName);


      protected:
      private:
        sf::RenderWindow &_window;
        sf::Font _font;
        sf::Font _font_2;

        sf::Text _title;
        sf::Sprite _logo;
        sf::RectangleShape _inputBox;
        sf::Text _userInput;
        sf::Sprite _validateButton;

        sf::Texture _logoTexture;
        sf::Texture _validateTexture;

        std::string _inputString;

        bool _isHovering = false;
        bool _isButtonPressed = false;
    };
} // namespace rtype

