
#include <SFML/Graphics.hpp>
#include <iostream>

namespace rtype
{
    /**
     * @class InputScreen
     * @brief Manages user inputs and interactions within a specific screen.
     */
    class InputScreen {
      public:
        /**
         * @brief Constructor for the InputScreen class.
         * @param win win The window in which inputs are handled.
         */
        InputScreen(sf::RenderWindow &win);

        /**
         * @brief Destructor for the InputScreen class.
         */
        ~InputScreen() {};

        /**
         * @brief  Handles user input events.
         * @param event Representing the current input event to be processed.
         * @param isInputScreen A boolean reference that indicates whether the input screen is active.
         * @param playerName A reference representing the player's name.
         */
        void handleEvent(sf::Event &event, bool &isInputScreen, std::string &playerName);

        /**
         * @brief Updates the game state based on the processed inputs.
         */
        void update();

        /**
         * @brief Renders the current state of the input screen.
         */
        void render();

        /**
         * @brief Runs the input screen loop.
         * @param isInputScreen A boolean reference that indicates whether the input screen is active.
         * @param playerName A reference representing the player's name.
         */
        void run(bool &isInputScreen, std::string &playerName);


      protected:
      private:
        sf::RenderWindow &_window;
        sf::Font _font;
        sf::Font _font_2;

        sf::Text _title;
        sf::Sprite _logo;
        sf::Sprite _backgroundSprite;
        sf::RectangleShape _inputBox;
        sf::Text _userInput;
        sf::Sprite _validateButton;

        sf::Texture _logoTexture;
        sf::Texture _backgroundTexture;
        sf::Texture _validateTexture;

        std::string _inputString;

        bool _isHovering = false;
        bool _isButtonPressed = false;
    };
} // namespace rtype

