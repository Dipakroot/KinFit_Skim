#//////////////////////////////////////////////////
#                                                 #
# 	Limit computation at 13 TeV 		          #
#                                                 #
#//////////////////////////////////////////////////
# python MyLimitComputer.py --ch ele --cat 1 --mass 120

import os
import sys
import argparse

def execme(command):
    #print "\033[01;32m"+ "Excecuting: "+ "\033[00m",  command
    os.system(command)

#---------------------------------------------
#function to prepare data cards
#---------------------------------------------
def makeDataCards(IN_FILE_DIR, HIST_DIR, HIST_NAME, CHANNEL_NAME, SIG_MASS, SIG_LABEL, SIG_FILE, YEAR):
    execme('root -l -q -b \"MyHPlusDataCardMaker.C(\\\"'+IN_FILE_DIR+'\\\",\\\"'+YEAR+'\\\", \\\"'+HIST_DIR+'\\\",\\\"'+HIST_NAME+'\\\",\\\"'+CHANNEL_NAME+'\\\",'+str(SIG_MASS)+', \\\"'+SIG_LABEL+'\\\", \\\"'+SIG_FILE+'\\\")\"')

def moveDataCards(CHANNEL_NAME, HIST_ARRAY, MASS, CAT_DIR, LIMIT_DIR):
    execme('mkdir -p '+LIMIT_DIR)
    execme('mv *.root '+LIMIT_DIR)
    execme('mv *datacard_* '+LIMIT_DIR)

#---------------------------------------------
#function to calculate limits
#---------------------------------------------
def calcLimits(CHANNEL_NAME, COMB_DATACARD_NAME, CAT_DIR, MASS, isGOF):
    t2wDataCardName = "t2w_"+COMB_DATACARD_NAME.replace(".txt",".root")
    print("t2wDataCardName : %s, COMB_DATACARD_NAME : %s"%(t2wDataCardName,COMB_DATACARD_NAME))
    command1 = 'text2workspace.py '+COMB_DATACARD_NAME+' -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o '+t2wDataCardName
    print("command1 : %s"%command1)
    execme('text2workspace.py '+COMB_DATACARD_NAME+' -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o '+t2wDataCardName )
    #execme('text2workspace.py '+COMB_DATACARD_NAME+'  -o '+t2wDataCardName )
    #Original
    #execme('combine  --rAbsAcc 0.000001 '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)
    command2 = 'combine --rAbsAcc 0.000001 --expectSignal 1 --setParameterRanges BR=0,1 '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR
    print("command2 : %s"%command2)
    execme(command2)

    #execme('combine --rAbsAcc 0.000001 --run blind '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)
    
    #execme('combine  '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --setParameterRanges r=0.,1. --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)
    #Blind
    #execme('combine --rAbsAcc 0.000001 --setParameters BR=1 --run blind '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)
    #Expected
    #execme('combine --rAbsAcc 0.000001 --run expected '+t2wDataCardName+' -M AsymptoticLimits --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)
    #Frequentists
    #execme('combine --rAbsAcc 0.000001 '+t2wDataCardName+'  --mass '+str(MASS)+' --name _hcs_13TeV_'+CHANNEL_NAME+'_'+CAT_DIR)

    #FitDiagnostics
    # execme('combine '+t2wDataCardName+' -M FitDiagnostics --expectSignal 1 --redefineSignalPOIs BR --setParameterRanges BR=0,0.10 --plots --saveShapes --saveWithUncertainties --saveNormalizations --cminDefaultMinimizerStrategy 0 --mass '+str(MASS)+' --name _hcs_13TeV_fitdiag_'+CHANNEL_NAME+'_'+CAT_DIR)
    # execme('python /Data/CMS-Analysis/NanoAOD-Analysis/Analysis/Analysis/mlfit/diffNuisances.py -a fitDiagnostics_hcs_13TeV_fitdiag_'+CHANNEL_NAME+'_'+CAT_DIR+'.root --poi=BR -f latex -g fitDiagTest > fitdiag.tex')
    # execme('mv *.png combine_logger.out fitdiag.tex *.pdf local/'+CHANNEL_NAME+'/'+CAT_DIR+'/Mass'+str(MASS))
    if(isGOF):
        #execme('combine '+t2wDataCardName+' -M GoodnessOfFit --algo saturated --mass '+str(MASS)+' --name _hcs_13TeV_data_'+CHANNEL_NAME+'_'+CAT_DIR)
        ## execme('combine '+t2wDataCardName+' -M GoodnessOfFit --algo saturated -t 1000 -s -1 --mass '+str(MASS)+' --name _hcs_13TeV_toy_'+CHANNEL_NAME+'_'+CAT_DIR)
        pass

#---------------------------------------------------
#function to get datacards to be combined
#---------------------------------------------------
def getCardsToBeCombined(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_ARRAY, MASS, YEAR):
    #make separate cards first
    for CH in range(len(CHANNEL_ARRAY)):
        for HIST in range(len(HIST_ARRAY)):
            SIG_LABEL = "WH"+str(MASS)
            #SIG_FILE = "all_Hplus"+str(MASS)+".root"
            SIG_FILE = "all_HplusM"+str(MASS)+".root"
            #SIG_FILE = "all_HplmiM"+str(MASS)+".root"
            print "getCardsToBeCombined :: CH: %s, HIST: %s"%(CH,HIST)
            print "getCardsToBeCombined :: IN_FILE_DIR_ARRAY[CH]: %s, HIST_ARRAY[HIST][0]: %s, HIST_ARRAY[HIST][1]: %s, CHANNEL_ARRAY[CH]: %s"%(IN_FILE_DIR_ARRAY[CH],HIST_ARRAY[HIST][0],HIST_ARRAY[HIST][1],CHANNEL_ARRAY[CH]) 
            makeDataCards(IN_FILE_DIR_ARRAY[CH], HIST_ARRAY[HIST][0],HIST_ARRAY[HIST][1], CHANNEL_ARRAY[CH], MASS, SIG_LABEL, SIG_FILE, YEAR)
    #store separate cards in an array
    COMB_CARD_CHANNEL_HIST_MASS = []
    for CH in range(len(CHANNEL_ARRAY)):
        COMB_CARD_HIST_MASS = []
        for HIST in range(len(HIST_ARRAY)):
            COMB_CARD_MASS = []
            COMB_CARD_MASS.append('datacard_hcs_13TeV_'+CHANNEL_ARRAY[CH]+'_'+HIST_ARRAY[HIST][0]+'_'+HIST_ARRAY[HIST][1]+CHANNEL_ARRAY[CH]+'_WH'+str(MASS)+'.txt')
            COMB_CARD_HIST_MASS.append(COMB_CARD_MASS)
        COMB_CARD_CHANNEL_HIST_MASS.append(COMB_CARD_HIST_MASS)    
    return COMB_CARD_CHANNEL_HIST_MASS

#---------------------------------------------------
#function to arrange datacards for combined limits
#---------------------------------------------------
def sortCardsForCombine(COMB_CARD_CHANNEL_HIST_MASS_ARRAY, CHANNEL_ARRAY, HIST_ARRAY, MASS):
    SORT_CARD = ' '
    COMB_CARD_MASS = []
    for CH in range(len(CHANNEL_ARRAY)):
        for HIST in range(len(HIST_ARRAY)):
            COMB_CARD_MASS.append(COMB_CARD_CHANNEL_HIST_MASS_ARRAY[CH][HIST][0])
    for STR in COMB_CARD_MASS:
        SORT_CARD = SORT_CARD+STR+' '
    return SORT_CARD

#---------------------------------------------------
#function to calculate combined limits
#---------------------------------------------------
def calcCombinedLimit(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_ARRAY, CAT_DIR, MASS_ARRAY, isCondSub, isGOF, YEAR):
    COMB_CHANNEL_NAME = '_'.join(CHANNEL_ARRAY)
    HIST_ARRAY_ = []
    for HIST in range(len(HIST_ARRAY)):
        HIST_ARRAY_.append(HIST_ARRAY[HIST][1])
    COMB_HIST_NAME = '_'.join(HIST_ARRAY_)
    print "COMB_HIST_NAME %s"%(COMB_HIST_NAME) 
    for MASS in range(len(MASS_ARRAY)):
        LIMIT_DIR = "local/"+COMB_CHANNEL_NAME+"/"+CAT_DIR+"/"+"Mass"+str(MASS_ARRAY[MASS])
        print "Mass : %d, %s"%(MASS, LIMIT_DIR)
        if not isCondSub: execme('mkdir -p '+LIMIT_DIR)
        getCardsToBeCombined_ = getCardsToBeCombined(CHANNEL_ARRAY, IN_FILE_DIR_ARRAY, HIST_ARRAY, MASS_ARRAY[MASS],YEAR)
        print "getCardsToBeCombined_ : %s"%(getCardsToBeCombined_)
        sortCardsForCombine_ = sortCardsForCombine(getCardsToBeCombined_, CHANNEL_ARRAY, HIST_ARRAY, MASS)
        print "sortCardsForCombine_ : %s"%(sortCardsForCombine_)
        COMB_DATACARD_NAME = 'combine_datacard_hcs_13TeV_'+COMB_CHANNEL_NAME+"_"+CAT_DIR+"_WH"+str(MASS_ARRAY[MASS])+".txt"
        if len(CHANNEL_ARRAY)>1 or len(HIST_ARRAY)>1:
            execme('combineCards.py '+sortCardsForCombine_+' > '+COMB_DATACARD_NAME)
            command0 = 'combineCards.py '+sortCardsForCombine_+' > '+COMB_DATACARD_NAME
            print("command0 : %s"%command0)
        else: execme('cp '+sortCardsForCombine_+' '+COMB_DATACARD_NAME)
        calcLimits(COMB_CHANNEL_NAME, COMB_DATACARD_NAME, CAT_DIR, MASS_ARRAY[MASS], isGOF)
        if not isCondSub: moveDataCards(COMB_CHANNEL_NAME, HIST_ARRAY, MASS_ARRAY[MASS], CAT_DIR, LIMIT_DIR)


if __name__=="__main__":
    #---------------------------------------------
    #USERS INPUTS
    #---------------------------------------------
    
    # path_file_dir="/Data/CMS-Analysis/MiniAOD-Analysis/Analysis/MiniAOD_Published/"
    # muon_file_dir=path_file_dir+"HIG-18-021_PRD_Histograms_Mu"
    # ele_file_dir=path_file_dir+"HIG-18-021_PRD_Histograms_Ele"
    
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD/2016/"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD/2017/"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v39_Syst/CBA_CTagDD/2018/"

    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagnPUJetID/2016"
    # path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_BJetSFTests/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_PtJet50/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_PtJet50/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_PtJet25_jetMass0/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_FSRdown/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_FSRup/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLV_TPUJetID/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLV_TPUJetID_KFAllJets/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLVTPUKFAFSRDo_MiniReso/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NanoReso/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NR-GausM/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NR-Offset/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_TLVTPUKFAFSRDo_NROGM/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_Nom1FSRDo_100MeVBin/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_Nom1_100MeVBin/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagReWt/2018"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_CTagReWt-Hist/2016"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR"
    path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuR-Hist"
    #path_file_dir="/Data/CMS-Analysis/NanoAOD-Analysis/SkimAna/root_files/grid_v40_Syst/CBA_muFmuRFSRDo"
    
    
    muon_file_dir=path_file_dir+""
    ele_file_dir=path_file_dir+""
    
    hist_array_Inc = []
    #hist_array_Inc.append(["KinFit", "mjj_kfit"])
    #hist_array_Inc.append(["", "_kb_mjj_"])
    hist_array_Inc.append(["", "_ct_ExcT_mjj_"])
    
    hist_array_CTagL = []
    hist_array_CTagL.append(["KinFit", "mjj_kfit_CTagIncL"])
    hist_array_CTagM = []
    hist_array_CTagM.append(["KinFit", "mjj_kfit_CTagIncM"])
    hist_array_CTagT = []
    hist_array_CTagT.append(["KinFit", "mjj_kfit_CTagIncT"])
    
    hist_array_CTagCat = []
    hist_array_CTagCat.append(["", "_ct_ExcL_mjj_"])
    hist_array_CTagCat.append(["", "_ct_ExcM_mjj_"])
    hist_array_CTagCat.append(["", "_ct_ExcT_mjj_"])
    
    #mass_array = [90, 100]
    #mass_array = [80, 90, 100, 120, 140, 150, 155, 160]
    mass_array = [80, 90, 100, 110, 120, 130, 140, 150, 155, 160]
    
    parser = argparse.ArgumentParser()
    parser.add_argument("--ch", default="mu", help="The channel name e.g. mu or ele or mu_ele")
    parser.add_argument("--year", default="2016", help="name of the mjj histogram")
    parser.add_argument("--hist", default="_kb_mjj_mu", help="name of the mjj histogram")
    parser.add_argument("--cat", default=1, help="Type of event category")
    parser.add_argument("--mass", default=120, help="Mass of the charged Higgs")
    parser.add_argument("--allMass", default=False, help="Mass of the charged Higgs")
    parser.add_argument("--batch", default=False, help="Want to submit condor jobs")
    parser.add_argument("--isGOF", default=False, help="Want to determine the goodness-of-fit")
    args = parser.parse_args()
    
    if(args.ch=="mu"):
        in_channel= ["mu"]
        in_file = [muon_file_dir]
    if(args.ch=="ele"):
        in_channel= ["ele"]
        in_file = [ele_file_dir]
    if(args.ch=="mu_ele"):
        in_channel= ["mu", "ele"]
        in_file = [muon_file_dir, ele_file_dir]
    
    if(int(args.cat)==1):
        in_hist = hist_array_Inc
        cat_dir = "Cat1_Inc"
    if(int(args.cat)==2):
        in_hist = hist_array_CTagL
        cat_dir = "Cat2_cTagInc"
    if(int(args.cat)==3):
        in_hist = hist_array_CTagCat
        cat_dir = "Cat3_cTagEx"

    if(args.allMass): in_mass = mass_array
    else: in_mass = [args.mass]
    calcCombinedLimit(in_channel, in_file, in_hist, cat_dir, in_mass, args.batch, args.isGOF, args.year)

