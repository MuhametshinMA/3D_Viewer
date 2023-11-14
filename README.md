# 3DViewer v2.0

Implementation of 3DViewer v2.0

The russian version of the task can be found in the repository.


## Contents

   3.1. [Part 1](#part-1-3dviewer-v20) \
   3.2. [Part 2](#part-2-bonus-settings) \
   3.3. [Part 3](#part-3-bonus-record)

## Part 1. 3DViewer v2.0

Program to visualise the 3D wireframe models.

- The program developed in C++ language of C++17 standard
- The program code located in the src folder
- Code writing follow the Google style
- The program built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory could be arbitrary, except the building one
- The program developed according to the principles of object-oriented programming;
- There only one model on the screen at a time
- The program provide the ability to:
    - Load a wireframe model from an obj file (vertices and surfaces list support only).
    - Translate the model by a given distance in relation to the X, Y, Z axes.
    - Rotate the model by a given angle in relation to its X, Y, Z axes.
    - Scale the model by a given value.
- GUI implementation, based on any GUI library with API for C++ Qt

- The graphical user interface contain:
    - A button to select the model file and a field to output its name.
    - A visualisation area for the wireframe model.
    - Button/buttons and input fields for translating the model.
    - Button/buttons and input fields for rotating the model.
    - Button/buttons and input fields for scaling the model.
    - Information about the uploaded model - file name, number of vertices and edges.
- The program correctly processes and allows user to view models with details up to 100, 1000, 10,000, 100,000, 1,000,000  vertices without freezing (a freeze is an interface inactivity of more than 0.5 seconds)
- The program implemented using the MVC pattern, and also:
    - there no business code in the view code
    - there no interface code in the controller and the model
    - controllers is thin
- There at least three different design patterns (e.g. facade, strategy and command)
- Classes implemented within the `s21` namespace

## Part 2. Bonus. Settings

- The program allows customizing the type of projection (parallel and central)
- The program allows setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices
- The program allows choosing the background color
- Settings saved between program restarts

## Part 3. Bonus. Record

- The program allows saving the captured (rendered) images as bmp and jpeg files.
- The program allows recording small screencasts - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s) by a special button
