#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <curses.h>
#include "rfmxx.h"

#define RUNNING 1               // The main program is running
#define STOPPED 0               // The main program has stopped

#define MAX_PAYLOADS	32

struct TPayload {
    int InUse;
    int Channel;

    time_t LastPacketAt;

    char Telemetry[256];
    char Payload[32];

    char Time[12];
    unsigned int Counter, LastCounter;
    double Longitude, Latitude;
    unsigned int Altitude, PreviousAltitude;
    float AscentRate;
    unsigned long LastPositionAt;
};

struct TLoRaDevice {
    double Frequency;
    double Bandwidth;
    double CurrentBandwidth;

    int InUse;
    int DIO0;
    int DIO5;
    double activeFreq;

    int AFC;                    // Enable Automatic Frequency Control
    double MaxAFCStep;          // Maximum adjustment, in kHz, per packet
    int AFCTimeout;             // Revert to original frequency if no packets for this period (in seconds)

    int SpeedMode;
    int Power;
    int PayloadLength;
    int ImplicitOrExplicit;
    int ErrorCoding;
    int SpreadingFactor;
    int LowDataRateOptimize;
    WINDOW *Window;
    unsigned int TelemetryCount, SSDVCount, BadCRCCount, UnknownCount;
    int Sending;
    // unsigned long Seconds;
    // double PredictedLongitude, PredictedLatitude;
    // unsigned int Satellites;
    time_t LastSSDVPacketAt, LastTelemetryPacketAt;
    time_t ReturnToCallingModeAt;
    time_t ReturnToOriginalFrequencyAt;
    int InCallingMode;
    int ActivityLED;
    double UplinkFrequency;
    int UplinkMode;

    // Normal (non TDM) uplink
    int UplinkTime;
    int UplinkCycle;

    // RJH Used to hold gateway.txt config
    TLoRaMode InitialLoRaSettings;

    // RJH Used to store the current RX mode when 
    // toggling -1 = as defined in gateway.txt 
    // 0,1,2,3... as defined rfmxx.h LoRaModes[]
    int CurrentMode;

    // RJH store for current frequency when toggeling through calling mode and back out
    double FrequencyHold;

};

struct TConfig {
    char Tracker[16];           // Callsign or name of receiver
    double latitude, longitude; // Receiver's location
    double altitude;
    int EnableHabitat;
    int EnableSSDV;
    int EnableTelemetryLogging;
    int EnablePacketLogging;
    int CallingTimeout;
    char SSDVJpegFolder[100];
    char ftpServer[100];
    char ftpUser[32];
    char ftpPassword[32];
    char ftpFolder[64];
    struct TLoRaDevice LoRaDevices[2];
    struct TPayload Payloads[MAX_PAYLOADS];
    int NetworkLED;
    int InternetLED;
    int ServerPort;             // JSON port for telemetry, settings
    char SMSFolder[64];
    char antenna[64];
    int EnableDev;
};

typedef struct {
    int parent_status;
    unsigned long packet_count;
} thread_shared_vars_t;

typedef struct {
    short int Channel;
    char Telemetry[257];
    int Packet_Number;
} telemetry_t;

typedef struct {
    short int Channel;
    char SSDV_Packet[257];
    int Packet_Number;
} ssdv_t;

struct TServerInfo {
    int Port;
    int Connected;
    int sockfd;
};

extern struct TConfig Config;

extern int SSDVSendArrayIndex;

extern pthread_mutex_t ssdv_mutex;

void LogMessage( const char *format, ... );

#endif
