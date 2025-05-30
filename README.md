# ArcaneLoom: A 2D Puzzle-Crafting Game

## Overview
ArcaneLoom is a unique 2D puzzle game built in C++ using the SFML library. Players weave arcane threads through a mystical tapestry to activate sigils, while countering chaotic rifts that unravel the fabric. The game blends strategic thread placement with dynamic environmental challenges, offering a fresh experience distinct from traditional puzzle or crafting games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, pattern-based puzzles, and dynamic systems. By sponsoring ArcaneLoom through GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Arcane Thread Weaving**: Place threads to connect sigils and form mystic patterns.
- **Chaotic Rifts**: Counter chaotic rifts that disrupt the tapestry’s fabric.
- **Minimalist Visuals**: Clean 2D graphics with glowing arcane effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SSFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.github.io/) or package manager).
- **CCMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/arcaneloom.git
   cd arcaneloom
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./ArcaneLoom
   ```

## Gameplay
- **Objective**: Activate all sigils by weaving threads to complete mystic patterns, while keeping chaos below the overload threshold.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **1/2/3**: Place horizontal, vertical, or diagonal threads.
  - **Space**: Counter a rift at the cursor.
  - **Enter**: Submit the tapestry pattern for
  - **scoring**.
  - **Ctrl+R**: Activate the level.
    - **R**: Reset - **Esc**: Exit.
- **Mechanics**: Threads connect sigils to form patterns. Rifts chaotic rifts randomly alter threads, increasing chaos. Counter rifts strategically to maintain tapestry stability.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (threads, rifts, threads, sigils).
- `vector/Game.hpp`: Core game logic, pattern weaving, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support ArcaneLoom’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New sigil patterns and rift types.
- Enhanced thread mechanics and visual effects.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.github.io/) for graphics and input.
- Inspired by mystical crafting and dynamic puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor ArcaneLoom to weave the fabric of innovative puzzle gaming!**