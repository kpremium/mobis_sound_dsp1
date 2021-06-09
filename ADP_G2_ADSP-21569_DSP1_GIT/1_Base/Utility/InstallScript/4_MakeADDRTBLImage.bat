@echo off

:: Execution files
set GRF2HEX_File=%~dp0DspMergeTool\DspMergeTool_1.2.9.exe

:: Input files
set LABEL_File=..\..\Schematic\LabelForAddrTbl\Address_Label.h
set SSn1_File=..\..\Schematic\ExportFilesForSSn\TxMetaBuffer_SH0_SSN1.dat
set SSn2_File=..\..\Schematic\ExportFilesForSSn\TxMetaBuffer_SH0_SSN2.dat

:: Output files
set Output_File=..\JtagFlash\_SSn_ADDR_TBL_ADSP-21569_DSP1.hex

:: Rebuild files
set Rebuild_File=..\JtagFlash\~SSn_ADDR_TBL_ADSP-21569_DSP1.ldr

:: Flash Memory Address Definition for HKMC
set FlashLabelAddr=F0000

@echo on

"%GRF2HEX_File%" "GRIFFIN" "ADDRTBL" "%Output_File%" "%LABEL_File%" "%FlashLabelAddr%" "%SSn1_File%" "%SSn2_File%"
"%GRF2HEX_File%" "REBUILD" "%Output_File%" "%Rebuild_File%"

del /F /Q "%Output_File%"
