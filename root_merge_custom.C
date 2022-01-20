// script to add different trees/branches...
#include "TTree.h"
#include "TFile.h"
#include "TTree.h"
#include "TTree.h"
#include <string>
#include <stdlib.h>

using namespace std;
void root_merge_custom(const string& input_str){
	string filename_unpacked;
	string filename_calibrated;
	filename_unpacked = string("/scratch8/ge37liw/workingspace/exp_s455/data/unpacked/s455_03_273_") + input_str + string("_unpacked.root");
	filename_calibrated = ("/scratch8/ge37liw/workingspace/exp_s455/data/calibrated/s455_03_273_") + input_str + string("_calibrated.root");

	const char* char_filename_unpacked = filename_unpacked.c_str();
	const char* char_filename_calibrated = filename_calibrated.c_str();
	TFile* unpacked_tfile = new TFile(char_filename_unpacked);
	TFile* calibrated_tfile = new TFile(char_filename_calibrated);
	TTree* tr_mapped = (TTree*)unpacked_tfile->Get("evt");
	TTree* tr_cal = (TTree*)calibrated_tfile->Get("evt");
	tr_cal->SetBranchStatus("*", 0);
	for (auto activeBranchName : {"SofSciCalData", "TofWHitData"})
		tr_cal->SetBranchStatus(activeBranchName, 1);
	tr_mapped->AddFriend("evt_jt = evt",char_filename_calibrated);

	TFile newfile("small.root", "recreate");
	TTree* newtree = tr_mapped->CloneTree();
//	newtree->AddFriend("evt_jt = evt",char_filename_unpacked);
	//newtree = tr_mapped->CloneTree();
	newtree->Print();
	newtree->Write();


}
