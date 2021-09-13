# Assignment 1

# Assumption
- The program is running into 2 operating system
    1. Windows
    2. Unix based operating system
- If the end user is running this program in the different system then above than "printTree()" function won't open the png viewer automatically.   
- Assuming that the linux based system has image magick preinstalled in the system. If it is not installed you can install it by running the command "sudo apt-get update && sudo apt-get install imagemagick"

# Code Structure
1. main.cpp – main source file, driver code
2. LLNode.h – Has signature of the Singly Linked List class
3. BSTNode.h – Contains binary search tree node class
4. ThreadedBST.h – Contains the ThreadedBST class, underlying using the BSTNode and having operations
5. utils.cpp – Source file which has implementation of all the methods of the ThreadedBST class


# How to run?
- download the zip file
- extract zip file into one folder
- before running the command make sure your system has alread graphviz installed
- open cmd to that location and run the command "g++ main.cpp"
- Choice 9 or "printTree()" function prints the tree in png format and save in the directory where the program resides. The funtion itself will open the png viewer for the windows and unix based systems. If it does not open the png viewer than go to the folder where the program is saved and open "graph.png"
