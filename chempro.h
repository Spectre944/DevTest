#ifndef CHEMPRO_H
#define CHEMPRO_H

#include <QObject>
#include <QDebug>
#include <QDate>


#define StatusCode 4
#define ResetCode 133
#define BaudrateCode 159
#define AlarmData 162
#define NumOfAlarmMemo 163
#define GetGasLibState 186
#define SetGasLibState 187
#define GetGasLibInfo 188
#define ShutDown 131
#define GetBatInfo 175

#define GetV3Meas 36
#define GetAges 139
#define GetTimeAndDate 143
#define SetTimeAndDate 144
#define GetDataLogSize 160
#define GetDataLogData 161
#define GetAlarmMemoItem 164
#define EraseAlarmMemo 165
#define GetDiagErrors 167
#define IsSystemBusy 172
#define SensorTestOnOff 191


#define CRC_LENGHT 2


#define RESETAUTHCODESIZE 12
#define MAXDATALOGDATASIZE 128
#define ALARMMEMOERASEAUTHCODESIZE 24


#define GASLIBNAMESIZE 16
#define SUBSETNAMESIZE 32
#define NUMOFSUBSETS 32

#define SHUTDOWNAUTHCODESIZE 14


// State bits :
#define ISSYSTEMBUSY_NOTBUSY 0
#define ISSYSTEMBUSY_FATALERROR 1 //bit 0: fatal error
#define ISSYSTEMBUSY_WARMINGUP 2 //bit 1: detector is starting
#define ISSYSTEMBUSY_RUNNINGDIAG 4 //bit 2: detector is running diagnostic (and possibly starting up)
#define ISSYSTEMBUSY_READINGDLOG 8 //bit 3: datalog transfer is on
#define ISSYSTEMBUSY_WRITINGFLASH 16 //bit 4. writing FLASH memory
#define ISSYSTEMBUSY_ADJUSTING 32 //bit 5: adjusting flow
#define ISSYSTEMBUSY_DECONTAMINATING 64 //bit 6: running decontamination
#define ISSYSTEMBUSY_SENSORTESTINPROG 256 //bit 8 : running sensor test
#define ISSYSTEMBUSY_STABILIZINGFLOW 512 //bit 9: stabilizing flow (and possibly starting up)

class ChemPro
{

public:

    ChemPro();

    //function that can transmmit 10 difrent packages
    QByteArray commonReq(unsigned char FCode);

    QByteArray resetSystem();
    QByteArray setBaudrate(unsigned char baudRate);
    QByteArray getAlarmData(unsigned char flushFIFO);
    QByteArray getGasLibInfo(unsigned char elementIndex);
    QByteArray setGasLibState(unsigned char gasLibIndex, unsigned char subsetIndex);
    QByteArray sensorTestOnOff(unsigned char testOn);
    QByteArray getDataLogData(unsigned char adress, unsigned char numOfBytes);
    QByteArray eraseAlarmMemoItem();
    QByteArray shutDown();
    QByteArray setTimeAndDate();







private:



};



/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  CRC CALCULATION
*/
const unsigned char crchi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
    };

const unsigned char crclo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
    };


// input: pointer to first data byte and num of data bytes
// output: CRC16 value
unsigned short CRC16(unsigned char *Data, unsigned long DataLen);

QByteArray retByteArray(unsigned char *Data, unsigned long DataLen);

/*
 *  HEADER FOR ALL PACKAGES
*/

//MsgHeader Function Code если значение 5 - передача сырых данных, если 10 - изменение номера девайса
//Стандартный номер девайса 10 (не менять)
//Ответ будет только в случае сопадения CRC и Кода пакета

struct MsgHeader
{
    unsigned char DeviceId = 10;
    unsigned char FunctionCode = 5;
};

struct SerDataHeader
{
    unsigned char FunctionCode;       //FunctionCode - ID пакета
    unsigned char NumOfBytes = 0;         //Если длина структуры <= 256 NOB и NOB16 заполняются одинаково
    unsigned short NumOfBytes16 = 0;      //Если длина структуры > 256 NOB = 0, NOB16 - кол-во посчитанных байт
};


struct MsgTail
{
    unsigned char CrcHi;
    unsigned char CrcLo;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  ERRORS WHILE TRANSMITTING
*/

struct SC_ErrorReplyMessage
{
    struct SerDataHeader Header;
    unsigned char ErrorCode;
    unsigned char Reserved;
};

enum SerialErrors
{
    SCERR_UnKnownCmd=1,     //Нераспознанная команда
    SCERR_WrongCmdCode,     //Ошибка в коммуникации (теоретически не должен появлятся вообще)
    SCERR_OutOfRange,       //???
    SCERR_InvalidMsgSize,   //Неправильный указанный размер пакета по сравнению с тем что запрограммировано в FunctionCode
    SCERR_CmdDisabled       //Нет доступа к запрошенным командам (типа режим админа)
};


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  COMMON STRUCT
*/

struct SC_Sensor_GetCommon
{
    struct MsgHeader msgHeader = {10, 5};
    struct SerDataHeader Header = {0, 4, 4};
    struct MsgTail msgTail = {0,0};
};



/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  GET SENSOR STATUS
*/
struct SensorStatus
{
    unsigned char ErrorFlags;
    unsigned char HwErrorCode;
};

struct SC_Sensor_GetStatusRequestMessage
{
    struct SerDataHeader Header;
};

struct SC_Sensor_GetStatusReplyMessage
{
    struct SerDataHeader Header;
    struct SensorStatus Status;
};


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  RESET SYSTEM
*/
struct SC_Processor_ResetSystemRequestMessage
{
    struct SerDataHeader Header;
    unsigned char AuthorizationCode[RESETAUTHCODESIZE];
};

struct SC_Processor_ResetSystemReplyMessage
{
    struct SerDataHeader Header;
};

//User struct
struct SC_Sensor_UReset
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_ResetSystemRequestMessage msgContent;
    struct MsgTail msgTail = {0,0};
};

/*
 *  SET BAUDRATE
 *
 *  0 = 9600 bit/s
 *  1 = 19200 bit/s
 *  2 = 28800 bit/s
 *  3 = 38400 bit/s
*/
struct SC_Processor_SetBaudRateRequestMessage
{
    struct SerDataHeader Header;
    unsigned char BaudRate;
    unsigned char Reserved;
};

struct SC_Processor_SetBaudRateReplyMessage
{
    struct SerDataHeader Header;
};

//User struct
struct SC_Sensor_UBaudRate
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_SetBaudRateRequestMessage msgContent = {{BaudrateCode, 0, 0}, 0, 0};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  SensorGetV3Meas
*/


struct EmeasStr
{
    float FlowSensorVoltage; /* Flow sensor output voltage [V] */
    float FlowSensorVal; /* Flow sensor output value [l/min] */
    unsigned long MOS1_HeaterResistance; /* MOS1 heater resistance */
    unsigned long MOS1_SensorResistance; /* MOS1 sensor resistance [ohm] */
    float MOS1_HeaterVoltage; /* MOS1 heater voltage [V] */
    unsigned long MOS2_HeaterResistance; /* MOS2 heater resistance */
    unsigned long MOS2_SensorResistance; /* MOS2 sensor resistance [ohm] */
    float MOS2_HeaterVoltage; /* MOS2 heater voltage [V] */
    unsigned long MOS3_HeaterResistance; /* MOS3 heater resistance */
    unsigned long MOS3_SensorResistance; /* MOS3 sensor resitance [ohm] */
    float MOS3_HeaterVoltage; /* MOS3 heater voltage [V] */
    float FET_SensorVoltage; /* FET sensor output signal [V] */
    float FET_SensorTempVoltage; /* FET sensor temperature signal [V] */
    unsigned short AirPressure; /* Air pressure [mBar] */
    unsigned short ImsArmMeasStatus; /* IMS processor status flags */
    float ImsFlow; /* IMS flow [l/min] */
    unsigned long MeasCount; /* Meas counter, changes every second */
    unsigned char ScCellFilterLen; /* ScCell filter length [samples] */
    unsigned char Reserved2; /* Reserved */
    unsigned long Mos3_Age; /* MOS3 sensor runtime [min] */
    unsigned char Reserved3[4]; /* Reserved */
    float MassFlowOffset; /* MassFlowOffset value */
    unsigned long MicroSensorA_Age; /* Microsensor unit A runtime [min] */
    unsigned long FET_Age; /* FET sensor runtime [min] */
    unsigned char Reserved1[12]; /* Reserved */
    unsigned char Reserved[4]; /* Reserved */
};

#define MAXIMSCH 8
struct SensorNewIMS
{
    float IMSpos[MAXIMSCH]; //Channel 1..8 IMS measurement with positive bias [pA]
    float IMSneg[MAXIMSCH]; //Channel 1..8 IMS measurement with negative bias [pA]
    float CellTemp; //Cell temperature [*C]
    float TempSp; //Cell temperature setting [*C]
    float ExternalTemp; //External temperature [*C]
    float Humidity; //Relative humidity [%]
    float Flow; //Air flow [l/min]
    float FlowSp; //Flow setting [l/min]
    unsigned long ScCell1R; //ScCell 1 resistance [ohm]
    float ScCell1; //ScCell 1 measurement [V] (0V..5V)
    unsigned long ScCell2R; //ScCell 2 resistance [ohm]
    float ScCell2; //ScCell 2 measurement [V] (0V..5V)
    float BattVoltage; //Battery voltage [V]
    unsigned short PumpPwm; //Pump PWM value
    unsigned char Filter; //IMS channel 1..8 filter used
    unsigned char Status; //IMS measurement status
    unsigned char Status2; //IMS measurement status 2
    unsigned char Counter; //Increased by one at every measurement cycle
    float AbsoluteHumidity; //Absolute humidity [g/m3]
};

struct SC_Sensor_GetV3MeasRequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Sensor_GetV3MeasReplyMessage
{
    struct SerDataHeader Header;
    struct SensorNewIMS NewImsMeas; // see SC_Sensor_GetNewMeas
    struct EmeasStr Emeas;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  GET AGES
*/

struct SC_Processor_GetAgesRequestMessage
{
    struct SerDataHeader Header;
};

struct SC_Processor_GetAgesReplyMessage
{
    struct SerDataHeader Header;
    unsigned long PumpAge;
    unsigned long ScCellAge;
};

struct SC_Processor_GetAgesReplyMessage100i
{
    struct SerDataHeader Header;
    unsigned long PumpAge; // [s]
    unsigned long ScCellAge; // [s]
    unsigned long MicroSensorA_Age; // [min]
    unsigned long Mos3_Age; // [min]
    unsigned long FET_Age; // [min]
};


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  GET TIME AND DATE
*/
struct TimeStr
{
    unsigned short Year;
    unsigned char Month;
    unsigned char Day;
    unsigned char Hour;
    unsigned char Minute;
    unsigned char Second;
    unsigned char WeekDay; //0=Monday, 6=Sunday
};

struct SC_Processor_GetTimeAndDateRequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Processor_GetTimeAndDateReplyMessage
{
    struct SerDataHeader Header;
    struct TimeStr TimeAndDate;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  SET TIME AND DATE
*/

struct SC_Processor_SetTimeAndDateRequestMessage
{
    struct SerDataHeader Header;
    struct TimeStr TimeAndDate;
};
struct SC_Processor_SetTimeAndDateReplyMessage
{
    struct SerDataHeader Header;
};

//User struct
struct SC_Sensor_USetTime
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_SetTimeAndDateRequestMessage msgContent = {{SetTimeAndDate, 0, 0}};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  GET DATA LOG SIZE
*/

struct SC_Processor_GetDataLogSizeRequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Processor_GetDataLogSizeReplyMessage
{
    struct SerDataHeader Header;
    unsigned long NumOfBytes;
};


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  GET DATA LOG DATA
*/

struct SC_Processor_GetDataLogDataRequestMessage
{
    struct SerDataHeader Header;
    unsigned long Address;
    unsigned char NumOfBytes;
    unsigned char Reserved;
};

struct SC_Processor_GetDataLogDataReplyMessage
{
    struct SerDataHeader Header;
    unsigned long Address;
    unsigned char NumOfBytes;
    unsigned char Reserved;
    unsigned char Data[MAXDATALOGDATASIZE];
};

//user Struct
struct SC_Sensor_UGetDataLogData
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_GetDataLogDataRequestMessage msgContent = {{GetDataLogData, 0, 0}, 0, 0, 0};
    struct MsgTail msgTail = {0,0};
};

/*
    NumOfBytes indicates the amount of data to be read. Maximum size is MAXDATALOGDATASIZE bytes.
    NumOfBytes field in the reply message indicates the amount of data read.
    Amount of data can be less than maximum size and is indicated by NumOfBytes field value.
*/


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  ALARM DATA
*/


//struct SC_Processor_GetAlarmDataRequestMessage
//{
//    struct SerDataHeader Header; // request data from FIFO
//};

struct SC_Processor_GetAlarmDataRequestMessage
{
    struct SerDataHeader Header;
    unsigned short FlushFIFO; // set this variable to 1 to FLUSH the FIFO
};

//User struct
struct SC_Sensor_UGetAlarmData
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_GetAlarmDataRequestMessage msgContent = {{AlarmData, 0, 0}, 0};
    struct MsgTail msgTail = {0,0};
};

struct LogDetInfoStr
{
    char Valid; // Zero if no library, running sensortest etc
    char InvalidityReason; // Why data is not ok
    char ConcClassification; // 0=below low, 1=low, 2=med, 3=high
    char ConcUnit; // Unit of concentration (mg/m3, ppm), do no use
    struct TimeStr TimeStamp; // Time (at CP100)
    long ClassId; // Alarm class id (-1 (0xffffffff), if no alarm)
    char GasName[32]; // Name of alarmed gas
    float Concentration; // Concentration, do not use
    float Memberhood; // Memberhood
    float Proj; // Projection to the closest neuron (-1, if no neurons in the class)
    signed short IMS[16]; // Relative IMS-channel values (pA/100) or the basic levels in basic level calculation
    float SCCell_Rel; // Value of the ScCell (relative)
    float SCCell_Abs; // Value of the ScCell (absolute)
    float CellTemp; // Temperature of the IMS-cell (*C)
    float ExternalTemp; // Outside temperature (*C)
    float Flow; // Air flow (l/min)
    float Humidity; // Relative humidity (%)
    unsigned short State; // State of the gas detection
    char BasicLevels; // If not zero, IMS-values indicate new basic levels, that successive measurements are relative to
    char AlarmMode; // Type of the alarm
    float SCCell2_Rel; // SCCell2 value (rel)
    float SCCell2_Abs; // SCCell2 value (abs)
};

struct SC_Processor_GetAlarmDataReplyMessage
{
    struct SerDataHeader Header;
    unsigned char NumOfBytes;
    unsigned char Reserved;
    LogDetInfoStr Data;
};

struct SC_Processor_SensortestOnOffReplyMessage
{
    struct SerDataHeader Header;
    unsigned char ErrorCode; //Possible error when activating test
    //(enum SC_SensortestModeErrorCodes)
    unsigned char Reserved;
};

//Error codes for sensor test reply message
enum SC_SensortestModeErrorCodes
{
    SC_STMEC_NoError=0, // No error
    SC_STMEC_NoCurrLib, // No library in use in device
    SC_STMEC_NoTestSubset, // No test subset in current library
    SC_STMEC_Alarm, // Alarm is on
    SC_STMEC_GDError, // Gas detection error
    SC_STMEC_SystemBusy, // Device is doing something more important
    SC_STMEC_UINotInMeasState // User interface is not in measurement state
};

/*
    If there was no alarm data to read, field NumOfBytes of the reply message is null.
    If there was alarm data NumOfBytes tells the amount of data bytes.
    Maximum data size (MAXADDATASIZE) is 128 bytes.
*/


/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  ALARM MEMO ITEMS
*/

struct SC_Processor_GetNumOfAlarmMemoItemsRequestMessage
{
    struct SerDataHeader Header;
};

struct SC_Processor_GetNumOfAlarmMemoItemsReplyMessage
{
    struct SerDataHeader Header;
    unsigned short NumOfAlarms;
    unsigned char MemoState;
    unsigned char Reserved;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 *  ALARM MEMO ITEM
*/

typedef struct
{
    float Latitude; /**< format ddmm.mmmm */
    float Longitude; /**< format dddmm.mmmm */
    float Altitude; /**< meters */
    char NS; /**< N=north or S=south */
    char EW; /**< E=east, W=west */
} AlarmItemGPSDataStr;

typedef struct
{
    long ClassId;
    char Name[32]; // Gas name
    char GasLibName[16]; // Gas library name
    struct TimeStr StartTime; // Alarm start time
    unsigned long StartTime_MeasNum;
    char Ack; // 1=acknowledged
    unsigned char AlarmItemVersion; // This must be always 1 (if specified format)
    struct TimeStr AckTime; // Alarm acknowledge time
    unsigned long AckTime_MeasNum;
    struct TimeStr EndTime; // Alarm end time
    unsigned long EndTime_MeasNum;
    float HighestConcentration;
    char ConcUnit;
    char ConcClassification; // Concentration: 0=below “low”, 1=low, 2=med, 3=high
    long MainClass;
    AlarmItemGPSDataStr GPSData; // GPS-data
} AlarmItemStr;

struct SC_Processor_GetAlarmMemoItemRequestMessage
{
    struct SerDataHeader Header;
    unsigned short TimeIndex;
    unsigned char NumOfBytes;
    unsigned char Reserved;
};

struct SC_Processor_GetAlarmMemoItemReplyMessage
{
    struct SerDataHeader Header;
    unsigned char NumOfBytes;
    unsigned char MemoState;
    AlarmItemStr Data;
};

//Kyllä lähtee alarmmemot!

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * ERASE ALARM MEMO ITEM
*/

struct SC_Processor_EraseAlarmMemoRequestMessage
{
    struct SerDataHeader Header;
    unsigned char AuthorizationCode[ALARMMEMOERASEAUTHCODESIZE];
};

struct SC_Processor_EraseAlarmMemoReplyMessage
{
    struct SerDataHeader Header;
};

//User struct
struct SC_Sensor_UEraseAlarmMemo
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_EraseAlarmMemoRequestMessage msgContent = {{EraseAlarmMemo, 0, 0},""};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * GET DIAG ERRORS
*/

struct DiagErrorBitsStr
{
    unsigned long Errors1; /* Diagnostic errors D00-D31 */
    unsigned long Errors2; /* Diagnostic errors D32-D63 */
};

struct SC_Processor_GetDiagErrorsRequestMessage
{
    struct SerDataHeader Header;
};

struct SC_Processor_GetDiagErrorsReplyMessage
{
    struct SerDataHeader Header;
    struct DiagErrorBitsStr DiagErrors;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * GET GAS LIB STATE
*/
struct SC_Processor_RequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Processor_GetGasLibStateReplyMessage
{
    struct SerDataHeader Header;
    unsigned short NumOfGasLibraries; // the number of valid gas libraries (zero=none)
    unsigned short GasLibraryInUse; // selected gaslibrary (0..NumOfGasLibraries-1)
    unsigned short SubsetInUse; // selected subset (0..31) – for example CWA, TIC …
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * SET GAS LIB STATE
*/

//Saa vaihtaa kirjastoa.
#define SETGASLIBAUTHCODESIZE 22

struct Fixed_SetGasLibInUseRequestMessage
{
    struct SerDataHeader Header;
    unsigned char AuthorizationCode[SETGASLIBAUTHCODESIZE];
    unsigned short GasLibIndex; // (0..NumOfGasLibraries-1) according the library
    unsigned short SubsetIndex; // (0..30) according the library   //DO NOT SET BIGGER THAN 30 IT CAN LOCK DEVICE
};

struct Fixed_SetGasLibInUseReplyMessage
{
    struct SerDataHeader Header;
    unsigned char GasLibraryChanged; // zero = gas lib change failed or not possible
    unsigned char Reserved;
};

//User struct
struct SC_Sensor_USetGasLibUse
{
    struct MsgHeader msgHeader = {10, 5};
    struct Fixed_SetGasLibInUseRequestMessage msgContent = {{SetGasLibState, 0, 0}, "", 0, 0};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * GET GAS LIB INFO
*/

struct SC_Processor_GetGasLibInfoRequestMessage
{
    struct SerDataHeader Header;
    unsigned short GasLibIndex; //library index (0..NumOfGasLibraries-1) according to GetGasLibState
};
struct SC_Processor_GetGasLibInfoReplyMessage
{
    struct SerDataHeader Header;
    char GasLibName[GASLIBNAMESIZE];
    char SubSetName[NUMOFSUBSETS][SUBSETNAMESIZE]; //Null if no subset available
};

//User struct
struct SC_Sensor_UGetGasLibInfo
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_GetGasLibInfoRequestMessage msgContent = {{GetGasLibInfo, 0, 0}, 0};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * SHUTDOWN AND REMOTE POWER UP
*/

//avoid shutting down the detector 30 min
//“Saa sammuttaa!”
struct SC_Processor_ShutDownRequestMessage
{
    struct SerDataHeader Header;
    unsigned char AuthorizationCode[SHUTDOWNAUTHCODESIZE];
};
struct SC_Processor_ShutDownReplyMessage
{
    struct SerDataHeader Header;
};

//User struct
struct SC_Sensor_UShutDown
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_ShutDownRequestMessage msgContent = {{ShutDown, 0, 0}};
    struct MsgTail msgTail = {0,0};
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * BATTERY INFO
*/
struct BattInfoStr
{
    float BattVoltage; // Battery voltage [V]
    float BattTemp; // Battery temperature [‘C]
    unsigned short ChargeCurrent; // The charge current of the battery [mA]
    unsigned char BattState; // 0=external power, 1=battery power, 2=battery charge
    unsigned char OverCurrent; // Over current state
    unsigned char MainProgVer; // Charging system version information
    unsigned char SubProgVer; // Charging system version information
    unsigned char BattPros; // The amount of charge left in the battery [%]
    unsigned char MeasNotReady; // Measurements are not currently ready (!= NULL)
};

struct SC_Processor_IsSystemBusyRequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Processor_IsSystemBusyReplyMessage
{
    struct SerDataHeader Header;
    unsigned short State; // See ISSYSTEMBUSY_.... state bits
};

struct SC_Processor_GetBattInfoRequestMessage
{
    struct SerDataHeader Header;
};
struct SC_Processor_GetBattInfoReplyMessage
{
    struct SerDataHeader Header;
    struct BattInfoStr BattInfo;
};

/*7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
 * SENSOR TEST
*/

struct SC_Processor_SensortestOnOffRequestMessage
{
    struct SerDataHeader Header;
    unsigned char TestOnOff; //0=test off, 1=test on
    unsigned char Reserved;
};

struct SC_Sensor_USensorTestOnOff
{
    struct MsgHeader msgHeader = {10, 5};
    struct SC_Processor_SensortestOnOffRequestMessage msgContent = {{SensorTestOnOff, 0, 0}, 0, 0};
    struct MsgTail msgTail = {0,0};
};

#endif // CHEMPRO_H
