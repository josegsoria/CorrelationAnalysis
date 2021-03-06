import numpy as np

ntupledir = '/global/project/projectdirs/alice/NTuples'

isovar = 'cluster_iso_its_04_sub'
isocut = 1.5
antiisocut = (5.0, 10.0)

isocuttext = '{0}<{1}'.format(isovar, isocut)
antiisocuttext = '{0}>{1} and {0}<{2}'.format(isovar, *antiisocut)

nn1 = 'cluster_NN1'
nn1bins = np.linspace(0, 1, 101)
nn1purity = (0.7, 0.9)

lambda2 = 'cluster_Lambda'
lambda2bins = np.linspace(0, 2, 101)
lambda2purity = (0.0, 0.3)

emaxe = 'cluster_emax_over_e'
emaxebins = np.linspace(0, 1, 101)
emaxepurity = (0.75, 0.95)

varinfo = {}
varinfo[nn1] = (nn1bins, nn1purity, 'Deep Neural Network Output')
varinfo[lambda2] = (lambda2bins, lambda2purity, '$\mathrm{\sigma^2_{long}}$')
varinfo[emaxe] = (emaxebins, emaxepurity, '$Emax/Ecluster$')

ghpt = (12, 16)
gjpt = (20, 30)
fullpt = (12, 30)

################################################################
# p-Pb files
################################################################
pPbdataFiles = []
pPbdataFiles.append('pPb/Skimmed_13def_ptmin12.0_Nevent_1416399.root')

pPbgjmcFiles = []
pPbgjmcFiles.append('MC/17g6a1/Skim_17g6a1_pthat1.root')
pPbgjmcFiles.append('MC/17g6a1/Skim_17g6a1_pthat2.root')
pPbgjmcFiles.append('MC/17g6a1/Skim_17g6a1_pthat3.root')
pPbgjmcFiles.append('MC/17g6a1/Skim_17g6a1_pthat4.root')
pPbgjmcFiles.append('MC/17g6a1/Skim_17g6a1_pthat5.root')

################################################################
# pp files
################################################################
ppdataFiles = []
ppdataFiles.append('pp/17q/Skimmed_17q_wSDD_ptmin12.0_Nevent_937949.root')

ppgjmcFiles = []
ppgjmcFiles.append('MC/18b10a/Skimmed_18b10a_pthat1to6.root')

ppjjmcFiles = []
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat1_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat2_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat3_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat4_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat5_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat6_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat7_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat8_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat9_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat10_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat11_ptmin12.0_Nevent_300000.root')
ppjjmcFiles.append('MC/18g7a/Skimmed_18g7a_calo_pthat12_ptmin12.0_Nevent_300000.root')