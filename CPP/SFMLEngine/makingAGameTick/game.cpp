#ifndef GAME_CPP
#define GAME_CPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "./Classes/Other/resources.hpp"
#include "./Classes/Other/world.hpp"
#include "./Classes/SceneNodeDerrivatives/SceneNode.hpp"
#include "./Classes/SceneNodeDerrivatives/SpriteNode.hpp"
#include "./Classes/SceneNodeDerrivatives/entity.hpp"
#include "./Classes/SceneNodeDerrivatives/aircraft.hpp"
#include "basic.cpp"





class Game : private sf::NonCopyable
{
  public:
    Game(); // Sets up player radius, position and fill color
    void run(); // runs the processEvents, update and render methods

  private:
    void processEvents(); // playerInput, mainLoop
    void update(sf::Time deltaTime); // code that updates the game
    void render(); // code that renders the game
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    bool mIsMovingUp = false;
    bool mIsMovingRight = false;
    bool mIsMovingLeft = false;
    bool mIsMovingDown = false;
  private:
    sf::RenderWindow mWindow;
    TextureHolder mTexture;
    sf::Sprite mPlayer;
    World mWorld;
};

Game::Game()
: mWindow(sf::VideoMode(640, 480), "World", sf::Style::Close)
, mWorld(mWindow)
/* , mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
*/
{
	/* mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
  */
}


// Resposible for managing game loop - fetching input form the window system, updating the world, and ordering the rendering of the game
void Game::run()
{
  /* Other useful frame rate related tecnhiques:
  sf::sleep - interrupts the execution for a given time, not very accurate
  sf::RenderWindow::setFramerateLimit() - tries to achieve the frame rate by calling sf::sleep, nice for testing purposes
  sf::RenderWindow::setVerticalSyncEnabled() - enables V-sync which adapts the rate of graphical updates from sf::RenderWindow::display() to the refresh rate of the monitor
  */
  sf::Clock clock;
  sf::Time timeSinceLastUpdateFunction = sf::Time::Zero;
  while (mWindow.isOpen()) // this loop calls the render method
  {
    processEvents();
    timeSinceLastUpdateFunction += clock.restart();
    while(timeSinceLastUpdateFunction > TIME_PER_FRAME) // fixed time stamps
    // this loop collects user input and computes game logic
    {
      timeSinceLastUpdateFunction -= TIME_PER_FRAME;
      processEvents();
      update(TIME_PER_FRAME);
    }

    render();
  }
}

/*
const std::vector < pair<bool, sf::Keyboard::Key> > PLAYER_MOVEMENT =
{
  {mIsMovingUp, sf::Keyboard::W},
  {mIsMovingDown, sf::Keyboard::S},
  {mIsMovingLeft, sf::Keyboard::A},
  {mIsMovingRight, sf::Keyboard::D}
}
*/

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
  if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
  else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
  else if (key == sf::Keyboard::A) mIsMovingLeft = isPressed;
  else if (key == sf::Keyboard::D) mIsMovingRight = isPressed;
}

void Game::processEvents()
{
  sf::Event event;
  while (mWindow.pollEvent(event)) // mainLoop/gameLoop
  {
    // each time while loop iterates it means that we got a new event registered by the window.
    switch (event.type)
    {
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
      default:
        break;
    }
  }
}

void Game::update(sf::Time deltaTime)
{

  sf::Vector2f movement (0.f, 0.f); // movement from the origin of the current coordinate system, in this case origin is the shape's positon
  movement.y += mIsMovingUp * MOVING_UP_SPEED + mIsMovingDown * MOVING_DOWN_SPEED;
  movement.x += mIsMovingLeft * MOVING_LEFT_SPEED + mIsMovingRight * MOVING_RIGHT_SPEED;
  mPlayer.move(movement * deltaTime.asSeconds());
  // from physics formula distance = speed * time
  // this allows us to move exactly the distance we want it to move in one second, no matter what computer are we on
  // delta time / time step - time that has elapsed since the last frame
  // mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds()); we scroll up the map, we update both the map and the player so he does not get left behind, we multiple by time to ensure that we have the same speed of n pixels per second no matter the simulation frame rate
}

void Game::render()
{
  mWindow.clear();
  mWorld.draw();

  mWindow.setView(mWindow.getDefaultView());
  // mWindow.draw(mStatisticsText);
  mWindow.display();
}

int main()
{
  try
  {
    Game game;
    game.run();
  }
  catch (std::exception& e)
  {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
}

#endif // GAME_CPP
