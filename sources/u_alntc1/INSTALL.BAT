@Echo off
Cls
Rem INSTALL 1 for Ultimate DOOM
Rem INSTALL 2 for v1.9
Rem INSTALL 3 for v1.666
If "%1%" == "1" Goto V_good
If "%1%" == "2" Goto V_good
If "%1%" == "3" Goto V_good
If "%1%" == "" Goto V_bad

:V_bad
Echo You need to specify for which version of DOOM you are installing.
Echo.
Echo Use INSTALL 1 if you are going to install ALIENS-TC into Ultimate DOOM
Echo Use INSTALL 2 if you are going to install ALIENS-TC into DOOM v1.9
Echo Use INSTALL 3 if you are going to install ALIENS-TC into DOOM v1.666
Echo.
Echo NOTE: Ultimate DOOM v1.9 _IS_ different than normal DOOM v1.9
Echo.
Goto End

:V_good
Echo.   ************************************
Echo.   *    ALIENS Total Conversion       *
Echo.   *                                  *
Echo.   *        by Justin Fisher          *
Echo.   *                                  *
Echo.   ************************************
Echo.
Echo.   Secret level by Richard Love
Echo.   New Installation by Olivier Montanuy
Echo.   Ultimate DOOM compatibility by Cale McCallum
Echo.
Echo.   ************ Good News ***************
Echo.   You won't need to un-install ALIENS-TC.
Echo.   DOOM will still work as usual.
Echo.
Echo.   ************ Bad News ****************
Echo.   Installation still requires about 2 additional megs.
Echo.
Echo.   Beside DeHackEd this install uses DeuSF, a powerfull 
Echo.   tool to regenerate sprite and flats PWADS.  Look for 
Echo.   the lastest version of DeuTex/DeuSF on ftp.cdrom.com.
Echo.
Pause
Echo This batch is for Registered version:
If "%1%" == "1" Goto U_DOOM
If "%1%" == "2" Goto V_19
If "%1%" == "3" Goto V_1666

:U_DOOM
Echo.   *** Ultimate DOOM ***
Goto V_end

:V_19
Echo.   *** DOOM 1.9 ***
Goto V_end

:V_1666
Echo.   *** DOOM 1.666 ***
Goto V_end

:V_end
Echo Hit CTRL-C now if this is incorrect.
Pause
Echo DOOM.EXE and DOOM.WAD must be in this directory.
Pause
Goto Save

:Miss_file
Echo ERROR: A file is missing from the archives.
Goto End

:Fail
Echo ERROR: Can't find DOOM files.
Goto End

:Save
If not exist DEHACKED.INI goto Save_2
Echo ERROR: Existing file DEHACKED.INI will compromise the installation. 
Echo Remove that file please.

:Save_2
If not exist DOOM.EXE goto fail
If not exist DOOM.WAD goto fail
Echo Copying DOOM.EXE to DOOMHACK.EXE.  This will be turned into ALIENTC.EXE. 
Pause
Copy DOOM.EXE DOOMHACK.EXE
Echo Checking ALITCWAD.WAD
If not exist ALITCWAD.WAD goto Miss_file
Echo Checking ALITCSND.WAD
If not exist ALITCSND.WAD goto Miss_file
Echo Checking ALITCSF.WAD
If not exist ALITCSF.WAD goto Miss_file
Echo Checking DEHACKED.EXE
If not exist DEHACKED.EXE goto Miss_file
Echo Checking DEUSF.EXE
If not exist DEUSF.EXE goto Miss_file
Echo Checking ALITCPUD.DEH
If not exist ALITCPUD.DEH goto Miss_file
Echo Checking ALITCP19.DEH
If not exist ALITCP19.DEH goto Miss_file
Echo Checking ALITCP16.DEH
If not exist ALITCP16.DEH goto Miss_file
If "%1%" == "1" Goto Ver_UDOOM
If "%1%" == "2" Goto Ver_19
If "%1%" == "3" Goto Ver_1666

:Ver_UDOOM
Echo Applying DeHackED patch for Ultimate DOOM
Pause
DeHackED -load ALITCPUD.DEH
If not ERRORLEVEL 0 goto Fail_patch
Goto Exe_Rename

:Ver_19
Echo Applying DeHackED patch for DOOM 1.9
Pause
DeHackED -load ALITCP19.DEH
If not ERRORLEVEL 0 goto Fail_patch
Goto Exe_Rename

:Ver_1666
Echo Applying DeHackED patch for DOOM 1.666
Pause
DeHackED -load ALITCP16.DEH
If not ERRORLEVEL 0 goto Fail_patch
Goto Exe_Rename

:Fail_patch
Echo ERROR: An error has occured while loading the DeHackED patch.
Echo -Did you use the right DOOM version?
Echo -Is your DOOM version registered?
Echo -Do you have enough disk space?
Goto End

:Exe_Rename
Echo Changing .EXE name.
Pause
If exist ALIENTC.EXE del ALIENTC.EXE
Rename DOOMHACK.EXE ALIENTC.EXE
Echo Modified DOOM.EXE is now ALIENTC.EXE.
Goto SF_Pwad

:SF_Pwad
Echo Creating new sprite and flat PWAD with DeuSF.
Echo This uses about 1.5 more meg of disk space.
Pause
Echo Appending sprites and flats to ALITCSF.WAD.
Echo This may take a minute or so.

REM REM the following lines if you do not want to append DOOM sprites to 
REM ALITCSF.WAD.
DeuSF -app ALITCSF.WAD > ALITCSF.LOG
If not ERRORLEVEL 0 goto Fail_SF

REM unREM the following lines if you want to create a completely new PWAD, like 
REM DMADDS did.
REM
REM Move ALITCSF.WAD ALITCSF2.WAD
REM DeuSf -add ALITCSF2.WAD ALITCSF.WAD
REM If not ERRORLEVEL 0 goto Fail_SF

REM Restoration
REM
Echo.
Echo To restore ALIENS-TC sprite file, type: DeuSF -restore ALITCSF.WAD
Goto Finished

:Fail_SF
Echo ERROR 
Echo An error occured during sprite and flat generation.
Echo -Did you have enough disk space?
Echo -Else that could mean there was a bug in Olivier Montanuy's DeuSF.EXE.  If 
Echo  this is confirmed, mail him your bitter disapointment together with the file 
Echo  ALITCSF.LOG at: montanuy@dmi.ens.fr
Goto End

:Finished
Echo Finished!
Echo PWAD Files:
Echo -ALITCSND.WAD = Sounds
Echo -ALITCWAD.WAD = Levels, demos, graphics, patches
Echo -ALITCSF.WAD = All the sprites & flats
Echo.
Echo. Play with ALIENTC.EXE -file ALITCSND.WAD ALITCWAD.WAD ALITCSF.WAD
Echo. Or simply type ALIEN.
Echo.
Echo. Warning:
Echo. To play network games, first save DOOM.EXE
Echo. as DOOM_OLD.EXE and rename ALIENTC.EXE to DOOM.EXE
Echo. else SETUP and SERSETUP won't recognise it.
:End

