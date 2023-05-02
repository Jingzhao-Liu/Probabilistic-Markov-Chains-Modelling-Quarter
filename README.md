# Probabilistic-Markov-Chains-Modelling-(Quarter version)

Probabilistic Markov chain modelling of photonic crystal surface emitting lasers (PCSELs) links the scattering parameters of the photonic crystal (PC) and device level losses of the PCSEL. The criteria for conversion of the numerical model and agreement with data from the literature is discussed in papers below. We then explore the effect of increasing PC coupling coefficients and boundary mirror reflectivity on the in-plane power loss from the PCSEL. The effect of spatially varying the boundary reflectivity on the near field is also explored.
This is the code of generally useing Probabilistic Markov Chain modelling (quarter version)
The model simulates a quarter of device of specific size due to the symetric of PCSEL. 

URL1: http://dx.doi.org/10.1117/12.2649077 (not yet activated)
URL2:

## Commission Information

* Please use following parameters for commission: (copy this and directly use in command line: 0.287 1334 386 38 5 0 4000)
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

