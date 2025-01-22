#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <string>
#include<mmsystem.h>


const int brickRows = 12;
const int brickCols = 14;
const float PI = 3.14159265358979323846;
extern int point = 0;

//Variables
int brickWidth = 50;
int brickHeight = 20;

float ballX = 495, ballY = 50;
float ballRadius = 10;
float ballXSpeed = 2.0f, ballYSpeed = 3.0f;
bool isBallLaunched = false;
float paddleX = 450, paddleY = 10;
float paddleWidth = 100, paddleHeight = 20;
float paddleSpeed = 10.0f;
bool powerUpActive = false;
float powerUpX = 0, powerUpY = 0;
float paddlePowerUpX = 0, paddlePowerUpY = 0;
bool paddlePowerUpActive = false;
bool paddlePowerUpSpawned = false;
float powerUpRadius = 10;
float powerUpSpeed = 2.0f;
bool moveLeft = false, moveRight = false;
float originalPaddleWidth = paddleWidth;
float enlargedPaddleWidth = 150;
bool powerUpSpawned = false;
int destroyedBricks = 0;
int currentLevel = 1;
int lives = 2;


//Functions
bool bricks[brickRows][brickCols] =
{
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// New Brick Layout for Level 2
bool level2Bricks[brickRows][brickCols] =
{
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// Brick layout for Level 3
bool level3Bricks[brickRows][brickCols] =
{
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
};

//////////////////////////////////////////////////////////////////////

struct GameDataBO

{

    int currentLevel;

    int highScore;

};



//write the game data

void writeGameDataBO(const GameDataBO& data)

{

    ofstream file("E:\DataFile\\game_bo.txt");



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

GameDataBO readGameDataBO()

{

    GameDataBO data = {1, 0};  // Default values: level 1 and high score 0

    ifstream file("E:\DataFile\\game_bo.txt");



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



//////////////////////////////////////


//display text
void renderBitmapString(float x, float y, void *font, const std::string &str)
{
    glRasterPos2f(x, y);
    for (char c : str)
    {
        glutBitmapCharacter(font, c);
    }
}

// Spawning Power
void spawnPowerUp(int brickRow, int brickCol)
{
    //destroyed bricks count
    std::cout << "Destroyed Bricks: " << destroyedBricks << std::endl;

    // Spawn paddle size power-up
    if (destroyedBricks == 7 && !paddlePowerUpSpawned)
    {
        paddlePowerUpX = brickCol * (brickWidth + 5) + 100 + brickWidth / 2;
        paddlePowerUpY = 600 - (brickRow * (brickHeight + 5) + 50) - brickHeight / 2;
        paddlePowerUpActive = true;
        paddlePowerUpSpawned = true;
    }

    // Spawn life power-up after exactly 5 bricks are destroyed
    if (destroyedBricks == 15 && !powerUpSpawned)
    {
        powerUpX = brickCol * (brickWidth + 5) + 100 + brickWidth / 2;
        powerUpY = 600 - (brickRow * (brickHeight + 5) + 50) - brickHeight / 2;
        powerUpActive = true;
        powerUpSpawned = true;
    }
}




//power up drawing
void drawPowerUp()
{
    if (powerUpActive) // Draw life power-up
    {
        glColor3f(1.0f, 0.0f, 0.0f); // Red for life power-up

        int triangleAmount = 100;
        float twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(powerUpX, powerUpY);
        for (int i = 0; i <= triangleAmount; i++)
        {
            glVertex2f(
                powerUpX + (powerUpRadius * cos(i * twicePi / triangleAmount)),
                powerUpY + (powerUpRadius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }

    if (paddlePowerUpActive)
    {
        glColor3f(0.0f, 1.0f, 0.0f); // Green

        int triangleAmount = 100;
        float twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(paddlePowerUpX, paddlePowerUpY);
        for (int i = 0; i <= triangleAmount; i++)
        {
            glVertex2f(
                paddlePowerUpX + (powerUpRadius * cos(i * twicePi / triangleAmount)),
                paddlePowerUpY + (powerUpRadius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }
}


// brick drawing
void drawBrick(float x, float y, bool isEye)
{
    if (currentLevel == 1)
    {
        glColor3ub(isEye ? 255 : 15, isEye ? 255 : 95, isEye ? 255 : 200); //Level 1
    }
    else if (currentLevel == 2)
    {
        glColor3ub(isEye ? 200 : 250, isEye ? 200 : 100, isEye ? 255 : 10); //Level 2
    }
    else if (currentLevel == 3)
    {
        glColor3ub(isEye ? 200 : 25, isEye ? 200 : 10, isEye ? 255 : 200); //Level 3
    }
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + brickWidth, y);
    glVertex2f(x + brickWidth, y - brickHeight);
    glVertex2f(x, y - brickHeight);
    glEnd();
}


void drawBricks()
{
    // Select the current level's brick layout
    bool (*currentBricks)[brickCols];
    if (currentLevel == 1)
        currentBricks = bricks;
    else if (currentLevel == 2)
        currentBricks = level2Bricks;
    else
        currentBricks = level3Bricks;

    for (int i = 0; i < brickRows; i++)
    {
        for (int j = 0; j < brickCols; j++)
        {
            if (currentBricks[i][j])
            {
                float x = j * (brickWidth + 5) + 100;
                float y = 600 - (i * (brickHeight + 5) + 50);

                bool isEye = false;
                if (currentLevel == 1)
                {
                    isEye = (i < 3 && (j == 3 || j == 4 || j == 9 || j == 10));
                }
                else if (currentLevel == 2)
                {
                    isEye = (i < 3 && (j == 6 || j == 7));
                }
                else if (currentLevel == 3)
                {
                    isEye = (i < 5 && (j == 1 || j == 10));
                }

                drawBrick(x, y, isEye);
            }
        }
    }
}



// Paddle drawing
void drawPaddle()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(paddleX, paddleY);
    glVertex2f(paddleX + paddleWidth, paddleY);
    glVertex2f(paddleX + paddleWidth, paddleY + paddleHeight);
    glVertex2f(paddleX, paddleY + paddleHeight);
    glEnd();
}

// Ball drawing
void drawBall()
{
    int i;
    int triangleAmount = 100;
    float twicePi = 2.0f * PI;

    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY);
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            ballX + (ballRadius * cos(i * twicePi / triangleAmount)),
            ballY + (ballRadius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}


// Lives drawing
void drawLives()
{
    int livesWidth = 30;
    int livesHeight = 20;
    int margin = 10;

    glColor3f(1.0f, 0.0f, 0.0f);

    for (int i = 0; i < lives; i++)
    {
        float x = 1000 - (i + 1) * (livesWidth + margin);
        float y = 580;
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + livesWidth, y);
        glVertex2f(x + livesWidth, y + livesHeight);
        glVertex2f(x, y + livesHeight);
        glEnd();
    }
}


///////////////////////////////////////////////
///////////////////////////////////////////////

// Collision with paddle
void checkBallPaddleCollision()
{
    if (ballX >= paddleX && ballX <= paddleX + paddleWidth && ballY - ballRadius <= paddleY + paddleHeight)
    {
        ballYSpeed = fabs(ballYSpeed); // ball moves upward

        // Adjust angle based on paddle hit position
        ballXSpeed = (ballX - (paddleX + paddleWidth / 2)) / 10;

        // Ensure the ball moves in the correct horizontal direction
        if (ballX - (paddleX + paddleWidth / 2) > 0)
        {
            // Ball hit the right side of the paddle
            ballXSpeed = fabs(ballXSpeed);
        }
        else if (ballX - (paddleX + paddleWidth / 2) < 0)
        {
            // Ball hit the left side of the paddle
            ballXSpeed = -fabs(ballXSpeed);
        }
        sndPlaySound("balltobreak.wav", SND_ASYNC);
    }
}



// Improved Ball-Brick Collision Logic
void checkBallBrickCollision(bool (*currentBricks)[brickCols])
{
    for (int i = 0; i < brickRows; i++)
    {
        for (int j = 0; j < brickCols; j++)
        {
            if (currentBricks[i][j])
            {
                float brickX = j * (brickWidth + 5) + 100;
                float brickY = 600 - (i * (brickHeight + 5) + 50);

                // Check for collision with the brick
                if (ballX + ballRadius >= brickX && ballX - ballRadius <= brickX + brickWidth &&
                        ballY + ballRadius >= brickY - brickHeight && ballY - ballRadius <= brickY)
                {
                    currentBricks[i][j] = 0;
                    destroyedBricks++;
                    point += 10;
                    std::cout << "Brick destroyed at (" << i << ", " << j << ")! Score: " << point << std::endl;
                    sndPlaySound("brick.wav",SND_ASYNC);

                    // Determine the direction of the bounce
                    bool hitHorizontalEdge = (ballY + ballRadius >= brickY - brickHeight && ballY - ballRadius <= brickY);
                    bool hitVerticalEdge = (ballX + ballRadius >= brickX && ballX - ballRadius <= brickX + brickWidth);

                    if (hitHorizontalEdge) // Ball hit the top or bottom of the brick
                    {
                        ballYSpeed = -ballYSpeed; // Reverse vertical direction
                    }
                    else if (hitVerticalEdge) // Ball hit the sides of the brick
                    {
                        ballXSpeed = -ballXSpeed; // Reverse horizontal direction
                    }

                    // Spawn power-ups after brick destruction
                    spawnPowerUp(i, j);
                }
            }
        }
    }
}







//Power-Up falling and activation
void handlePowerUp()
{
    // Handle life power-up
    if (powerUpActive)
    {
        powerUpY -= powerUpSpeed;

        // Paddle collects the life power-up
        if (powerUpX + powerUpRadius >= paddleX && powerUpX - powerUpRadius <= paddleX + paddleWidth &&
                powerUpY - powerUpRadius <= paddleY + paddleHeight)
        {
            lives++;  // Increase lives
            powerUpActive = false;
            sndPlaySound("powerupBO.wav", SND_ASYNC);
        }

        // Destroy life power-up
        if (powerUpY + powerUpRadius <= 0)
        {
            powerUpActive = false;
        }
    }

    //paddle size power-up
    if (paddlePowerUpActive)
    {
        paddlePowerUpY -= powerUpSpeed;

        // Paddle collects the paddle size power-up
        if (paddlePowerUpX + powerUpRadius >= paddleX && paddlePowerUpX - powerUpRadius <= paddleX + paddleWidth &&
                paddlePowerUpY - powerUpRadius <= paddleY + paddleHeight)
        {
            paddleWidth = 150;
            paddlePowerUpActive = false;
        }

        if (paddlePowerUpY + powerUpRadius <= 0)
        {
            paddlePowerUpActive = false;
        }
    }
}

void resetGameParameters()
{
    destroyedBricks = 0;
    ballX = paddleX + paddleWidth / 2 - ballRadius;
    ballY = paddleY + paddleHeight + ballRadius;
    ballXSpeed = 0.0f;
    ballYSpeed = 0.0f;
    isBallLaunched = false;

    paddlePowerUpSpawned = false;
    powerUpSpawned = false;
}


// Level Progression Logic
void checkLevelProgression(bool (*currentBricks)[brickCols])
{
    bool levelCompleted = true;
    for (int i = 0; i < brickRows; i++)
    {
        for (int j = 0; j < brickCols; j++)
        {
            if (currentBricks[i][j])
            {
                levelCompleted = false;
                break;
            }
        }
    }

    if (levelCompleted)
    {
        if (currentLevel == 3) // If all levels completed
        {
            std::cout << "You Win! Final Score: " << point << std::endl;
            exit(0); // Exit the game
        }
        else
        {
            currentLevel++;
            paddleWidth = 100;
            resetGameParameters();
        }
    }
}

void update(int value)
{
    if (isBallLaunched)
    {
        ballX += ballXSpeed;
        ballY += ballYSpeed;

        // Handle Ball Wall Collisions
        if (ballX - ballRadius <= 0 || ballX + ballRadius >= 1000) ballXSpeed = -ballXSpeed;
        if (ballY + ballRadius >= 600) ballYSpeed = -ballYSpeed;

        // Ball-Paddle Collision
        checkBallPaddleCollision();

        // Ball-Brick Collision
        bool (*currentBricks)[brickCols] = (currentLevel == 1) ? bricks : (currentLevel == 2) ? level2Bricks : level3Bricks;
        checkBallBrickCollision(currentBricks);

        // Check for Level Completion and Progression
        checkLevelProgression(currentBricks);

        // Ball Falls Below Paddle
        if (ballY - ballRadius <= 0)
        {
            lives--;
            if (lives == 0)
            {
                std::cout << "Game Over! Final Score: " << point << std::endl;
                exit(0);
            }
            resetGameParameters();
        }
        handlePowerUp();
    }
    else
    {
        ballX = paddleX + paddleWidth / 2 - ballRadius;  // Align the ball with the center of the paddle
        ballY = paddleY + paddleHeight + ballRadius;
    }

    // Paddle Movement
    if (moveLeft)
    {
        paddleX -= paddleSpeed;
        if (paddleX < 0) paddleX = 0;
    }
    if (moveRight)
    {
        paddleX += paddleSpeed;
        if (paddleX + paddleWidth > 1000) paddleX = 1000 - paddleWidth;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


//Key press handler
void handleKeyPress(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        moveLeft = true;
    }
    else if (key == 'd' || key == 'D')
    {
        moveRight = true;
    }
    else if (key == ' ')
    {
        if (!isBallLaunched)
        {
            isBallLaunched = true;
            ballXSpeed = 2.0f;
            ballYSpeed = 3.0f;
        }
    }
}

void handleKeyRelease(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
    {
        moveLeft = false;
    }
    else if (key == 'd' || key == 'D')
    {
        moveRight = false;
    }
}

//mouse movement
void mouseMove(int x, int y)
{
    paddleX = x - paddleWidth / 2;
    if (paddleX < 0) paddleX = 0;
    if (paddleX + paddleWidth > 1000) paddleX = 1000 - paddleWidth;
}
void handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (!isBallLaunched)
        {
            isBallLaunched = true;
            ballXSpeed = 2.0f;
            ballYSpeed = 3.0f;
            std::cout << "Ball launched with left mouse click!" << std::endl;
        }
    }
}


// Display function
void displaybreakout()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GameDataBO data = readGameDataBO();

    data.highScore = point;

    writeGameDataBO(data);
    drawBricks();
    drawPaddle();
    drawBall();
    drawPowerUp();
    glutMouseFunc(handleMouseClick);

    // Display score
    glColor3f(1.0f, 1.0f, 1.0f);
    renderBitmapString(10, 580, GLUT_BITMAP_HELVETICA_18, "Score: " + std::to_string(point));

    drawLives();

    glutSwapBuffers();
}

void runBreakout(int argc, char** argv)
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1000, 600);

    glutCreateWindow("Breakout");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glOrtho(0, 1000, 0, 600, -1, 1);

    glutDisplayFunc(displaybreakout);

    glutKeyboardFunc(handleKeyPress);

    glutKeyboardUpFunc(handleKeyRelease);

    glutPassiveMotionFunc(mouseMove);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

}

#endif
