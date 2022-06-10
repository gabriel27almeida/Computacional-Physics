#include "Rwalk1D.h"
#include <TRandom3.h>
#include <time.h>
#include <TGraph.h>

using namespace std;

Rwalk1D::Rwalk1D(
	int N, double x, // N=nb of particles, x=x(0) 
	double pL, double pR, // probabilities Left Right
	double dt, double dx // time and space steps
)
{
	x0 = x;
	this->N = N;
	this->pL = pL;
	this->pR = pR;
	this->dt = dt;
	this->dx = dx;

	for(int i=1; i<= N; i++){
		vector<double> v;
		v.push_back(x);
		mT[i] = v;
	}
}

void Rwalk1D::Run(int nsteps){
	TRandom3 r(time(NULL));
	for(int i=0; i<nsteps; i++){
		for(int j = 1; j<= N; j++){
			double p = r.Uniform();
			double nx = mT[j][i];
			if (p<pL) nx -= dx;
			else if (p < pL+pR) nx += dx;
			
			mT[j].push_back(nx);
		}
	}
}

const std::vector<double>& Rwalk1D::GetTrajectory(int n){
	return mT[n];
}
		
		
double Rwalk1D::GetTimeStep(){
	return dt;
}

double Rwalk1D::GetSpaceStep(){
	return dx;
}

TMultiGraph* Rwalk1D::GetGraph(){
	TMultiGraph* ans = new TMultiGraph;

	for(int i=1; i<=N; i++){
		TGraph* g = new TGraph;
		int j = 0;
		for(auto u: mT[i]){
			g->AddPoint(j*dt, u);
			j++;
		}
		g->SetLineColor(i+1);
		ans->Add(g);
	}

	return ans;

}