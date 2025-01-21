# Multi-Game Application

This project is a multi-game application built using OpenGL. It includes three games: Pacman, Breakout, and Xiao Agent. The project provides a menu interface for selecting games and viewing instructions.

---

## Table of Contents

- [Features](#features)
- [Games Included](#games-included)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Dependencies](#dependencies)
- [File Structure](#file-structure)
- [Future Enhancements](#future-enhancements)
- [Known Issues](#known-issues)

---

## Features

- **Pacman Game**: Classic maze-based gameplay.
- **Breakout Game**: Brick-breaking arcade experience.
- **Xiao Agent**: Platformer with shooting mechanics.
- Intuitive main menu for navigation.
- Instructions for each game.
- Save and load game progress for Breakout and Xiao Agent.

---

## Games Included

### 1. **Pacman**
   - Navigate the maze, eat pellets, and avoid ghosts.
   - Controls: `W`, `A`, `S`, `D`, and `Esc` to quit.

### 2. **Breakout**
   - Break bricks using a paddle and ball.
   - Controls: `A`, `D`, `Space`, and mouse for paddle control.

### 3. **Xiao Agent**
   - Jump platforms, defeat enemies, and collect coins.
   - Controls: `W`, `A`, `D`, `Space`, mouse click for actions, and `Esc` to quit.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/multi-game-app.git
   cd multi-game-app
   ```

2. Install the required dependencies (see [Dependencies](#dependencies)).

3. Compile the code using a compatible compiler:
   ```bash
   g++ main.cpp -o multi_game_app -lGL -lGLU -lglut
   ```

4. Run the executable:
   ```bash
   ./multi_game_app
   ```

---

## Usage

- Launch the application.
- Use the menu to select a game or view instructions.
- Follow the on-screen prompts for gameplay.

---

## Controls

### General
- **Menu Navigation**: Mouse
- **Select Option**: Left Mouse Click

### Game-Specific
See [Games Included](#games-included) for game-specific controls.

---

## Dependencies

- OpenGL
- GLUT
- C++ Standard Libraries
- A compatible graphics driver

---

## File Structure

- `main.cpp`: Entry point and menu handling.
- `menu.h`: Menu rendering and interaction logic.
- `breakout.h`: Breakout game logic and rendering.
- `xiaoagent.h`: Xiao Agent game logic and rendering.
- Additional dependencies are configured as per the OpenGL environment.

---

## Future Enhancements

- **Multiplayer Mode**: Adding support for local multiplayer to enhance the gaming experience.
- **New Games**: Expanding the library to include additional games.
- **High Score System**: Implementing a global leaderboard.
- **Improved Graphics**: Enhancing visuals with modern OpenGL features.
- **Cross-Platform Compatibility**: Ensuring smooth performance across multiple operating systems.

---

## Known Issues

- **Resolution Scaling**: The application may not scale correctly on high-resolution displays.
- **Performance**: Minor lag may occur on older hardware.
- **File Permissions**: Ensure the program has write permissions for saving progress.
- **Limited Instructions**: Some game instructions may lack clarity and need improvement.

---

## Contribution

Contributions are welcome! Please submit a pull request or open an issue.

---

## License

This project is licensed under the MIT License.
