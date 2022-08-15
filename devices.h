#ifndef DEVICES_H
#define DEVICES_H

#include <QObject>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QByteArray>


#include "all_devices_info.h"


#define NOANSWER_TIME   1000        // Время ожидания страховочного таймера
#define MIN_TIME        100          // Мин. время ожидания страховочного таймера - в случае ошибки
#define WAIT_SAVE_TIME  10          // Время ожидания окончания записи
#define PROCESS_TIME    1000        // Время срабатывания таймера запросов
#define SVNG_PORT       "COM20"      // Порт, закрепленный за СВНГ-Т (уточнить по МОХА)
#define MIN_PED         1e-6        // Минимальное значение ПЕД




class Devices : public QObject
{

    Q_OBJECT

public:

    explicit Devices(QObject *parent = nullptr);


    enum typeDevice { NO_DEV, SVNG_T, SRHR_T, AIR_MAR, CHEM_PRO };

    typeDevice typeDev;   // С каким из приборов работаем в данное время


//////////////////////// ФЛАГИ ОШИБОК СВНГ-Т //////////////////////////////////////////////

    bool errorOpenSvngComPort;     // Флаг ошибки открытия СОМ-порта
    bool errorSaveSvngComPort;     // Флаг ошибки записи в СОМ-порт
    bool errorCRCSvngComPort;      // Флаг ошибки CRC принятого пакета
    bool errorSizePackSvng;        // Флаг ошибки размера принятого пакета
    bool errorNotAnswerSvng;       // Флаг неответа прибора

////////////////////////////////////////////////////////////////////////////////////////////


public slots:


    /*
    *  Слот старта работы потока для объекта Device
    *  здесь реализуем все создания объектов и коннекты
    */
    void startDeviceThread();


    /*
    *  Слот обработчика таймера ошибок
    */
    void procDevErrorTimer();



    /*
    *  Слот обработчика таймера процесса обработки
    */
    void procProcessTimer();


    // ДОПИСАТЬ Ф-ЦИЮ ЗАКРЫТИЯ ВСЕХ СОМ-ПОРТОВ  ?????????????????????????????????????????????????


    /*
    * Слот формирования массивов запросов к девайсам
    */
    void saveDeviceRequest();


    /*
    * Геттер и сеттер минимальной ПЕД
    */
    void setMinPed(float);
    float getMinPed();



    void exec_req_command();




///////////////////////////////////// ФУНКЦИИ СВНГ-Т НАЧАЛО /////////////////////////////////////////////////////////

    /*
    *  Слот открытия СОМ-порта СВНГ-Т
    */
    bool openSvngSerialPort(const QString & portName); // openSvngSerialPort closeSvngSerialPort writeSvngData readSvngData checkSvngCRC

    /*
    *  Слот закрытия СОМ-порта СВНГ-Т
    */
    void closeSvngSerialPort();

    /*
    *  Слот записи в СОМ-порт СВНГ-Т
    */
    void writeSvngData(QByteArray , int);

    /*
    *  Слот записи в СОМ-порт СВНГ-Т
    */
    void readSvngData();

    /*
    *  Функция для проверки CRC пакета СВНГ-Т
    */
    bool checkSvngCRC(QByteArray& buff, int size);

///////////////////////////////////// ФУНКЦИИ СВНГ-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////







private:


    /*
    *  Указатель на аварийный таймер (если какой-то из девайсов не ответит)
    */
    QTimer * devErrorTimer;


    /*
    *  Указатель на  таймер запросов к девайсам
    */
    QTimer * processTimer;


    /*
    *  Указатель на  объект класса - информация по девайсам
    */
    All_Devices_Info *devInfo;


    QByteArray copyData;



///////////////////////////////////// СВНГ-Т НАЧАЛО /////////////////////////////////////////////////////////

    /*
    *  Указатель на COM-порт СВНГ-Т
    */
    QSerialPort * svng_port;


    /*
    *  Массив для запроса в СВНГ-Т
    */
    QByteArray svng_data_request;


    /*
    * Счетчик ошибок для СВНГ-Т
    */
    int errorSVNG;


    float minPed;



///////////////////////////////////// СВНГ-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////








///////////////////////////////////// СРХР-Т НАЧАЛО /////////////////////////////////////////////////////////

    /*
    * Счетчик ошибок для СРХР-Т
    */
    int errorSRHR;

///////////////////////////////////// СРХР-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////////





///////////////////////////////////// AIR-MAR НАЧАЛО /////////////////////////////////////////////////////////

    /*
    * Счетчик ошибок для AirMar
    */
    int errorAIRMAR;

///////////////////////////////////// AIR-MAR ОКОНЧАНИЕ /////////////////////////////////////////////////////////




///////////////////////////////////// CHEM-PRO НАЧАЛО /////////////////////////////////////////////////////////

    /*
    * Счетчик ошибок для AirMar
    */
    int errorCHEMPRO;

///////////////////////////////////// CHEM-PRO ОКОНЧАНИЕ /////////////////////////////////////////////////////////



signals:

    void transmitDataObject(All_Devices_Info *);




};

#endif // DEVICES_H
