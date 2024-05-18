#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "definitions.h"
#include "Player.h"
#include "Background.h"
#include "PlatformHandler.h"
#include "Score.h"
#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
    // Initialise the game
    bool gameOn = true;

    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "JUMP OR DIE");
    window.setFramerateLimit(FRAME_RATE);

    SoundBuffer jumpSound; jumpSound.loadFromFile("Assets/jump.ogg");
    SoundBuffer highJumpSound; highJumpSound.loadFromFile("Assets/high-jump.ogg");
    SoundBuffer deathSound; deathSound.loadFromFile("Assets/death.ogg");
    Sound sound;

    View view(FloatRect(0.f, 0.f, WIN_WIDTH, WIN_HEIGHT));
    float yNextView;
    
    Background bg;
    Player player;
    PlatformHandler platforms;
    Score score;

    while (window.isOpen())
    {
        Event event;
        // Check if the window is closed
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();

        // If the game hasn't begun
        if (!gameOn)
        {
            // Mouse position relative to the window
            Vector2i mousePos = sf::Mouse::getPosition(window);
            // Mouse position translated into world coordinates
            Vector2f translatedPos = window.mapPixelToCoords(mousePos); 
            // Check if the player is clicked
            if (Mouse::isButtonPressed(sf::Mouse::Left) && player.getRect().contains(translatedPos)) gameOn = true;
        }

        if (gameOn)
        {
            // Update the camera
            yNextView = std::min(view.getCenter().y, player.getPosition().y + 250);
            view.move(0, yNextView - view.getCenter().y);

            window.setView(view);
            // Move the player
            player.move();

            // If the player falls under the screen
            if (player.getPosition().y > view.getCenter().y + (WIN_HEIGHT / 2.f))
            {
                gameOn = false;

                sound.setBuffer(deathSound);
                sound.play();

                // Reset objects
                view.setCenter(WIN_WIDTH / 2.f, WIN_HEIGHT / 2.f);
                player.reset();
                platforms.reset();
                score.reset();

                float yNextView;

                window.setView(view);
            }
            // Check if the player is in collision with a platform
            if (player.getVelocity().y > 0)
            {
                // Loop all platform instances
                for (auto i = begin(platforms.table); i != end(platforms.table); i++)
                    {
                    if (player.getCollisionBox().intersects(i->getCollisionBox()))
                    {
                        // Check the type of the platform 
                        if (i->type == BOOST)
                        {
                            player.setVelocity(Vector2f(player.getVelocity().x, -50));
                            sound.setBuffer(highJumpSound);
                            sound.play();
                        }
                        else
                        {
                            player.setVelocity(Vector2f(player.getVelocity().x, -15));
                            if (i->type == FRAIL) platforms.del(i);
                            sound.setBuffer(jumpSound);
                            sound.play();
                        }
                    }
                }
            }
        }
        // Draw to the window and display
        bg.update(&window, view.getCenter().y);
        platforms.update(&window, view.getCenter().y);
        player.update(&window);
        score.update(&window, view.getCenter(), gameOn);

        window.display();
    }

    return 0;
}