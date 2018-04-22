# CSV Indexer #

##### Process: ######

1. The program accepts a text file in the CSV format, takes the individual cell information and then puts it on a tridimensional array. 
2. The user can decide to search for specific keywords.
3. The program will create and save the search results to a tabulated userRequest.dat file.

##### How to: ######

Drag and drop any CSV file to the spreadsheet_indexer.exe file. An example file testLine.csv is included which contains the ISO list of country codes and a lot of other country facts. After dropping the file a command prompt window will appear asking you to type your search criteria. 
>For displaying efficiency the search results are cropped to fit into the command prompt window. After finishing your research, the complete results will be copied to the userRequest.dat file for your review.

While running the program you can try searching for words such as Coco, Island or Islam. You can also search for currencies such as Dollar or Pound. 

>You will be surprised by how many countries actually use these country names or currencies.

To quit the program simply press Control-C.

___

## The Dungeon ###
 
The initial version of the game allows an imaginary character to move between different rooms.You can type commands such as "north"("n"), "south"("s"), "east"("e") and "west"("w") to make a move and you can also pickup objects and move them around different rooms by using the commands "take" and "drop".
 
As the course progresses, students are required to integrate the files included on the weekly folders and add new features to the game such as directions commands, rooms, actions, objects and descriptions by making use of structures, pointers, functions, input files, etc.
 

##### Assignment 1 #####
 
- Added a long description field to the object and room structures.
- Added "examine" and "look" commands."examine" shows the description of the object in the room or the actor's possessions, "look" prints the room descriptions
 
##### Assignment 2 #####
 
- Added dungeon.dat file that is parsed to create rooms, objects and descriptions structure instances
- Implemented a way or those long descriptions to be read from the data file 
- Added new command directions and room structure possibilities such as "northwest" ("nw"), "southwest" ("sw"), "up" and "down" exits
 
##### Assignment 3 #####
  
- Integrated the sentence structure which can handle verb and preposition inputs
- Added "break" and "cut" commands and updated the dungeon.dat file
- Created the plural function which scans for objects' names and replies to the command inputs with grammatically coherent comments
 
