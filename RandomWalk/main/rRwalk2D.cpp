#include "Rwalk2D.h"

// For drawing
#include "TApplication.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TAxis.h"

int main(){
	Rwalk2D RW2; //default = constant step
	Rwalk2D RW2exp(1, 0, 0, 1, "exp");

	RW2.Run(100);
	RW2exp.Run(100);

	// Draw trajectories

	TApplication app("app", nullptr, nullptr);
	TCanvas c("","",1200, 800);

	TMultiGraph* mg = RW2.GetGraph();
	mg->Draw("APL");
	mg->SetTitle("Random Walk 2D (step = 1)");
	mg->GetXaxis()->SetName("time");
	mg->GetYaxis()->SetName("x");

	c.Update();
	c.WaitPrimitive();



	TMultiGraph* mg2 = RW2exp.GetGraph();
	mg2->Draw("APL");
	mg2->SetTitle("Random Walk 2D (exponential step)");
	mg2->GetXaxis()->SetName("time");
	mg2->GetYaxis()->SetName("x");

	c.Update();
	c.WaitPrimitive();
}