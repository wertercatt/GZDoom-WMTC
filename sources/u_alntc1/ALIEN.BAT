@Echo off
Cls
Echo.
Echo.             ALIENS-TC
Echo.         by Justin Fisher
Echo.     Secret level by Richard Love
Echo.     Installation by Olivier Montanuy 
Echo.     Ultimate DOOM compatibility by Cale McCallum
Echo.
If exist ALIENTC.EXE goto Run_it
Echo WARNING: You must install ALIENS-TC first
Echo Type: INSTALL 1 if you install on Ultimate DOOM 1.9
Echo Type: INSTALL 2 if you install on DOOM 1.9
Echo Type: INSTALL 3 if you install on DOOM 1.666
Echo.
Echo. DOOM will lock-up during startup if you didn't install ALIENS-TC properly.
Goto End
:Run_it  
Echo | ALIENTC.EXE -FILE ALITCSND.WAD ALITCWAD.WAD ALITCSF.WAD %1 %2 %3 %4 %5 %6 %7 %8 %9 %10
:End  

