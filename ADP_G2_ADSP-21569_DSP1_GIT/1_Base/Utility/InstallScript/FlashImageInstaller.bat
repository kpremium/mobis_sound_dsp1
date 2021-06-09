@echo off

cls

set Install_Option=

echo "***** Select a install option for HKMC *****"
echo "* [1] Make Full image                      *"
echo "* [2] Make SSn image                       *"
echo "* [3] Make ASD image                       *"
echo "* [4] Make ADDRTBL image                   *"
echo "* [5] Make USER image                      *"
echo "********************************************"
choice /c 12345 /t 30 /d 1 /m "What is your option"
if ERRORLEVEL 1 set Install_Option=1
if ERRORLEVEL 2 set Install_Option=2
if ERRORLEVEL 3 set Install_Option=3
if ERRORLEVEL 4 set Install_Option=4
if ERRORLEVEL 5 set Install_Option=5
echo You chose to option %Install_Option%

if /I "%Install_Option%" == "1" (
call 1_MakeFullImage.bat
)

if /I "%Install_Option%" == "2" (
call 2_MakeSSnImage.bat
)

if /I "%Install_Option%" == "3" (
call 3_MakeASDImage.bat
)

if /I "%Install_Option%" == "4" (
call 4_MakeADDRTBLImage.bat
)

if /I "%Install_Option%" == "5" (
call 5_MakeUserImage.bat
)

pause