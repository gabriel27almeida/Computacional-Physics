#ifndef __RWALK2D_H
#define __RWALK2D_H

#include <vector>
#include <map>
#include <TMultiGraph.h>
#include <functional>

using namespace std;

class Rwalk2D {
	public:
		Rwalk2D(
			int N=1, 
			double x=0, 
			double y=0,
			double dt=1,
			string key = "const",
			double step = 1 //step size
			
		);
		~Rwalk2D() = default;
		
		// particle simulation
		void Run(int nsteps); // number of steps 

		//setters
		void SetCustomPDF(function<double(double)>);

		// getters
		const vector<pair<double, double>>& GetTrajectory(int n=0); // particle number 
		double GetTimeStep();
		double GetSpaceStep();

		//draw
		TMultiGraph* GetGraph();

	private:
		double x0, y0; // init coo
		int N; // number of particles
		
		double dt; // steps (time, space)
		map<int, vector< pair<double, double>> > mT; // trajectories
		
		//probability distribution of step length
		function<double(double)> func; //custom PDF (already integrated and inverted)
};

#endif