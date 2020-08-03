To build the project, run qmake followed by make.

## Bonus Features

## Inexplicit memory management
This bonus feature comes from the Assignment Specification and Guidelines. All of the heap memory used by Quadris is managed using smart pointers and STL vector containers. As a result, we have no explicit delete statements.

## Graphical User Interface Input
The GUI display accepts button input for commands. The keyboard keys ASD can be used for block movement, the arrow keys can be used to rotate a block left and right, and the space bar can be used to drop blocks.z

## Multithreading
In order to facilitate receiving non-blocking input from the Graphical Display simultaneously with the Console, we had to incorporate multithreading using mutex locks.
