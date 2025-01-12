# CellularAutomataLib

Cellular Automata Models in Modelica (version 3.0)

This library can be used to describe 1D, 2D and 3D cellular automata models in Modelica.
It also includes interface models to combine cellular automata with other Modelica models.

Author:

		Victorino Sanz
		Dpto. Informática y Automática, UNED
		Juan del Rosal, 16
		28040, Madrid
		Spain
		Email: vsanz@dia.uned.es
		Website: www.euclides.dia.uned.es/vsanz

Copying:

Licensed by Victorino Sanz under the LGPL-3.0 or later.
Copyright 2024, Victorino Sanz.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this program (LICENSE.txt). If not, see <https://www.gnu.org/licenses/>. Since LGPL is a set of additional permissions on top of the GPL, we also include a copy of the GNU General Public License (LICENSE-GPL.txt).


INSTALLATION:

1. The library is composed of multiple .mo files and directories, that contain the Modelica code, and the Resources directory, that contains the C code used to perform the simulations and to describe the models. These files need to be located in a directory (e.g., CellularAutomataLib/) in your local workspace, no further installation is required.

2. In order to automatically generate the graphical animations of the simulations the Raylib (www.raylib.com) library program has to be installed in the computer. Raylib installation depends on your operating system:
- Windows: just download and run the installer. More detailed instructions can be found at https://github.com/raysan5/raylib/wiki/Working-on-Windows
- Linux: follow these instructions: https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux to intall dependencies and build the library.
- Other OS: Raylib supports other operating systems, described in the wiki as development platforms (https://github.com/raysan5/raylib/wiki)

Once installed, no further action is required since CellularAutomataLib includes and links Raylib code with the models in order to execute it in the simulations.


USE, MODEL DEVELOPMENT AND SIMULATION:

Once installed, the library can be loaded into a Modelica development tool (e.g., Dymola, OpenModelica) by opening the package.mo file at the top of the hierarchy of directories.

The NewModels package included in this Documentation contains a description on how to construct new models and use the library, combining C and Modelica code to develop new models.
The InterfaceModels package contains a description on how to combine cellular automata models with other Modelica models using the provided interfaces.

The Examples package contains multiple examples that can be directly simulated using the functionality provided by the Modelica tool. The files contaning the C code of each example are located in the Resources/Include directory. Check the annotations of external functions in each model to locate the corresponding C file.



