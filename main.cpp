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

extern void runPacman(int argc, char** argv);
extern void runBreakout(int argc, char** argv);
extern void runXiaoAgent(int argc, char** argv);

bool isMusicOn = true;

Button buttons[5] = {
    {50, 300, 200, 60, "Pacman", "./pacman", false},
    {300, 300, 200, 60, "BreakOut", "./breakout", false},
    {550, 300, 200, 60, "Xiao Agent", "./xiao_agent", false},
    {50, 200, 200, 60, "Music: On", "./settings", false},
    {300, 200, 200, 60, "Instructions", "./instructions", false}
};

bool showingInstructions = false;

Button backButton = {50, 50, 200, 60, "Back", "./back", false};

void updateSettingsButton() {
    buttons[3].label = isMusicOn ? "Music: On" : "Music: Off";
}

void drawButton(Button btn) {
    glBegin(GL_QUADS);
    if (btn.isHovered) {
        glColor3f(0.5f, 0.8f, 0.3f);
    } else {
        glColor3f(0.3f, 0.3f, 0.7f);
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

// Display main menu
void displayMainMenu() {
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

    for (int i = 0; i < 5; i++) {
        drawButton(buttons[i]);
    }

    const char* names[] = {
        "ANTU CHANDRA DEV NATH             22-49289-3",
        "MD. MOINUL HAQUE                        22-49403-3",
        "RAHUL BISWAS                                  22-49413-3"
    };
    glColor3f(1.0f, 1.0f, 1.0f); // White text
    float textY = 80;
    for (int i = 0; i < 3; i++) {
        float textX = 200;
        glRasterPos2f(textX, textY);
        for (const char* c = names[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        textY -= 20; // Move to the next line
    }

    glFlush();
}

// Display instructions page with added text
void displayInstructions() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the instructions page background
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.5f); // Dark blue background
    glVertex2f(0, 500);
    glColor3f(0.1f, 0.1f, 0.3f); // Darker shade at the bottom
    glVertex2f(800, 500);
    glColor3f(0.0f, 0.0f, 0.2f); // Even darker bottom
    glVertex2f(800, 0);
    glVertex2f(0, 0);
    glEnd();

    // Draw instructions text
    const char* instructions[] = {
        "Pacman Controls:",
        "  - Use W, A, S, D to move to.",
        "  - Collect food to increase score.",
        "",
        "Breakout Controls:",
        "  - Use A and D to move the paddle.",
        "  - Space to launch the ball.",
        "",
        "ZYO Agent Controls:",
        "  - Use W to jump, A/D to move left/right.",
        "  - Left Click to move left, Right Click to move right.",
        "",
        "Press Back button to exit and return to main menu."
    };

    glColor3f(1.0f, 1.0f, 1.0f); // White text
    float textY = 400;
    for (int i = 0; i < 11; i++) {
        float textX = 50;
        glRasterPos2f(textX, textY);
        for (const char* c = instructions[i]; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
        textY -= 20;
    }

    drawButton(backButton);

    glFlush();
}


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

    if (x >= backButton.x && x <= backButton.x + backButton.width &&
        y >= backButton.y && y <= backButton.y + backButton.height) {
        backButton.isHovered = true;
    } else {
        backButton.isHovered = false;
    }

    glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y; // Adjust for OpenGL's coordinate system

        // Handle clicks on the main menu buttons
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
                } else if (strcmp(buttons[i].label, "Music: On") == 0 ||
                           strcmp(buttons[i].label, "Music: Off") == 0) {
                    isMusicOn = !isMusicOn;
                    updateSettingsButton();
                    glutPostRedisplay();
                } else if (strcmp(buttons[i].label, "Instructions") == 0) {
                    showingInstructions = true;
                    glutPostRedisplay();
                }
            }
        }

        // Handle click on the back button
        if (x > backButton.x && x < backButton.x + backButton.width &&
            y > backButton.y && y < backButton.y + backButton.height) {
            showingInstructions = false;
            glutPostRedisplay();
        }
    }
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 500);
    updateSettingsButton();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Game Menu");

    init();
    glutDisplayFunc([]() {
        if (showingInstructions) {
            displayInstructions();
        } else {
            displayMainMenu();
        }
    });
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse);

    glutMainLoop();
    return 0;
}
