#ifndef PACMAN_H
#define PACMAN_H

#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <mmsystem.h>

extern int score2 = 0;
const int mazeWidth = 21;
const int mazeHeight = 25;

using namespace std;
int maze1[mazeHeight][mazeWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 0, 2, 2, 0, 1},
    {1, 0, 2, 1, 0, 2, 1, 1, 1, 1, 1, 0, 1, 0, 2, 1, 0, 2, 0, 0, 1},
    {1, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 2, 0, 1, 1, 1, 1, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 1, 0, 2, 2, 2, 2, 0, 1, 2, 1, 1, 1, 0, 2, 1, 1, 0, 1},
    {1, 0, 2, 1, 2, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 1, 2, 1},
    {1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 0, 2, 0, 0, 0, 1, 2, 1},
    {1, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1},
    {1, 0, 2, 1, 2, 0, 1, 0, 2, 2, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 1, 0, 2, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 2, 0, 1, 0, 0, 0, 1},
    {1, 2, 0, 1, 0, 2, 2, 2, 0, 0, 1, 2, 0, 1, 2, 0, 1, 0, 2, 2, 1},
    {1, 2, 2, 1, 0, 0, 2, 0, 0, 2, 1, 2, 0, 1, 0, 0, 1, 2, 2, 0, 1},
    {1, 2, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 1, 2, 2, 0, 2, 0, 0, 1},
    {1, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 1},
    {1, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 1, 2, 0, 1, 0, 0, 0, 0, 1},
    {1, 2, 0, 0, 2, 2, 2, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 2, 0, 0, 0, 0, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // Your maze definition goes here...
};
int maze2[mazeHeight][mazeWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 1, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 2, 1},
    {1, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 2, 1},
    {1, 2, 1, 2, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1},
    {1, 2, 1, 2, 1, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 1, 0, 1, 2, 1},
    {1, 2, 1, 2, 1, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 1, 0, 1, 2, 1},
    {1, 0, 1, 2, 1, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 2, 0, 1, 2, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 1, 2, 2, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 2, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 1, 0, 2, 0, 1, 0, 2, 2, 1, 0, 2, 2, 2, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 1, 0, 1},
    {1, 2, 1, 0, 1, 0, 2, 2, 2, 2, 0, 0, 2, 0, 2, 2, 1, 0, 1, 2, 1},
    {1, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 2, 1},
    {1, 2, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 2, 2, 0, 2, 2, 1, 0, 0, 0, 0, 1, 2, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int food[mazeHeight][mazeWidth] = {0};
float pacmanX = 30.0f, pacmanY = 30.0f;
float pacmanRadius = 10.0f;
float enemyX, enemyY;
float enemySpeed = 5.0f;
float enemy2X, enemy2Y;
float enemy2Speed = 5.0f;
float enemy3X, enemy3Y;
float enemy3Speed = 5.0f;
bool gameOver = false;
int paclevel = 1;
///////////////////////////////////////////////////////
struct GameDataPac
{
    int currentLevel;
    int highScore;
};

//write the game data
void writeGameDataPac(const GameDataPac& data)
{
    ofstream file("E:\DataFile\\game_pac.txt");

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
GameDataPac readGameDataPac()
{
    GameDataPac data = {1, 0};  // Default values: level 1 and high score 0
    ifstream file("E:\DataFile\\game_pac.txt");

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

////////////////////////////////////////////////////////////////////////////////////////////
void initOpenGL() {
    glClearColor(0.82f, 0.99f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, mazeWidth * 20, 0, mazeHeight * 20);
}

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void initializeFood() {
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            food[i][j] = (maze1[i][j] == 0) ? 1 : 0;
        }
    }
}

void initializeEnemy() {
    for (int y = mazeHeight / 2; y < mazeHeight; y++) {
        for (int x = mazeWidth / 2; x < mazeWidth; x++) {
            if (maze1[y][x] == 0) {
                enemyX = x * 20 + 150;
                enemyY = y * 20 + 170;
                enemy2X = x * 20 - 90;
                enemy2Y = y * 20 + 180;

                return;
            }
        }
    }
}

void drawFood() {
    glColor4f(1.0f, 0.0f, 0.0f, 0.0);
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            if (food[i][j] == 1) {
                float x = j * 20 + 10;
                float y = (mazeHeight - 1 - i) * 20 + 10;
                drawCircle(x, y, 5.0f);
            }
        }
    }
}

void drawMaze() {
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            if (maze1[i][j] == 1) {
                glColor3f(0.0f, 0.0f, 0.0f);
                glRectf(j * 20.0f, (mazeHeight - 1 - i) * 20.0f,
                        j * 20.0f + 20.0f, (mazeHeight - i) * 20.0f);
            }
        }
    }
}

void sound() {
    sndPlaySound("audio", SND_ASYNC | SND_FILENAME);

}
void soundgameover() {
    sndPlaySound("sound",SND_ASYNC|SND_FILENAME|SND_LOOP);
}

bool checkCollision(float x, float y) {
    int gridX = (int)(x / 20.3);
    int gridY = mazeHeight - 1 - (int)(y / 20.3);
    return maze1[gridY][gridX] == 1;
}

void moveEnemy() {
    if (gameOver) return;

    auto moveSingleEnemy = [](float& ex, float& ey, float speed) {
        float dx = pacmanX - ex;
        float dy = pacmanY - ey;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist > 0) {
            float stepX = speed * (dx / dist);
            float stepY = speed * (dy / dist);
            if (!checkCollision(ex + stepX , ey)) ex += stepX;
            if (!checkCollision(ex, ey + stepY)) ey += stepY;
        }
        if (std::abs(ex - pacmanX) < pacmanRadius && std::abs(ey - pacmanY) < pacmanRadius) {
            gameOver = true;
            std::cout << "Game Over! Final Score: " << score2 << std::endl;
            soundgameover();
        }
    };

    moveSingleEnemy(enemyX, enemyY, enemySpeed);
    moveSingleEnemy(enemy2X, enemy2Y, enemy2Speed);
    moveSingleEnemy(enemy3X, enemy3Y, enemy3Speed);
}

bool checkLevelComplete() {
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            if (food[i][j] == 1) {
                return false;  // Food still exists
            }
        }
    }
    return true;  // All food eaten
}

void handleKeypress(unsigned char key, int x, int y) {
    if (gameOver) return;
    float newPacmanX = pacmanX;
    float newPacmanY = pacmanY;
    switch (key) {
        case 'w': newPacmanY += 20; break;
        case 's': newPacmanY -= 20; break;
        case 'a': newPacmanX -= 20; break;
        case 'd': newPacmanX += 20; break;
        case 27: exit(0);
    }
    if (!checkCollision(newPacmanX, newPacmanY)) {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;
        int gridX = (int)(pacmanX / 20);
        int gridY = mazeHeight - 1 - (int)(pacmanY / 20);
        if (food[gridY][gridX] == 1) {
            food[gridY][gridX] = 0;
            score2++;
            sound();
        }
    }

   // Inside checkLevelComplete() or in the level-up logic
if (checkLevelComplete()) {
    paclevel++;
    std::cout << "Level " << paclevel << " Completed!" << std::endl;

    // Switch to next level maze
    if (paclevel == 2) {
        memcpy(maze1, maze2, sizeof(maze2));  // Copy second level maze
    }

    // Reset food and enemies for the new level
    initializeFood();
    initializeEnemy();
}

    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {
    if (gameOver || state != GLUT_DOWN) return;

    float newPacmanX = pacmanX;
    float newPacmanY = pacmanY;

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Translate mouse coordinates
    float clickX = (float)x / windowWidth * (mazeWidth * 20);
    float clickY = (float)(windowHeight - y) / windowHeight * (mazeHeight * 20);

    // Determine movement direction
    enum Direction { LEFT, RIGHT, UP, DOWN, NONE };
    Direction moveDirection = NONE;

    if (clickX < pacmanX - pacmanRadius) {
        moveDirection = LEFT;
    } else if (clickX > pacmanX + pacmanRadius) {
        moveDirection = RIGHT;
    }

    if (clickY > pacmanY + pacmanRadius) {
        moveDirection = UP;
    } else if (clickY < pacmanY - pacmanRadius) {
        moveDirection = DOWN;
    }

    // Handle movement
    switch (moveDirection) {
        case LEFT:
            newPacmanX -= 20;
            break;
        case RIGHT:
            newPacmanX += 20;
            break;
        case UP:
            newPacmanY += 20;
            break;
        case DOWN:
            newPacmanY -= 20;
            break;
        default:

            return;
    }


    if (!checkCollision(newPacmanX, newPacmanY)) {
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;

        int gridX = (int)(pacmanX / 20);
        int gridY = mazeHeight - 1 - (int)(pacmanY / 20);
        if (food[gridY][gridX] == 1) {
            food[gridY][gridX] = 0;
            score2++;
            sound();
        }
    }

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMaze();

     GameDataPac data = readGameDataPac();
     data.highScore = score2;
        writeGameDataPac(data);  // Save the new high score

    drawFood();
    glColor3f(1.0f, 0.0157f, 0.773f);
    drawCircle(pacmanX, pacmanY, pacmanRadius);
    glColor3f(0.0f, 0.5f, 0.5f);
    drawCircle(enemyX, enemyY, pacmanRadius);
    glColor3f(1.0f, 0.5f, 0.0f);
    drawCircle(enemy2X, enemy2Y, pacmanRadius);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, mazeHeight * 20 - 20);
    std::string scoreText = "Score: " + std::to_string(score2);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    std::string levelText = "Level: " + std::to_string(paclevel);
    glRasterPos2f(10, mazeHeight * 20 - 40);
    for (char c : levelText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(mazeWidth * 10 - 40, mazeHeight * 10);
        std::string gameOverText = "GAME OVER!";
        for (char c : gameOverText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glutSwapBuffers();
}

void timer(int value) {
    if (!gameOver) {
        moveEnemy();
    }
    glutPostRedisplay();
    glutTimerFunc(200, timer, 0);
}

void runPacman(int argc, char** argv) {
    //glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pac-Man");
    initOpenGL();
    initializeFood();
    initializeEnemy();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);
    glutTimerFunc(200, timer, 0);
    glutMainLoop();
}
#endif // PACMAN_H
