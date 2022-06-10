#include "Rwalk1D.h"

// For drawing
#include "TApplication.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TAxis.h"

int main(){

	Rwalk1D RW(4); 

	RW.Run(500);
	
	// Draw trajectory

	TApplication app("app", nullptr, nullptr);
	TCanvas c("","",1200, 800);

	TMultiGraph* mg = RW.GetGraph();
	mg->Draw("APL");
	mg->SetTitle("Random Walk 1D");
	mg->GetXaxis()->SetName("time");
	mg->GetYaxis()->SetName("x");

	c.Update();
	c.WaitPrimitive();
}