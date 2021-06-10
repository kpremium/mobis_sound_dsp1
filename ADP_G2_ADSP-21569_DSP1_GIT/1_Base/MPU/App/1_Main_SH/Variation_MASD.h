
#ifndef _AUDIOPROCESSING_H_
#define _AUDIOPROCESSING_H_

#ifdef USE_MEASURE_MIPS
extern ST_MIPS_INFO oMipsInfoAP_uL;
extern ST_MIPS_INFO oMipsInfoAP_uS;
#endif

#define SAMPLING_RATE_96                (96000)         // Audio Sampling Rate : 96kHz
#define SAMPLING_RATE_48                (48000)         // Audio Sampling Rate : 48kHz

#define PINGPONG_BUF           (2)             // Number of Ping-Pong Buffer
#define AP_A2B_BLKSIZ          (16)            // Number of Samples for A2B (3kHz cycles @ 48kHz sampling rate)
#define AP_AMP_I_CH             (16)            // TDM A2B Data Channels
#define AP_AMP_O_CH            (16)            // TDM A2B Data Channels
#define AP_ACC_I_CH             (16)            // TDM ACC1 Data Channels - (Accel x5, + option x1(ESEV))
#define AP_MIC_I_CH             (8)             // TDM PMIC Data Channels - (Mic x8)
#define AP_IPC_I_CH              (16)            // TDM Griffin-UL for DSP1/DSP2 Data Channels
#define AP_IPC_O_CH             (16)            // TDM Griffin-UL for DSP1/DSP2 Data Channels
#define AP_VES_O_CH            (2)             // I2S SHARC for VESS Data Channels
#define AP_CAM_I_CH            (2)             // Camping Scenario Data Channels
#define AP_CAM_O_CH           (2)             // Camping Scenario Data Channels
#define NUM_SPORT_SAMPLES               (32)            // Number of Samples for SPORT IO
#define AP_IPC_BLKSIZ              (NUM_SPORT_SAMPLES)         // Number of Samples for ANCASD (3kHz cycles @ 96kHz sampling rate)
#define AP_ASD_I_CH          (8)             // TDM SHARC for ANC/ASD Data Channels
#define AP_ASD_O_CH         (8)             // TDM SHARC for ANC/ASD Data Channels

#define NUM_SSN                         (2)             // Number of SS4SH Schematic (*NEVER CHANGE*)
#define NUM_SSn1_BLOCK_SAMPLES          (AP_A2B_BLKSIZ)           // Number of SSN 'A' Block Samples
#define NUM_SSn2_BLOCK_SAMPLES          (AP_A2B_BLKSIZ)           // Number of SSN 'B' Block Samples
#define NUM_IP_CHANNELS_SSn1            (26)            // SSN I Channels
#define NUM_OP_CHANNELS_SSn1            (10)            // SSN O Channels
#define NUM_IP_CHANNELS_SSn2            (2)             // SSN I Channels
#define NUM_OP_CHANNELS_SSn2            (2)             // SSN O Channels

uint32_t MAIN_AudioProcessingInit(void);
void DoneAudioProcessing(void);
void ExecAudioProcessing(void);
void MAIN_AudioProcessing_uL(unsigned int id, void* arg);
void MAIN_AudioProcessing_uS(unsigned int id, void* arg);
uint8_t IsBlockedAudioProcessing(void);
void ChangeModeAudioProcessing(uint8_t bBlocked);
void ReadInputDataFromAMP(void);
void WriteOutputDataToAMP(void);
void ReadInputDataFromDSP(void);
void WriteOutputDataToDSP(void);
void ReadInputDataFromACC1(void);
void ReadInputDataFromPMIC(void);
void WriteOutputDataToVESS(void);
void ReadInputDataFromASRC(void);
void WriteOutputDataToASRC(void);
void ChangeModeAudioProcessing(uint8_t bBlocked);

#endif /* _AUDIOPROCESSING_H_ */

