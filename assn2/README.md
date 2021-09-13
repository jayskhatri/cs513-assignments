# Assignment 2

Roll number: 214101023
Name: Jay Khatri

# Assumption
- Program is checked in linux system as I have used make tool in ubuntu
- System is already having graphviz installed
- System is already having make installed for linux

# Code Structure
1. main.cpp – main source file, driver code
2. AVL_Node.h – contains the AVL_Node class structure
3. AVL_Tree.h – Contains AVL tree class
4. AVL_Tree.cpp – Contains the implementation of the methods of AVL_Tree class, underlying using the AVL_Node and having operations
5. Makefile - makefile containing the code to automate the compilation


# How to run?
- download the zip file
- extract zip file into one folder
- before running the command make sure your system has alread graphviz installed
- Go to Source Files directory
- open terminal to that location and run the command ```make```
- to run the code write ```./avl``` in terminal and hit enter
- Choice 4 or ```AVL_Print()``` function prints the tree in png format and save in the directory where the program resides. The funtion itself will open the png viewer for the windows. If it does not open the png viewer than go to the folder where the program is saved and open the png file in the png viewer.


# Note
- If program is being run in the windows system then to make it run there is only one change need to be done and that is in file "main.cpp" the first line has included "AVL_Tree.h". For program to run in windows change that include file to "AVL_Tree.cpp" and then run the command ```g++ main.cpp``` for ubuntu it's as usual like above instructions. 
