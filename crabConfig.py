from WMCore.Configuration import Configuration

config = Configuration()

config.section_("General")
config.General.requestName   = 'Run2016_MC_p500_new'
config.General.transferLogs = True
config.General.workArea = 'crab'
config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName    = 'ntuple.py'
#config.JobType.inputFiles = ['startup-v1_DESRUN2_74_V4_ape-candidate1.db','startup-v1_DESRUN2_74_V4_ape-candidate2.db']

config.section_("Data")
config.Data.inputDataset = '/SPLooseMuCosmic_38T_p500/CosmicSpring16DR80-DECO_80X_mcRun2cosmics_asymptotic_deco_v0-v1/GEN-SIM-RAW'
# /Cosmics/Run2016B-CosmicSP-PromptReco-v2/RAW-RECO, /Cosmics/Run2016C-CosmicSP-PromptReco-v2/RAW-RECO, /Cosmics/Run2016D-CosmicSP-PromptReco-v2/RAW-RECO, /Cosmics/Run2016E-CosmicSP-PromptReco-v2/RAW-RECO, /Cosmics/Run2016H-CosmicSP-PromptReco-v2/RAW-RECO'
#config.Data.allowNonValidInputDataset = True
#f = open('cosmic_files.txt')
#flist = []
#for line in f:
 #   flist.append(line)
#config.Data.userInputFiles = flist
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
#config.Data.publication = True
# This string is used to construct the output dataset name
#config.Data.publishDataName = 'CRAB3-tutorial'
config.Data.outLFNDirBase = '/afs/cern.ch/work/s/swuycken/'
#config.Data.outLFNDirBase = '/store/group/phys_smp/skaur/'
#config.Data.ignoreLocality = True

# These values only make sense for processing data
#    Select input data based on a lumi mask
#config.Data.lumiMask = 'cosmics_Combined2016_Global_PIXEL_TRACKER_DT_CertifiedAndSignoff_2016-12-20.json'
#    Select input data based on run-ranges
#config.Data.runRange = '190456-194076'

config.section_("Site")
# Where the output files will be transmitted to
config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T2_US*']
