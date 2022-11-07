#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <io.h>  
#include<iomanip>
#include <string> 
#include <ctime>
#include <cmath>
#include <atlstr.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using  namespace std;
double PC_NOW[1000000][13] = { 0 };   //Power state for present time-step
double PC_PRE[1000000][13] = { 0 };   //Power state for previous time-step
int PC_Total;
double Period;
double Energy;
double K1D, K2D, Krad, Ki;
double refl;
double N_out = 0, S_out = 0, W_out = 0, E_out = 0;
double Vertical_out = 0, Internal_out = 0;
double Total_Period, P1D, P2D, Prad, Pi, Pforward;
double alpha_para, alpha_flag, alpha_parameter;
double mode_data[490000];

ofstream fout;
ofstream val;

/* Input parameters from file parameters.txt */

/* Convert Kappas into probability(K to P) */
double Transfer(double K)
{	return (1 / K) * pow(10, 4);}

double Calculate_Percent(double K)
{	return (1 - exp(-1)) / (K / Period);}

/* Optical power calculation in each direcation */
double Calculate_Energy_N(double N_in, double S_in, double W_in, double E_in)
{	return (S_in * Pforward + W_in * P2D + E_in * P2D + N_in * P1D);}

double Calculate_Energy_S(double N_in, double S_in, double W_in, double E_in)
{	return (N_in * Pforward + (W_in + E_in) * P2D + S_in * P1D);}

double Calculate_Energy_W(double N_in, double S_in, double W_in, double E_in)
{	return (E_in * Pforward + (N_in + S_in) * P2D + W_in * P1D);}

double Calculate_Energy_E(double N_in, double S_in, double W_in, double E_in)
{	return (W_in * Pforward + (N_in + S_in) * P2D + E_in * P1D);}

double Calculate_Energy_Vertical(double N_in, double S_in, double W_in, double E_in)
{	return ((N_in + S_in + W_in + E_in) * Prad * 2);}

double Calculate_Energy_Internal(double N_in, double S_in, double W_in, double E_in)
{	return ((N_in + S_in + W_in + E_in) * Pi);}


/* Scattering model */
bool Initialize()
{
	alpha_flag = 0.0;
	alpha_parameter = Krad;
	K1D = Transfer(K1D);
	K2D = Transfer(K2D);
	Krad = Transfer(Krad);
	Ki = Transfer(Ki);
	P1D = Calculate_Percent(K1D);
	P2D = Calculate_Percent(K2D);
	Prad = Calculate_Percent(Krad);
	Pi = Calculate_Percent(Ki);
	Pforward = 1.0 - (P1D + P2D * 2 + Prad * 2 + Pi);
	return true;
}


/* Scattering model */
void Simulator(int ord, int index,int ts)
{
	bool Even_odd = ord % 2;   //Judge the order number is Even or Odd 
	int TimeStep, PC_Counter;
	PC_Total = (ord / 2) * (ord / 2);
	PC_Counter = PC_Total;
	double Output_Total = 0;
	double Ver_Total = 0;
	double Int_Total = 0;
	memset(PC_NOW, 0, sizeof(PC_NOW));
	memset(PC_PRE, 0, sizeof(PC_PRE));
	double alpha_para = 0.0;
	bool TimeOut = true;

	for (TimeStep = 0; (TimeOut); TimeStep++)
	{

		for (PC_Counter = 0; (PC_Counter < PC_Total); PC_Counter++)
		{
			double loss = 0;

		
			PC_NOW[PC_Counter][0] = TimeStep;//make record for debug
			PC_NOW[PC_Counter][1] = PC_Counter;//make record for debug
			bool dir[4] = { 1, 1, 1, 1 };   //N-S-W-E identifiers  

			/* Locate the pc */
			if (PC_Counter / (ord / 2) == 0)  // At the bottom line
				{dir[1] = 0;}
			else if ((PC_Counter / (ord / 2)) == ((ord / 2) - 1))	 //At the top line
				{dir[0] = 0;}  //Mirror Method
			if (PC_Counter % (ord / 2) == 0)	 //At the leftmost line
				{dir[2] = 0;}	
			else if ((PC_Counter % (ord / 2)) == ((ord / 2) - 1))	 //At the rightmost line
				{dir[3] = 0;}//Mirror Method			  
			if (dir[0] == 0)
			{	
				if (Even_odd == 0) //Input of Even boundary
				{PC_NOW[PC_Counter][2] = PC_PRE[PC_Counter][6] * (1 - Pi);}   //Nin = Nout (Mirror)			
				else  //Input of Odd boundary
				{PC_NOW[PC_Counter][2] = PC_PRE[PC_Counter - (ord / 2)][6] * (1 - Pi);}   //Nin = Nout (Mirror)		
			}
			else
			{PC_NOW[PC_Counter][2] = PC_PRE[PC_Counter + (ord / 2)][7] * (1 - Pi);}
			if (dir[1] == 0)
			{PC_NOW[PC_Counter][3] = PC_PRE[PC_Counter][7] * refl * (1 - Pi);}			
			else
			{PC_NOW[PC_Counter][3] = PC_PRE[PC_Counter - (ord / 2)][6] * (1 - Pi);}
			if (dir[2] == 0)
			{PC_NOW[PC_Counter][4] = PC_PRE[PC_Counter][8] * refl * (1 - Pi);}
			else
			{PC_NOW[PC_Counter][4] = PC_PRE[PC_Counter - 1][9] * (1 - Pi);}
			if (dir[3] == 0)
			{
				if (Even_odd == 0) //Input of Even boundary
				{PC_NOW[PC_Counter][5] = PC_PRE[PC_Counter][9] * (1 - Pi);}   //Ein = Eout (Mirror)
				else //Input of Odd boundary
				{PC_NOW[PC_Counter][5] = PC_PRE[PC_Counter - 1][9] * (1 - Pi);}   //Ein = Eout (Mirror)
			}
			else
			{PC_NOW[PC_Counter][5] = PC_PRE[PC_Counter + 1][8] * (1 - Pi);}
			
			/* Energy injection in here, auto-increase by one after assignment the values */ 
			PC_NOW[PC_Counter][6]  = Calculate_Energy_N(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
			PC_NOW[PC_Counter][7]  = Calculate_Energy_S(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
			PC_NOW[PC_Counter][8]  = Calculate_Energy_W(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
			PC_NOW[PC_Counter][9]  = Calculate_Energy_E(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]) + 1;
			PC_NOW[PC_Counter][10] = Calculate_Energy_Vertical(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]);
			PC_NOW[PC_Counter][11] = Calculate_Energy_Internal(PC_NOW[PC_Counter][2], PC_NOW[PC_Counter][3], PC_NOW[PC_Counter][4], PC_NOW[PC_Counter][5]);

			if (Even_odd == 0)   //Output of Even boundary
			{						
				if (dir[1] == 0)
				{loss = loss + PC_NOW[PC_Counter][7] * (1 - refl);}				
				if (dir[2] == 0)
				{loss = loss + PC_NOW[PC_Counter][8] * (1 - refl);}					
			}

			else   //Output of Odd boundary
			{
				if (dir[0] == 0)  //N//No Actual Nout
				{PC_NOW[PC_Counter][10] = PC_NOW[PC_Counter][10] / 2;	 //Divide the PC into 1/2
				 PC_NOW[PC_Counter][11] = PC_NOW[PC_Counter][11] / 2;}	 //Divide the PC into 1/2	 									
				if (dir[1] == 0)  //S
				{
					if (dir[3] == 0)  //In the bottom right corner
					{loss = loss + PC_NOW[PC_Counter][7] * (1 - refl) / 2;}  //Half of the Sout
					else
					{loss = loss + PC_NOW[PC_Counter][7] * (1 - refl);}  // If not, the Sout is full	
				}
				if (dir[2] == 0)  //W
				{
					if (dir[0] == 0)  //In the top left corner
					{loss = loss + PC_NOW[PC_Counter][8] * (1 - refl) / 2;}  //Half of the Wout			
					else
					{loss = loss + PC_NOW[PC_Counter][8] * (1 - refl);}  // If not, the Wout is full
				}
				if (dir[3] == 0)  //E//No actual Eout
				{PC_NOW[PC_Counter][10] = PC_NOW[PC_Counter][10] / 2;	  //Divide the PC into 1/2
				 PC_NOW[PC_Counter][11] = PC_NOW[PC_Counter][11] / 2;}	  //Divide the PC into 1/2				 					  	
			}	

			/*calculate losses here*/
			Ver_Total              = Ver_Total + PC_NOW[PC_Counter][10] * 4;	 //Calculate total vertical loss (x4)
			Int_Total              = Int_Total + PC_NOW[PC_Counter][11] * 4;	 //Calculate total internal loss (x4)
			Output_Total           = Output_Total + loss * 4;  //Calculate total in-plane loss (x4)
			PC_NOW[PC_Counter][12] = loss;//the in-plane loss
		}
		alpha_para = alpha_parameter * Output_Total / Ver_Total;		
		printf("%d\n", TimeStep);
		/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (TimeStep == ts)
		{
			printf("alpha = %f", alpha_para);
			TimeOut = 0;
			fout <<ord <<"\r" << setprecision(12) << alpha_para << "\r";
		}
		/*active here to get mode data*/
		/*if (TimeStep == ts)
		{
			printf("alpha = %f", alpha_para);
			TimeOut = 0;
			double Vertical_atcurrent = 0.0;
			for (int i = 1; i <= (ord / 2); i++)
			{
				for (int j = 1; j <= (ord / 2); j++)
				{fout << setprecision(12) << PC_NOW[(i - 1) * (ord / 2) + j - 1][10] << ",";
				 Vertical_atcurrent = Vertical_atcurrent + PC_NOW[(i - 1) * (ord / 2) + j - 1][10];}
				fout << "\r";
			}
		}*/
		/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/* Prepare for timestep jump */
		for (PC_Counter = 0; PC_Counter < PC_Total; PC_Counter++)
		{
			for (int i = 0; i < 13; i++)
			{PC_PRE[PC_Counter][i] = PC_NOW[PC_Counter][i];
			 PC_NOW[PC_Counter][i] = 0;}			
		}
	}
}

/// <main program here>
/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// remember to change the file name!!
/// <returns></returns>
int main()
{
	printf_s("please type in period(mm)\n");
	scanf_s("%lf", &Period);
	printf_s("please type in K1D(cm-1)\n");
	scanf_s("%lf", &K1D);
	printf_s("please type in K2D(cm-1)\n");
	scanf_s("%lf", &K2D);
	printf_s("please type in Krad(cm-1)\n");
	scanf_s("%lf", &Krad);
	printf_s("please type in Ki(cm-1)\n");
	scanf_s("%lf", &Ki);
	printf_s("please type in reflectivity(0-1)\n");
	scanf_s("%lf", &refl);
	int timestep;
	printf_s("please type in timestep\n");
	scanf_s("%d", &timestep);
	Initialize();
	printf_s("please type in saving name(.csv)\n");
	char str[] = {""};
	scanf_s("%s", &str,1);
	int OrderArray[] = {500};//,200,300,400,500,600,700,800,900,1000 	

	fout.open(str);
	for (int i = 0; i <1; i++)

	{
		Simulator(OrderArray[i], i,timestep);
		fout << "\r";
		printf("%d finshed \n\n", OrderArray[i]);	
	}
	fout.close();
}