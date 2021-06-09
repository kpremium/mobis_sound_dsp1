@echo off

:: Execution files
set ElvisASD2HEX_File=%~dp0DspMergeTool\DspMergeTool_1.2.9.exe

:: Input Paths
set INPUT_PATH=%~dp0..\..\Miscellany\elvis3

:: Input files
set ASD_S1_BaseLayer_BinFile=%INPUT_PATH%\CV_S1_BeyohdTheOrbit.bin
set ASD_S1_LoadLayer_BinFile=%INPUT_PATH%\CV_S1_BeyohdTheOrbit.bin
set ASD_S2_BaseLayer_BinFile=%INPUT_PATH%\CV_S2_CV_01.bin
set ASD_S2_LoadLayer_BinFile=%INPUT_PATH%\CV_S2_CV_01.bin
set ASD_S3_BaseLayer_BinFile=%INPUT_PATH%\CV_S3_CV_wave_2.bin
set ASD_S3_LoadLayer_BinFile=%INPUT_PATH%\CV_S3_CV_wave_2.bin
set ASD_S1_Param1_BinFile=%INPUT_PATH%\292_sound1.param08BE
set ASD_S1_Param2_BinFile=%INPUT_PATH%\292_sound1.param08BE
set ASD_S1_Param3_BinFile=%INPUT_PATH%\292_sound1.param08BE
set ASD_S1_Param4_BinFile=%INPUT_PATH%\292_sound1.param08BE
set ASD_S2_Param1_BinFile=%INPUT_PATH%\291_Sound2.param08BE
set ASD_S2_Param2_BinFile=%INPUT_PATH%\291_Sound2.param08BE
set ASD_S2_Param3_BinFile=%INPUT_PATH%\291_Sound2.param08BE
set ASD_S2_Param4_BinFile=%INPUT_PATH%\291_Sound2.param08BE
set ASD_S3_Param1_BinFile=%INPUT_PATH%\294_Sound3.param08BE
set ASD_S3_Param2_BinFile=%INPUT_PATH%\294_Sound3.param08BE
set ASD_S3_Param3_BinFile=%INPUT_PATH%\294_Sound3.param08BE
set ASD_S3_Param4_BinFile=%INPUT_PATH%\294_Sound3.param08BE
set ASD_SignalChain1_BinFile=%INPUT_PATH%\apa.chain.bin
set ASD_SignalChain2_BinFile=%INPUT_PATH%\apa.chain.bin
set ASD_SignalChain3_BinFile=%INPUT_PATH%\apa.chain.bin
set ASD_Ver_File=%INPUT_PATH%\~Tuning_Ver.h
set ASD_Gain_File=%INPUT_PATH%\~Tuning_Gain.h

:: Output files
set ASD_S1_BaseLayer_HexFile=S1.BL.hex
set ASD_S1_LoadLayer_HexFile=S1.LL.hex
set ASD_S2_BaseLayer_HexFile=S2.BL.hex
set ASD_S2_LoadLayer_HexFile=S2.LL.hex
set ASD_S3_BaseLayer_HexFile=S3.BL.hex
set ASD_S3_LoadLayer_HexFile=S3.LL.hex
set ASD_S1_Param1_HexFile=S1.param1.hex
set ASD_S1_Param2_HexFile=S1.param2.hex
set ASD_S1_Param3_HexFile=S1.param3.hex
set ASD_S1_Param4_HexFile=S1.param4.hex
set ASD_S2_Param1_HexFile=S2.param1.hex
set ASD_S2_Param2_HexFile=S2.param2.hex
set ASD_S2_Param3_HexFile=S2.param3.hex
set ASD_S2_Param4_HexFile=S2.param4.hex
set ASD_S3_Param1_HexFile=S3.param1.hex
set ASD_S3_Param2_HexFile=S3.param2.hex
set ASD_S3_Param3_HexFile=S3.param3.hex
set ASD_S3_Param4_HexFile=S3.param4.hex
set ASD_SignalChain1_HexFile=S1.apa.chain.hex
set ASD_SignalChain2_HexFile=S2.apa.chain.hex
set ASD_SignalChain3_HexFile=S3.apa.chain.hex
set ASD_Ver_HexFile=UserVer.hex
set ASD_Gain_HexFile=UserGain.hex

:: Output file for full
set Output_File=%~dp0..\JtagFlash\_ASD_SRC_ADSP-21569_DSP1.hex

:: Rebuild file for full
set Rebuild_File=%~dp0..\JtagFlash\~ASD_SRC_ADSP-21569_DSP1.ldr

:: Flash Memory Address Definition for HKMC
set FlashAddr_S1_BaseLayer=300000
set FlashAddr_S1_LoadLayer=318000
set FlashAddr_S2_BaseLayer=330000
set FlashAddr_S2_LoadLayer=348000
set FlashAddr_S3_BaseLayer=360000
set FlashAddr_S3_LoadLayer=378000
set FlashAddr_S1_Param1=390000
set FlashAddr_S1_Param2=394000
set FlashAddr_S1_Param3=398000
set FlashAddr_S1_Param4=39C000
set FlashAddr_S2_Param1=3A0000
set FlashAddr_S2_Param2=3A4000
set FlashAddr_S2_Param3=3A8000
set FlashAddr_S2_Param4=3AC000
set FlashAddr_S3_Param1=3B0000
set FlashAddr_S3_Param2=3B4000
set FlashAddr_S3_Param3=3B8000
set FlashAddr_S3_Param4=3BC000
set FlashAddr_SignalChain1=400000
set FlashAddr_SignalChain2=402000
set FlashAddr_SignalChain3=404000
set FlashAddr_Ver=406000
set FlashAddr_Gain=407000

@echo on

%ElvisASD2HEX_File% ASD ELVIS ^
%ASD_S1_BaseLayer_HexFile% %ASD_S1_BaseLayer_BinFile% -16BE %FlashAddr_S1_BaseLayer% ^
%ASD_S1_LoadLayer_HexFile% %ASD_S1_LoadLayer_BinFile% -16BE %FlashAddr_S1_LoadLayer% ^
%ASD_S2_BaseLayer_HexFile% %ASD_S2_BaseLayer_BinFile% -16BE %FlashAddr_S2_BaseLayer% ^
%ASD_S2_LoadLayer_HexFile% %ASD_S2_LoadLayer_BinFile% -16BE %FlashAddr_S2_LoadLayer% ^
%ASD_S3_BaseLayer_HexFile% %ASD_S3_BaseLayer_BinFile% -16BE %FlashAddr_S3_BaseLayer% ^
%ASD_S3_LoadLayer_HexFile% %ASD_S3_LoadLayer_BinFile% -16BE %FlashAddr_S3_LoadLayer% ^
%ASD_S1_Param1_HexFile% %ASD_S1_Param1_BinFile% -8BE %FlashAddr_S1_Param1% ^
%ASD_S1_Param2_HexFile% %ASD_S1_Param2_BinFile% -8BE %FlashAddr_S1_Param2% ^
%ASD_S1_Param3_HexFile% %ASD_S1_Param3_BinFile% -8BE %FlashAddr_S1_Param3% ^
%ASD_S1_Param4_HexFile% %ASD_S1_Param4_BinFile% -8BE %FlashAddr_S1_Param4% ^
%ASD_S2_Param1_HexFile% %ASD_S2_Param1_BinFile% -8BE %FlashAddr_S2_Param1% ^
%ASD_S2_Param2_HexFile% %ASD_S2_Param2_BinFile% -8BE %FlashAddr_S2_Param2% ^
%ASD_S2_Param3_HexFile% %ASD_S2_Param3_BinFile% -8BE %FlashAddr_S2_Param3% ^
%ASD_S2_Param4_HexFile% %ASD_S2_Param4_BinFile% -8BE %FlashAddr_S2_Param4% ^
%ASD_S3_Param1_HexFile% %ASD_S3_Param1_BinFile% -8BE %FlashAddr_S3_Param1% ^
%ASD_S3_Param2_HexFile% %ASD_S3_Param2_BinFile% -8BE %FlashAddr_S3_Param2% ^
%ASD_S3_Param3_HexFile% %ASD_S3_Param3_BinFile% -8BE %FlashAddr_S3_Param3% ^
%ASD_S3_Param4_HexFile% %ASD_S3_Param4_BinFile% -8BE %FlashAddr_S3_Param4% ^
%ASD_SignalChain1_HexFile% %ASD_SignalChain1_BinFile% -8LE %FlashAddr_SignalChain1% ^
%ASD_SignalChain2_HexFile% %ASD_SignalChain2_BinFile% -8LE %FlashAddr_SignalChain2% ^
%ASD_SignalChain3_HexFile% %ASD_SignalChain3_BinFile% -8LE %FlashAddr_SignalChain3%

%ElvisASD2HEX_File% ASD TXT %ASD_Ver_HexFile% %ASD_Ver_File% -COSTUM %FlashAddr_Ver%
%ElvisASD2HEX_File% ASD MOBIS %ASD_Gain_HexFile% %ASD_Gain_File% -COSTUM %FlashAddr_Gain%

%ElvisASD2HEX_File% MERGE HEX ^
%Output_File% ^
%ASD_S1_BaseLayer_HexFile% %ASD_S1_LoadLayer_HexFile% ^
%ASD_S2_BaseLayer_HexFile% %ASD_S2_LoadLayer_HexFile% ^
%ASD_S3_BaseLayer_HexFile% %ASD_S3_LoadLayer_HexFile% ^
%ASD_S1_Param1_HexFile% %ASD_S1_Param2_HexFile% %ASD_S1_Param3_HexFile% %ASD_S1_Param4_HexFile% ^
%ASD_S2_Param1_HexFile% %ASD_S2_Param2_HexFile% %ASD_S2_Param3_HexFile% %ASD_S2_Param4_HexFile% ^
%ASD_S3_Param1_HexFile% %ASD_S3_Param2_HexFile% %ASD_S3_Param3_HexFile% %ASD_S3_Param4_HexFile% ^
%ASD_SignalChain1_HexFile% %ASD_SignalChain2_HexFile% %ASD_SignalChain3_HexFile% ^
%ASD_Ver_HexFile% %ASD_Gain_HexFile%

%ElvisASD2HEX_File% REBUILD %Output_File% %Rebuild_File%

del /F /Q ^
%ASD_S1_BaseLayer_HexFile% %ASD_S1_LoadLayer_HexFile% ^
%ASD_S2_BaseLayer_HexFile% %ASD_S2_LoadLayer_HexFile% ^
%ASD_S3_BaseLayer_HexFile% %ASD_S3_LoadLayer_HexFile% ^
%ASD_S1_Param1_HexFile% %ASD_S1_Param2_HexFile% %ASD_S1_Param3_HexFile% %ASD_S1_Param4_HexFile% ^
%ASD_S2_Param1_HexFile% %ASD_S2_Param2_HexFile% %ASD_S2_Param3_HexFile% %ASD_S2_Param4_HexFile% ^
%ASD_S3_Param1_HexFile% %ASD_S3_Param2_HexFile% %ASD_S3_Param3_HexFile% %ASD_S3_Param4_HexFile% ^
%ASD_SignalChain1_HexFile% %ASD_SignalChain2_HexFile% %ASD_SignalChain3_HexFile% ^
%ASD_Ver_HexFile% %ASD_Gain_HexFile% %Output_File%
