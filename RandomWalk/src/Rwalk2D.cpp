#include "Rwalk2D.h"
#include <cmath>
#include "TRandom3.h"
#include <time.h>
#include "TGraph.h"

using namespace std;

Rwalk2D::Rwalk2D(
	int N_,
	double x_,
	double y_, 
	double dt_,
	string key,
	double step
) : N(N_), x0(x_), y0(y_), dt(dt_) {

	if (key == "uniform"){
		func = [step](double x){ return x*step; };
	}

	else if(key == "exp"){
		func = [](double x) { return - log(1-x); };
	}

	else {
		key = "const";
		func = [step](double x){ return step; };
	}
}

void Rwalk2D::Run(int nsteps){
	TRandom3 r;
	r.SetSeed(time(NULL));

	for(int i=0; i < N; i++){
		vector<pair<double, double> > traj;
		traj.push_back({x0, y0});
		for(int j=0; j < nsteps; j++){
			double radius = func(r.Uniform());
			double theta = 2 * M_PI *r.Uniform();
			
			auto pos = traj.back();
			traj.push_back(
			{
				pos.first + radius * cos(theta), 
				pos.second + radius * sin(theta)
			});
		}

		mT[i] = traj;
	}
}

const vector<pair<double, double>>& Rwalk2D::GetTrajectory(int n){
	return mT[n];
}

double Rwalk2D::GetTimeStep(){
	return dt;
}

TMultiGraph* Rwalk2D::GetGraph(){
	auto mg = new TMultiGraph;
	for(int i=0; i<N; i++){
		auto g = new TGraph; 
		for(const auto& u: mT[i]){
			g->AddPoint(u.first, u.second);
		}
		g->SetLineWidth(4);
		g->SetLineColor(i+2);
		mg->Add(g);
	}

	return mg;
}

void Rwalk2D::SetCustomPDF(function<double(double)> f){
	func = f;
}