@echo off

:: Execution files
set GRF2HEX_File=%~dp0DspMergeTool\DspMergeTool_1.2.9.exe

:: Input files
set SSn1_File=..\..\Schematic\ExportFilesForSSn\TxMetaBuffer_SH0_SSN1.dat
set SSn2_File=..\..\Schematic\ExportFilesForSSn\TxMetaBuffer_SH0_SSN2.dat

:: Output files
set SSn1_Hex=..\JtagFlash\~SSn1_TuningInfo.hex
set SSn2_Hex=..\JtagFlash\~SSn2_TuningInfo.hex

:: Output file for full
set Output_File=..\JtagFlash\_SSn_TuningInfo_ADSP-21569_DSP1.hex

:: Rebuild file for full
set Rebuild_File=..\JtagFlash\~SSn_TuningInfo_ADSP-21569_DSP1.ldr

:: Flash Memory Address Definition for HKMC
set FlashSSn1Addr=40000
set FlashSSn2Addr=60000
set FlashSSn3Addr=80000

@echo on

"%GRF2HEX_File%" "GRIFFIN" "SSN1" "%SSn1_Hex%" "%SSn1_File%" "%FlashSSn1Addr%"
"%GRF2HEX_File%" "GRIFFIN" "SSN2" "%SSn2_Hex%" "%SSn2_File%" "%FlashSSn2Addr%"
"%GRF2HEX_File%" "MERGE" "HEX" "%Output_File%" "%SSn1_Hex%" "%SSn2_Hex%"
"%GRF2HEX_File%" "REBUILD" "%Output_File%" "%Rebuild_File%"

del /F /Q "%SSn1_Hex%" "%SSn2_Hex%" "%Output_File%"
