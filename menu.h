#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <string>
#include <iostream>

// Button positions and sizes
struct Button {
    float x, y, width, height;
    std::string label;
};

Button buttons[] = {
    {100, 400, 300, 50, "1. Start Pac-Man"},
    {100, 300, 300, 50, "2. Start Breakout"},
    {100, 200, 300, 50, "3. Start Xiao Agent"},
    {100, 100, 300, 50, "4. Instructions"},
    {100, 0,   300, 50, "5. Settings"}
};

int selectedGame = 0;

// Function to render text
void renderText(float x, float y, void* font, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}

// Display the menu
void displayMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    renderText(100, 500, GLUT_BITMAP_HELVETICA_18, "Select an Option:");

    for (const Button& button : buttons) {
        // Draw button background
        glColor3f(0.0f, 0.5f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2f(button.x, button.y);
        glVertex2f(button.x + button.width, button.y);
        glVertex2f(button.x + button.width, button.y + button.height);
        glVertex2f(button.x, button.y + button.height);
        glEnd();

        // Draw button label
        glColor3f(1.0f, 1.0f, 1.0f);
        renderText(button.x + 10, button.y + 30, GLUT_BITMAP_HELVETICA_18, button.label);
    }

    glutSwapBuffers();
}

// Mouse click handler
void handleMenuClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y; // Convert from window coordinates to OpenGL coordinates

        for (int i = 0; i < 5; ++i) {
            if (x >= buttons[i].x && x <= buttons[i].x + buttons[i].width &&
                y >= buttons[i].y && y <= buttons[i].y + buttons[i].height) {
                selectedGame = i + 1;
                if (selectedGame == 1) {
                    runPacman(0, nullptr);
                } else if (selectedGame == 2) {
                    runBreakout(0, nullptr);
                } else if (selectedGame == 3) {
                    runxiaoagent(0, nullptr);
                } else if (selectedGame == 4) {
                    std::cout << "Instructions window coming soon!" << std::endl;
                } else if (selectedGame == 5) {
                    std::cout << "Settings window coming soon!" << std::endl;
                }
            }
        }
    }
}

// Initialize menu
void initMenu() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Set coordinate system for menu
}

#endif // MENU_H
