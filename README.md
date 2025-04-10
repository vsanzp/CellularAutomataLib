# *CellularAutomataLib*

Cellular Automata Models in Modelica (version 3.0)

This library can be used to describe 1D, 2D and 3D cellular automata models in Modelica.
It also includes interface models to combine cellular automata with other Modelica models.

## Author:

Victorino Sanz

Dpto. Informática y Automática, UNED

Juan del Rosal, 16

28040, Madrid

Spain

Email: [vsanz@dia.uned.es](mailto:vsanz@dia.unes.es)

Website: [www.euclides.dia.uned.es/vsanz](http://www.euclides.dia.uned.es/vsanz) 

## Licensing:

Licensed by Victorino Sanz under the LGPL-3.0 or later.
Copyright 2024, Victorino Sanz.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You have received a copy of the GNU Lesser General Public License along with this program (LICENSE.txt). If not, see <[https://www.gnu.org/licenses/](https://www.gnu.org/licenses/)>. Since LGPL is a set of additional permissions on top of the GPL, we also include a copy of the GNU General Public License (at the end of the LICENSE.txt file).

## Installation:

*CellularAutomataLib* is an autonomous Modelica library that has been tested under Dymola and OpenModelica. The functionality included in the library to generate graphical animations and save them as H264 videos depends on [Raylib](www.raylib.com) and [FFMPEG](www.ffmpeg.org), that need to be installed together with the library. Both are freely distributed under the *zlib/libpng* and *LGPL* licenses, respectively.

#### Raylib:

The installation of [Raylib](www.raylib.com) depends on the platform you are working. Please, consult [Raylib Wiki](https://github.com/raysan5/raylib/wiki) for detailed and updated instructions.

Briefly:

- Windows: just download and run the installer. More detailed instructions can be found at [https://github.com/raysan5/raylib/wiki/Working-on-Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
- Linux: follow these instructions: [https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) to install dependencies and build the library.
- Other OS: Raylib supports other operating systems, described in the wiki as development platforms ([https://github.com/raysan5/raylib/wiki](https://github.com/raysan5/raylib/wiki).

#### FFMPEG (libav* libraries):

*CellularAutomataLib* depends on the `libavformat`, `libavcodec`, `libavutil` and `libswscale`libraries (not the FFMPEG command line program). However, these libraries are distributed together with the ffmpeg program.

Analogous to Raylib, the [FFMPEG download website](www.ffmpeg.org/download.html) includes detailed and updated installation instructions.
Currently, FFMPEG supports [Linux](https://ffmpeg.org/download.html#build-linux),  [Windows](https://ffmpeg.org/download.html#build-windows) and [MacOS](https://ffmpeg.org/download.html#build-mac).

#### CellularAutomataLib:

[Download](https://github.com/vsanzp/CellularAutomataLib/archive/refs/heads/main.zip) or [clone]([GitHub - vsanzp/CellularAutomataLib: Cellular automata models in Modelica](https://github.com/vsanzp/CellularAutomataLib.git)) this repository.

The library is composed of multiple `.mo` files and directories, that contain the Modelica code, and the `Resources` directory, that contains the C code used to perform the simulations and to describe the models. 
In order to install the library, all these files and directories need to be located inside a single directory (e.g., `CellularAutomataLib/`) in your local workspace. No further installation is required.

Once installed, no further action is required since *CellularAutomataLib* includes and links Raylib and FFMPEG libraries with the developed models, during their translation, in order to execute them in the simulations.

## Model Development and Simulation:

The library can be loaded into a Modelica development tool (e.g., Dymola or OpenModelica) by opening the `package.mo` file at the top of the hierarchy of directories.

The User Guide (either the [`user_guide.md`](user_guide.md) file or the `UserGuide` package in Modelica) contains a description about how to construct new models and use the library, combining C and Modelica code to develop new models. It also contains a description on how to combine cellular automata models with other Modelica models using the provided interfaces.

The `Examples` package contains multiple examples that can be directly simulated using the functionality provided by the Modelica tool. The files contaning the C code of each example are located in the `Resources/Include` directory. Check the annotations of external functions in each model to locate their corresponding C file.

## Testing:

The `Test` package includes multiple testing models configured to test the entire functionality of the library. It includes 1D, 2D and 3D models, that, in combination, make use of all the compoments included in the library and all the external C functions included in the `CellularAutomataLib.c` file.
These models can serve to validate any modification performed to the library, either in the Modelica or the C code. A *.mos* script is also distributed (`run_Tests.mos` file in the Resources directory) to facilitate the sequential execution of the tests. This script translates and runs each test checking its result, and showing a summary of the results in a message box at the end of the run.

## Contributing

If you'd like to contribute, please fork the repository and use a feature branch. Pull requests are warmly welcome.

Please, do not hesitate to contact me for any question regarding the library ([vsanz@dia.uned.es](vsanz@dia.uned.es).
