#ifndef makeRecoKinTuple_h
#define makeRecoKinTuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TLorentzVector.h>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "TRandom3.h"
#include "PUReweight.h"

#include "EventTree.h"
#include "EventPick.h"
#include "Selector.h"

#include "JECvariation.h"

#include <iomanip>
#include <cmath>

//#include <boost/program_options.hpp>

// Standalone Btag scale factor tool from 
// https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration
#include "BTagCalibrationStandalone.h"

// Header file for the classes stored in the TTree if any.
#include "vector"

#include "METzCalculator.h"
#include "TopEventCombinatorics.h"

// Header file that includes all of the event luminosity scaling
#include "ScaleFactorFunction.h"

#include "muSF_reader.h"
#include "eleSF_reader.h"
#include "UncertaintySourcesList.h"

// Header file for Kinematic Fitting
#include "KinFit.h"


class makeRecoKinTuple {
 public :

  makeRecoKinTuple(char* outputFileName,char** inputFileName);
  makeRecoKinTuple(int ac, char** av);

 private :

  EventTree*	tree;		   
  EventPick*	evtPick;	   
  Selector*	selector;	   
	
  bool	isMC;

  TTree*	outputTree;

  string	sampleType;
  string	systematicType;

  int	eventNum = -1;
  
  bool	isSystematicRun;

  bool	useGenWeightScaling;

  bool	getGenScaleWeights;
  bool	applypdfweight;
  bool	applyqsquare;

  MuonSF*	muSFa;
  MuonSF*	muSFb;
  ElectronSF*	eleSF;

  TH2D*	l_eff;
  TH2D*	c_eff;
  TH2D*	b_eff;

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  // Declaration of leaf types
  Int_t			 _run;
  Long64_t		 _event;
  Int_t			 _lumis;
  Bool_t		 _isData;
  Long64_t               _skim_entryId;

  Float_t		 _PUweight;
  Float_t		 _PUweight_Up;
  Float_t		 _PUweight_Do;
	
  Float_t		 _q2weight_Up;
  Float_t		 _q2weight_Do;
  Float_t		 _q2weight_nominal;
  std::vector<float>	 _genScaleSystWeights;

  Float_t		 _pdfWeight;
  Float_t		 _pdfuncer;
  Float_t		 _pdfweight_Up;
  Float_t		 _pdfweight_Do;
  std::vector<float>	 _pdfSystWeight;

  Float_t		 _ISRweight_Up;
  Float_t		 _ISRweight_Do;

  Float_t		 _FSRweight_Up;
  Float_t		 _FSRweight_Do;

  float			 _prefireSF;
  float			 _prefireSF_Up;
  float			 _prefireSF_Do;

  float			 _btagWeight_1a;
  float			 _btagWeight_1a_b_Up;
  float			 _btagWeight_1a_b_Do;
  float			 _btagWeight_1a_l_Up;
  float			 _btagWeight_1a_l_Do;

  std::vector<float>	 _btagWeight;
  std::vector<float>	 _btagWeight_b_Up;
  std::vector<float>	 _btagWeight_b_Do;
  std::vector<float>	 _btagWeight_l_Up;
  std::vector<float>	 _btagWeight_l_Do;

  std::vector<float>	 _btagSF;
  std::vector<float>	 _btagSF_b_Up;
  std::vector<float>	 _btagSF_b_Do;
  std::vector<float>	 _btagSF_l_Up;
  std::vector<float>	 _btagSF_l_Do;

  Float_t		 _muEffWeight;
  Float_t		 _muEffWeight_Up;
  Float_t		 _muEffWeight_Do;

  Float_t		 _muEffWeight_IdIso;
  Float_t		 _muEffWeight_IdIso_Up;
  Float_t		 _muEffWeight_IdIso_Do;

  Float_t		 _muEffWeight_Trig;
  Float_t		 _muEffWeight_Trig_Up;
  Float_t		 _muEffWeight_Trig_Do;

  Float_t		 _eleEffWeight;
  Float_t		 _eleEffWeight_Up;
  Float_t		 _eleEffWeight_Do;

  Float_t		 _eleEffWeight_IdReco;
  Float_t		 _eleEffWeight_IdReco_Up;
  Float_t		 _eleEffWeight_IdReco_Do;

  Float_t		 _eleEffWeight_Trig;
  Float_t		 _eleEffWeight_Trig_Up;
  Float_t		 _eleEffWeight_Trig_Do;
  
  Float_t		 _evtWeight;
  Float_t		 _lumiWeight;
  Float_t		 _sampleWeight;
  Double_t               _nMC_total;
  Double_t               _nMC_totalUS;
  Float_t                _xss;

  Int_t			 _nVtx;
  Int_t			 _nGoodVtx;
  Bool_t		 _isPVGood;
  
  Float_t		 _genMET;
        
  Float_t		 _pfMET;
  Float_t		 _pfMETPhi;
  Float_t		 _nu_px;
  Float_t		 _nu_py;
  Float_t		 _nu_pz;
  Float_t		 _nu_pz_other;
  Float_t		 _WtransMass;
  
  bool                   _hasConv;
  bool                   _hasRDPass;
  int                    _ltype;
  int                    _ltypekF;
  Float_t		 _chi2;
  int			 _NDF;
  int			 _Nbiter;
  Float_t		 _M_jj;
  Float_t		 _M_jjkF;
  int			 _bjlep_id;
  int			 _bjhad_id;
  int			 _cjhad_id;
  int			 _sjhad_id;
  Float_t		 _lepPt;
  Float_t		 _lepEta;
  Float_t		 _lepPhi;
  Float_t		 _lepEnergy;
  Float_t		 _metPx;
  Float_t		 _metPy;
  Float_t		 _metPz;
  Float_t		 _jetBlepPt;
  Float_t		 _jetBlepEta;
  Float_t		 _jetBlepPhi;
  Float_t		 _jetBlepEnergy;
  Float_t		 _jetBhadPt;
  Float_t		 _jetBhadEta;
  Float_t		 _jetBhadPhi;
  Float_t		 _jetBhadEnergy;
  Float_t		 _jetChadPt;
  Float_t		 _jetChadEta;
  Float_t		 _jetChadPhi;
  Float_t		 _jetChadEnergy;
  Float_t		 _jetShadPt;
  Float_t		 _jetShadEta;
  Float_t		 _jetShadPhi;
  Float_t		 _jetShadEnergy;

  /* Float_t		 _lepPtDiff; */
  /* Float_t		 _blepPtDiff; */
  /* Float_t		 _bhadPtDiff; */
  /* Float_t		 _chadPtDiff; */
  /* Float_t		 _shadPtDiff; */
  /* Float_t		 _cshadPtDiff; */
  /* Float_t		 _M_bjj; */
  /* Float_t		 _M_jj; */
  /* Float_t		 _TopHad_pt; */
  /* Float_t		 _TopHad_eta; */
  /* Float_t		 _TopLep_pt; */
  /* Float_t		 _TopLep_eta; */
  /* Float_t		 _TopLep_charge; */
  /* Float_t		 _chi2; */
  /* Bool_t		 _MassCuts; */
  /* int		 _blep_id; */
  /* int		 _bhad_id; */

  /* Float_t		 _DilepMass; */
  /* Float_t		 _DilepDelR; */

  Int_t			 _nEle;
  Int_t			 _nEleLoose;
  std::vector<float>	 _elePt;
  std::vector<float>	 _elePhi;
  std::vector<float>	 _eleSCEta;
  std::vector<float>	 _elePFRelIso;
  
  Int_t			 _nMu;
  Int_t			 _nMuLoose;
  std::vector<float>	 _muPt;
  std::vector<float>	 _muEta;
  std::vector<float>	 _muPhi;
  std::vector<float>	 _muPFRelIso;
  std::vector<float>     _muRoccoR;

  Int_t			 _nJet;
  Int_t			 _nBJet;
  std::vector<float>	 _jetPt;
  std::vector<float>	 _jetEta;
  std::vector<float>	 _jetPhi;
  std::vector<float>	 _jetMass;

  Int_t			 _nfwdJet;
  std::vector<float>	 _fwdJetPt;
  std::vector<float>	 _fwdJetEta;
  std::vector<float>	 _fwdJetPhi;
  std::vector<float>	 _fwdJetMass;

  std::vector<float>	 _jetCMVA;
  std::vector<float>	 _jetCSVV2;
  std::vector<float>	 _jetDeepB;
  std::vector<float>	 _jetDeepC;

  std::vector<Int_t>	 _jetGenJetIdx;

  /* std::vector<int>    _jetPartonID; */
  /* std::vector<float>  _jetGenJetPt; */
  /* std::vector<int>    _jetGenPartonID; */
  /* std::vector<float>  _jetGenPt; */
  /* std::vector<float>  _jetGenEta; */
  /* std::vector<float>  _jetGenPhi; */

  Int_t			 _nGenJet;
  std::vector<float>	 _genJetPt;
  std::vector<float>	 _genJetEta;
  std::vector<float>	 _genJetPhi;
  std::vector<float>	 _genJetMass;
  std::vector<float>	 _genJetPartonFlavour;
  std::vector<float>	 _genJetHadronFlavour;

  Int_t			 _nLHEPart;
  Int_t			 _nGenPart;
  std::vector<float>	 _genPt;
  std::vector<float>	 _genEta;
  std::vector<float>	 _genPhi;
  std::vector<float>	 _genMass;
  std::vector<int>	 _genStatus;
  std::vector<int>	 _genStatusFlag;
  std::vector<int>	 _genPDGID;
  std::vector<int>	 _genMomIdx;
  /* std::vector<int>    _genMomPID; */
  /* std::vector<int>    _genGMomPID; */

  double		 _M3;
  double		 _HT;
  bool			 _passPresel_Ele;
  bool			 _passPresel_Mu;
  bool			 _passAll_Ele;
  bool			 _passAll_Mu;
  bool			 _passTrigger_ele;
  bool			 _passTrigger_mu;
  bool			 _passFilter;
  /////////////////////// End of Tree leaf and branches ///////////////////////////
  bool  dileptonsample;

  METzCalculator metZ;
  TopEventCombinatorics topEvent;
  TLorentzVector jetVector;
  TLorentzVector lepVector;
  TLorentzVector lepVector2;
  TLorentzVector METVector;
  std::vector<TLorentzVector> ljetVectors;
  std::vector<TLorentzVector> bjetVectors;
  std::vector<TLorentzVector> jetVectors;

  float lepCharge;


  std::vector<double> ljetResVectors;
  std::vector<double> bjetResVectors;

  std::vector<double> jetResolutionVectors;
  std::vector<double> jetBtagVectors;

  TLorentzVector bhad;
  TLorentzVector blep;
  TLorentzVector Wj1;
  TLorentzVector Wj2;

  TLorentzVector leptonBF, bjlepBF, bjhadBF, cjhadBF, sjhadBF; 
  TLorentzVector leptonAF, neutrinoAF, bjlepAF, bjhadAF, cjhadAF, sjhadAF; 


  KinFit kinFit;
  /* std::vector<bool> isBjet; */
  /* std::vector<int> b_ind; */
  /* std::vector<int> j_ind; */


  void InitVariables();
  //void FillEvent(std::string year);
  void FillEvent(std::string year, bool isHemVetoObj);
  void InitBranches();

  double SFtop(double pt);
  double topPtWeight();
  void loadBtagEff(string sampleType, string year);
  float getBtagSF_1a(string sysType, BTagCalibrationReader reader, bool verbose=false);
  vector<float> getBtagSF_1c(string sysType, BTagCalibrationReader reader, vector<float> &btagSF);

  /* double getMuSF(int muInd, int systLevel); */
  /* double getEleSF(int eleInd, int systLevel); */
};


void makeRecoKinTuple::InitBranches(){
  
    outputTree->Branch("run"			, &_run				);
    outputTree->Branch("event"			, &_event			);    
    outputTree->Branch("lumis"			, &_lumis			);
    outputTree->Branch("isData"			, &_isData			);
    outputTree->Branch("skim_entryId"  		, &_skim_entryId       		);
    
    outputTree->Branch("PUweight"		, &_PUweight			);
    if (!isSystematicRun){
	outputTree->Branch("PUweight_Up"	, &_PUweight_Up			);
	outputTree->Branch("PUweight_Do"	, &_PUweight_Do			);
    }

    if (!isSystematicRun){
	outputTree->Branch("q2weight_Up"	, &_q2weight_Up			);
	outputTree->Branch("q2weight_Do"	, &_q2weight_Do			);
	outputTree->Branch("q2weight_nominal"	, &_q2weight_nominal		);
	/* outputTree->Branch("genScaleSystWeights", &_genScaleSystWeights		); */
	
	outputTree->Branch("pdfWeight"		, &_pdfWeight			);
	outputTree->Branch("pdfuncer"		, &_pdfuncer			);
	outputTree->Branch("pdfweight_Up"	, &_pdfweight_Up		);
	outputTree->Branch("pdfweight_Do"	, &_pdfweight_Do		);
	/* outputTree->Branch("pdfSystWeight"	, &_pdfSystWeight		); */

	outputTree->Branch("ISRweight_Up"	, &_ISRweight_Up		);
	outputTree->Branch("ISRweight_Do"	, &_ISRweight_Do		);

	outputTree->Branch("FSRweight_Up"	, &_FSRweight_Up		);
	outputTree->Branch("FSRweight_Do"	, &_FSRweight_Do		);
    }

    /* outputTree->Branch("prefireSF"		, &_prefireSF			); */
    /* if (!isSystematicRun){ */
    /* 	outputTree->Branch("prefireSF_Up"	, &_prefireSF_Up		); */
    /* 	outputTree->Branch("prefireSF_Do"	, &_prefireSF_Do		); */
    /* } */

    outputTree->Branch("btagWeight"		, &_btagWeight			);
    outputTree->Branch("btagWeight_1a"		, &_btagWeight_1a		);
    if (!isSystematicRun){
	/* outputTree->Branch("btagWeight_b_Up"	, &_btagWeight_b_Up		); */
	/* outputTree->Branch("btagWeight_b_Do"	, &_btagWeight_b_Do		); */
	/* outputTree->Branch("btagWeight_l_Up"	, &_btagWeight_l_Up		); */
	/* outputTree->Branch("btagWeight_l_Do"	, &_btagWeight_l_Do		); */
	outputTree->Branch("btagWeight_1a_b_Up"	, &_btagWeight_1a_b_Up		);
	outputTree->Branch("btagWeight_1a_b_Do"	, &_btagWeight_1a_b_Do		);
	outputTree->Branch("btagWeight_1a_l_Up"	, &_btagWeight_1a_l_Up		);
	outputTree->Branch("btagWeight_1a_l_Do"	, &_btagWeight_1a_l_Do		);
    }
    /* outputTree->Branch("btagSF"			, &_btagSF			);  */
    /* if (!isSystematicRun){ */
    /*   outputTree->Branch("btagSF_b_Up"		, &_btagSF_b_Up			); */
    /*   outputTree->Branch("btagSF_b_Do"		, &_btagSF_b_Do			); */
    /*   outputTree->Branch("btagSF_l_Up"		, &_btagSF_l_Up			); */
    /*   outputTree->Branch("btagSF_l_Do"		, &_btagSF_l_Do			); */
    /* } */
    outputTree->Branch("muEffWeight"		, &_muEffWeight			);
    outputTree->Branch("muEffWeight_IdIso"	, &_muEffWeight_IdIso		);
    outputTree->Branch("muEffWeight_Trig"	, &_muEffWeight_Trig		);
    if (!isSystematicRun){
    	outputTree->Branch("muEffWeight_Up"	, &_muEffWeight_Up		);
    	outputTree->Branch("muEffWeight_Do"	, &_muEffWeight_Do		);

    	outputTree->Branch("muEffWeight_IdIso_Up", &_muEffWeight_IdIso_Up	);
    	outputTree->Branch("muEffWeight_IdIso_Do", &_muEffWeight_IdIso_Do	);

    	outputTree->Branch("muEffWeight_Trig_Up", &_muEffWeight_Trig_Up		);
    	outputTree->Branch("muEffWeight_Trig_Do", &_muEffWeight_Trig_Do		);
    }
    outputTree->Branch("eleEffWeight"		, &_eleEffWeight		);
    outputTree->Branch("eleEffWeight_IdReco"	, &_eleEffWeight_IdReco		);
    outputTree->Branch("eleEffWeight_Trig"	, &_eleEffWeight_Trig		);
    if (!isSystematicRun){
    	outputTree->Branch("eleEffWeight_Up"	, &_eleEffWeight_Up		);
    	outputTree->Branch("eleEffWeight_Do"	, &_eleEffWeight_Do		);

    	outputTree->Branch("eleEffWeight_IdReco_Up", &_eleEffWeight_IdReco_Up	);
    	outputTree->Branch("eleEffWeight_IdReco_Do", &_eleEffWeight_IdReco_Do	);

    	outputTree->Branch("eleEffWeight_Trig_Up", &_eleEffWeight_Trig_Up	);
    	outputTree->Branch("eleEffWeight_Trig_Do", &_eleEffWeight_Trig_Do	);
    }
    
    outputTree->Branch("evtWeight"		, &_evtWeight			);      
    outputTree->Branch("lumiWeight"		, &_lumiWeight			);      
    outputTree->Branch("sampleWeight"    	, &_sampleWeight       		);      
    outputTree->Branch("nMC_total"      	, &_nMC_total       		);      
    outputTree->Branch("nMC_totalUS"    	, &_nMC_totalUS       		);      
    outputTree->Branch("xss"              	, &_xss         		);      

    outputTree->Branch("nVtx"			, &_nVtx			); 
    outputTree->Branch("nGoodVtx"		, &_nGoodVtx			); 
    outputTree->Branch("isPVGood"		, &_isPVGood			);
    
    if (!isSystematicRun){
	outputTree->Branch("genMET"		, &_genMET			); 
    }
    outputTree->Branch("pfMET"			, &_pfMET			);
    outputTree->Branch("pfMETPhi"		, &_pfMETPhi			);
    outputTree->Branch("nu_px"			, &_nu_px			);
    outputTree->Branch("nu_py"			, &_nu_py			);
    outputTree->Branch("nu_pz"			, &_nu_pz			);
    outputTree->Branch("nu_pz_other"		, &_nu_pz_other			);
    /* outputTree->Branch("WtransMass"		, &_WtransMass			); */

    /* outputTree->Branch("hasConv"		, &_hasConv			); */
    /* outputTree->Branch("hasRDPass"	       	, &_hasRDPass			); */
    /* outputTree->Branch("ltype"		        , &_ltype			); */
    /* outputTree->Branch("ltypekF"       	        , &_ltypekF			); */
    /* outputTree->Branch("chi2"			, &_chi2			); */
    /* outputTree->Branch("NDF"			, &_NDF				); */
    /* outputTree->Branch("Nbiter"			, &_Nbiter			); */
    /* outputTree->Branch("M_jj"			, &_M_jj			); */
    /* outputTree->Branch("M_jjkF"			, &_M_jjkF			); */
    /* outputTree->Branch("bjlep_id"		, &_bjlep_id			); */
    /* outputTree->Branch("bjhad_id"		, &_bjhad_id			); */
    /* outputTree->Branch("cjhad_id"		, &_cjhad_id			); */
    /* outputTree->Branch("sjhad_id"		, &_sjhad_id			); */
    /* outputTree->Branch("lepPt"			, &_lepPt			); */
    /* outputTree->Branch("lepEta"			, &_lepEta			); */
    /* outputTree->Branch("lepPhi"			, &_lepPhi			); */
    /* outputTree->Branch("lepEnergy"		, &_lepEnergy			); */
    /* outputTree->Branch("metPx"			, &_metPx			); */
    /* outputTree->Branch("metPy"			, &_metPy			); */
    /* outputTree->Branch("metPz"			, &_metPz			); */
    /* outputTree->Branch("jetBlepPt"		, &_jetBlepPt			); */
    /* outputTree->Branch("jetBlepEta"		, &_jetBlepEta			); */
    /* outputTree->Branch("jetBlepPhi"		, &_jetBlepPhi			); */
    /* outputTree->Branch("jetBlepEnergy"		, &_jetBlepEnergy		); */
    /* outputTree->Branch("jetBhadPt"		, &_jetBhadPt			); */
    /* outputTree->Branch("jetBhadEta"		, &_jetBhadEta			); */
    /* outputTree->Branch("jetBhadPhi"		, &_jetBhadPhi			); */
    /* outputTree->Branch("jetBhadEnergy"		, &_jetBhadEnergy		); */
    /* outputTree->Branch("jetChadPt"		, &_jetChadPt			); */
    /* outputTree->Branch("jetChadEta"		, &_jetChadEta			); */
    /* outputTree->Branch("jetChadPhi"		, &_jetChadPhi			); */
    /* outputTree->Branch("jetChadEnergy"		, &_jetChadEnergy		); */
    /* outputTree->Branch("jetShadPt"		, &_jetShadPt			); */
    /* outputTree->Branch("jetShadEta"		, &_jetShadEta			); */
    /* outputTree->Branch("jetShadPhi"		, &_jetShadPhi			); */
    /* outputTree->Branch("jetShadEnergy"		, &_jetShadEnergy		); */

    outputTree->Branch("nEle"			, &_nEle			); 
    outputTree->Branch("nEleLoose"		, &_nEleLoose			); 
    outputTree->Branch("elePt"			, &_elePt			);
    outputTree->Branch("elePhi"			, &_elePhi			); 
    outputTree->Branch("eleSCEta"		, &_eleSCEta			); 
    outputTree->Branch("elePFRelIso"		, &_elePFRelIso			); 

    outputTree->Branch("nMu"			, &_nMu				); 
    outputTree->Branch("nMuLoose"		, &_nMuLoose			); 
    outputTree->Branch("muPt"			, &_muPt			); 
    outputTree->Branch("muEta"			, &_muEta			);
    outputTree->Branch("muPhi"			, &_muPhi			);
    outputTree->Branch("muPFRelIso"		, &_muPFRelIso			);
    outputTree->Branch("muRoccoR"		, &_muRoccoR			);
    
    outputTree->Branch("nJet"			, &_nJet			); 
    outputTree->Branch("nBJet"			, &_nBJet			); 
    outputTree->Branch("jetPt"			, &_jetPt			);
    outputTree->Branch("jetEta"			, &_jetEta			); 
    outputTree->Branch("jetPhi"			, &_jetPhi			); 
    outputTree->Branch("jetMass"		, &_jetMass			);

    /* outputTree->Branch("nfwdJet"		, &_nfwdJet			); */
    /* outputTree->Branch("fwdJetPt"		, &_fwdJetPt			); */
    /* outputTree->Branch("fwdJetEta"		, &_fwdJetEta			); */
    /* outputTree->Branch("fwdJetPhi"		, &_fwdJetPhi			); */
    /* outputTree->Branch("fwdJetMass"		, &_fwdJetMass			); */

    if (!isSystematicRun){
	/* outputTree->Branch("jetCMVA"		, &_jetCMVA			); */
	outputTree->Branch("jetCSVV2"		, &_jetCSVV2			);
	outputTree->Branch("jetDeepB"		, &_jetDeepB			);
	outputTree->Branch("jetDeepC"		, &_jetDeepC			);
	outputTree->Branch("jetGenJetIdx"	, &_jetGenJetIdx		);
    }
	
    if (!tree->isData_ && !isSystematicRun){
	outputTree->Branch("nLHEPart"		, &_nLHEPart			); 
	outputTree->Branch("nGenPart"		, &_nGenPart			); 
	outputTree->Branch("genPt"		, &_genPt			);
	outputTree->Branch("genEta"		, &_genEta			); 
	outputTree->Branch("genPhi"		, &_genPhi			); 
	outputTree->Branch("genMass"		, &_genMass			); 
	outputTree->Branch("genStatus"		, &_genStatus			);
	outputTree->Branch("genStatusFlag"	, &_genStatusFlag		);
	outputTree->Branch("genPDGID"		, &_genPDGID			); 
	outputTree->Branch("genMomIdx"		, &_genMomIdx			);

	outputTree->Branch("nGenJet"		, &_nGenJet			); 
	outputTree->Branch("genJetPt"		, &_genJetPt			);
	outputTree->Branch("genJetEta"		, &_genJetEta			); 
	outputTree->Branch("genJetPhi"		, &_genJetPhi			); 
	outputTree->Branch("genJetMass"		, &_genJetMass			); 
	outputTree->Branch("genJetPartonFlavour", &_genJetPartonFlavour		); 
	outputTree->Branch("genJetHadronFlavour", &_genJetHadronFlavour		); 
    }

    /* outputTree->Branch("M3"			, &_M3				);  */
    /* outputTree->Branch("HT"			, &_HT				);  */

    outputTree->Branch("passPresel_Ele"		, &_passPresel_Ele		); 
    outputTree->Branch("passPresel_Mu"		, &_passPresel_Mu		);
    outputTree->Branch("passAll_Ele"		, &_passAll_Ele			); 
    outputTree->Branch("passAll_Mu"		, &_passAll_Mu			);
    outputTree->Branch("passTrigger_ele"	, &_passTrigger_ele	       	);
    outputTree->Branch("passTrigger_mu"		, &_passTrigger_mu 		);
    outputTree->Branch("passFilter"		, &_passFilter  		);
}


void makeRecoKinTuple::InitVariables()
{

    _run			= -9999;
    _event			= -9999;
    _lumis			= -9999;
    _isData			= false;

    /* _PUweight			= 1.; */
    /* _PUweight_Up		= 1.; */
    /* _PUweight_Do		= 1.; */

    _q2weight_Up		= 1.;
    _q2weight_Do		= 1.;
    _q2weight_nominal		= 1.;
    _genScaleSystWeights.clear();

    _pdfWeight			= 1.;
    _pdfuncer			= 0.;
    _pdfweight_Up		= 1.;
    _pdfweight_Do		= 1.;
    _pdfSystWeight.clear();

    _ISRweight_Up		= 1.;
    _ISRweight_Do		= 1.;

    _FSRweight_Up		= 1.;
    _FSRweight_Do		= 1.;

    /* _prefireSF			= 1.; */
    /* _prefireSF_Up		= 1.; */
    /* _prefireSF_Do		= 1.; */

    _btagWeight_1a		= 1.;
    _btagWeight_1a_b_Up		= 1.;
    _btagWeight_1a_b_Do		= 1.;
    _btagWeight_1a_l_Up		= 1.;
    _btagWeight_1a_l_Do		= 1.;

    _btagWeight.clear();
    _btagWeight_b_Up.clear();
    _btagWeight_b_Do.clear();
    _btagWeight_l_Up.clear();
    _btagWeight_l_Do.clear();
    
    _btagSF.clear();
    _btagSF_b_Up.clear();
    _btagSF_b_Do.clear();
    _btagSF_l_Up.clear();
    _btagSF_l_Do.clear();

    _muEffWeight		= 1.;
    _muEffWeight_Do		= 1.;
    _muEffWeight_Up		= 1.;

    /* _muEffWeight_IdIso		= 1.; */
    /* _muEffWeight_IdIso_Up	= 1.; */
    /* _muEffWeight_IdIso_Do	= 1.; */

    /* _muEffWeight_Trig		= 1.; */
    /* _muEffWeight_Trig_Up	= 1.; */
    /* _muEffWeight_Trig_Do	= 1.; */

    _eleEffWeight		= 1.;
    _eleEffWeight_Do		= 1.;
    _eleEffWeight_Up		= 1.;

    /* _eleEffWeight_IdReco	= 1.; */
    /* _eleEffWeight_IdReco_Up	= 1.; */
    /* _eleEffWeight_IdReco_Do	= 1.; */

    /* _eleEffWeight_Trig		= 1.; */
    /* _eleEffWeight_Trig_Up	= 1.; */
    /* _eleEffWeight_Trig_Do	= 1.; */

    /* _evtWeight			= 1.; */
    /* _lumiWeight			= 1.; */
    _nVtx			= -9999;
    _nGoodVtx			= -9999;

    _genMET			= -9999;

    _pfMET			= -9999;
    _pfMETPhi			= -9999;
    _nu_px			= -9999;
    _nu_py			= -9999;
    _nu_pz			= -9999;
    _nu_pz_other		= -9999;
    _WtransMass			= -9999;

    _hasConv		= false;
    _hasRDPass		= false;
    _ltype              = -9999 ;
    _ltypekF            = -9999 ;
    _chi2		= -9999 ;
    _NDF		= -9999 ;
    _Nbiter		= -9999 ;
    _M_jj		= -9999 ;
    _M_jjkF		= -9999 ;
    _bjlep_id		= -9999 ;
    _bjhad_id		= -9999 ;
    _cjhad_id		= -9999 ;
    _sjhad_id		= -9999 ;
    _lepPt		= -9999 ;
    _lepEta		= -9999 ;
    _lepPhi		= -9999 ;
    _lepEnergy		= -9999 ;
    _metPx		= -9999 ;
    _metPy		= -9999 ;
    _metPz		= -9999 ;
    _jetBlepPt		= -9999 ;
    _jetBlepEta		= -9999 ;
    _jetBlepPhi		= -9999 ;
    _jetBlepEnergy	= -9999 ;
    _jetBhadPt		= -9999 ;
    _jetBhadEta		= -9999 ;
    _jetBhadPhi		= -9999 ;
    _jetBhadEnergy	= -9999 ;
    _jetChadPt		= -9999 ;
    _jetChadEta		= -9999 ;
    _jetChadPhi		= -9999 ;
    _jetChadEnergy	= -9999 ;
    _jetShadPt		= -9999 ;
    _jetShadEta		= -9999 ;
    _jetShadPhi		= -9999 ;
    _jetShadEnergy	= -9999 ;


    _nEle			= -9999;
    _nEleLoose			= -9999;
    _elePt.clear();
    _elePhi.clear();
    _eleSCEta.clear();
    _elePFRelIso.clear();

    _nMu			= -9999;
    _nMuLoose			= -9999;
    _muPt.clear();
    _muEta.clear();
    _muPhi.clear();
    _muPFRelIso.clear();
    _muRoccoR.clear();

    _nJet			= -9999;  
    _nBJet			= -9999;  
    _jetPt.clear();
    _jetEta.clear();
    _jetPhi.clear();
    _jetMass.clear();
  
    _nfwdJet			= -9999;  
    _fwdJetPt.clear();
    _fwdJetEta.clear();
    _fwdJetPhi.clear();
    _fwdJetMass.clear();
    
    _jetCMVA.clear();
    _jetCSVV2.clear();
    _jetDeepB.clear();
    _jetDeepC.clear();

    _jetGenJetIdx.clear();    

    _nGenJet			= -9999;
    _genJetPt.clear();
    _genJetEta.clear();
    _genJetPhi.clear();
    _genJetMass.clear();
    _genJetPartonFlavour.clear();
    _genJetHadronFlavour.clear();
    
    _nLHEPart			= -9999;
    _nGenPart			= -9999;
    _genPt.clear();
    _genPhi.clear();
    _genEta.clear();
    _genMass.clear();
    _genStatus.clear();
    _genStatusFlag.clear();
    _genPDGID.clear();
    _genMomIdx.clear();

    _M3				= -9999;
    _HT				= -9999;
    _passPresel_Ele		= false;
    _passPresel_Mu		= false;
    _passAll_Ele		= false;
    _passAll_Mu			= false;
    _passTrigger_ele		= false;
    _passTrigger_mu		= false;
    _passFilter			= false;
}



#endif

