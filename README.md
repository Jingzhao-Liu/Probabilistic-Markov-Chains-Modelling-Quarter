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
to be update
```
```
to be update
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
## How To Compile

### From Command Line

Navigate to the folder containing the code then run
```
g++ <name of code> -o <name of output>
```

### From Visual Studio

Visual studio can be downdlede [here](https://visualstudio.microsoft.com/vs/features/cplusplus/) for free.

Then open a new project ....
<put in description here>
 
 
##  How To Run
 
### From Command Line
 
 Assuming the application name from above (<name of output>).
 
```
./<name of output> period K1D K2D ....
```
 
 Where, 
 
 * period = 0.287
  * K1D = 1334
  * K2D = 386
  * Krad = 38
  * Ki = 5
  * refl = 0 
  * timestep = 4000
  * file name = Name.csv
* the defination of the parameters can be found in previous mentioned papers. 
* the current timestep will be print on command line to show the progress.
* a csv file will be created (if not exist already) under default address (if no other address provided). the file contains the size(s) requested to be simulated and the alpha parallel of the size at the timestep set.
* the result of commission (with example parameters) is 17.9.
* the default size in the code is 700 * 700 (fit the example), it can be changed directly in OrderArray. Multiple size is accepted in OrderArray, but the range of i should match the quantity of size put in. 
For example, 
 
 ```
./<name of output> 0.287 1334 386 38 5 0 4000
```

 
## How the Simulator Works 

At the core, the simulation calculates the probability of a photon's path thorugh a grid of atoms within the crystal.
 
Within the simulation, the grid of atoms are represented by:

 ```
 PC_NOW[PC number][13] 
 PC_PRE[PC number][13]
 ```
 
Where:
 ```
 PC_NOW : Represents the representation of the crystal in the current simulation time step
 PC_NUMBER: A specific atom witin the crystal
 SIM_ACCOUNTING: An array of accounting information for the simulator
 PC_PRE: 
 ```
 
## PC atom information array
* Array PC_NOW[PC number][13] & PC_PRE[PC number][13]:
* The limit of PC number is 10000000, for quarter PCSEL simulator, that allow maximum 2000*2000 PC atoms matrix.
* Content of information array:
  * [0]  = time-step
  * [1]  = PC number
  * [2]  = input power from north;
  * [3]  = input power from south;
  * [4]  = input power from west;
  * [5]  = input power from east;
  * [6]  = output power to north;
  * [7]  = output power to south;
  * [8]  = output power to west;
  * [9]  = output power to east;
  * [10] = out-of-plane loss;
  * [11] = internal loss;
  * [12] = in-plane loss;

