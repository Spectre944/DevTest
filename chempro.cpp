#include "chempro.h"

ChemPro::ChemPro()
{


}

QString ChemPro::getSensorStatus(unsigned char FCode)
{
    SC_Sensor_GetStatusRequestMessage get;

    get.Header.FunctionCode = FCode;
    get.Header.NumOfBytes = sizeof(SC_Sensor_GetStatusRequestMessage);
    get.Header.NumOfBytes16 = sizeof(SC_Sensor_GetStatusRequestMessage);

    //header.CRC16 = CRC16(&header.FunctionCode,header.NumOfBytes16);

    QString tmpStr = 0;

    tmpStr.append(retByteArray(&get.Header.FunctionCode,sizeof(get)));
    tmpStr.append('\n');

    //Reply msg
    SC_Sensor_GetStatusReplyMessage repply;

    repply.Header = get.Header;

    repply.Header.NumOfBytes = sizeof(SC_Sensor_GetStatusReplyMessage);
    repply.Header.NumOfBytes16 = sizeof(SC_Sensor_GetStatusReplyMessage);

    //error flags
    repply.Status.ErrorFlags = 0;
    repply.Status.ErrorFlags = 1;

    tmpStr.append(retByteArray(&repply.Header.FunctionCode, sizeof(repply)));


    return tmpStr;
}

QString ChemPro::resetSystem(unsigned char FCode)
{
    SC_Processor_ResetSystemRequestMessage get;

    get.Header.FunctionCode = FCode;
    get.Header.NumOfBytes = sizeof(SC_Processor_ResetSystemRequestMessage);
    get.Header.NumOfBytes16 = sizeof(SC_Processor_ResetSystemRequestMessage);


    get.AuthorizationCode[0] = 'R';
    get.AuthorizationCode[1] = 'e';
    get.AuthorizationCode[2] = 's';
    get.AuthorizationCode[3] = 'e';
    get.AuthorizationCode[4] = 't';
    get.AuthorizationCode[5] = 'o';
    get.AuthorizationCode[6] = 'i';
    get.AuthorizationCode[7] = ' ';
    get.AuthorizationCode[8] = 'v';
    get.AuthorizationCode[9] = 'a';
    get.AuthorizationCode[10] = 'a';
    get.AuthorizationCode[11] = 'n';



    QString tmpStr = 0;

    tmpStr.append(retByteArray(&get.Header.FunctionCode,sizeof(get)));
    tmpStr.append('\n');

    //Reply msg
    SC_Processor_ResetSystemReplyMessage repply;

    repply.Header = get.Header;

    repply.Header.NumOfBytes = sizeof(SC_Processor_ResetSystemReplyMessage);
    repply.Header.NumOfBytes16 = sizeof(SC_Processor_ResetSystemReplyMessage);

    tmpStr.append(retByteArray(&repply.Header.FunctionCode, sizeof(repply)));

    return tmpStr;
}

QString ChemPro::setBaudrate(unsigned char FCode)
{

    SC_Processor_SetBaudRateRequestMessage get;

    get.Header.FunctionCode = FCode;
    get.Header.NumOfBytes = sizeof(SC_Processor_SetBaudRateRequestMessage);
    get.Header.NumOfBytes16 = sizeof(SC_Processor_SetBaudRateRequestMessage);

    get.BaudRate = 3;
    get.Reserved = 0;
    //header.CRC16 = CRC16(&header.FunctionCode,header.NumOfBytes16);

    QString tmpStr = 0;

    tmpStr.append(retByteArray(&get.Header.FunctionCode,sizeof(get)));
    tmpStr.append('\n');

    //Reply msg
    SC_Processor_SetBaudRateReplyMessage repply;

    repply.Header = get.Header;

    repply.Header.NumOfBytes = sizeof(SC_Processor_SetBaudRateReplyMessage);
    repply.Header.NumOfBytes16 = sizeof(SC_Processor_SetBaudRateReplyMessage);

    tmpStr.append(retByteArray(&repply.Header.FunctionCode, sizeof(repply)));


    return tmpStr;
}

QString ChemPro::getV3Meas(unsigned char FCode)
{

    SC_Sensor_GetV3MeasRequestMessage get;

    get.Header.FunctionCode = FCode;
    get.Header.NumOfBytes = sizeof(SC_Sensor_GetV3MeasRequestMessage);
    get.Header.NumOfBytes16 = sizeof(SC_Sensor_GetV3MeasRequestMessage);


    //header.CRC16 = CRC16(&header.FunctionCode,header.NumOfBytes16);

    QString tmpStr = 0;

    tmpStr.append(retByteArray(&get.Header.FunctionCode,sizeof(get)));
    tmpStr.append('\n');

    //Reply msg
    SC_Sensor_GetV3MeasReplyMessage repply;

    repply.Header = get.Header;

    repply.Header.NumOfBytes = sizeof(SC_Sensor_GetV3MeasReplyMessage);
    repply.Header.NumOfBytes16 = sizeof(SC_Sensor_GetV3MeasReplyMessage);


    tmpStr.append(retByteArray(&repply.Header.FunctionCode, sizeof(repply)));


    return tmpStr;
}

QString ChemPro::getAges(unsigned char FCode)
{

    SC_Processor_GetAgesRequestMessage get;

    get.Header.FunctionCode = FCode;
    get.Header.NumOfBytes = sizeof(SC_Processor_GetAgesRequestMessage);
    get.Header.NumOfBytes16 = sizeof(SC_Processor_GetAgesRequestMessage);


    //header.CRC16 = CRC16(&header.FunctionCode,header.NumOfBytes16);

    QString tmpStr = 0;

    tmpStr.append(retByteArray(&get.Header.FunctionCode,sizeof(get)));
    tmpStr.append('\n');

    //Reply msg
    SC_Processor_GetAgesReplyMessage100i repply;

    repply.Header = get.Header;

    repply.Header.NumOfBytes = sizeof(SC_Processor_GetAgesReplyMessage100i);
    repply.Header.NumOfBytes16 = sizeof(SC_Processor_GetAgesReplyMessage100i);

    tmpStr.append(retByteArray(&repply.Header.FunctionCode, sizeof(repply)));


    return tmpStr;
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

QString retByteArray(unsigned char *Data, unsigned long DataLen)
{
    QByteArray bArray;
    QString array;
    char index;

    while(DataLen--)
    {
        index = *Data++;
        bArray.append(index);
    }

    return bArray.toHex(' ');
}

