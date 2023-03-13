# Probabilistic-Markov-Chains-Modelling-(Quarter version)
This is the code of generally useing Probabilistic Markov Chain modelling (quarter version)
This simulation links defines the scattering parameters of the photonic crystal (PC) and device level losses of the PCSEL.
The criteria for conversion, agreement with data from the literature of the numerical model and other applications are discussed in following papers:
URL1
URL2

## Commission Information
* Please use following parameters for commission:
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 
 * K1D = 

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

