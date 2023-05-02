# HexMaze-Solver

Generates a HexBoard with HexCells consisting of hexagons with axial coordinates and solves the maze via DFS.

![r=15](https://user-images.githubusercontent.com/89245846/235605163-8e29a7b9-6fbc-4f95-8b53-c8e388c8c0b7.png)


#Axial coordinates
Axial and Cube coordinates are essentially the same. In the Cube system, we store the third coordinate, s. In the Axial system, we don't store it, but instead have to calculate it as needed, s = -q-r.
function cube_to_axial(cube):
    var q = cube.q
    var r = cube.r
    return Hex(q, r)

function axial_to_cube(hex):
    var q = hex.q
    var r = hex.r
    var s = -q-r
    return Cube(q, r, s)Converting between the systems like this is probably overkill. If you're using Cube and need Axial, ignore the s coordinate. If you're using Axial and need Cube, calculate the s coordinate in the algorithms that need it.
    
    <img width="536" alt="Screenshot 2023-05-02 at 12 16 38 AM" src="https://user-images.githubusercontent.com/89245846/235603398-38420395-9d09-4ce7-a22b-2a062c65c475.png">

![maze_sol_colour_r5_out](https://user-images.githubusercontent.com/89245846/235605288-126c0268-9af6-4ccf-82ec-82859892597d.png)


     
![maze_sol_r5_out](https://user-images.githubusercontent.com/89245846/235605319-50fc2f64-bd29-4d4a-9881-f549b8ceaf92.png)

