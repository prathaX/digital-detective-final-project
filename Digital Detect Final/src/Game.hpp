#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Game {
private:

private:
    // Other private variables...
    /* sf::View gameView; */
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::View gameView;
    sf::Clock horseClock;
    sf::Clock corruptClock;

    // Menu variables
    bool inMenu;
    bool showingInstructions = false;
    int menuSelection;
    sf::Texture menuBackgroundTexture;
    sf::Sprite menuBackgroundSprite;
    sf::Texture menuglitchTexture;
    sf::Sprite menuglitchSprite;
    sf::Texture glitchTexture;
    sf::Sprite glitchSprite;
    sf::Text titleText;
    sf::Text instructionsPageText;
    sf::Text playText;
    sf::Text instructionsText;
    sf::Text exitText;

    // Resources
    sf::Texture detectiveTexture;
    sf::Texture wallTexture;
    sf::Texture keyTexture;
    sf::Texture exitTexture;
    sf::Texture virusTexture1;
    sf::Texture virusTexture2;
    sf::Texture virusTexture3;
    sf::Texture backgroundTexture;
    sf::Texture backgroundTexture2;
    sf::Texture timerBoostTexture;
    sf::Texture horseTexture;
    sf::Texture firewallTexture;
    sf::Texture wallTexture1;
    sf::Texture deathScreenTexture;
    sf::Texture horseGlitchTexture;
    sf::Texture packetTexture;
    sf::Texture corruptTexture;
    sf::Texture heartTexture;
    sf::Texture crashTexture;
    sf::Texture instructionsTexture;
    sf::Texture winTexture;
    sf::Font gameFont;

    // Game objects
    sf::Sprite playerSprite;
    std::vector<sf::Sprite> walls;
    sf::Sprite key;
    sf::Sprite key2;
    sf::Sprite exitSprite;
    std::vector<sf::Sprite> viruses;  // Added for viruses
    std::vector<sf::Vector2f> virusDirections;  // '2f' because it stores X and Y movement.
    std::vector<sf::Sprite> dataPackets;

    sf::Sprite backgroundSprite;
    sf::Sprite backgroundSprite2;
    sf::Sprite timerBoost;
    sf::Sprite horse;
    sf::Sprite firewallSprite;
    sf::Sprite deathScreenSprite;
    sf::Sprite horseGlitchSprite;
    sf::Sprite corruptSprite;
    sf::Sprite heartSprite;
    sf::Sprite crashSprite;
    sf::Sprite instructionsSprite;
    sf::Sprite winSprite;

    sf::Text timerText;
    sf::Text levelText;
    sf::Text objectiveText;
    sf::Text packetText;
    sf::Text horseText;
    sf::Text corruptText;

    sf::Music backgroundMusic;

    sf::SoundBuffer packetBuffer;
    sf::Sound packetSound;

    sf::SoundBuffer levelCompleteBuffer;
    sf::Sound levelCompleteSound;

    sf::SoundBuffer trojanBuffer;
    sf::Sound trojanSound;

    sf::SoundBuffer iloveuBuffer;
    sf::Sound iloveuSound;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;


    // Game logic
    int currentLevel;
    int packetCount;
    float timer;
    bool hasKey;
    bool hasKey2;
    bool levelCompleted;
    bool gameOver;
    bool timerBoostActive;
    bool horseActive;
    bool packetActive;
    bool corruptActive;
    bool corruptActive1;
    bool levelWon;
    sf::Vector2f exitPos;

    // Private functions
    void initMenu();
    void updateMenu();
    void renderMenu();

    void initVariables();
    void initWindow();
    void initTextures();
    void initSound();
    void initPlayer();
    void initLevel1();
    void initLevel2();
    void resetLevel();
    void resetGame();
    void saveGame();
    void loadGame();

    sf::Text saveLoadMessageText;
    sf::Clock saveLoadClock;
    bool showSaveMessage = false;
    bool showLoadMessage = false;

    bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    bool checkWallCollisions(sf::Vector2f newPosition);

    void advanceLevel();

public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;
    const bool getLevelCompleted() const;

    // Functions
    void pollEvents();
    void updatePlayer();
    void updateViruses();
    void updateTimer();
    void update();
    void renderLevel();
    void renderGUI();
    void render();

};
