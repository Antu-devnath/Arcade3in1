#include <GL/glut.h>
#include <iostream>
#include <cstring> // For strcmp
#include <cmath>   // For math functions
#include "pacman.h"
#include "breakout.h"
#include "xiaoagent.h"

// Button structure with additional properties for design
struct Button {
    float x, y, width, height;
    const char* label;
    const char* command; // Command to execute
    bool isHovered;      // To handle hover effect
};

// Function prototypes for the games
extern void runPacman(int argc, char** argv);
extern void runBreakout(int argc, char** argv);
extern void runXiaoAgent(int argc, char** argv);

// Create five buttons for the game menu
Button buttons[5] = {
    {50, 300, 200, 60, "Pacman", "./pacman", false},
    {300, 300, 200, 60, "BreakOut", "./breakout", false},
    {550, 300, 200, 60, "Xiao Agent", "./xiao_agent", false},
    {50, 200, 200, 60, "Settings", "./settings", false},
    {300, 200, 200, 60, "Instructions", "./instructions", false}
};

// Game instructions
const char* pacmanInstructions[] = {
    "Pacman Instructions:",
    "Use 'W' to Move Up",
    "Use 'S' to Move Down",
    "Use 'A' to Move Left",
    "Use 'D' to Move Right",
    "Press 'Esc' to Quit"
};

const char* breakoutInstructions[] = {
    "BreakOut Instructions:",
    "Use 'A' to Move Paddle Left",
    "Use 'D' to Move Paddle Right",
    "Press SPACE to Launch Ball",
    "Move Mouse to Control Paddle"
};

const char* platformerInstructions[] = {
    "ZYO AGENT Instructions:",
    "Use 'W' to Jump",
    "Use 'A' to Move Left",
    "Use 'D' to Move Right",
    "Press SPACE to Shoot",
    "Mouse Click to Control Character",
    "Press 'Esc' to Quit"
};

bool showingInstructions = false;  // Flag to check if instructions should be shown

// Back button for instructions screen
Button backButton = {50, 50, 200, 60, "Back", "./back", false};

// Draw button (same as before)
void drawButton(Button btn) {
    glBegin(GL_QUADS);
    if (btn.isHovered) {
        glColor3f(0.5f, 0.8f, 0.3f); // Lighter color on hover
    } else {
        glColor3f(0.3f, 0.3f, 0.7f); // Base color
    }
    glVertex2f(btn.x, btn.y);
    glColor3f(0.2f, 0.2f, 0.5f); // Darker shade
    glVertex2f(btn.x + btn.width, btn.y);
    glColor3f(0.3f, 0.3f, 0.7f); // Back to base color
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    // Simulate rounded corners (optional for visual effect)
    glColor3f(0.0f, 0.0f, 0.0f); // Black border
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(btn.x, btn.y);
    glVertex2f(btn.x + btn.width, btn.y);
    glVertex2f(btn.x + btn.width, btn.y + btn.height);
    glVertex2f(btn.x, btn.y + btn.height);
    glEnd();

    // Draw button label
    glColor3f(1.0f, 1.0f, 1.0f); // White for text
    float textX = btn.x + btn.width / 2 - (float)strlen(btn.label) * 4.5f;
    float textY = btn.y + btn.height / 2 - 5.0f;
    glRasterPos2f(textX, textY);
    const char* c;
    for (c = btn.label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Display game instructions in three columns
void displayInstructions() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw background for instructions
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.3f); // Dark background for instructions
    glVertex2f(0, 500);
    glColor3f(0.0f, 0.0f, 0.2f); // Even darker bottom
    glVertex2f(800, 500);
    glColor3f(0.1f, 0.1f, 0.3f);
    glVertex2f(800, 0);
    glVertex2f(0, 0);
    glEnd();

    // Draw instructions title
    const char* title = "Game Instructions";
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for title
    glRasterPos2f(250, 460);
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // Instructions for Pacman (left column)
    int yOffset = 400;
    for (int i = 0; i < 6; i++) {
        glColor3f(1.0f, 1.0f, 1.0f); // White color for text
        glRasterPos2f(50, yOffset);
        for (const char* c = pacmanInstructions[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        yOffset -= 40;
    }

    // Instructions for BreakOut (middle column)
    yOffset = 400;
    for (int i = 0; i < 5; i++) {
        glRasterPos2f(250, yOffset);
        for (const char* c = breakoutInstructions[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        yOffset -= 40;
    }

    // Instructions for Shooting Platformer (right column)
    yOffset = 400;
    for (int i = 0; i < 7; i++) {
        glRasterPos2f(520, yOffset);
        for (const char* c = platformerInstructions[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        yOffset -= 40;
    }

    // Draw Back button
    drawButton(backButton);

    glFlush();
}

// Display main menu
void displayMove() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the menu background
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.5f); // Dark blue background
    glVertex2f(0, 500);
    glColor3f(0.1f, 0.1f, 0.3f); // Darker shade at the bottom
    glVertex2f(800, 500);
    glColor3f(0.0f, 0.0f, 0.2f); // Even darker bottom
    glVertex2f(800, 0);
    glVertex2f(0, 0);
    glEnd();

    // Draw the title
    const char* title = "Welcome to Game Menu";
    glColor3f(0.0f, 0.0f, 0.0f); // Shadow for text
    glRasterPos2f(255, 460);
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow title
    glRasterPos2f(250, 465);
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // Draw all buttons with updated visuals
    for (int i = 0; i < 5; i++) {
        drawButton(buttons[i]);
    }

    glFlush();
}

// Handle mouse movement to detect hover
void passiveMouse(int x, int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    y = windowHeight - y;

    for (int i = 0; i < 5; i++) {
        Button& btn = buttons[i];
        if (x >= btn.x && x <= btn.x + btn.width &&
            y >= btn.y && y <= btn.y + btn.height) {
            btn.isHovered = true;
        } else {
            btn.isHovered = false;
        }
    }

    // Check hover for the back button
    if (x >= backButton.x && x <= backButton.x + backButton.width &&
        y >= backButton.y && y <= backButton.y + backButton.height) {
        backButton.isHovered = true;
    } else {
        backButton.isHovered = false;
    }

    glutPostRedisplay();
}

// Handle mouse click
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y; // Adjust for OpenGL's coordinate system

        for (int i = 0; i < 5; i++) {
            if (x > buttons[i].x && x < buttons[i].x + buttons[i].width &&
                y > buttons[i].y && y < buttons[i].y + buttons[i].height) {
                std::cout << buttons[i].label << " clicked!\n";
                if (strcmp(buttons[i].label, "Pacman") == 0) {
                    runPacman(__argc, __argv); // Run Pac-Man
                } else if (strcmp(buttons[i].label, "BreakOut") == 0) {
                    runBreakout(__argc, __argv); // Run Breakout
                } else if (strcmp(buttons[i].label, "Xiao Agent") == 0) {
                    runxiaoagent(__argc, __argv); // Run Xiao Agent
                } else if (strcmp(buttons[i].label, "Settings") == 0) {
                    std::cout << "Settings clicked!\n"; // Placeholder
                } else if (strcmp(buttons[i].label, "Instructions") == 0) {
                    showingInstructions = true;  // Set the flag to show instructions
                    glutPostRedisplay();  // Redisplay to update the window
                }
            }
        }

        // Check if the Back button is clicked
        if (x > backButton.x && x < backButton.x + backButton.width &&
            y > backButton.y && y < backButton.y + backButton.height) {
            showingInstructions = false; // Go back to the main menu
            glutPostRedisplay();  // Redisplay to update the window
        }
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500); // Adjust to fit all buttons
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Game Menu");

    init();
    glutDisplayFunc([]() {
        if (showingInstructions) {
            displayInstructions();  // Show instructions if the flag is set
        } else {
            displayMove();  // Show the main menu
        }
    });
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse); // For hover effect

    glutMainLoop();
    return 0;
}
