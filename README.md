 # <p align="center"> Procedural Terrain Generation with Hydraulic Erosion </p>

<p align="center"> <img src="https://i.imgur.com/wphOflp.gif" alt="animation" /> </p>


_______________________________________________________________________________________________________________

#### COMPATIBILITY:

Tested to run on SoC Linux, but should work on other Linux distributions.

_______________________________________________________________________________________________________________

#### KNOWN ISSUES:

It is inadvisable to run the application inside a virtual machine or on a remote computer (e.g. using VPN), as the mouse movement is not registered correctly and makes navigating the scene difficult. 

_______________________________________________________________________________________________________________

#### OBTAINING THE SOURCE CODE:

Either use the following command in a terminal: git clone https://github.com/Alexander-Agafonov/terrain

Or download a zipped file of the repository from https://github.com/Alexander-Agafonov/terrain. Don't forget to unpack.

_______________________________________________________________________________________________________________

#### RUNNING AND COMPILING:

Two options are available: running from Qt and running from a terminal emulator. The latter is recommended due to significantly better performance.

#### Running from terminal (recommended):

1. Navigate to the directory containing the source code of the project.
2. module add qt (skip if not on SoC Linux)
3. qmake
4. make
5. ./terrain


#### Running from Qt:

1. Open Qt and select "Open Project".
2. Navigate to the downloaded source files.
3. Search for "terrain.pro" and select the file.
4. Press the run button in Qt.

_______________________________________________________________________________________________________________

#### USING THE APPLICATION:

The application interface is split into two parts: 

1. A menu containing all parameters for generating and eroding a terrain
2. A scene in which the resulting terrain is rendered

The first step is to generate (and erode, if desired) a terrain heightmap using the menu in 1). An initial terrain heightmap is generated when a button under an empty heightmap container is pressed. The terrain will be generated using the following specified parameters: terrain size, random seed and noise layers (with respective individual parameters). The heightmap will appear in the container once generated.

To erode a heightmap, an initial heightmap needs to be generated first. Similar to the previous step, erosion will begin after a button below a heightmap container is pressed, using the specified parameters to the left of the container.

#### Step 1: initial menu with preset parameters
 <img src="https://i.imgur.com/a8v2j32.png" alt="main_menu" />
 
#### Step 2: a heightmap has been generated and is displayed in a container on the right
 <img src="https://i.imgur.com/sAqM4gC.png" alt="main_menu" />
 
#### Step 3: a previously generated heightmap has now been eroded from the menu and is also displayed on the right
 <img src="https://i.imgur.com/5ha96ML.png" alt="main_menu" />


#### Rendered output. From left to right: uneroded, eroding, eroded.
 <img src="https://i.imgur.com/UN1cJYZ.png" alt="output" />

_______________________________________________________________________________________________________________

#### EXPLANATION OF PARAMETERS:

#### Generation parameters:

Terrain size: defines the terrain size in squares, where each square is composed of two triangles. Larger sizes increase the terrain area, but triangle density remains unchanged.

Random seed: if enabled, allows to generate a different-looking terrain given the same generation parameters.

Noise layers: each layer corresponds to the output of a noise function given the specified frequency and amplitude parameters for that particular layer. The final heighmap is built by adding the output of all active layers together.

Frequency: higher values produce a greater amount of detail in the layer output.

Amplitude: higher values lead to a greater numeric range of heights/values in the layer output.


#### Erosion parameters:

Number of cycles: defines the number of cycles during which new water should appear (in other words, the duration of rain). The total number of cycles is greater since all reamining water needs to be evaporated and thus the overall length of erosion depends on the following: number of cycles, water amount, evaporation rate and post-evaporation rate.

Water amount: defines the amount of water that arrives at each terrain cell during a single cycle of raining.

Carrying capacity: controls the maximum amount of material that a cell can hold in the form of sediment.

Erosion rate: controls the maximum amount of material that can be eroded by a cell during a single cycle.

Deposition rate: controls the maximum amount of material that can be deposited by a cell during a single cycle.

Evaporation rate: controls the amount of water that disappears from each cell during a single cycle of raining.

Post evaporation rate: controls the amount of water that disappears from each cell during a single cycle of drying (in other words, the evaporation rate after the rain has passed).

Water drops: if disabled, the same constant amount of water will appear at each cell during a single cycle of raining. Hence, visually the water movement will mostly appear static. If enabled, new water will appear randomly, spanning multiple neighboring cells at once, but in amounts proportionate to the specified water amount. Enabling water drops will make water movement much more apparent and will lead to somewhat more chaotic erosion results.

_______________________________________________________________________________________________________________

#### NAVIGATION CONTROLS:

The following controls are available when viewing the rendered scene:

Move the mouse to look around.

Use W, S, A, D keys to move forward, back, left and right.

Use Space to move up and Shift to move down.

Press F to toggle the FPS count. If the terrain is eroding in-scene, this will toggle the iteration count for the erosion process.

Press Esc to return to the main menu.

_______________________________________________________________________________________________________________

#### CHOOSING SUITABLE PARAMETERS:

The number of available parameters is large. The user interface provides an almost complete control over the parameter values, meaning that not every combination will produce the desired results. It is not advised to use and especially combine extreme parameter values, such as maximum water amount and minimum evaporation rate. Eroding the terrain in real-time can help to understand the effects of different parameters and hence the final result. The application also comes preset with appropriate generation and erosion parameters, which can be used as a starting point.
_______________________________________________________________________________________________________________

