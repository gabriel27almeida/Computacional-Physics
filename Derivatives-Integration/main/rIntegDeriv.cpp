#include "Functor.h"
#include "IntegDeriv.h"
#include <cmath>
#include <iostream>

#include "TApplication.h"

using namespace std;

int main(){
	class MyFunction : public Functor {
	public:
		MyFunction(string s) {;}
		~MyFunction() = default;

		double operator()(double x){
			return x*sin(2*x);
		}
	};

	MyFunction f("f");
	cout << "f(1) = " << f(1) << endl;


	TApplication app("", nullptr, nullptr);
	f.Draw(-3, 3, 100); 

	IntegDeriv ID(f);
	cout << "f'(0) = " << ID.FirstDerivative(0) << endl;
	cout << "f\"(0) = " << ID.SecondDerivative(0) << endl;

	double Integral, Error = 1e-5;

	cout << "\nIntegral from 0 to 1\n";

	ID.TrapezoidalRule(0, 1, Integral, Error); 
	cout << "Trapezoidal: " << Integral << " ± " << Error << endl;

	Error = 1e-5;
	ID.simpsonRule(0, 1, Integral, Error); 
	cout << "Simpson: " << Integral << " ± " << Error << endl;

	Error = 1e-5;
	ID.MonteCarlo(0, 1, Integral, Error); 
	cout << "Monte Carlo: " << Integral << " ± " << Error << endl;





}
