# Probabilistic-Markov-Chains-Modelling-(Quarter version)
This is the code of generally useing Probabilistic Markov Chain modelling (quarter version)
This simulation links defines the scattering parameters of the photonic crystal (PC) and device level losses of the PCSEL.
The criteria for conversion, agreement with data from the literature of the numerical model and other applications are discussed in following papers:
URL1
URL2

## Commission Information
* Please use following parameters for commission:
 * period = 0.287
 * K1D = 1334
 * K2D = 386
 * Krad = 38
 * Ki = 5
 * refl = 0 
 * timestep = 4000
 * file name = Name.csv
* the default size in the code is 700*700, you can change it directly in code line 250 (OrderArray). multiple size is accepted in OrderArray, but the range of i in 253 should be changed as well. 
* the result of commission is 17.9

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

