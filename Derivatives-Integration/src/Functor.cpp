#include "Functor.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TAxis.h"

TCanvas* Functor::c = nullptr;

///////////////////////////
//
double Functor::operator()(double x){
	return 1;
}

///////////////////////////
//
void Functor::Draw(
	double xi, 
	double xf, 
	int num, 
	std::string xtitle, 
	std::string ytitle
){
	if(!c) c = new TCanvas("c", "c", 1200, 800);

	TGraph* graph = new TGraph(num);

	double dx = (xf-xi) / (num - 1);
	for(int i=0; i < num; i++){
		double x = xi + dx*i;
		graph->SetPoint(i, x, operator()(x));
		//graph->SetPoint(i, x, *this(x)); alternativa
	}

	graph->Draw("APL");
	graph->SetMarkerStyle(25);
	graph->GetXaxis()->SetTitle(xtitle.c_str());
	graph->GetYaxis()->SetTitle(ytitle.c_str());
	graph->SetTitle(name.c_str());

	c->Update();
	c->WaitPrimitive();
	gSystem->ProcessEvents();

}