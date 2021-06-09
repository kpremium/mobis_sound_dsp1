@echo off

:: Execution files
set GRF2HEX_File=%~dp0DspMergeTool\DspMergeTool_1.2.9.exe

:: Input files
set Sounder_File=..\..\Framework\Sounder\Debug\~ADP_G2-21569_Sounder_DSP1.ldr
set SSn_File=..\JtagFlash\~SSn_TuningInfo_ADSP-21569_DSP1.ldr
set ASD_File=..\JtagFlash\~ASD_SRC_ADSP-21569_DSP1.ldr
set ADDRTBL_File=..\JtagFlash\~SSn_ADDR_TBL_ADSP-21569_DSP1.ldr
set USER_File=..\JtagFlash\~OPT_USER_ADSP-21569_DSP1.ldr

:: Output file
set Output_File=..\JtagFlash\~ADP_G2-21569_FULL_DSP1.ldr

@echo on

"%GRF2HEX_File%" "MERGE" "HEX" "%Output_File%" "%Sounder_File%" "%SSn_File%" "%USER_File%" "%ADDRTBL_File%" "%ASD_File%"
