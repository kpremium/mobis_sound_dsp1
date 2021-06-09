"C:\Analog Devices\CrossCore Embedded Studio 2.9.3\elfar.exe" -s -ve "%~dp0%2\%1_ENC.dlb" "%~dp0%2\%1.dlb" "%~dp0non-encrypted_functions" "xxx"

if not exist "%~dp0..\Voyager_MASD\lib\Sounder\%2" ( md "%~dp0..\Voyager_MASD\lib\Sounder\%2" )
copy "%~dp0%2\%1_ENC.dlb" "%~dp0..\Voyager_MASD\lib\Sounder\%2\%1_ENC.dlb"

copy "%~dp0src\%3" "%~dp0..\Voyager_MASD\src\%3"
copy "%~dp0src\%4" "%~dp0..\Voyager_MASD\src\%4"
copy "%~dp0src\include\%5" "%~dp0..\Voyager_MASD\src\include\%5"
copy "%~dp0src\%6" "%~dp0..\Voyager_MASD\src\%6"
copy "%~dp0system\startup_ldf\%7" "%~dp0..\Voyager_MASD\system\startup_ldf\%7"
