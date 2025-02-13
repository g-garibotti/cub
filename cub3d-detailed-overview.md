# Cub3D Technical Overview

## Introduction

Cub3D is an advanced graphics project implementing a raycaster engine similar to Wolfenstein 3D. The project combines 3D rendering techniques, resource management, and game development principles.

## Code Structure Overview

### Memory Management (`cleanup.c`)
- Systematic resource cleanup
- Components:
  - Texture cleanup
  - Map grid cleanup
  - Window/MLX cleanup
  - Game state cleanup
```c
// Example cleanup flow:
clean_game()
  ├── clean_texture()  // Free textures
  ├── clean_map()      // Free grid
  ├── clean_window()   // Free MLX resources
  └── close_fd()       // Close file descriptors
```

### Initialization System (`init.c`, `init_player_pos.c`)
- Structured initialization process:
  - Game state
  - Map data
  - Player position
  - Weapon system
```c
// Initialization hierarchy:
init_game()
  ├── init_map()
  ├── init_player()
  ├── init_gun()
  └── init_window()
```

### Game Control System (`hooks.c`, `hooks_utils.c`)
- Input handling:
  - Keyboard events (WASD, ESC, E)
  - Mouse movement
  - Mouse click events
- Event management:
  - Window events
  - Animation timers
  - Game loop control

### Rendering System

#### Core Raycasting (`raycast.c`, `dda.c`)
- DDA (Digital Differential Analysis) implementation
- Ray calculation and wall detection
- Distance calculation
- Wall height determination
```
Ray Calculation Process:
1. Calculate ray direction
2. Determine map position
3. Perform DDA steps
4. Calculate wall distance
5. Determine wall height
```

#### Texture Management (`texture.c`, `texture_load.c`)
- Texture loading system
- Texture mapping
- Wall orientation handling
- Transparent texture support
- XPM file processing

#### Weapon System (`gun.c`)
- Weapon state management
- Animation system
- Texture scaling
- Screen positioning
- Transparency handling

### Map System

#### Parser (`parser.c`, `parser_utils.c`)
- File format validation
- Map element parsing
- Error handling
- Resource path validation

#### Map Validation (`validate_map.c`, `validate_map_utils.c`)
- Map integrity checks
- Wall continuity validation
- Player position validation
- Flood fill algorithm for map closure

#### Color and Texture Parsing (`parse_color.c`, `parse_texture.c`)
- RGB color parsing
- Texture path validation
- Format verification
- Error handling

### Movement System (`movement.c`)
- Collision detection
- Player movement
- Rotation handling
- Speed management

### Mathematical Components (`vectors.c`)
- Vector calculations
- Angle management
- Normalization functions
- Perpendicular calculations

## Core Game Loop

```plaintext
Game Loop Flow:
┌─────────────────┐
│  Input Handling │
├─────────────────┤
│ Player Movement │
├─────────────────┤
│   Ray Casting   │
├─────────────────┤
│ Wall Rendering  │
├─────────────────┤
│    Minimap      │
├─────────────────┤
│  Gun Animation  │
└─────────────────┘
```

## Key Data Structures

### Game State (`t_game`)
- Core game data
- Resource handles
- Display information
- Player state
- Map data

### Map Data (`t_map`)
- Grid representation
- Dimensions
- Textures
- Colors
- Validation flags

### Player Data (`t_player`)
- Position
- Direction
- Movement flags
- View angles
- Collision data

## Technical Implementation Details

### Raycasting Algorithm
1. Ray Direction Calculation
2. DDA Implementation
3. Wall Distance Calculation
4. Texture Mapping
5. Rendering

### Memory Management Strategy
- Systematic initialization
- Proper deallocation
- Resource tracking
- Error handling

### File Handling
- Map file parsing
- Texture loading
- Error checking
- Resource validation

## Project Requirements

### Dependencies
- MinilibX (MLX)
- Math library
- Standard C libraries

### Build System
```bash
make          # Build project
make clean    # Clean objects
make fclean   # Full clean
make re       # Rebuild
```

### Map File Format
```plaintext
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
DO ./path_to_door_texture

F 220,100,0
C 225,30,0

1111111111
1000000001
1000N00001
1000000001
1111111111
```

## Performance Optimizations

### Rendering
- Efficient DDA implementation
- Optimized texture mapping
- Smart buffer management

### Memory
- Minimal allocations
- Proper cleanup
- Resource pooling

### Input Handling
- Event-based system
- Smooth movement
- Responsive controls

## Error Handling

### Validation Checks
- Map integrity
- Resource availability
- Memory allocation
- File operations

### Cleanup Procedures
- Systematic resource release
- Error state management
- Graceful exit handling

This overview provides a comprehensive look at the Cub3D project structure and implementation details. Each component is designed to work together to create a smooth, efficient 3D gaming experience.
