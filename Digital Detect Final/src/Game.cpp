#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>

using namespace std;

// Constructors / Destructors
Game::Game() {
    initVariables();
    initWindow();
    initTextures();
    initSound();
    initMenu();
    initPlayer();
    initLevel1();
}

Game::~Game() {
    delete window;
}

void Game::initVariables() {
    window = nullptr;
    currentLevel = 1;
    timer = 60.f;
    hasKey = false;
    hasKey2 = false;
    levelCompleted = false;
    gameOver = false;
    timerBoostActive = false;
    horseActive = false;
    corruptActive = false;
    inMenu = true;  // Start in menu
    menuSelection = 0;  // 0 = Play, 2 = Exit
    packetCount = 0;

    gameView.setSize(800.f, 600.f);     // Initialize the view
    gameView.setCenter(400.f, 300.f);
}

void Game::initWindow() {
    videoMode.width = 800;
    videoMode.height = 600;
    window = new sf::RenderWindow(videoMode, "Digital Detective", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
}

void Game::initTextures() {
    // Load assets
    if (!menuBackgroundTexture.loadFromFile("assets/computer.jpg")) {
        cout << "ERROR::GAME::Could not load menu background texture!" << endl;
    }
    if (!menuglitchTexture.loadFromFile("assets/glitch.png")) {
        cout << "ERROR::GAME::Could not load menu glitch texture!" << endl;
    }
    if (!instructionsTexture.loadFromFile("assets/instructions.png")) {
        cout << "ERROR::GAME::Could not load instructions background texture!" << endl;
    }
    if (!glitchTexture.loadFromFile("assets/glitch1.png")) {
        cout << "ERROR::GAME::Could not load glitch background texture!" <<endl;
    }
    if (!detectiveTexture.loadFromFile("assets/player.png")) {
        cout << "ERROR::GAME::Could not load detective texture!" <<endl;
    }
    if (!wallTexture.loadFromFile("assets/wall.png")) {
        cout << "ERROR::GAME::Could not load wall texture!" <<endl;
    }
    if (!wallTexture1.loadFromFile("assets/wall5.png")) {
        cout << "ERROR!! Could not load horse texture" <<endl;      
    }
    if (!exitTexture.loadFromFile("assets/zip.png")) {
        cout << "ERROR!! Could not load zip texture" <<endl;
    }
    if (!keyTexture.loadFromFile("assets/key.png")) {
        cout << "ERROR!! Could not load key texture" <<endl;
    }
    if (!virusTexture1.loadFromFile("assets/virus.png")) {
        cout << "ERROR!! Could not load virus texture " <<endl;
    }
    if (!virusTexture2.loadFromFile("assets/virus2.png")) {
        cout << "ERROR!! Could not load virus2 texture" <<endl;
    }
    if (!virusTexture3.loadFromFile("assets/virus3.png")) {
        cout << "ERROR!! Could not load virus2 texture" <<endl;
    }
    if (!packetTexture.loadFromFile("assets/packet.png")) {
        cout << "ERROR!! Could not load packets texture" << endl;
    }
    if (!backgroundTexture.loadFromFile("assets/binary.png")) {
        cout << "ERROR::GAME::Could not load background binary texture!" <<endl;
    }
    if (!backgroundTexture2.loadFromFile("assets/background.png")) {
        cout << "ERROR::GAME::Could not load glitch background texture!" <<endl;
    }
    if (!timerBoostTexture.loadFromFile("assets/clock1.png")) {
        cout << "ERROR!! Could not load timer boost texture" <<endl;
    }
    if (!horseTexture.loadFromFile("assets/horse.png")) {
        cout << "ERROR!! Could not load horse texture" <<endl;
    }
    if (!corruptTexture.loadFromFile("assets/corrupt.png")) {
        cout << "ERROR!! Could not load corrupt texture" << endl;
    }
    if (!firewallTexture.loadFromFile("assets/firewall.png")) {
        cout << "ERROR!! Could not load horse texture" <<endl;
    }
    if (!deathScreenTexture.loadFromFile("assets/deathScreen.jpg")) {
        cout << "ERROR!! Could not load death screen texture" << endl;
    }
    if (!horseGlitchTexture.loadFromFile("assets/horseGlitch.png")) {
        cout << "ERROR!! Could not load horse glitch texture" << endl;
    }
    if (!heartTexture.loadFromFile("assets/heart.png")) {
        cout << "ERROR!! Could not load heart glitch texture" << endl;
    }
    if (!crashTexture.loadFromFile("assets/crash.png")) {
        cout << "ERROR!! Could not load crash glitch texture" << endl;
    }
    if (!winTexture.loadFromFile("assets/win.png")) {
        cout << "ERROR!! Could not load win texture" << endl;
    }
    if (!gameFont.loadFromFile("assets/font.ttf")) {
        cout << "WARNING::GAME::Could not load font, using system default" <<endl;
    }
}

void Game::initSound() {
    if (!backgroundMusic.openFromFile("assets/music.mp3")) {
        std::cout << "Error loading music.mp3\n";
    }
    else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(30); // adjusting volume of background music.
        backgroundMusic.play();
    }

    // Loading the sound effects
    packetBuffer.loadFromFile("assets/packetcollected.wav");
    packetSound.setBuffer(packetBuffer);

    levelCompleteBuffer.loadFromFile("assets/levelcomplete.wav");
    levelCompleteSound.setBuffer(levelCompleteBuffer);

    gameOverBuffer.loadFromFile("assets/gameover.wav");
    gameOverSound.setBuffer(gameOverBuffer);

    trojanBuffer.loadFromFile("assets/trojan.wav");
    trojanSound.setBuffer(trojanBuffer);

    iloveuBuffer.loadFromFile("assets/iloveu.wav");
    iloveuSound.setBuffer(iloveuBuffer);
}

void Game::initMenu()
{
    menuBackgroundSprite.setTexture(menuBackgroundTexture);
    menuBackgroundSprite.setScale(1.8f, 1.8f); 

    sf::FloatRect menuBounds = menuBackgroundSprite.getGlobalBounds();       //centering the image background in menu
    menuBackgroundSprite.setPosition(
        (window->getSize().x - menuBounds.width) / 2.f,
        (window->getSize().y - menuBounds.height) / 2.f
    );

    menuglitchSprite.setTexture(menuglitchTexture);
    menuglitchSprite.setScale(0.2f, 0.2f); // scale smaller
    sf::FloatRect menuglitchBounds = menuglitchSprite.getGlobalBounds();
    menuglitchSprite.setPosition(
        (window->getSize().x - menuglitchBounds.width) / 2.f,
        (window->getSize().y - menuglitchBounds.height) / 2.f
    ); 

    titleText.setFont(gameFont);                           //setup title of game
    titleText.setString("DIGITAL DETECTIVE");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f,
        2.f
    );

    playText.setFont(gameFont);
    playText.setString("Play");                      //play.
    playText.setCharacterSize(40);
    playText.setPosition(
        window->getSize().x / 2.f - playText.getGlobalBounds().width / 2.f,
        180.f
    );

    instructionsText.setFont(gameFont);
    instructionsText.setString("Instructions");
    instructionsText.setCharacterSize(35);
    instructionsText.setPosition(300.f, 250.f);     

    exitText.setFont(gameFont);
    exitText.setString("Exit");                    //exit.
    exitText.setCharacterSize(40);
    exitText.setPosition(
        window->getSize().x / 2.f - exitText.getGlobalBounds().width / 2.f,
        305.f
    );
}

void Game::initPlayer() {
    playerSprite.setTexture(detectiveTexture);
    playerSprite.setScale(0.6f, 0.6f);      //player scale (size).
    playerSprite.setPosition(50.f, 50.f);       // starting position for player.
}

void Game::initLevel1() {
    // Clear previous level data
    walls.clear();
    viruses.clear();
    virusDirections.clear();
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        (20.0f * 64.0f) / backgroundTexture.getSize().x,
        (15.0f * 64.0f) / backgroundTexture.getSize().y);

    // Reset game state
    hasKey = false;
    levelCompleted = false;
    gameOver = false;
    timer = 60.f;                                           //setting timer to 60 seconds.

    int wallSize = 64;                                      // wall size for maze.

    // Level 1 maze layout: 1 = wall, 0 = path.
    int mazeLayout[15][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1},
        {1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Creating wall sprites. 
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (mazeLayout[i][j] == 1) {                //if index[i][j] = 1 then load wall texture.
                sf::Sprite wallSprite;
                wallSprite.setTexture(wallTexture);
                wallSprite.setScale(                    //set size for wall.
                    wallSize / float(wallTexture.getSize().x),
                    wallSize / float(wallTexture.getSize().y)
                );
                wallSprite.setPosition(j * wallSize, i * wallSize);
                walls.push_back(wallSprite);            //walls is a vector list so every wallSprite/ wall tecture is pushed onto the list.
            }
        }
    }

    key.setTexture(keyTexture);                         //placing key on the maze.
    key.setScale(1.0f, 2.0f);                           //sizing the key according to my preference.
    key.setPosition(18 * wallSize, 13 * wallSize);      //setting a desired position, * 64 can also be done.

    // Set exit position
    exitPos = sf::Vector2f(18 * wallSize, 1 * wallSize);

    //size of exit
    exitSprite.setTexture(exitTexture);                 //loading a zip file image for 'exit'.
    exitSprite.setPosition(exitPos);
    exitSprite.setScale(0.95f, 0.95f);

    //packets
    sf::Sprite p1;                                     //multiple packets are going to be used so multiple sprites are created.
    p1.setTexture(packetTexture);
    p1.setPosition(4 * 64, 5 * 64);
    p1.setScale(1.f, 1.f);
    dataPackets.push_back(p1);                         //adding or pushing p1 onto list dataPackets.

    sf::Sprite p2;
    p2.setTexture(packetTexture);
    p2.setPosition(7 * 64, 9 * 64);
    p2.setScale(1.f, 1.f);
    dataPackets.push_back(p2);

    sf::Sprite p3;
    p3.setTexture(packetTexture);
    p3.setPosition(14 * 64, 11 * 64);
    p3.setScale(1.f, 1.f);
    dataPackets.push_back(p3);

    sf::Sprite p4;
    p4.setTexture(packetTexture);
    p4.setPosition(13 * 64, 1 * 64);
    p4.setScale(1.f, 1.f);
    dataPackets.push_back(p4);

    corruptSprite.setTexture(corruptTexture);          //loading corrupted packets.
    corruptSprite.setPosition(13 * 64, 4 * 64);
    corruptSprite.setScale(1.f, 1.f);

    heartSprite.setTexture(heartTexture);              //effect image for corrupt packet ilu virus.
    heartSprite.setScale(2.f, 2.f);

    crashSprite.setTexture(crashTexture);              //effect image for corrupt packet ilu virus.
    crashSprite.setScale(2.f, 2.f);

    //create virus and set their initial positions and directions.
    sf::Sprite virus1;
    virus1.setTexture(virusTexture1);
    virus1.setScale(0.6f, 0.6f);
    virus1.setPosition(10 * wallSize, 13 * wallSize);   //virus 1- in the bottom corridor
    viruses.push_back(virus1);
    virusDirections.push_back(sf::Vector2f(-2.0f, 0.0f));    //-2 = move left, 0 = dont move up or down.

    sf::Sprite virus2;
    virus2.setTexture(virusTexture2);
    virus2.setScale(0.9f, 0.9f);
    virus2.setPosition(18 * wallSize, 1 * wallSize);         //virus 2 - in upper right corridor
    viruses.push_back(virus2);
    virusDirections.push_back(sf::Vector2f(0.0f, 2.0f));

    sf::Sprite virus3;
    virus3.setTexture(virusTexture3);
    virus3.setScale(1.0f, 1.0f);
    virus3.setPosition(8 * wallSize, 5 * wallSize);
    viruses.push_back(virus3);
    virusDirections.push_back(sf::Vector2f(2.0f, 0.0f));     // Moving right

    deathScreenSprite.setTexture(deathScreenTexture);        //blue screen of death for when game is over.
    deathScreenSprite.setScale(2.f, 2.f);

    instructionsSprite.setTexture(instructionsTexture);     //instruction image
    instructionsSprite.setScale(1.f, 1.f);

    winSprite.setTexture(winTexture);                       //winner image.    
    winSprite.setScale(1.8f, 1.8f);

    glitchSprite.setTexture(glitchTexture);                
    glitchSprite.setScale(1.f, 1.f);
    glitchSprite.setPosition(1 * wallSize, 1 * wallSize);

    saveLoadMessageText.setFont(gameFont);
    saveLoadMessageText.setCharacterSize(40);
    saveLoadMessageText.setFillColor(sf::Color::Green);
    saveLoadMessageText.setPosition(300.f, 10.f); 

    // Set up GUI elements
    timerText.setFont(gameFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);

    levelText.setFont(gameFont);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10.f, 40.f);
    levelText.setString("Level 1: Data Maze");

    objectiveText.setFont(gameFont);
    objectiveText.setCharacterSize(20);
    objectiveText.setFillColor(sf::Color::Yellow);
    objectiveText.setPosition(550.f, 10.f);
    objectiveText.setString("Find the key!");

    packetText.setFont(gameFont);
    packetText.setCharacterSize(22);
    packetText.setFillColor(sf::Color::Cyan);
    packetText.setPosition(650.f, 50.f);                     // top right corner
    packetText.setString("Data: 0");


    // Reset player position
    playerSprite.setPosition(wallSize + 5, wallSize + 5);    //putting the player in a safe starting position. 

    // Reset the view center to the player
    gameView.setCenter(playerSprite.getPosition());          //making game view follow the player using setCenter.
}

void Game::initLevel2() {
    //clear previous level data
    walls.clear();
    viruses.clear();
    virusDirections.clear();

    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setScale(
        (20.0f * 64.0f) / backgroundTexture2.getSize().x,
        (15.0f * 64.0f) / backgroundTexture2.getSize().y);

    //reset gamestate
    hasKey = false;
    hasKey2 = false;                                        //added one more key for level 2.
    levelCompleted = false;
    gameOver = false;
    timerBoostActive = false;                               //added a time boost for level 2.
    timer = 60.f;
    horseActive = false;                                    //new corrupt packet for level 2.
    levelWon = false;


    int wallSize = 64;
    //create walls for maze layout where 1=wall and 0=path
    int mazeLayout[15][20] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
        {1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,1,1,1,1,1},
        {1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
        {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // Create wall sprites based on the layout same as before.
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (mazeLayout[i][j] == 1) {
                sf::Sprite wallSprite1;
                wallSprite1.setTexture(wallTexture1);
                wallSprite1.setScale(
                    wallSize / float(wallTexture1.getSize().x),
                    wallSize / float(wallTexture1.getSize().y)
                );
                wallSprite1.setPosition(j * wallSize, i * wallSize);
                walls.push_back(wallSprite1);
            }
        }
    }

    key.setTexture(keyTexture);                             //placing the first key.
    key.setScale(0.8f, 0.9f);
    key.setPosition(18 * wallSize, 10 * wallSize);

    key2.setTexture(keyTexture);                            // Place the second key
    key2.setScale(0.8f, 0.9f);
    key2.setPosition(1 * wallSize, 13 * wallSize);

    // Place timer boost
    timerBoost.setTexture(timerBoostTexture);
    timerBoost.setScale(0.5f, 0.5f);
    timerBoost.setPosition(3 * wallSize, 6 * wallSize);

    //trojan virus
    horse.setTexture(horseTexture);
    horse.setScale(0.8f, 0.9f);
    horse.setPosition(5 * wallSize, 10 * wallSize);

    horseGlitchSprite.setTexture(horseGlitchTexture);       //glitch when horseActive is true.
    horseGlitchSprite.setScale((20.0f * 64.0f) / backgroundTexture2.getSize().x,
        (15.0f * 64.0f) / backgroundTexture2.getSize().y);

    // Size of firewall exit
    firewallSprite.setTexture(firewallTexture);
    firewallSprite.setPosition(18 * wallSize, 1 * wallSize);
    firewallSprite.setScale(1.2f, 1.2f);

    sf::Sprite p1;                                          //setting up data packets in level 2 too.
    p1.setTexture(packetTexture);
    p1.setPosition(4 * 64, 5 * 64);
    p1.setScale(1.f, 1.f);
    dataPackets.push_back(p1);

    sf::Sprite p2;
    p2.setTexture(packetTexture);
    p2.setPosition(7 * 64, 9 * 64);
    p2.setScale(1.f, 1.f);
    dataPackets.push_back(p2);

    sf::Sprite p3;
    p3.setTexture(packetTexture);
    p3.setPosition(14 * 64, 11 * 64);
    p3.setScale(1.f, 1.f);
    dataPackets.push_back(p3);

    sf::Sprite p4;
    p4.setTexture(packetTexture);
    p4.setPosition(13 * 64, 1 * 64);
    p4.setScale(1.f, 1.f);
    dataPackets.push_back(p4);

    corruptSprite.setTexture(corruptTexture);               //ilu virus in level2.
    corruptSprite.setPosition( 6* 64, 4 * 64);
    corruptSprite.setScale(1.f, 1.f);

    // Create viruses with faster speeds for level 2
    sf::Sprite virus1;                                      // Virus 1 - horizontal patrol
    virus1.setTexture(virusTexture1);
    virus1.setScale(0.8f, 0.8f);
    virus1.setPosition(8 * wallSize, 11 * wallSize);
    viruses.push_back(virus1);
    virusDirections.push_back(sf::Vector2f(3.0f, 0.0f));    // Faster movement

    sf::Sprite virus2;                                      // Virus 2 - vertical patrol
    virus2.setTexture(virusTexture2);
    virus2.setScale(0.8f, 0.8f);
    virus2.setPosition(3 * wallSize, 3 * wallSize);
    viruses.push_back(virus2);
    virusDirections.push_back(sf::Vector2f(0.0f, 3.0f));    // Faster movement

    sf::Sprite virus3;                                      // Virus 3 - guarding the exit
    virus3.setTexture(virusTexture3);
    virus3.setScale(0.8f, 0.8f);                            // Slightly larger
    virus3.setPosition(17 * wallSize, 1 * wallSize);
    viruses.push_back(virus3);
    virusDirections.push_back(sf::Vector2f(0.0f, 2.5f));

    sf::Sprite virus4;                                     // Virus 4 - patrolling bottom corridor
    virus4.setTexture(virusTexture2);
    virus4.setScale(1.0f, 1.0f);
    virus4.setPosition(10 * wallSize, 13 * wallSize);
    viruses.push_back(virus4);
    virusDirections.push_back(sf::Vector2f(-2.5f, 0.0f));

    // Set up GUI elements
    timerText.setFont(gameFont);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);

    levelText.setFont(gameFont);
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(10.f, 40.f);
    levelText.setString("Level 2: Firewall Fortress");

    objectiveText.setFont(gameFont);
    objectiveText.setCharacterSize(20);
    objectiveText.setFillColor(sf::Color::Yellow);
    objectiveText.setPosition(550.f, 10.f);
    objectiveText.setString("Find both keys!");

    playerSprite.setPosition(wallSize + 5, wallSize + 5);   //putting the player in a safe starting position

    gameView.setCenter(playerSprite.getPosition());         //making gameview follow the playing using setCenter.
}

void Game::advanceLevel() {
    currentLevel++;                                         //when advance level is called current level is incremented by 1.

    if (currentLevel == 2) {
        initLevel2();
    }
    else {
        currentLevel = 1;                                   // For now, if we go beyond level 2, loop back to level 1
        initLevel1();
    }
}

void Game::resetGame() {
    currentLevel = 1;                                       //if reset game is called, current level is set to 1.
    initLevel1();                                           //initLevel1 function runs.
 }

void Game::resetLevel() {
    if (currentLevel == 1) {                                //if reset level is called then current level is reset to the same level (runs from the very beggining)
        initLevel1();
    }
    else if (currentLevel == 2) {
        initLevel2();
    }
 }

bool Game::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {       //takes 2 sprite parameters.
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());             //checks if therectangle baounds are overlapping if yes returns true otherwise false.
}

bool Game::checkWallCollisions(sf::Vector2f newPosition) {                        //function to check if a player is touching walls.
    sf::Sprite tempSprite = playerSprite;                                         //temporary copy of player so that real player position isn't affected.
    tempSprite.setPosition(newPosition);                                          //move temp player to new position.

    sf::FloatRect playerBounds = tempSprite.getGlobalBounds();                    //bounding box around temp player.

    // Make hitbox slightly smaller.
    float margin = 0.2f;                                                          //20% smaller.
    playerBounds.left += playerBounds.width * margin;
    playerBounds.top += playerBounds.height * margin;
    playerBounds.width *= (1.0f - 2 * margin);
    playerBounds.height *= (1.0f - 2 * margin);

    // Check for collisions with walls
    for (auto& wall : walls) {                                                  
        if (playerBounds.intersects(wall.getGlobalBounds())) {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

const bool Game::running() const {
    return window->isOpen();
}

const bool Game::getLevelCompleted() const {
    return levelCompleted;
}

void Game::pollEvents() {
    while (window->pollEvent(ev)) {
        switch (ev.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::updateViruses() {
    for (size_t i = 0; i < viruses.size(); ++i) {
        sf::Vector2f newPosition = viruses[i].getPosition() + virusDirections[i];   //to get the new position: gets current position and adds movemnt direction.

        //check for collisions with walls
        sf::Sprite tempSprite = viruses[i];                                         //dont move the real virus yet so we create a temp sprite like in player position.
        tempSprite.setPosition(newPosition);

        bool wallCollision = false;

        for (auto& wall : walls) {
            if (tempSprite.getGlobalBounds().intersects(wall.getGlobalBounds())) {  //check if our temp sprite collides with any of the walls.
                wallCollision = true;                                               //if yes, set wallCollison true.
                break;
            }
        }
        // If collision, reverse direction
        if (wallCollision) {                                                        //if wall collision is true then, 
            virusDirections[i] *= -1.0f;                                            //move the virus to opposite direction.
        }
        else {
            viruses[i].setPosition(newPosition);                                    //if our temp virus didnt bump into walls then move real virus to new position.
        }

        if (checkCollision(playerSprite, viruses[i])) {                             //now check for collison with player.
            gameOver = true;
            gameOverSound.play();
            break;
        }
    }
}

void Game::updateMenu() {
    static bool keyReleased = true;                                                 //static so that keyReleased value is stored even after function ends.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keyReleased) {
        menuSelection = (menuSelection - 1 + 3) % 3;  // Wrap around to bottom
        keyReleased = false;
    }
    // Down arrow key
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keyReleased) {
        menuSelection = (menuSelection + 1) % 3;  // Wrap around to top
        keyReleased = false;
    }
    // Enter key to select
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && keyReleased) {
        switch (menuSelection) {
        case 0:  // Play
            inMenu = false;                                                         //close menu
            resetGame();                                                            //call resetGame and enter level 1.
            break;
        case 1:
            showingInstructions = true;
            break;
        case 2:  // Exit
            window->close();
            break;
        }
        keyReleased = false;
    }
    // Key release detection
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        keyReleased = true;
    }

    playText.setFillColor(menuSelection == 0 ? sf::Color::Yellow : sf::Color::White);   //selected option is colored yellow, unselected option is colored white.
    instructionsText.setFillColor(menuSelection == 1 ? sf::Color::Yellow : sf::Color::White);
    exitText.setFillColor(menuSelection == 2 ? sf::Color::Yellow : sf::Color::White);

}

void Game::updatePlayer() {
    // Movement speed
    float movementSpeed = 5.f;
    sf::Vector2f movement(0.f, 0.f);

    // Keyboard input - directly checking each key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x = -movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x = movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y = -movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y = movementSpeed;
    }

    // Apply movement if non-zero
    if (movement.x != 0.f || movement.y != 0.f) {
        // Calculate new position directly
        sf::Vector2f newPosition = playerSprite.getPosition() + movement;

        // Check if the new position would cause a collision
        if (!checkWallCollisions(newPosition)) {
            // If no collision, move to the new position
            playerSprite.setPosition(newPosition);
        }
        else {
            // Try horizontal movement only
            sf::Vector2f horizontalMove = playerSprite.getPosition();
            horizontalMove.x += movement.x;

            if (!checkWallCollisions(horizontalMove)) {
                playerSprite.setPosition(horizontalMove);
            }

            // Try vertical movement only
            sf::Vector2f verticalMove = playerSprite.getPosition();
            verticalMove.y += movement.y;

            if (!checkWallCollisions(verticalMove)) {
                playerSprite.setPosition(verticalMove);
            }
        }
    }

    // Update view to follow player (camera follows player)
    gameView.setCenter(playerSprite.getPosition());

    // Check for first key collection
    if (!hasKey && checkCollision(playerSprite, key)) {
        hasKey = true;
        if (currentLevel == 2 && !hasKey2) {
            objectiveText.setString("Find the second key!");
        }
        else {
            objectiveText.setString("Find the exit!");
        }
    }

    // Check for second key collection (Level 2)
    if (currentLevel == 2 && !hasKey2 && checkCollision(playerSprite, key2)) {
        hasKey2 = true;
        if (hasKey) {
            objectiveText.setString("Find the exit!");
        }
        else {
            objectiveText.setString("Find the first key!");
        }
    }

    // Check for timer boost (Level 2)
    if (currentLevel == 2 && !timerBoostActive && checkCollision(playerSprite, timerBoost)) {
        timerBoostActive = true;
        timer += 15.0f; // Add 15 seconds to timer
    }

    //check for horse(level 2)
    if (currentLevel == 2 && !horseActive && checkCollision(playerSprite, horse)) {
        trojanSound.play();
        horseActive = true;
        horseClock.restart();
        timer -= 15.0f; // minus 15 seconds to timer
    }

    if (!corruptActive && checkCollision(playerSprite, corruptSprite)) {
        iloveuSound.play();
        corruptActive = true;
        corruptClock.restart();
    }

    for (int i = 0; i < dataPackets.size(); ++i) {
        if (checkCollision(playerSprite, dataPackets[i])) {
            packetSound.play();
            packetCount++;
            packetText.setString("Data: " + std::to_string(packetCount));
            dataPackets.erase(dataPackets.begin() + i);
            break;
        }
    }

    // Check for exit (different conditions for different levels)
    bool canExit = false;
    if (currentLevel == 1 && hasKey) {
        canExit = true;
    }

    if (currentLevel == 2 && hasKey && hasKey2 &&
        playerSprite.getGlobalBounds().intersects(exitSprite.getGlobalBounds())) {
        levelWon = true; 
    }

    // Check for exit (only if has key)
    if (canExit) {
        float exitRadius = 50.0f; // Increased from 32.f
        if (playerSprite.getPosition().x > exitPos.x - exitRadius &&
            playerSprite.getPosition().x < exitPos.x + exitRadius &&
            playerSprite.getPosition().y > exitPos.y - exitRadius &&
            playerSprite.getPosition().y < exitPos.y + exitRadius) {
            levelCompleted = true;
            objectiveText.setString("Level Complete!");
        }
    }
}

void Game::updateTimer() {
    // Decrease timer
    if (rand() % 200 == 0) {  // Roughly once every few seconds
        float shake = 10.0f;
        gameView.move(rand() % int(shake) - shake / 5, rand() % int(shake) - shake / 2);
    }

    timer -= 0.017f; // Approximately one frame at 60fps

    // Update timer text
    stringstream ss;
    ss << "Time: " << static_cast<int>(timer);
    timerText.setString(ss.str());

    // Check if time is up
    if (timer <= 0.f) {
        timer = 0.f;
        resetLevel();
    }
}

void Game::update() {
    pollEvents();

    if (inMenu) {
        updateMenu();
    }
    if (showingInstructions && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
        showingInstructions = false;
    }
    else if (!levelCompleted && !gameOver) {
        updatePlayer();
        updateViruses();
        updateTimer();
    }
    else if (gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {      // Check for space key to restart
            resetGame();
        }
    }
    else if (levelCompleted) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            advanceLevel();
        }
    }
    if (levelWon && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
        saveGame();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
        loadGame();
    }


}

void Game::saveGame() {
    std::ofstream saveFile("save.txt");
    if (saveFile.is_open()) {
        saveFile << currentLevel << "\n";
        saveFile << packetCount << "\n";
        saveFile << playerSprite.getPosition().x << "\n";
        saveFile << playerSprite.getPosition().y << "\n";
        saveFile.close();

        saveLoadMessageText.setString("Game Saved!");
        showSaveMessage = true;
        saveLoadClock.restart();
    }
}

void Game::loadGame() {
    std::ifstream loadFile("save.txt");
    if (loadFile.is_open()) {
        loadFile >> currentLevel;
        loadFile >> packetCount;

        float px, py;
        loadFile >> px;
        loadFile >> py;

        loadFile.close();

        // Load level FIRST
        if (currentLevel == 1) initLevel1();
        else if (currentLevel == 2) initLevel2();

        // THEN update position and score text
        playerSprite.setPosition(px, py);
        packetText.setString("Data: " + std::to_string(packetCount));

        saveLoadMessageText.setString("Game Loaded!");
        showLoadMessage = true;
        saveLoadClock.restart();
    }
}

void Game::renderMenu() {
    window->draw(menuBackgroundSprite);
    window->draw(menuglitchSprite);

    // Draw title and menu options
    window->draw(titleText);
    window->draw(playText);
    window->draw(instructionsText); 
    window->draw(exitText);
}

void Game::renderLevel() {
   // Inside renderLevel()
    if (currentLevel == 1) {
        window->draw(backgroundSprite);     // binary.png for level 1
    }
    else if (currentLevel == 2) {
        window->draw(backgroundSprite2);    // background.png for level 2
    }

    if (rand() % 200 == 0) {
        window->draw(glitchSprite);
    }

    for (auto& wall : walls) {
        window->draw(wall);
    }
    
    for (auto& packet: dataPackets) {
        window->draw(packet);
    }

    // Draw key if not collected
    if (!hasKey) {
        window->draw(key);
    }

    // Draw second key if in level 2 and not collected
    if (currentLevel == 2 && !hasKey2) {
        window->draw(key2);
    }

    // Draw timer boost if in level 2 and not collected
    if (currentLevel == 2 && !timerBoostActive) {
        window->draw(timerBoost);
    }

    //draw horse
    if (currentLevel == 2 && !horseActive) {
        window->draw(horse);
    }
    if (horseActive == 1) {
        window->draw(horseGlitchSprite);
    }

    if (!corruptActive) {
        window->draw(corruptSprite);
    }
    if (corruptActive == 1) {
        window->draw(heartSprite);
        window->draw(crashSprite);

    }

    //draw viruses
    for (auto& virus : viruses) {
        window->draw(virus);
    }

    // Draw player
    window->draw(playerSprite);

    //draw exit zip
    if (currentLevel == 1) {
        window->draw(exitSprite);
    }
    
    //draw exit firewall
    if (currentLevel == 2) {
        window->draw(firewallSprite);
    }
}

void Game::renderGUI() {
    window->draw(timerText);
    window->draw(levelText);
    window->draw(objectiveText);
    window->draw(packetText);
}

void Game::render() {
    window->clear(sf::Color(30, 30, 50)); // Dark blue-ish for digital feel

    if (showingInstructions) {
        window->clear();
        window->draw(instructionsSprite);

        instructionsPageText.setFont(gameFont);
        instructionsPageText.setCharacterSize(24);
        instructionsPageText.setFillColor(sf::Color::Cyan);
        instructionsPageText.setString(
            "                            HOW TO PLAY:\n\n"
            "             - Use arrow keys or WASD to move\n"
            "             - Collect data packets (coins)\n"
            "             - Avoid viruses!\n"
            "             - Collect the key and find the zip file \n                to complete level\n\n\n\n"
            "               Press Backspace to return to menu"
        );
        instructionsPageText.setPosition(100.f, 100.f);

        window->draw(instructionsPageText);
        window->display();
        return;  // skip the rest of render if in instructions
    }

    if (inMenu) {
        // Render menu
        renderMenu();
    }
    else {
        // Set the game view (centered on player)
        window->setView(gameView);

        // Draw level
        renderLevel();

        // Switch to default view for GUI elements
        window->setView(window->getDefaultView());

        // Draw GUI
        renderGUI();

        // If level completed
        if (levelCompleted) {
            window->draw(menuBackgroundSprite);
            levelCompleteSound.play();
            sf::Text completeText;
            completeText.setFont(gameFont);
            completeText.setCharacterSize(30);
            completeText.setFillColor(sf::Color::Green);
            completeText.setString("Level Complete!\nPress Space for \n      next level");
            completeText.setPosition(
                window->getSize().x / 1.8f - completeText.getGlobalBounds().width / 1.8f,
                window->getSize().y / 2.f - completeText.getGlobalBounds().height / 2.f
            );
            window->draw(completeText);
        }

        if (horseActive && horseClock.getElapsedTime().asSeconds() < 2.f) {
            horseText.setFont(gameFont);
            horseText.setCharacterSize(36);
            horseText.setFillColor(sf::Color::Red);
            horseText.setString("TROJAN VIRUS DETECTED!\n -15 SECONDS");
            horseText.setPosition(
                window->getSize().x / 2.2f - horseText.getGlobalBounds().width / 2.2f,
                window->getSize().y / 2.2f - horseText.getGlobalBounds().height / 2.2f
            );
            window->draw(horseText);
        }
        else if (horseActive && horseClock.getElapsedTime().asSeconds() >= 4.f) {
            horseActive = false; // After 2 seconds, disable it
            trojanSound.stop();
        }

        if (corruptActive && corruptClock.getElapsedTime().asSeconds() < 2.f) {
            corruptText.setFont(gameFont);
            corruptText.setCharacterSize(36);
            corruptText.setFillColor(sf::Color::Red);
            corruptText.setString("ILOVEYOU VIRUS DETECTED! \n ILOVEYOU VIRUS DETECTED! \n ILOVEYOU VIRUS DETECTED! \n ILOVEYOU VIRUS DETECTED! \n ");
            corruptText.setPosition(
                window->getSize().x / 2.f - corruptText.getGlobalBounds().width / 2.f,
                window->getSize().y / 2.f - corruptText.getGlobalBounds().height / 2.f
            );
            window->draw(corruptText);   
        }
        else if (corruptActive && corruptClock.getElapsedTime().asSeconds() >= 4.f) {
            corruptActive = false; // After 4 seconds, disable it
        }

        if (levelWon) {
            window->clear();
            window->draw(winSprite);

            sf::Text winText;
            winText.setFont(gameFont);
            winText.setCharacterSize(36);
            winText.setFillColor(sf::Color::Green);
            winText.setString("Press ESC to Exit");

            winText.setPosition(
                window->getSize().x / 2.f - winText.getGlobalBounds().width / 2.f,
                window->getSize().y - 100.f
            );
            window->draw(winText);
            window->display();
            return;
        }

        if (gameOver) {
            window->draw(deathScreenSprite);
            sf::Text gameOverText;
            gameOverText.setFont(gameFont);
            gameOverText.setCharacterSize(36);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("VIRUS DETECTED!\nGame Over\nPress Space to restart");

            gameOverText.setPosition(
                window->getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
                window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f
            );
            window->draw(gameOverText);
        }

        // Show Save/Load Message for 2 seconds
        if (showSaveMessage && saveLoadClock.getElapsedTime().asSeconds() < 2.f) {
            window->draw(saveLoadMessageText);
        }
        else if (showSaveMessage) {
            showSaveMessage = false;
        }

        if (showLoadMessage && saveLoadClock.getElapsedTime().asSeconds() < 2.f) {
            window->draw(saveLoadMessageText);
        }
        else if (showLoadMessage) {
            showLoadMessage = false;
        }

    }

    window->display();
}