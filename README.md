# Probabilistic-Markov-Chains-Modelling-(Quarter)
this is the basic code for Probabilistic Markov Chains modelling (quarter version)

##commission information


## PC atom information array
* Array PC_NOW[PC number][13] & PC_PRE[PC number][13]:
* the limit of PC number is 10000000, for quarter PCSEL simulator, that allow maximum 2000*2000 PC atoms matrix.
* content of information array:
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

