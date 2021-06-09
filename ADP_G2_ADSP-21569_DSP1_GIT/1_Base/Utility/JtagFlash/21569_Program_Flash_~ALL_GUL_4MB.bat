@set LDR_FILE="%~dp0~ADP_G2-21569_FULL_DSP1.ldr"

@if not exist %LDR_FILE% goto _GOTO_ERROR_

@c:

@cd\Analog Devices\CrossCore Embedded Studio 2.9.3

cldp -proc ADSP-21569 -verbose -cmd prog -driver "%~dp0MT25QL512ABB_dpia_2156x.dxe" -erase affected -emu ice-2000 -format hex -file %LDR_FILE% 

@goto _GOTO_EXIT_

:_GOTO_ERROR_

@echo %LDR_FILE% file not found

@goto _GOTO_EXIT_

:_GOTO_EXIT_

@pause