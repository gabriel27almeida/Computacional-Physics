#ifndef __INTEGDERIV__ 
#define __INTEGDERIV__
#include "Functor.h" 

class IntegDeriv {
	public: 
		IntegDeriv(Functor& func);
		~IntegDeriv() = default;

		// integration methods
		void TrapezoidalRule(double xi, double xf, double& Integral, double& Error);
		void simpsonRule(double xi, double xf, double& Integral, double& Error); 
		void MonteCarlo(double xi, double xf, double& Integral, double& Error);
		
		// derivative methods
		double FirstDerivative(double x);
		double SecondDerivative(double x);

	private: 
		Functor& F;
};
#endif