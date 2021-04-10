import itertools
import os
import sys

#IMPORT MODULES FROM OTHER DIR
sys.path.insert(0, os.getcwd().replace("RecoNtuple_Skim/condor","Skim_NanoAOD/sample"))
from NanoAOD_Gen_SplitJobs_cff import Samples_2016, Samples_2017, Samples_2018 

if not os.path.exists("tmpSub_cf/log"):
    os.makedirs("tmpSub_cf/log")
condorLogDir = "log"
tarFile = "tmpSub_cf/RecoNtuple_Skim.tar.gz"
if os.path.exists(tarFile):
	os.system("rm %s"%tarFile)
os.system("tar -zcvf %s ../../RecoNtuple_Skim --exclude condor"%tarFile)
os.system("cp runMakeRecoNtuple_cutflow.sh tmpSub_cf/")
common_command = \
'Universe   = vanilla\n\
should_transfer_files = YES\n\
when_to_transfer_output = ON_EXIT\n\
Transfer_Input_Files = RecoNtuple_Skim.tar.gz, runMakeRecoNtuple_cutflow.sh\n\
x509userproxy = $ENV(X509_USER_PROXY)\n\
use_x509userproxy = true\n\
+BenchmarkJob = True\n\
#+JobFlavour = "workday"\n\
+MaxRuntime = 28000\n\
Output = %s/log_$(cluster)_$(process).stdout\n\
Error  = %s/log_$(cluster)_$(process).stderr\n\
Log    = %s/log_$(cluster)_$(process).condor\n\n'%(condorLogDir, condorLogDir, condorLogDir)

#----------------------------------------
#Create jdl files
#----------------------------------------
subFile = open('tmpSub_cf/condorSubmit.sh','w')
for year in [2016,2017,2018]:
    sampleList = eval("Samples_%i"%year)
    jdlName = 'submitJobs_%s.jdl'%(year)
    jdlFile = open('tmpSub_cf/%s'%jdlName,'w')
    jdlFile.write('Executable =  runMakeRecoNtuple_cutflow.sh \n')
    jdlFile.write(common_command)
    # condorOutDir="/store/user/rverma/Output/cms-hcs-run2/RecoNtuple_Skim"
    # os.system("eos root://cmseos.fnal.gov mkdir -p %s/%s"%(condorOutDir, year))
    # condorOutDir="/cms/store/user/idas/Output/cms-hcs-run2/RecoNtuple_Skim_cutflow"
    # os.system("xrdfs root://se01.indiacms.res.in/ mkdir -p %s/%s"%(condorOutDir, year))
    condorOutDir="/eos/user/i/idas/Output/cms-hcs-run2/RecoNtuple_Skim_tune16_iter1_cutflow"
    os.system("eos root://eosuser.cern.ch mkdir -p %s/%s"%(condorOutDir, year))
    jdlFile.write("X=$(step)+1\n")
    
    for sampleName, nJob in sampleList.items():
        if nJob==1:
            run_command =  'Arguments  = %s %s \nQueue 1\n\n' %(year, sampleName)
        else:
            run_command =  'Arguments  = %s %s $INT(X) %i\nQueue %i\n\n' %(year, sampleName, nJob, nJob)
	jdlFile.write(run_command)
    
	#print "condor_submit jdl/%s"%jdlFile
    subFile.write("condor_submit %s\n"%jdlName)
    jdlFile.close() 
subFile.close()
