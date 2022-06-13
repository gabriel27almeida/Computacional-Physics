#include "IntegDeriv.h"
#include <iostream>
#include <TRandom3.h>
#include <time.h>
#include <cmath>

using namespace std;

IntegDeriv::IntegDeriv(Functor& func) : F(func) {;}

double IntegDeriv::FirstDerivative(double x){
	double h = 1e-4;
	return ( F(x - 2*h) + 8 * F(x + h) - (8 * F(x - h) + F(x + 2*h))) / (12*h);
}

double IntegDeriv::SecondDerivative(double x){
	double h = 1e-4;
	return ( -F(x - 2*h) + 16 * F(x - h) - 30 * F(x) + 16 * F(x + h) - F(x + 2*h) ) / (12*h*h);
}

void IntegDeriv::TrapezoidalRule(double xi, double xf, double& Integral, double& Error ){
	int k = 0;
	int up_lim = 1;
	double nIntegral = (xf - xi)/2 * (F(xf) + F(xi));

	int MAX_NUM_ITER = 20; //infinite loop safety
	do{
		//store last value
		Integral = nIntegral;

		//calculate new value
		nIntegral = Integral/2; 
		double sum = 0;
		for(int i=1; i <= up_lim; i++){
			sum += F(xi + (2*i - 1) * (xf - xi) / (2 * up_lim));
		}
		nIntegral += (xf - xi) / (2 * up_lim) * sum;
		
		//prepare next iteration
		up_lim *= 2;
		k++;
	}while(k < MAX_NUM_ITER && abs(nIntegral - Integral) > Error);

	Error = abs(nIntegral - Integral);
	Integral = nIntegral;
}

void IntegDeriv::simpsonRule(double xi, double xf, double& Integral, double& Error){
	int n = (int) ( pow(xf - xi, 5) / (180 * Error) ); //Number of slices
	if (n%2) n++;
	
	double h = (xf - xi)/n;
	Integral = 0;
	for(int i=0; i<n/2; i++){
		double x = xi + 2*h*i;
		Integral += (F(x) + 4*F(x+h) + F(x+2*h))*h/3;
	}
}

void IntegDeriv::MonteCarlo(double xi, double xf, double& Integral, double& Error){
	TRandom3 r(time(NULL));
	
	int MAX_NUM_ITER = 1000000; //infinite loop safety
	double sum_sq = 0, sum = 0;
	int n = 1;
	double er;
	do{
		double f = F(xi + (xf - xi)* r.Uniform());

		sum += f;
		sum_sq += f*f;

		er = sqrt( (sum_sq/n - sum* sum / n / n) / n);
		er *= (xf - xi);

		n++;
	}while(n < MAX_NUM_ITER && (n < 3 || er > Error));
	
	Integral = sum/n * (xf - xi);
	Error = er;
}