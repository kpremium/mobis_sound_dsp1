
#ifndef _AUDIOPROCESSING_H_
#define _AUDIOPROCESSING_H_

#ifdef USE_MEASURE_MIPS
extern ST_MIPS_INFO oMipsInfoAP_uL;
extern ST_MIPS_INFO oMipsInfoAP_uS;
#endif

#define SAMPLING_RATE_96                (96000)         // Audio Sampling Rate : 96kHz
#define SAMPLING_RATE_48                (48000)         // Audio Sampling Rate : 48kHz

#define NUM_IN_OUT_BLOCKS               (2)             // Number of Ping-Pong Buffer
#define NUM_A2B_SAMPLES                 (16)            // Number of Samples for A2B (3kHz cycles @ 48kHz sampling rate)
#define NUM_IP_CHANNELS_A2B             (16)            // TDM A2B Data Channels
#define NUM_OP_CHANNELS_A2B             (16)            // TDM A2B Data Channels
#define NUM_IP_CHANNELS_ACC1            (16)            // TDM ACC1 Data Channels - (Accel x5, + option x1(ESEV))
#define NUM_IP_CHANNELS_PMIC            (8)             // TDM PMIC Data Channels - (Mic x8)
#define NUM_IP_CHANNELS_DSP             (16)            // TDM Griffin-UL for DSP1/DSP2 Data Channels
#define NUM_OP_CHANNELS_DSP             (16)            // TDM Griffin-UL for DSP1/DSP2 Data Channels
#define NUM_OP_CHANNELS_VESS            (2)             // I2S SHARC for VESS Data Channels
#define NUM_IP_CHANNELS_CAMPING         (2)             // Camping Scenario Data Channels
#define NUM_OP_CHANNELS_CAMPING         (2)             // Camping Scenario Data Channels
#define NUM_SPORT_SAMPLES               (32)            // Number of Samples for SPORT IO
#define NUM_ANCASD_SAMPLES              (NUM_SPORT_SAMPLES)         // Number of Samples for ANCASD (3kHz cycles @ 96kHz sampling rate)
#define NUM_IP_CHANNELS_ANCASD          (8)             // TDM SHARC for ANC/ASD Data Channels
#define NUM_OP_CHANNELS_ANCASD          (8)             // TDM SHARC for ANC/ASD Data Channels

#define NUM_SSN                         (2)             // Number of SS4SH Schematic (*NEVER CHANGE*)
#define NUM_SSn1_BLOCK_SAMPLES          (NUM_A2B_SAMPLES)           // Number of SSN 'A' Block Samples
#define NUM_SSn2_BLOCK_SAMPLES          (NUM_A2B_SAMPLES)           // Number of SSN 'B' Block Samples
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

