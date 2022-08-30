#include "chempro.h"

ChemPro::ChemPro()
{


}


/*
    AVALIABLE COMMANDS

    StatusCode;
    GetV3Meas;
    GetAges;
    GetTimeAndDate;
    GetDataLogSize;
    GetAlarmMemoItem;
    GetDiagErrors;
    GetGasLibState;
    IsSystemBusy;
    GetBatInfo;
*/
QByteArray ChemPro::commonReq(unsigned char FCode)
{
    QByteArray retArr;
    int tmpCrc = 0;

    //Fill structure by default, only diffrence FCode
    SC_Sensor_GetCommon get = { {10, 5},
                                {FCode, 4, 4},
                                {0, 0}};

    //Calculate CRC
    tmpCrc = CRC16(&get.Header.FunctionCode, 4);

    //rewrite CRC
    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, 8);

    return retArr;
}



QByteArray ChemPro::resetSystem()
{
    QByteArray retArr;

    unsigned char size = sizeof(SC_Processor_ResetSystemRequestMessage);
    int tmpCrc = 0;


    SC_Sensor_UReset get =  { {10, 5},
                            { {ResetCode, size, size}, {'R','e','s','e','t','o','i',' ','v','a','a','n'}},
                              {0, 0}};
    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);

    //rewrite CRC (весь пакет)
    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UReset));

    return retArr;

    //repply is SC_Processor_ResetSystemReplyMessage (only header and size)
}

QByteArray ChemPro::setBaudrate(unsigned char baudRate)
{
    QByteArray retArr;

    unsigned char size = sizeof(SC_Processor_SetBaudRateRequestMessage);
    int tmpCrc = 0;


    SC_Sensor_UBaudRate get ={ {10, 5},
                             { {BaudrateCode, size, size}, baudRate, 0},
                               {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UBaudRate));

    return retArr;

    //repply is SC_Processor_SetBaudRateReplyMessage (only header and size)

}

QByteArray ChemPro::getAlarmData(unsigned char flushFIFO)
{

    //запросы на чтение не чаще 1 секунды для избежания потери данных
    QByteArray retArr;

    unsigned char size = sizeof(SC_Processor_GetAlarmDataRequestMessage);
    int tmpCrc = 0;


    SC_Sensor_UGetAlarmData get = { {10, 5},
                                 { {AlarmData, size, size}, flushFIFO},
                                   {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UGetAlarmData));

    return retArr;

    //repply is SC_Processor_GetAlarmDataReplyMessage

}

QByteArray ChemPro::getGasLibInfo(unsigned char elementIndex)
{
    //запросы на чтение не чаще 1 секунды для избежания потери данных
    QByteArray retArr;

    unsigned char size = sizeof(SC_Processor_GetGasLibInfoRequestMessage);
    int tmpCrc = 0;


    SC_Sensor_UGetGasLibInfo get = { {10, 5},
                                 { {GetGasLibInfo, size, size}, elementIndex},
                                   {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UGetGasLibInfo));

    return retArr;

    //repply is SC_Processor_GetGasLibInfoReplyMessage
}

QByteArray ChemPro::setGasLibState(unsigned char gasLibIndex, unsigned char subsetIndex)
{
    QByteArray retArr{0};

    unsigned char size = sizeof(Fixed_SetGasLibInUseRequestMessage);
    int tmpCrc = 0;

    //выйти если неверный диапазон, неправильные данные могут сломать детектор
//УТОЧНИТЬ
    if(gasLibIndex > 30 || subsetIndex > 30){
        qDebug() << "Wrong range SetGasLib";
        return retArr;
    }
     SC_Sensor_USetGasLibUse get = { {10, 5},
                                   { {SetGasLibState, size, size},
                                     {'S','a','a',' ','v','a','i','h','t','a','a',' ','k','i','r','j','a','s','t','o','a','.'},
                                     gasLibIndex, subsetIndex},
                                     {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_USetGasLibUse));

    return retArr;

    //repply is Fixed_SetGasLibInUseReplyMessage

}

QByteArray ChemPro::sensorTestOnOff(unsigned char testOn)
{
    QByteArray retArr{0};

    unsigned char size = sizeof(SC_Processor_SensortestOnOffRequestMessage);
    int tmpCrc = 0;

     SC_Sensor_USensorTestOnOff get = { {10, 5},
                                      { {SensorTestOnOff, size, size}, testOn , 0},
                                        {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_USensorTestOnOff));

    return retArr;

    //repply is SC_Processor_SensortestOnOffReplyMessage
}

QByteArray ChemPro::getDataLogData(unsigned char adress, unsigned char numOfBytes)
{

    //numOfBytes берётся из запроса GetDataLogSize
    QByteArray retArr{0};

    unsigned char size = sizeof(SC_Processor_GetDataLogDataRequestMessage);
    int tmpCrc = 0;

     SC_Sensor_UGetDataLogData get = { {10, 5},
                                      { {GetDataLogData, size, size}, adress , numOfBytes, 0},
                                        {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UGetDataLogData));

    return retArr;

    //repply is SC_Processor_GetDataLogDataReplyMessage
}

QByteArray ChemPro::eraseAlarmMemoItem()
{
    QByteArray retArr{0};

    unsigned char size = sizeof(SC_Processor_EraseAlarmMemoRequestMessage);
    int tmpCrc = 0;

     SC_Sensor_UEraseAlarmMemo get = { {10, 5},
                                       { {EraseAlarmMemo, size, size},
                                        {'K','y','l','l',132,' ','l',132,'h','t','e','e',' ','a','l','a','r','m','m','e','m','o','t','!'}},
                                        {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UEraseAlarmMemo));

    return retArr;

    //repply is SC_Processor_EraseAlarmMemoReplyMessage
}

QByteArray ChemPro::shutDown()
{
    QByteArray retArr{0};

    unsigned char size = sizeof(SC_Processor_ShutDownRequestMessage);
    int tmpCrc = 0;

     SC_Sensor_UShutDown get = { {10, 5},
                                       { {ShutDown, size, size},
                                        {'S','a','a',' ','s','a','m','m','u','t','t','a','a','!'}},
                                        {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_UShutDown));

    return retArr;

    //repply is SC_Processor_ShutDownReplyMessage
}

QByteArray ChemPro::setTimeAndDate()
{
    QByteArray retArr{0};

    QDate curDate;
    QTime curTime;

    unsigned char size = sizeof(SC_Processor_SetTimeAndDateRequestMessage);
    int tmpCrc = 0;

//     SC_Sensor_USetTime get = { {10, 5},
//                              { {SetTimeAndDate, size, size},{curDate.year(), curDate.month(), curDate.day(), curTime.hour(), curTime.minute(), curTime.second(), curDate.dayOfWeek()}},
//                                {0, 0}};

    SC_Sensor_USetTime get = { {10, 5},
                             { {SetTimeAndDate, size, size},{0, 0, 0, 0, 0, 0, 0}},
                               {0, 0}};

    //Calculate CRC (только msgContent)
    tmpCrc = CRC16(&get.msgContent.Header.FunctionCode, size);


    get.msgTail.CrcLo = tmpCrc;
    get.msgTail.CrcHi = tmpCrc >> 8;

    //rewrite CRC (весь пакет)
    retArr.clear();
    retArr = retByteArray(&get.msgHeader.DeviceId, sizeof(SC_Sensor_USetTime));

    return retArr;

    //repply is SC_Processor_SetTimeAndDateReplyMessage
}



unsigned short CRC16(unsigned char *Data, unsigned long DataLen)
{
    unsigned char hi,lo,index;
    hi = 0xff;
    lo = 0xff;
    while(DataLen--)
    {
        index = hi^*Data++;
        hi = lo^crchi[index];
        lo = crclo[index];
    }
    return(hi*256 | lo);
}


QByteArray retByteArray(unsigned char *Data, unsigned long DataLen)
{
    QByteArray bArray;
    QString array;
    unsigned char index;

    while(DataLen--)
    {
        index = *Data++;
        bArray.append(index);
    }

    return bArray;
}

