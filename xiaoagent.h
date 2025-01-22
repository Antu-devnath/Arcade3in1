#ifndef XIAOAGENT_H
#define XIAOAGENT_H

#include <GL/glut.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include<mmsystem.h>

using namespace std;
// Gravity and jump velocity
const float GRAVITY = 0.001f;
const float JUMP_VELOCITY = 0.03f;
const float GROUND_LEVEL = -0.95f;
int score=0;
bool isGameOver =false;

// Platform properties
struct Platform
{
    float x, y;
    float width = 0.75f;
};
vector<Platform> platforms;

// Player properties
struct Player
{
    float x, y;
    float width = 0.05f, height = 0.1f;
    bool movingRight = false, movingLeft = false;
    bool isJumping = false;
    bool facingRight = true;
    float yVelocity = 0.0f;
    int health = 5; // Player health
} player;

// Power-up properties
struct PowerUp
{
    float x, y;
    float size = 0.05f;
    bool active = true;
};
vector<PowerUp> healthPowerUps; //store multiple power-ups

// Bullet properties
struct Bullet
{
    float x, y;
    float speed =0.03f;
};
vector<Bullet> bullets;
vector<Bullet> enemyBullets;
struct Enemy
{
    float x, y;
    float width = 0.05f, height = 0.1f;
    float lastShootTime = 0.0f;
    int health = 3;
    float moveSpeed = 0.01f;
    float moveRange = 0.3f;
    float startX;
    bool movingRight = true;
};
vector<Enemy> enemies;


struct Coin
{
    float x, y;
    float size = 0.05f;
    bool active = true;
};
vector<Coin> coins;

////////////////////////////////////////////////////////////////////////////
struct GameData
{
    int currentLevel;
    int highScore;
};

//write the game data
void writeGameData(const GameData& data)
{
    ofstream file("E:\DataFile\\game_data.txt");

    if (file.is_open())
    {
        file << "Current Level: " << data.currentLevel << "\n";
        file << "High Score: " << data.highScore << "\n";
        file.close();
        //cout << "Game data saved successfully.\n";
    }
    else
    {
        cerr << "Failed to open file for writing.\n";
    }
}

// Read game data from a file
GameData readGameData()
{
    GameData data = {1, 0};
    ifstream file("E:\DataFile\\game_data.txt");

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (line.find("Current Level:") != string::npos)
            {
                data.currentLevel = stoi(line.substr(line.find(":") + 1));
            }
            else if (line.find("High Score:") != string::npos)
            {
                data.highScore = stoi(line.substr(line.find(":") + 1));
            }
        }
        file.close();
        //cout << "Game data loaded successfully.\n";
    }
    else
    {
        cerr << "Failed to open file for reading. Using default values.\n";
    }

    return data;
}

string getCurrentTimestamp()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}

void appendGameData(int currentLevel, int currentScore)
{
    ofstream file("E:\DataFile\\game_data.txt", ios::app); // Open in append mode

    if (file.is_open())
    {
        file << "Timestamp: " << getCurrentTimestamp() << "\n";
        file << "Level: " << currentLevel << ", Score: " << currentScore << "\n";
        file << "---------------------------------------\n";
        file.close();
        cout << "Game session data saved successfully.\n";
    }
    else
    {
        cerr << "Failed to open file for appending.\n";
    }
}


///////////////////////////////////////////////////////////////////////////////////////
//render text in position
void renderText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; ++i)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}


// Draw coins
void drawCoins()
{
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for coins
    for (size_t i = 0; i < coins.size(); ++i)
    {
        if (coins[i].active)
        {
            glRectf(coins[i].x, coins[i].y, coins[i].x + coins[i].size, coins[i].y + coins[i].size);
        }
    }
}

// Background position
float backgroundOffset = 0.0f;

void initPlayer()
{
    player.x = -0.9f;
    player.y = -0.875f;
}
bool gunFacingRight = true;
void drawPlayer()
{
    float S = 0.7f;

    glColor3f(0.0f, 1.0f, 0.0f);
    // Body
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 207);  // Color of the body
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.2f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.2f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.025f);
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.025f);
    glEnd();

    // Body dress (lower)
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 0);
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.1f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.1f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.025f);
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.025f);
    glEnd();

    // Body dress (upper)
    glBegin(GL_QUADS);
    glColor3ub(228, 0, 0);
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.1f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.1f);
    glVertex2f(player.x + S * 0.15f, player.y + S * 0.125f);
    glVertex2f(player.x + S * 0.025f, player.y + S * 0.125f);
    glEnd();

    // Right leg
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(player.x + S * 0.1f, player.y + S * 0.025f);
    glVertex2f(player.x + S * 0.1f, player.y + S * 0.0f);
    glVertex2f(player.x + S * 0.125f, player.y + S * 0.0f);
    glVertex2f(player.x + S * 0.125f, player.y + S * 0.025f);
    glEnd();

    // Left leg
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(player.x + S * 0.05f, player.y + S * 0.025f);
    glVertex2f(player.x + S * 0.05f, player.y + S * 0.0f);
    glVertex2f(player.x + S * 0.075f, player.y + S * 0.0f);
    glVertex2f(player.x + S * 0.075f, player.y + S * 0.025f);
    glEnd();

    // Right eye
    glBegin(GL_QUADS);
    glColor3ub(24, 79, 199);
    glVertex2f(player.x + S * 0.1f, player.y + S * (0.025f + 0.15f));
    glVertex2f(player.x + S * 0.1f, player.y + S * (0.0f + 0.15f));
    glVertex2f(player.x + S * 0.125f, player.y + S * (0.0f + 0.15f));
    glVertex2f(player.x + S * 0.125f, player.y + S * (0.025f + 0.15f));
    glEnd();

    // Left eye
    glBegin(GL_QUADS);
    glColor3ub(24, 79, 199);
    glVertex2f(player.x + S * 0.05f, player.y + S * (0.025f + 0.15f));
    glVertex2f(player.x + S * 0.05f, player.y + S * (0.0f + 0.15f));
    glVertex2f(player.x + S * 0.075f, player.y + S * (0.0f + 0.15f));
    glVertex2f(player.x + S * 0.075f, player.y + S * (0.025f + 0.15f));
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 79, 199); // Gun color
    if (gunFacingRight)
    {
        // Gun on the right
        glVertex2f(player.x + S * 0.175f, player.y + S * 0.075f);
        glVertex2f(player.x + S * 0.175f, player.y + S * 0.05f);
        glVertex2f(player.x + S * 0.15f, player.y + S * 0.05f);
        glVertex2f(player.x + S * 0.15f, player.y + S * 0.1f);
        glVertex2f(player.x + S * 0.225f, player.y + S * 0.1f);
        glVertex2f(player.x + S * 0.225f, player.y + S * 0.075f);
    }
    else
    {
        // Gun on the left (mirrored)
        glVertex2f(player.x + S * 0.0f, player.y + S * 0.075f); // Far left, top
        glVertex2f(player.x + S * 0.0f, player.y + S * 0.05f);  // Far left, bottom
        glVertex2f(player.x + S * 0.025f, player.y + S * 0.05f);   // Near left, bottom
        glVertex2f(player.x + S * 0.025f, player.y + S * 0.1f);    // Near left, top
        glVertex2f(player.x + S * (-0.05f), player.y + S * 0.1f);   // Extension left, top
        glVertex2f(player.x + S * (-0.05f), player.y + S * 0.075f); // Extension left, bottom
    }
    glEnd();
}


// Draw the platforms
void drawPlatforms()
{
    glColor3f(0.5f, 0.5f, 0.5f);
    for (const auto& platform : platforms)
    {
        glRectf(platform.x, platform.y, platform.x + platform.width, platform.y + 0.01f);
    }
}



// Draw power-ups
void drawPowerUps()
{
    for (const auto& powerUp : healthPowerUps)
    {
        if (powerUp.active)
        {
            glColor3f(0.0f, 1.0f, 1.0f); // Cyan color for the power-up
            glRectf(powerUp.x, powerUp.y, powerUp.x + powerUp.size, powerUp.y + powerUp.size);
        }
    }
}


bool enemyMove = true;
// Draw enemies
void drawEnemies()
{
    float S = 0.7f; // Scaling

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        float x = enemies[i].x;
        float y = enemies[i].y;

        // Draw body
        glBegin(GL_QUADS);
        glColor3ub(228, 221, 207); // Body color
        glVertex2f(x + S * 0.025f, y + S * 0.2f);
        glVertex2f(x + S * 0.15f, y + S * 0.2f);
        glVertex2f(x + S * 0.15f, y + S * 0.025f);
        glVertex2f(x + S * 0.025f, y + S * 0.025f);
        glEnd();

        // Draw dress bottom
        glBegin(GL_QUADS);
        glColor3ub(228, 221, 0); // Yellow dress
        glVertex2f(x + S * 0.025f, y + S * 0.1f);
        glVertex2f(x + S * 0.15f, y + S * 0.1f);
        glVertex2f(x + S * 0.15f, y + S * 0.025f);
        glVertex2f(x + S * 0.025f, y + S * 0.025f);
        glEnd();

        // Draw dress top
        glBegin(GL_QUADS);
        glColor3ub(228, 0, 0); // Red dress
        glVertex2f(x + S * 0.025f, y + S * 0.1f);
        glVertex2f(x + S * 0.15f, y + S * 0.1f);
        glVertex2f(x + S * 0.15f, y + S * 0.125f);
        glVertex2f(x + S * 0.025f, y + S * 0.125f);
        glEnd();

        // Draw legs
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0); // Black legs
        glVertex2f(x + S * 0.1f, y + S * 0.025f);
        glVertex2f(x + S * 0.1f, y);
        glVertex2f(x + S * 0.125f, y);
        glVertex2f(x + S * 0.125f, y + S * 0.025f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0); // Black legs
        glVertex2f(x + S * 0.05f, y + S * 0.025f);
        glVertex2f(x + S * 0.05f, y);
        glVertex2f(x + S * 0.075f, y);
        glVertex2f(x + S * 0.075f, y + S * 0.025f);
        glEnd();

        // Draw eyes
        glBegin(GL_QUADS);
        glColor3ub(171, 10, 37); // Red eyes
        glVertex2f(x + S * 0.1f, y + S * (0.025f + 0.15f));
        glVertex2f(x + S * 0.1f, y + S * (0.0f + 0.15f));
        glVertex2f(x + S * 0.125f, y + S * (0.0f + 0.15f));
        glVertex2f(x + S * 0.125f, y + S * (0.025f + 0.15f));
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(171, 10, 37); // Red eyes
        glVertex2f(x + S * 0.05f, y + S * (0.025f + 0.15f));
        glVertex2f(x + S * 0.05f, y + S * (0.0f + 0.15f));
        glVertex2f(x + S * 0.075f, y + S * (0.0f + 0.15f));
        glVertex2f(x + S * 0.075f, y + S * (0.025f + 0.15f));
        glEnd();

        // Draw weapon
        glBegin(GL_POLYGON);
        glColor3ub(209, 8, 162); // Purple gun
        glVertex2f(x + S * 0.175f, y + S * 0.075f);
        glVertex2f(x + S * 0.175f, y + S * 0.05f);
        glVertex2f(x + S * 0.15f, y + S * 0.05f);
        glVertex2f(x + S * 0.15f, y + S * 0.1f);
        glVertex2f(x + S * 0.225f, y + S * 0.1f);
        glVertex2f(x + S * 0.225f, y + S * 0.075f);
        glEnd();

        if (enemies[i].movingRight)
        {
            // Gun on the right side of the enemy
            glVertex2f(x + S * 0.175f, y + S * 0.075f); // Right position
            glVertex2f(x + S * 0.175f, y + S * 0.05f);
            glVertex2f(x + S * 0.15f, y + S * 0.05f);
            glVertex2f(x + S * 0.15f, y + S * 0.1f);
            glVertex2f(x + S * 0.225f, y + S * 0.1f);
            glVertex2f(x + S * 0.225f, y + S * 0.075f);
        }
        else
        {
            // Gun on the left side of the enemy
            glVertex2f(x + S * 0.0f, y + S * 0.075f); // Far left, top
            glVertex2f(x + S * 0.0f, y + S * 0.05f);  // Far left, bottom
            glVertex2f(x + S * 0.025f, y + S * 0.05f);   // Near left, bottom
            glVertex2f(x + S * 0.025f, y + S * 0.1f);    // Near left, top
            glVertex2f(x + S * (-0.05f),y + S * 0.1f);   // Extension left, top
            glVertex2f(x + S * (-0.05f), y + S * 0.075f); // Extension left, bottom
        }
        glEnd();


    }
}



// Draw health bar
void drawHealthBar()
{
    float barWidth = 0.40f;
    float barHeight = 0.05f;
    float x = -0.95f;
    float y = 0.9f;

    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x, y, x + barWidth, y + barHeight);

    glColor3f(0.0f, 1.0f, 0.0f);
    glRectf(x, y, x + barWidth * (player.health / 5.0f), y + barHeight);
}

void drawBackground()
{
    glColor3f(0.2f, 0.2f, 0.2f);
    for (float i = -1.0f + backgroundOffset; i < 1.0f; i += 0.1f)
    {
        glBegin(GL_LINES);
        glVertex2f(i, -1.0f);
        glVertex2f(i, 1.0f);
        glEnd();
    }
}


// Level Box properties
struct LevelBox
{
    float x, y;
    float size = 0.05f;
    bool active = false;
};
LevelBox levelBox = {-0.975f,0.55f};

// Draw the level box
void drawLevelBox()
{
    if (levelBox.active)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glRectf(levelBox.x, levelBox.y, levelBox.x + levelBox.size, levelBox.y + levelBox.size);
    }
}

int level = 1;

void resetForNextLevel()
{
    player.health = 5;
    bullets.clear();
    enemyBullets.clear();
    enemies.clear();
    coins.clear();
    healthPowerUps.clear();

    level++;

    if (level == 1)
    {
        player.x = -0.9f;
        player.y = -0.875f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});
        // Reset level 1 enemies, health power-ups, and coins
        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2


        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({0.5f, 0.125f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("levelup.wav",SND_ASYNC);
        PlaySound("fullmusic.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

    }
    else if (level == 2)
    {
        player.x = -0.9f;
        player.y = 0.875f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});
        // Reset level 1 enemies, health power-ups, and coins
        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2
        enemies.push_back({0.75f, 0.625f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 3

        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({0.5f, 0.125f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("levelup.wav",SND_ASYNC);
        PlaySound("fullmusic.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);


    }
    else if (level ==3)
    {
        player.x = 0.0f;
        player.y = -0.75f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});

        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2
        enemies.push_back({-0.9f, -0.95f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 3
        enemies.push_back({0.375f, -0.95f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 4
        enemies.push_back({0.75f, 0.625f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 5


        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({0.5f, 0.125f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("levelup.wav",SND_ASYNC);
        PlaySound("fullmusic.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);



    }
    GameData data = readGameData();
    if (score > data.highScore)
    {
        data.highScore = score;
        writeGameData(data);  // Save the new high score
    }
    levelBox.active = false;
}
int getLevelThreshold(int level)
{
    if (level == 1)
    {
        levelBox.active=true;
        return 100 ;

    }
    else if (level == 2)
    {
        levelBox.active=true;
        return 200;
    }
    else if (level == 3)
    {
        levelBox.active=true;
        return 300;
    }
    else if (level==4)
    {
        levelBox.active=true;
        return 400;
    }
    return 100;
}
void checkCollisions()
{
    for (size_t i = 0; i < healthPowerUps.size(); ++i)
    {
        if (healthPowerUps[i].active &&
                player.x + player.width > healthPowerUps[i].x &&
                player.x < healthPowerUps[i].x + healthPowerUps[i].size &&
                player.y + player.height > healthPowerUps[i].y &&
                player.y < healthPowerUps[i].y + healthPowerUps[i].size)
        {
            healthPowerUps[i].active = false; // Deactivate the power-up
            player.health = min(player.health + 3, 5); // Increase health (max 5)
            cout << "Health increased! Current health: " << player.health << std::endl;
                    sndPlaySound("levelup.wav",SND_ASYNC);

        }
    }

    for (size_t i = 0; i < bullets.size(); ++i)
    {
        for (size_t j = 0; j < enemies.size(); ++j)
        {
            if (bullets[i].x + 0.02f > enemies[j].x &&
                    bullets[i].x < enemies[j].x + enemies[j].width &&
                    bullets[i].y + 0.02f > enemies[j].y &&
                    bullets[i].y < enemies[j].y + enemies[j].height)
            {
                // Collision detected
                enemies[j].health--; // Decrease enemy health
                bullets.erase(bullets.begin() + i); // Remove the bullet
                --i;
                sndPlaySound("bullet.wav",SND_ASYNC);
                if (enemies[j].health <= 0)
                {
                    enemies.erase(enemies.begin() + j); // Remove the enemy if health is 0
                    --j;
                }
                break; // Exit inner loop to avoid accessing erased bullet
            }
        }
    }

    // Check for collisions between enemy bullets and the player
    for (size_t i = 0; i < enemyBullets.size(); ++i)
    {
        if (enemyBullets[i].x + 0.02f > player.x &&
                enemyBullets[i].x < player.x + player.width &&
                enemyBullets[i].y + 0.02f > player.y &&
                enemyBullets[i].y < player.y + player.height)
        {

            player.health--;
            enemyBullets.erase(enemyBullets.begin() + i);
            --i;

            if (player.health <= 0)
            {
                cout << "Game Over!" << endl;
                isGameOver = true;
                sndPlaySound("gameover.wav",SND_ASYNC);
                return;
            }
        }
    }
    if (levelBox.active &&
            player.x + player.width > levelBox.x &&
            player.x < levelBox.x + levelBox.size &&
            player.y + player.height > levelBox.y &&
            player.y < levelBox.y + levelBox.size)
    {
        if (score >= getLevelThreshold(level))
        {
            cout << "Level " << level << " Completed! Moving to the next level..." << endl;
            resetForNextLevel();  // Reset the game state for the next level
            //score = 0;            // Reset score for the next level
            sndPlaySound("boxcollusion.wav",SND_ASYNC);
        }
        else
        {
            cout << "Score too low. Keep playing!" << endl;
        }
    }
}
void CoinCollusin()
{
    for (size_t i = 0; i < coins.size(); ++i)
    {
        if (coins[i].active &&
                player.x + player.width > coins[i].x &&
                player.x < coins[i].x + coins[i].size &&
                player.y + player.height > coins[i].y &&
                player.y < coins[i].y + coins[i].size)
        {
            coins[i].active = false; // Deactivate the coin
            score += 25; // Increase score by 10 points for each collected coin
            appendGameData(level, score);
            cout << "Coin collected! Score: " << score << std::endl;
            sndPlaySound("coin.wav",SND_ASYNC);

        }
    }
}



// Update player movement and jumping
void updatePlayer()
{
    // Horizontal movement
    if (player.movingRight)
    {
        player.x += 0.01f;
        player.facingRight = true;
    }
    if (player.movingLeft)
    {
        player.x -= 0.01f;
        player.facingRight = false;
    }

    // Check if player is standing on any platform
    bool onPlatform = false;
    for (size_t i = 0; i < platforms.size(); ++i)
    {
        // Platform collision check (player should be above the platform and within its width)
        if (player.y > platforms[i].y - player.height && player.y < platforms[i].y &&
                player.x + player.width > platforms[i].x && player.x < platforms[i].x + platforms[i].width)
        {
            player.y = platforms[i].y;
            player.isJumping = false;
            player.yVelocity = 0.0f;
            onPlatform = true;
            break;
        }
    }

    if (!onPlatform)
    {
        player.y += player.yVelocity;
        player.yVelocity -= GRAVITY;

        if (player.y <= GROUND_LEVEL)
        {
            player.y = GROUND_LEVEL;
            player.isJumping = false;
            player.yVelocity = 0.0f;
        }

    }

    if (!player.isJumping && player.y == -0.8f)
    {
        player.yVelocity = 0.0f;
    }
}



// Enemy shooting logic
void enemyShoot(Enemy& enemy)
{
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    if (currentTime - enemy.lastShootTime >= 1.0f)
    {
        Bullet enemyBullet;

        enemyBullet.x = enemy.x + enemy.width / 2;
        enemyBullet.y = enemy.y + enemy.height / 2;

        enemyBullet.speed = (player.x < enemy.x) ? -0.02f : 0.02f;

        // Add the bullet to the list
        enemyBullets.push_back(enemyBullet);

        // Update the last shoot time
        enemy.lastShootTime = currentTime;
    }
}

// Update enemy positions
void updateEnemies()
{
    for (Enemy& enemy : enemies)
    {
        // Check if the enemy has found the player (within horizontal bounds)
        if (enemy.y - 0.1f <= player.y + player.height && enemy.y + 0.1f >= player.y)
        {
            // If the player is within the range vertically, stop moving horizontally and shoot
            if (fabs(enemy.x - player.x) <= 0.2f)
            {
                enemy.movingRight = false;
                enemyShoot(enemy);
            }
        }
        else
        {
            // Move the enemy left or right
            if (enemy.movingRight)
            {
                enemy.x += enemy.moveSpeed;  // Move to the right
                if (enemy.x >= enemy.startX + enemy.moveRange)
                {
                    enemy.movingRight = false;  // Reverse direction
                }
            }
            else
            {
                enemy.x -= enemy.moveSpeed;  // Move to the left
                if (enemy.x <= enemy.startX - enemy.moveRange)
                {
                    enemy.movingRight = true;  // Reverse direction
                }
            }
        }
    }
}

// Update bullet positions
void updateBullets()
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].x += bullets[i].speed;
        if (bullets[i].x > 1.0f || bullets[i].x < -1.0f)
        {
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}

// Update enemy bullets
void updateEnemyBullets()
{
    for (size_t i = 0; i < enemyBullets.size(); ++i)
    {
        enemyBullets[i].x += enemyBullets[i].speed; // Update bullet's x position
        if (enemyBullets[i].x < -1.0f || enemyBullets[i].x > 1.0f)
        {
            // Remove bullets that go off-screen
            enemyBullets.erase(enemyBullets.begin() + i);
            --i;
        }
    }
}
void drawEnemyBullets()
{
    glColor3f(1.0f, 0.5f, 0.0f); // Orange color for enemy bullets
    for (const auto& bullet : enemyBullets)
    {
        glRectf(bullet.x, bullet.y, bullet.x + 0.02f, bullet.y + 0.02f);
    }
}
void drawBullets()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        glRectf(bullets[i].x, bullets[i].y, bullets[i].x + 0.02f, bullets[i].y + 0.02f);
    }
}


void restartGame()
{
    // Reset player state
    player.x = -0.9f;
    player.y = -0.875f;
    player.health = 5; // Reset player health
    player.movingRight = false;
    player.movingLeft = false;
    player.isJumping = false;
    player.facingRight = true;
    player.yVelocity = 0.0f;
    bullets.clear();
    enemyBullets.clear();
    backgroundOffset = 0.0f;

    // Reset the game over flag
    isGameOver = false;

    if (level == 1)
    {
        player.x = -0.9f;
        player.y = -0.875f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});
        // Reset level 1 enemies, health power-ups, and coins
        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2


        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({0.5f, 0.125f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("gameover.wav",SND_ASYNC);
    }
    else if (level == 2)
    {
        player.x = -0.9f;
        player.y = 0.875f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});
        // Reset level 1 enemies, health power-ups, and coins
        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2
        enemies.push_back({0.75f, 0.625f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 3

        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({0.5f, 0.125f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("gameover.wav",SND_ASYNC);
    }
    else if (level ==3)
    {
        player.x = -0.05f;
        player.y = -0.75f;

        platforms.push_back({-1.0f, 0.5f});
        platforms.push_back({0.0f, 0.625f});
        platforms.push_back({-1.0f, 0.0f});
        platforms.push_back({0.0f, 0.0f});
        platforms.push_back({0.5f, 0.0f});
        platforms.push_back({-1.0f, -0.5f});
        platforms.push_back({-0.0f, -0.375f});
        platforms.push_back({-1.0f, -0.95f});
        platforms.push_back({-0.25f, -0.95f});
        platforms.push_back({0.5f,-0.95f});

        enemies.clear();
        enemies.push_back({-0.625f, 0.0f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 1
        enemies.push_back({0.375f, -0.375f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 2
        enemies.push_back({-0.9f, -0.95f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, -0.7f});  // Enemy 3
        enemies.push_back({0.375f, -0.95f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 4
        enemies.push_back({0.75f, 0.625f, 0.05f, 0.1f, 0.0f, 5, 0.007f, 0.3f, 0.375f});  // Enemy 5


        healthPowerUps.clear();
        healthPowerUps.push_back({0.0f, 0.085f});
        healthPowerUps.push_back({-0.875f, -0.425f});
        healthPowerUps.push_back({0.625f, -0.325f});
        healthPowerUps.push_back({0.625f, 0.675f});

        coins.clear();
        coins.push_back({0.425f, -0.25f});
        coins.push_back({-0.0f, -0.95f});
        coins.push_back({-0.95f, 0.120f});
        coins.push_back({0.125f, 0.75f});
        sndPlaySound("gameover.wav",SND_ASYNC);

    }

    GameData data = readGameData();
    if (score > data.highScore)
    {
        data.highScore = score;
        writeGameData(data);  // Save the new high score
    }

    cout << "Game Restarted!" << std::endl;
}
// Update background for scrolling effect
void updateBackground()
{

}

// Key press handler for continuous movement
void keyboardPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        if (!player.isJumping)
        {
            player.isJumping = true;
            player.yVelocity = JUMP_VELOCITY;
        }
        break;
    case 'a':
        player.movingLeft = true;
        gunFacingRight = false;
        break;
    case 'd':
        player.movingRight = true;
        gunFacingRight = true;
        break;
    case ' ':
    {
        Bullet bullet = {player.x + (player.facingRight ? player.width : -0.02f), player.y + player.height / 2, player.facingRight ? 0.02f : -0.02f};
        bullets.push_back(bullet);
        break;
    }
    }
    glutPostRedisplay();
}
void mouseClickForRun(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        player.movingLeft = true;
        gunFacingRight = false;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        player.movingRight = true;
        gunFacingRight = true;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        player.movingLeft = false;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        player.movingRight = false;
    }

    glutPostRedisplay();
}



// Key release handler to stop continuous movement
void keyboardUpToButton(unsigned char key, int x, int y)
{
    if (key == 'd' || key == 'D')
    {
        player.movingRight = false;
    }
    if (key == 'a'|| key == 'A')
    {
        player.movingLeft = false;
    }
    if (key == 'r' || key == 'R')
    {
        if (isGameOver)
        {
            restartGame();
        }
    }
}
void drawPlatform()
{
    glColor3f(0.5f, 0.5f, 0.5f);
    //2ND
    glBegin(GL_POLYGON);
    glColor3ub(87,84,69);
    glVertex2f(-1.0f,0.5f);
    glVertex2f(-0.25f,0.5f);
    glVertex2f(-0.25f,0.125f);
    glVertex2f(-0.5f,0.25f);
    glVertex2f(-1.0f,0.25f);
    glEnd();
    //3 RD
    glBegin(GL_QUADS);
    glColor3ub(87,84,69);
    glVertex2f(0.25f,1.0f);
    glVertex2f(0.5f,1.0f);
    glVertex2f(0.5f,0.925f);
    glVertex2f(0.25f,0.925f);
    glEnd();
    //5TH
    glBegin(GL_POLYGON);
    glColor3ub(87,84,69);
    glVertex2f(0.0f,0.625f);
    glVertex2f(0.75f,0.625f);
    glVertex2f(0.75f,0.25f);
    glVertex2f(0.5f,0.375f);
    glVertex2f(0.0f,0.375f);
    glEnd();
    //6TH
    glBegin(GL_QUADS);
    glColor3ub(87,84,69);
    glVertex2f(0.0f,0.0f);
    glVertex2f(1.0f,0.0f);
    glVertex2f(1.0f,-0.125f);
    glVertex2f(0.0f,-0.125f);
    glEnd();
    //7th
    glBegin(GL_QUADS);
    glColor3ub(87,84,69);
    glVertex2f(-1.0f,0.0f);
    glVertex2f(-0.25f,0.0f);
    glVertex2f(-0.25f,-0.125f);
    glVertex2f(-1.0f,-0.125f);
    glEnd();
    //9TH
    glBegin(GL_POLYGON);
    glColor3ub(87,84,69);
    glVertex2f(-0.25f, -0.5f);
    glVertex2f(0.0f, -0.375f);
    glVertex2f(0.75f, -0.375f);
    glVertex2f(0.75f, -0.625f);
    glVertex2f(-1.0f, -0.625f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();
    //last box
    glBegin(GL_QUADS);
    glColor3ub(87,84,69);
    glVertex2f(-1.0f,-1.0f);
    glVertex2f(1.0f,-1.0f);
    glVertex2f(1.0f,-0.95f);
    glVertex2f(-1.0f,-0.95f);
    glEnd();
}
void lights()
{

    //1 st quad
    glBegin(GL_QUADS);
    glColor3ub(87,84,69);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(-0.5f,1.0f);
    glVertex2f(-0.5f,0.875f);
    glVertex2f(-1.0f,0.875f);
    glEnd();
    //look quads for look good Design
    glBegin(GL_QUADS);
    glColor3ub(103,117,114);
    glVertex2f(-0.5f,0.625f);
    glVertex2f(-0.825f,0.625f);
    glVertex2f(-0.825f,0.8f);
    glVertex2f(-0.5f,0.8f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(69,93,95);
    glVertex2f(-0.525f,0.65f);
    glVertex2f(-0.8f,0.65f);
    glVertex2f(-0.8f,0.775f);
    glVertex2f(-0.525f,0.775f);
    glEnd();
    //Light1
    glBegin(GL_TRIANGLES);
    glColor4ub(234,224,168,0);
    glVertex2f(0.375f,0.975f);
    glVertex2f(0.625f,0.625f);
    glVertex2f(0.125f,0.625f);
    glEnd();

    //light1 box
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 207);
    glVertex2f(0.30f,0.980f);
    glVertex2f(0.45f,0.980f);
    glVertex2f(0.45f,0.925f);
    glVertex2f(0.30f,0.925f);

    glEnd();
    //Light2
    glBegin(GL_TRIANGLES);
    glColor3ub(234,224,168);
    glVertex2f(-0.625f,-0.05f);
    glVertex2f(-0.375f,-0.5f);
    glVertex2f(-0.875f,-0.5f);
    glEnd();
    //light2_BOX
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 207);
    glVertex2f(-0.55f,-0.05f);
    glVertex2f(-0.55f,-0.125f);
    glVertex2f(-0.70f,-0.125f);
    glVertex2f(-0.70f,-0.05f);
    glEnd();
    //last lab triangle light
    glBegin(GL_TRIANGLES);
    glColor3ub(234,224,168);
    glVertex2f(-0.625f,-0.55f);
    glVertex2f(-0.875f,-0.95f);
    glVertex2f(-0.375f,-0.95f);
    glEnd();
    //light box
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 207);
    glVertex2f(-0.55f,-0.55f);
    glVertex2f(-0.55f,-0.625f);
    glVertex2f(-0.70f,-0.625f);
    glVertex2f(-0.70f,-0.55f);
    glEnd();

    //light triangle last
    glBegin(GL_TRIANGLES);
    glColor3ub(234,224,168);
    glVertex2f(0.375f,-0.55f);
    glVertex2f(0.125f,-0.95f);
    glVertex2f(0.625f,-0.95f);
    glEnd();
    //last lab light box
    glBegin(GL_QUADS);
    glColor3ub(228, 221, 207);
    glVertex2f(0.3f,-0.55f);
    glVertex2f(0.3f,-0.625f);
    glVertex2f(0.45f,-0.625f);
    glVertex2f(0.45f,-0.55f);
    glEnd();

}
void gamedataview()
{

}

// Display function
void XIAOdisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer
    drawBackground();
    drawPlatforms();
    drawPlatform();
    lights();
    drawPlayer();
    drawHealthBar();
    drawBullets();
    drawEnemies();
    drawEnemyBullets();
    drawPowerUps();
    drawLevelBox(); //Next Level Box
    drawCoins();  // Draw the coins
    //getLevelThreshold();
    //initPlayer();
    gamedataview();

    if (level==4)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.2f, 0.0f);

        string gameOverText = "Game Over! YOU WIN!!!!!!!!!!!!!";
        for (char c : gameOverText)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    // Render the score on top of everything
    glColor3f(1.0f, 1.0f, 1.0f); // White color for score text
    string scoreText = "Score: " + to_string(score);
    renderText(0.7f, 0.9f, scoreText.c_str()); // Position the score on screen


    if (isGameOver)
    {        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.2f, 0.0f);  // Position to draw the text
        string gameOverText = "Game Over! Press R to Restart";
        for (char c : gameOverText)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
    // Display the level
    glRasterPos2f(0.7f, 0.85f);
    string levelText = "Level: " + to_string(level);
    for (char c : levelText)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
    // Display the high score
    GameData data = readGameData();
    glRasterPos2f(0.7f, 0.80f);
    string highScoreText = "High Score: " + to_string(data.highScore);
    for (char c : highScoreText)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    glutSwapBuffers();
    updateEnemies();
}


// Timer function to update game state
void Xiaotimer(int)
{
    updateBullets();
    updateEnemyBullets();
    updatePlayer();
    checkCollisions();
    CoinCollusin();
    updateBackground();
    glutPostRedisplay();
    for (Enemy& enemy : enemies)
    {
        enemyShoot(enemy);
    }
    if (score >= 100 && !levelBox.active)
    {
        levelBox.active = true;
    }

    glutTimerFunc(16, Xiaotimer, 0);
}


// Main function
void runxiaoagent(int argc, char** argv)
{

    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 800);
    glutInitWindowPosition(300,100);
    glutCreateWindow("AGENT: ZYO");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    GameData gameData = readGameData();
    level = gameData.currentLevel;
    score = gameData.highScore;
    score=0;
    resetForNextLevel();
    initPlayer();      // Initialize player
    gamedataview();    // Load game data

    glutDisplayFunc(XIAOdisplay);
    glutKeyboardFunc(keyboardPress);
    glutKeyboardUpFunc(keyboardUpToButton);
    glutMouseFunc(mouseClickForRun);

    glutTimerFunc(0, Xiaotimer, 0);
PlaySound("fullmusic.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
   glutMainLoop();

}
#endif
