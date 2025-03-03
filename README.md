# cub3D

A 3D maze explorer using raycasting technique inspired by Wolfenstein 3D.

![cub3D preview](screenshots/preview.png)

## Overview

cub3D is a first-person 3D maze explorer built with raycasting technology. This project aims to recreate the essence of the revolutionary Wolfenstein 3D game, which pioneered the first-person shooter genre. The core challenge is to build a dynamic view inside a maze where players navigate through walls with different textures based on orientation.

## Features

- 3D maze rendering using raycasting technique
- Textured walls with different textures for north, south, east, and west faces
- First-person camera movement (WASD keys) and rotation (arrow keys)
- Minimap display for navigation assistance
- Animated weapon rendering
- Interactive doors that can be opened and closed
- Wall collision detection
- Mouse-controlled camera rotation
- Customizable floor and ceiling colors

## Requirements

- Linux environment (Ubuntu recommended)
- GCC compiler
- Make
- MinilibX graphical library

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/g-garibotti/cub
   cd cub3D
   ```

2. Compile the project:
   ```
   make
   ```

## Usage

Run the program with a map file as argument:
```
./cub3D maps/test_valid.cub
```

### Controls

- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` / `→` - Rotate camera left/right
- `E` - Interact with doors (open/close)
- `Mouse` - Look around
- `Left Mouse Button` - Fire weapon
- `Shift` - Sprint
- `ESC` - Exit game

## Map Format

Maps are defined in `.cub` files with the following structure:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
DO ./path_to_the_door_texture (optional)

F R,G,B    # Floor color in RGB format
C R,G,B    # Ceiling color in RGB format

# Map layout (must be the last element in the file)
1111111111
1000000001
100N000001
1000000001
1111111111
```

### Map Symbols

- `0` - Empty space (floor)
- `1` - Wall
- `N`, `S`, `E`, `W` - Player starting position and orientation
- `d` - Closed door
- `D` - Open door
- ` ` (space) - Void (outside the map)

### Map Rules

- The map must be enclosed by walls (`1`)
- Only one player position is allowed
- The map can be of any shape as long as it's closed

## Technical Details

### Architecture

The project is structured around several key components:

1. **Raycasting Engine**: The core rendering system that creates the 3D illusion
2. **Player Controls**: Handle movement and rotation in the 3D space
3. **Map Parser**: Reads and validates map files
4. **Texture Management**: Loads and applies textures to walls
5. **Minimap System**: Provides a top-down view for navigation
6. **Game Loop**: Coordinates rendering, input handling, and game state

### Performance Considerations

- Uses Digital Differential Analysis (DDA) algorithm for efficient raycasting
- Optimized texture mapping to minimize distortion
- Efficient collision detection

## Development

### Dependencies

- **libft**: Custom C standard library
- **MinilibX**: Simple X-Window graphical library

### Compilation

The project includes a Makefile with the following rules:
- `make` or `make all`: Compile the program
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Rebuild the program

## Credits

This project is inspired by the classic game Wolfenstein 3D by id Software, created by John Carmack and John Romero.

## License

This project is part of the 42 school curriculum and is provided for educational purposes.