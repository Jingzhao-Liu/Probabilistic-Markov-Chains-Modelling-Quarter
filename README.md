# Introduction
This code simulates the propagation of photons in photonic crystal surface emitting lasers (PCSEL). 

# Probabilistic-Markov-Chains-Modelling-(Quarter version)

Probabilistic Markov chain modelling of photonic crystal surface emitting lasers (PCSELs) links the scattering parameters of the photonic crystal (PC) and device level losses of the PCSEL. The criteria for conversion of the numerical model and agreement with data from the literature is discussed in papers below. We then explore the effect of increasing PC coupling coefficients and boundary mirror reflectivity on the in-plane power loss from the PCSEL. The effect of spatially varying the boundary reflectivity on the near field is also explored.
This is the code of generally useing Probabilistic Markov Chain modelling (quarter version)
The model simulates a quarter of device of specific size due to the symetric of PCSEL. 

Reference 1: (where this code be lead to, do not have yet will update when this code going to public).

Reference 2: http://dx.doi.org/10.1117/12.2649077 (not yet activated)

If citing this work, please use the following references(reference 1):

```
Will be updated after paper published
```
```
Will be updated after paper published
```

please DO NOT use the following references(reference 2):
```
@inproceedings{10.1117/12.2649077,
author = {Jingzhao Liu and Daehyun Kim and Zijun Bian and Jianyang Feng and Yunyun Gao and Paul Harvey and Richard Hogg},
title = {{Convergence criteria for probabilistic Markov chains modelling of photonic crystal surface emitting lasers}},
volume = {12440},
booktitle = {Novel In-Plane Semiconductor Lasers XXII},
editor = {Alexey A. Belyanin and Peter M. Smowton},
organization = {International Society for Optics and Photonics},
publisher = {SPIE},
pages = {124400D},
abstract = {Probabilistic Markov Chains modelling to define the relationship between microscopic scattering and macroscopic device level losses of photonic crystal surface emitting lasers (PCSEL) is reported. Here, we assume a priori knowledge of the microscopic scattering via simulation or measurement. The commissioning of the simulator, and convergence criteria are discussed.},
keywords = {PCSEL, lattice, bandstructure, loss, simulation, modelling},
year = {2023},
doi = {10.1117/12.2649077},
URL = {https://doi.org/10.1117/12.2649077}
}
```
```
Jingzhao Liu, Daehyun Kim, Zijun Bian, Jianyang Feng, Yunyun Gao, Paul Harvey, and Richard Hogg.
Convergence criteria for probabilistic Markov chains modelling of photonic crystal surface emitting lasers.
In Alexey A. Belyanin and Peter M. Smowton, editors, Novel In-Plane Semiconductor Lasers XXII, volume
12440, page 124400D. International Society for Optics and Photonics, SPIE, 2023
```
## How To Compile & Run

### From Command Line

Navigate to the folder containing the code then run
```
g++ Probabilistic Markov Chains Modelling.cpp -o Probabilistic Markov Chains Modelling.exe
```
type in the parameters according to the hint from command line.

For commissioning, please use example parameters:

Copy the parameters directly into the command line:

```
0.287 1337 386 38 5 0 4000 example_name.csv
```
Where, 
 
  * period = 0.287
  * K1D = 1334
  * K2D = 386
  * Krad = 38
  * Ki = 5
  * refl = 0 
  * timestep = 4000
  * file name = example_name.csv
* the defination of the parameters can be found in previous mentioned papers. 
* the current timestep will be print on command line to show the progress.
* a csv file will be created (if not exist already) under default address (if no other address provided). the file contains the size(s) requested to be simulated and the alpha parallel of the size at the timestep set.
* the result of commission (with example parameters) is 17.9.
* the default size in the code is 700 * 700 (fit the example), it can be changed directly in OrderArray. Multiple size is accepted in OrderArray, but the range of i should match the quantity of size put in. 
For example, 

Copy the parameters directly into the command line:

```
0.287 1337 386 38 5 0 4000 example_name.csv
```

### From Visual Studio

Please follow process:

Visual studio can be downloaded [here](https://visualstudio.microsoft.com/vs/features/cplusplus/) for free.

Then creat a new empty project.

creat an empty .cpp file under folder source files under your new project, then copy the code provided in to the file and save it 

or download the .cpp file provided and put it in your project folder and add it from Visual studio

use Local windows Debugger to compile and run it.

the command line will appear after finish, please follow the command line process above.


## How the Simulator Works 

At the core, the simulation calculates the probability of a photon's path thorugh a grid of atoms within the crystal.
 
Within the simulation, the grid of atoms are represented by:

 ```
 PC_NOW[PC number][13] 
 PC_PRE[PC number][13]
 ```
 
Where:
 ```
 PC_NOW: Represents the representation of the crystal in the current simulation time step
 PC_PRE: Represents the representation of the crystal in the previous simulation time step
 ```

 PC atom information array
* Array PC_NOW[PC number][13] & PC_PRE[PC number][13]:
* The limit of PC number is 10000000, for quarter PCSEL simulator, that allow maximum 2000*2000 PC atoms matrix.
* Content of information array(variable names and explaination if appliable):
  * [0]  = time-step(TimeStep: the current time step counting)
  * [1]  = PC number(A specific atom witin the crystal, using plane map coordinate system, counting from south west conner 0 to total atom number-1)
  * [2]  = input power from north;(represent the injection power coming from the atom on the north)
  * [3]  = input power from south;(represent the injection power coming from the atom on the south)
  * [4]  = input power from west;(represent the injection power coming from the atom on the west)
  * [5]  = input power from east;(represent the injection power coming from the atom on the east)
  * [6]  = output power to north;(represent the scatterd power going to the atom on the north)
  * [7]  = output power to south;(represent the scatterd power going to the atom on the south)
  * [8]  = output power to west;(represent the scatterd power going to the atom on the west)
  * [9]  = output power to east;(represent the scatterd power going to the atom on the east)
  * [10] = out-of-plane loss;(used to collect total out-of-plane loss)
  * [11] = internal loss;(used to collect total internal loss)
  * [12] = in-plane loss;(used to collect total in-plane loss)

the simulation will stop at set time step:
```
for (TimeStep = 0; (TimeOut); TimeStep++)
```

in each time step, the PC_PRE will be updated from PC_NOW of last time step and PC_NOW will be calculated based on PC_PRE.
```
memcpy(&PC_PRE, &PC_NOW, sizeof(double) * 13 * PC_Total);
memset(&PC_NOW, 0, sizeof(double) * 13 * PC_Total);
```

for each atom, the output power to 4 directions are calculated individually:
```
PC_NOW[PC_Counter][6] = Calculate_Energy_N(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
PC_NOW[PC_Counter][7] = Calculate_Energy_S(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
PC_NOW[PC_Counter][8] = Calculate_Energy_W(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
PC_NOW[PC_Counter][9] = Calculate_Energy_E(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
PC_NOW[PC_Counter][10] = Calculate_Energy_Vertical(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]);
PC_NOW[PC_Counter][11] = Calculate_Energy_Internal(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]);
```
for one direction output, applying the probabilities calculated from scattering coefficients to power inputting from all 4 directions and adding them up: 

example:
```
double Calculate_Energy_N(double N_in, double S_in, double W_in, double E_in)
{return (S_in * Pforward + W_in * P2D + E_in * P2D + N_in * P1D);}
```

