# terrain
Procedural Terrain Generation with Hydraulic Erosion

![alt text](https://i.imgur.com/MNuLoG6.png)

Compatibility:
Tested to run on SoC Linux, but should work on other Linux distributions. 

Running and compiling:
Two options are available: running from Qt and running from a terminal emulator. The latter is recommended due to significantly better performance.

Obtaining the source code:
Clone the repository of this project using git clone https://github.com/Alexander-Agafonov/terrain in a terminal. Alternatively, you may download a zipped file of the repository from https://github.com/Alexander-Agafonov/terrain, in which case you will need to unpack it.

Running from Qt:
1. Open Qt and select "Open Project".
2. Navigate to the downloaded source files.
3. Search for "terrain.pro" and select the file.
4. Press the run button in Qt.

Running from a terminal emulator:
1. Navigate to the directory containing the source files of the project.
2. module add qt (skip if not on SoC Linux)
3. qmake
4. make
5. ./terrain
