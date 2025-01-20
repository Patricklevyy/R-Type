#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @file InputScreen.hpp
 * @brief InputScreen class header file.
 */

namespace rtype
{
    /**
     * @brief Represents the input screen in the game.
     * 
     * The InputScreen class handles user input, updates UI elements,
     * and renders the input screen for the game. This screen allows users
     * to input their name or other information before proceeding in the game.
     */
    class InputScreen {
      public:
        /**
         * @brief Constructs a new InputScreen object.
         * 
         * Initializes the input screen and loads necessary assets, like fonts and textures.
         * 
         * @param win A reference to the main render window used for displaying the screen.
         */
        InputScreen(sf::RenderWindow &win);

        /**
         * @brief Destructor for the InputScreen class.
         */
        ~InputScreen() {};

        /**
         * @brief Handles user input events such as keyboard and mouse interactions.
         * 
         * Processes events to capture user input, handle button clicks, or update the input box.
         * 
         * @param event The event object containing details about user input.
         * @param isInputScreen A boolean indicating whether the input screen is active.
         * @param playerName A reference to the string where the player's name will be stored.
         */
        void handleEvent(sf::Event &event, bool &isInputScreen, std::string &playerName);

        /**
         * @brief Updates the visual state of the input screen.
         * 
         * This includes checking for button hover effects and other animations or states.
         */
        void update();

        /**
         * @brief Renders the input screen elements to the window.
         * 
         * This includes drawing the background, text fields, and other UI components.
         */
        void render();

        /**
         * @brief Runs the input screen logic.
         * 
         * This method serves as the main loop for the input screen, managing event handling,
         * updates, and rendering in sequence.
         * 
         * @param isInputScreen A boolean indicating whether the input screen is active.
         * @param playerName A reference to the string where the player's name will be stored.
         */
        void run(bool &isInputScreen, std::string &playerName);

      protected:
      private:
        sf::RenderWindow &_window; ///< Reference to the render window for displaying UI elements.
        sf::Font _font; ///< Font used for the main text on the input screen.
        sf::Font _font_2; ///< Secondary font, used for optional stylized text.

        sf::Text _title; ///< Title displayed on the input screen.
        sf::Sprite _logo; ///< Sprite for the logo displayed on the screen.
        sf::Sprite _backgroundSprite; ///< Background sprite for the input screen.
        sf::RectangleShape _inputBox; ///< Input box where the user types their name or input.
        sf::Text _userInput; ///< Text showing the user input inside the input box.
        sf::Sprite _validateButton; ///< Sprite representing the validate button.

        sf::Texture _logoTexture; ///< Texture for the logo.
        sf::Texture _backgroundTexture; ///< Texture for the background.
        sf::Texture _validateTexture; ///< Texture for the validate button.

        std::string _inputString; ///< String storing the current input from the user.

        bool _isHovering = false; ///< Boolean indicating whether the mouse is hovering over the button.
        bool _isButtonPressed = false; ///< Boolean indicating whether the validate button is pressed.
    };
} // namespace rtype
