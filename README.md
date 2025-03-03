# cub3D

![C](https://img.shields.io/badge/language-C-blue.svg)

A 3D raycasting engine inspired by Wolfenstein 3D, built with the MiniLibX graphics library.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Game Controls](#game-controls)
- [Map Format](#map-format)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Challenges and Solutions](#challenges-and-solutions)
- [Contributing](#contributing)
- [License](#license)

## Overview

cub3D is a first-person 3D maze explorer that uses raycasting technology to create a 3D perspective in a 2D map. This project reimagines the groundbreaking Wolfenstein 3D game, showcasing skills in 3D graphics programming, efficient rendering algorithms, and game development principles in C.

## Features

- Raycasting-based 3D rendering
- Textured walls with orientation-specific textures (north, south, east, west)
- First-person navigation through maze environments
- Minimap for spatial awareness
- Interactive doors that can be opened and closed
- Animated weapon rendering with firing effects
- Mouse-controlled camera rotation
- Wall collision detection
- Customizable floor and ceiling colors

## Requirements

- GCC compiler
- Make
- MiniLibX library
- X11 include files (for Linux)
- Math library

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/g-garibotti/cub
   ```
2. Navigate to the project directory:
   ```
   cd cub3D
   ```
3. Compile the project:
   ```
   make
   ```

## Usage

Run the game with a map file:

```
./cub3D maps/test_valid.cub
```

## Game Controls

- Move Forward: `W`
- Move Backward: `S`
- Strafe Left: `A`
- Strafe Right: `D`
- Rotate Camera Left: `←`
- Rotate Camera Right: `→`
- Interact with Doors: `E`
- Look Around: Mouse movement
- Fire Weapon: Left Mouse Button
- Sprint: `Shift`
- Quit Game: `ESC` or close window

## Map Format

Maps are defined in `.cub` files with the following structure:

```
NO ./path_to_the_north_texture.xpm
SO ./path_to_the_south_texture.xpm
WE ./path_to_the_west_texture.xpm
EA ./path_to_the_east_texture.xpm
DO ./path_to_the_door_texture.xpm (optional)

F R,G,B    # Floor color in RGB format (0-255)
C R,G,B    # Ceiling color in RGB format (0-255)

# Map layout (must be the last element in the file)
111111111111
100000000001
100N000d0001
100000000001
111111111111
```

### Map Symbols

- `0` - Empty space (floor)
- `1` - Wall
- `N`, `S`, `E`, `W` - Player starting position and orientation
- `d` - Closed door
- `D` - Open door
- `X` or ` ` (space) - Void (outside the map)

## Project Structure

- `main.c`: Entry point and game initialization
- `init.c`, `game_init.c`: Game and structure initialization
- `cleanup.c`: Memory management and cleanup
- `hooks.c`, `hooks_utils.c`: Event handling and input management
- `dda.c`, `raycast.c`: Core raycasting implementation
- `movement.c`: Player movement and collision detection
- `init_player_pos.c`, `player_pos_utils.c`: Player positioning and orientation
- `texture.c`, `texture_load.c`: Texture loading and rendering
- `parser.c`, `parser_utils.c`: Map parsing and validation
- `fill_grid.c`, `parse_color.c`, `parse_texture.c`: Map element processing
- `validate_map.c`, `validate_map_utils.c`: Map validation algorithms
- `minimap.c`: Minimap rendering
- `gun.c`: Weapon rendering and animation
- `vectors.c`: Vector calculations and utilities

## Technical Details

### Raycasting Engine
- Implements Digital Differential Analysis (DDA) algorithm for efficient ray casting
- Calculates wall distances and heights for 3D perspective illusion
- Applies textures based on wall orientation and impact point

### Map Parsing and Validation
- Loads and validates map files with comprehensive error checking
- Ensures maps are enclosed and properly formatted
- Validates player position, textures, and color declarations

### Texture Management
- Loads textures from XPM files using MiniLibX
- Maps textures to walls based on orientation and position
- Handles transparent pixels for weapon animations

### Game Logic
- Implements collision detection with walls and doors
- Provides door interaction mechanics
- Handles player movement with precise vector calculations

### Memory Management
- Careful allocation and deallocation to prevent memory leaks
- Proper cleanup of all allocated resources, including MiniLibX objects

## Challenges and Solutions

1. **Challenge**: Implementing efficient raycasting algorithm
   **Solution**: Used DDA algorithm with optimized calculations to minimize processing overhead

2. **Challenge**: Realistic texture mapping with proper perspective
   **Solution**: Implemented wall coordinate calculation based on ray intersection point

3. **Challenge**: Handling different wall orientations
   **Solution**: Determined wall faces based on ray direction and map coordinates

4. **Challenge**: Creating smooth player movement and rotation
   **Solution**: Implemented frame-independent movement and rotation with vector-based calculations

5. **Challenge**: Interactive door system
   **Solution**: Designed a state-based door system with proper collision handling

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is part of the 42 school curriculum and is provided for educational purposes.