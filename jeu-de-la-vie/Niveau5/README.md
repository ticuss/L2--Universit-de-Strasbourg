# Read me First!

The Game of Life is an example of a cellular automaton and a zero-player game. It takes place on an infinite two-dimensional grid in which cells can be ‘on’ (alive) or ‘off’ (dead), and is defined by a set of rules that jointly determine the state of a cell given the state of its neighbours.Following specification of an initial configuration, patterns evolve over time across the grid requiring no further user input (thus ‘zero-player’). 

## Build instructions 

- 'make' allows you to build the GoL Niveau 5 with graphic interface
- 'make MODE=TEXTE' allows you to build the project without graphic interface
- './bin/cairo ./grilles/grille8.txt' this command is for testing GoL with graphic interface to evolve the cells press 'left-click of the mouse'
- './bin/main ./grilles/grille8.txt' this command is for testing GoL without graphic interface for the file grille8.txt to evolve the cells press 'ENTER'
- 'make clean' allows you to delete the folders obj, bin.
- 'make dist' Allows you to buid a tar file with all necessary files inside.
- 'make doc' Will create you the page html usig doxygen


## Additional notes:
when you will execute the code don't forget to try the the "C V N" buttons 

- 'C' you can change between cyclic and non-cyclic mode.
- 'V' will show tou the age of the  cells.
- 'N' you can charge another file from the folder grilles using only the terminal with the code ./grilles/grille1.txt' from 1 to 8;

