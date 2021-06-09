@echo off

:: Execution files
set ElvisASD2HEX_File=%~dp0DspMergeTool\DspMergeTool_1.2.9.exe

:: Input files
set USER_File=..\..\Userarea\~DSP_USER_AREA.h

:: Output files
set Output_File=..\JtagFlash\_OPT_USER_ADSP-21569_DSP1.hex

:: Rebuild files
set Rebuild_File=..\JtagFlash\~OPT_USER_ADSP-21569_DSP1.ldr

:: Flash Memory Address Definition for HKMC
set FlashUserAddr=E0000

@echo on

"%ElvisASD2HEX_File%" "ASD" "TXT" "%Output_File%" "%USER_File%" "-COSTUM" "%FlashUserAddr%"
"%ElvisASD2HEX_File%" "REBUILD" "%Output_File%" "%Rebuild_File%"

del /F /Q "%Output_File%"
