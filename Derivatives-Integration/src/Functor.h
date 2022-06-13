#ifndef __FUNCTOR__ 
#define __FUNCTOR__
#include <string> 
#include "TCanvas.h" 

class Functor {
	public:
		Functor(std::string s="Functor") : name(s) {;} 
		~Functor() = default;

		virtual double operator()(double x);
		
		// args:
		// xi, xf ........... xmin and xmax limits for function display
		// num .............. number of sampling points to be used o TGraph
		// xtitle, ytitle ... axis titles
		virtual void Draw(
			double xi, 
			double xf, 
			int num, 
			std::string xtitle="x", 
			std::string ytitle="y"
		);
	protected:
		static TCanvas *c;
		std::string name;
};
#endif