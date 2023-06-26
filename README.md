### SFML Map Generator Tool
C++ SFML Tile Map Maker

This project will make a tool to load a tile set and an empty grid to help place tiles. 
It will output a text file containing the tileset name and the positions of each tile in the map to be used in other projects.

Producing first window
- initially saved in the master branch
- with cmake and SFML properly installed, this repository can be used to produce the first window
1. `git clone git@github.com:terrill37/tilemapGenerator.git tilemapGenerator`
2. `cd sfmlSample`
3. `mkdir build && cd build`
4. `cmake ..`
5. `make`
    - will produce the executable as listed in the `CMakeLists.txt` file
6. `./tileMapGenerator` (name will probably change in upcoming update)


The current development branch is based off tag v1.0
Features to be added in next tag version
- larger tilesets
    - ability to load larger tilesets (64x64)
- placement of larger tiles (64x64)

