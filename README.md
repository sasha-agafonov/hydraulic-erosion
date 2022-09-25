 # <p align="center"> Procedural Terrain Generation with Hydraulic Erosion </p>

<p align="center"> <img src="https://i.imgur.com/wphOflp.gif" alt="animation" /> </p>


_______________________________________________________________________________________________________________

#### COMPATIBILITY:

Tested to run on SoC Linux, but should work on other Linux distributions.

_______________________________________________________________________________________________________________

#### KNOWN ISSUES:

It is inadvisable to run the application inside a virtual machine or on a remote computer (e.g. using VPN), as Qt does not register mouse movement properly. This can make navigating the scene difficult.

_______________________________________________________________________________________________________________

#### OBTAINING THE SOURCE CODE:

Either use the following command in a terminal: git clone https://github.com/sasha-agafonov/terrain

Or download a zipped file of the repository from https://github.com/sasha-agafonov/terrain. Don't forget to unpack.

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

`Terrain size` defines the terrain size in squares, where each square is composed of two triangles. Larger sizes increase the terrain area, but triangle density remains unchanged.

`Random seed` allows to generate a different-looking terrain given the same generation parameters.

`Noise layers` each layer corresponds to the output of a noise function given the specified frequency and amplitude parameters for that particular layer. The final heighmap is constructed by amalgamating all active noise layers.

`Frequency` defines the amount of detail that should be generated. Higher values produce finer grained heightmaps.

`Amplitude` defines the maximum and minimum heights that can appear on a heightmap. The higher the amplitude, the greater the possible numeric range of the output.


#### Erosion parameters:

`Number of cycles` defines the number of cycles during which new water should appear (in other words, the duration of rain). The total number of cycles is greater since all reamining water needs to be evaporated and thus the overall length of erosion depends on the following: number of cycles, water amount, evaporation rate and post-evaporation rate.

`Water amount` defines the amount of water that arrives at each terrain vertex during a single cycle of raining.

`Carrying capacity` defines the maximum amount of material that can be contained in a unit of water.

`Erosion rate` defines the maximum amount of material that can be eroded by a unit of water during a single cycle.

`Deposition rate` defines the maximum amount of material that can be deposited by a unit of water during a single cycle.

`Evaporation rate` defines the maximum amount of water that can evaporate from each terrain vertex during a single cycle of raining.

`Post-evaporation rate` defines the amount of water that can evaporate from each terrain vertex during a single cycle of drying.

`Water drops` if disabled, the same constant amount of water will appear at each terrain vertex during a single cycle of raining. This will result in a very subtle water movement. If enabled, new water will appear randomly, spanning multiple neighboring vertices at once, but in amounts proportionate to the specified water amount. Enabling water drops will make water movement much more apparent and will lead to somewhat more chaotic erosion results.

_______________________________________________________________________________________________________________

#### NAVIGATION CONTROLS:

The following controls are available when viewing the rendered scene:

Move the mouse to look around.

Use `W` `A` `S` `D` keys to move forward, back, left and right.

Use `Space` to move up and Shift to move down.

Press `F` to toggle the FPS count. If the terrain is eroding in-scene, this will toggle the iteration count for the erosion process.

Press `Esc` to return to the main menu.

_______________________________________________________________________________________________________________

#### CHOOSING SUITABLE PARAMETERS:

The number of available parameters is large. The user interface provides an almost complete control over the parameter values, meaning that not every combination will produce the desired results. It is not advised to use and especially combine extreme parameter values, such as maximum water amount and minimum evaporation rate. Eroding the terrain in real-time can help to understand the effects of different parameters and hence the final result. The application also comes preset with appropriate generation and erosion parameters, which can be used as a starting point.
_______________________________________________________________________________________________________________

