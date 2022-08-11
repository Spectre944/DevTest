#include "devices.h"

Devices::Devices(QObject *parent) : QObject(parent)
{


    errorSVNG     = 0;             // Сбросили счетчик ошибок СВНГ-Т

                  // Для пошагового тестирования
    errorSRHR     = 3;             // Сбросили счетчик ошибок СРХР-Т    - 3 - для теста
    errorAIRMAR   = 3;             // Сбросили счетчик ошибок AirMar    - 3 - для теста
    errorCHEMPRO  = 3;             // Сбросили счетчик ошибок ChemPro   - 3 - для теста

    minPed = MIN_PED;

    saveDeviceRequest();   // Формируем (одноразово) QByteArray массивы запросов к девайсам

}




void Devices::startDeviceThread()
{
    /*
    * Слот сработает по сигналу запуска потока оъекта для работы с девайсами
    */


    devErrorTimer =  new QTimer(this);       // Таймер обработки ошибок и неответа прибора
    devErrorTimer->stop();
    connect(devErrorTimer , &QTimer::timeout, this, &Devices::procDevErrorTimer);

    processTimer =  new QTimer(this);        // Таймер периодического опроса девайсов
    processTimer->stop();
    connect(processTimer , &QTimer::timeout, this, &Devices::procProcessTimer);

    devInfo = new All_Devices_Info(this);     // Информационный объект (все данные о приборах )



///////////////////////////////////// СВНГ-Т НАЧАЛО /////////////////////////////////////////////////////////

    svng_port = new QSerialPort(this);        // СОМ-порт для опроса СВНГ-Т
    openSvngSerialPort(SVNG_PORT);            // После создания указателя на СОМ-порт сразу открываем его
    connect(svng_port, &QSerialPort::readyRead, this, &Devices::readSvngData);

///////////////////////////////////// СВНГ-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////





///////////////////////////////////// АВТОЗАПУСК ОПРОСА НАЧАЛО ////////////////////////////////////////////////////

//    typeDev = SVNG_T;                           // Тип опрашиваемого прибора ( начинаем с СВНГ-Т )

//    processTimer->start(2 * PROCESS_TIME);        // Сразу запускаем опрос девайсов (авторежим - по умолчанию )

///////////////////////////////////// АВТОЗАПУСК ОПРОСА ОКОНЧАНИЕ ////////////////////////////////////////////////////

}



void Devices::saveDeviceRequest()
{
   int i;

//////////////////////////// СВНГ НАЧАЛО ///////////////////////////////////////////////////////

    const unsigned char start_dev[6] = {0x55, 0xAA, 0x01, 0x06, 0x11, 0x17};
    svng_data_request.clear();
    for(i = 0; i < 6; ++i) {
        svng_data_request.append(start_dev[i]);   // Массив запроса данных СВНГ-Т
    }

//////////////////////////// СВНГ ОКОНЧАНИЕ ///////////////////////////////////////////////////////


}


void Devices::setMinPed(float value)
{
    minPed = value;
}

float Devices::getMinPed()
{
    return minPed;
}





void Devices::procDevErrorTimer()
{
    devErrorTimer->stop();

    if(typeDev == SVNG_T) {   // Ошибки произошли в СВНГ-Т

        if(errorSVNG >= 3) {                               // Кол-во ошибок превысило допустимый уровень

            if(errorOpenSvngComPort)                       // Не открылся порт СВНГ-Т - вызов из writeSvngData(...)
                devInfo->set_err_open_svng_comport(true);            

            else if(errorSaveSvngComPort)                  // Записались не все данные - - вызов из writeSvngData(...)
                devInfo->set_err_save_svng_comport(true);            

            else if(errorCRCSvngComPort)                   // Ошибка CRC принятого пакета - вызов из readSvngData()
                devInfo->set_err_crc_svng(true);            

            else if(errorSizePackSvng)                     // Ошибка размера принятого пакета - вызов из readSvngData()
                devInfo->set_err_size_pack_svng(true);            

            else
                devInfo->set_err_not_answ_svng(true);     //  Девайс не ответил вообще

            devInfo->set_err_general_svng(true);          // Записали значение общего флага неисправности СВНГ-Т в информационном объекте


            if(errorSRHR < 3)  {                              // СРХР-Т исправен, переходим к его опросу
                typeDev = SRHR_T;                             // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
                // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
                processTimer->start(100);                     // Запустили таймер опроса девайсов
            }

            else if(errorCHEMPRO < 3)  {                       // СРХР-Т неисправен, переходим к опросу ChemPro
                typeDev = CHEM_PRO;                            // Изменили тип опрашиваемого девайса на следующий - ChemPro
                // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
                processTimer->start(100);                      // Запустили таймер опроса девайсов
            }

            else if(errorAIRMAR < 3)  { // СРХР-Т неисправен, ChemPro неисправен, переходим к опросу AirMar
                typeDev = AIR_MAR;                              // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
                 // Открыть СОМ-порт AirMar ????????????????????????????????????????????????????????????????????????????????????????
                processTimer->start(100);                       // Запустили таймер опроса девайсов
            }

            else {  // Все приборы неисправны, отправляем сигнал в GUI
                // Сигнал в GUI - отправляем неизмененный объект

                emit transmitDataObject(devInfo);
            }

            return;
        }

        if(errorOpenSvngComPort)                  //  Если порт СВНГ-Т не открыт, пробуем открыть еще раз
            openSvngSerialPort(SVNG_PORT);

        ++errorSVNG;                               // инкрементируем счетчик ошибок
        writeSvngData(copyData, WAIT_SAVE_TIME);   // Во всех случаях повторяем запрос к девайсу

        return;
    }














    else if(typeDev == SRHR_T) {
        /*
        * Ошибки произошли в СРХР-Т
        */


    }

    else if(typeDev == AIR_MAR) {
        /*
        * Ошибки произошли в AirMar
        */


    }

    else if(typeDev == CHEM_PRO) {
        /*
        * Ошибки произошли в СhemPro
        */


    }

    else return;

}

void Devices::procProcessTimer()
{
    processTimer->stop(); // Остановили таймер


    if( typeDev == SVNG_T) {

        writeSvngData(svng_data_request, WAIT_SAVE_TIME); // Если режим - СВНГ-Т и девайс "рабочий", отправляем запрос к СВНГ-Т
        return;
    }


    else if( typeDev == SRHR_T) {
        /*
        * Здесь выбираем вид запроса к СРХР-Т и отправляем
        * Дальнейший алгоритм реализуем в обработчиках
        */

    }

    else if( typeDev == CHEM_PRO) {

    }

    else if( typeDev == AIR_MAR) {

    }






}





void Devices::exec_req_command()              // Слот старта опроса девайсов - команда из GUI
{
    if(errorSVNG < 3)  {                      // СВНГ-Т исправен, переходим к опросу СВНГ-Т
            typeDev = SVNG_T;                 // Изменили тип опрашиваемого девайса на следующий - СВНГ-Т
            processTimer->start(100);         // Запустили таймер опроса девайсов
    }

    else if(errorSRHR < 3)  {                 // СВНГ-Т неисправен, СРХР-Т исправен, переходим к опросу СРХР-Т
        typeDev = SRHR_T;                     // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
        // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
        processTimer->start(100);             // Запустили таймер опроса девайсов
    }

    else if(errorCHEMPRO < 3)  {              // СВНГ-Т неисправен, СРХР-Т неисправен, переходим к опросу ChemPro
        typeDev = CHEM_PRO;                   // Изменили тип опрашиваемого девайса на следующий - ChemPro
        // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
        processTimer->start(100);             // Запустили таймер опроса девайсов
    }

    else if(errorAIRMAR < 3)  {                // СВНГ-Т неисправен, СРХР-Т неисправен, ChemPro неисправен, переходим к опросу AirMar
        typeDev = AIR_MAR;                     // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
        // Открыть СОМ-порт AirMar ????????????????????????????????????????????????????????????????????????????????????????
        processTimer->start(100);              // Запустили таймер опроса девайсов
    }

    else {  // Все приборы неисправны, отправляем сигнал в GUI
        // Сигнал в GUI - отправляем неизмененный объект

        emit transmitDataObject(devInfo);
    }

}





bool Devices::openSvngSerialPort(const QString &portName)
{
    if (svng_port->isOpen()) {
        svng_port->close();
    }
    svng_port->setPortName(portName);
    svng_port->setBaudRate(QSerialPort::Baud19200);
    svng_port->setDataBits(QSerialPort::Data8);
    svng_port->setParity(QSerialPort::Parity::NoParity);
    svng_port->setStopBits(QSerialPort::StopBits::OneStop);
    svng_port->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    return svng_port->open(QSerialPort::ReadWrite);
}

void Devices::closeSvngSerialPort()
{
    if(svng_port->isOpen())
        svng_port->close();
}

void Devices::writeSvngData(QByteArray data, int time)
{
    errorOpenSvngComPort = false;
    errorSaveSvngComPort = false;
    errorCRCSvngComPort  = false;
    errorSizePackSvng    = false;
    errorNotAnswerSvng   = false;    // Сбросили флаги ошибок неоткрытия порта, записи в порт, CRC, несоответствия размера и неответа прибора

    copyData.clear();
    copyData.append(data);                        // Очистили массив-копию и записали последние переданные данные

    if(svng_port->isOpen()) {                     // Если порт открыт
        int size = svng_port->write(data);
        svng_port->waitForBytesWritten(time);     // Записываем данные и ждем окончания записи

        if(size == data.size()) {
            devErrorTimer->start(NOANSWER_TIME);
            return;                               // Запись прошла корректно, запустили страховочный таймер
        }

        else {
            errorSaveSvngComPort = true;
            devErrorTimer->start(MIN_TIME);  // Запись прошла некорректно - ошибка - записались не все данные, запускаем
            return;                          // страховочный таймер еще раз(мин. интервал - 100 мсек) и пробуем опять опросить прибор
        }
    }

    else {
        errorOpenSvngComPort = true;         // Запись прошла некорректно - ошибка - порт СВНГ-Т почему-то не открыт,  запускаем
        devErrorTimer->start(MIN_TIME);    // страховочный таймер еще раз(мин. интервал - 100 мсек) и пробуем опять открыть порт СВНГ-Т и опросить прибор
        return;
    }
}



void Devices::readSvngData()
{
    devErrorTimer->stop();   // Останавливаем таймер ошибок - прибор ответил
    QByteArray receiveBuff;

    receiveBuff.append(svng_port->readAll());
    while(svng_port->waitForReadyRead(8))
        receiveBuff.append(svng_port->readAll()); // Прочитали всю информацию из СОМ-порта

    svng_port->clear();     // Очистили СОМ-порт

    bool ok;
    int i_ped;
    int i_var;
    float f_ped;
    float koeff = static_cast<float>(0.01);
    quint8 i_digit;

    unsigned char * point;
    point = (unsigned char *)&i_ped;

    if(receiveBuff.size() != 30) {

        /*
        *  Длина пакета СВНГ-Т   - 30 байт
        *  Проверить длину принятого пакета
        *     Если нет ( длина пакета не совпадает с указанной ) :
        *       - Повторить запрос к девайсу через таймер ошибок
        *       - Выйти
        *
        */
        errorSizePackSvng = true;
        devErrorTimer->start(NOANSWER_TIME);
        return;
    }



    /*
    * Проверить CRC
    *   - если CRC ОК: Передать массив receiveBuff в обработку
    *   - если CRC NO: Cделать еще запрос к девайсу
    */

    if(checkSvngCRC(receiveBuff, receiveBuff.size()))  { // CRC совпало, все ОК

        /*
        * Обработать массив receiveBuff
        * Проверить длину принятого пакета
        *    Если все норм :
        *       - Заполнить нужные поля  All_Devices_Info *devInfo;
        *       - Передать управление для дальнейшего опроса девайсов
        *
        */

        errorSVNG = 0;  // Счетчик ошибок сбрасываем только после корректного ответа девайса

        for(int i = 5, j = 0; i < 24; i += 6, ++j) {                    // Основной цикл обработки - 4 пакета

            *(point)     =  receiveBuff.at(i);
            *(point + 1) =  receiveBuff.at(i + 1);
            *(point + 2) =  receiveBuff.at(i + 2);
            *(point + 3) =  receiveBuff.at(i + 3);                      // Вытягиваем целочисленное значение ПЕД

            if(i_digit & 0x80)                                          //  Записали коэфф (0.1 или 0.01)
                koeff = static_cast<float>(0.1);

            f_ped = (static_cast<float>(i_ped)) * koeff;
            devInfo->set_svng_value_arr(f_ped, j);                       // Записали ПЕД на соответствующую позицию в массиве svng_value_arr

            i_var = receiveBuff.mid(i + 4).toHex().toInt(&ok, 16);
            devInfo->set_svng_chance_data_arr(i_var, j);                 // Записали стат.ошибку на соответствующую позицию в массиве svng_value_arr

            i_digit = receiveBuff.mid(i + 5).toHex().toUInt(&ok, 16);

            if(i_digit & 0x01)
                devInfo->set_svng_high_sens_arr(true, j);                //  Записали неисправность высокоч. датчика

            if(i_digit & 0x02)
                devInfo->set_svng_low_sens_arr(true, j);                 //  Записали неисправность низкочув. датчика

            if(i_digit & 0x10)
                devInfo->set_svng_loss_connect_arr(true, j);             //  Записали отсутствие связи с датчиком
        }

        // Здесь прописать полное заполнение данных СВНГ-Т  ???????????????????????????????????????????????????????????




        float sensor_front = devInfo->get_svng_value_arr(0),
              sensor_back  = devInfo->get_svng_value_arr(1),
              sensor_left  = devInfo->get_svng_value_arr(2),
              sensor_right = devInfo->get_svng_value_arr(3);

        if(sensor_front >= minPed || sensor_back >= minPed || sensor_left >= minPed || sensor_right >= minPed)
            devInfo->set_radiation_danger_flag(true); // При превышении мин. уровня на любом из датчиков
                                                      // поднимаем флаг радиационной угрозы


        if((sensor_front / sensor_back) > 2.0)  {
            if((sensor_right / sensor_left ) > 2.0)
                devInfo->set_svng_angle(315);
            else if((sensor_left / sensor_right ) > 2.0)
                devInfo->set_svng_angle(225);
            else
                devInfo->set_svng_angle(180);
        }
        else if((sensor_right / sensor_left) > 2.0) {
            if((sensor_front / sensor_back ) > 2.0)
                devInfo->set_svng_angle(315);
            else if((sensor_back / sensor_front ) > 2.0)
                devInfo->set_svng_angle(45);
            else
                devInfo->set_svng_angle(0);
        }
        else if((sensor_back / sensor_front) > 2.0) {
            if((sensor_right / sensor_left ) > 2.0)
                devInfo->set_svng_angle(45);
            else if((sensor_left / sensor_right ) > 2.0)
                devInfo->set_svng_angle(135);
            else
                devInfo->set_svng_angle(90);
        }
        else if((sensor_left / sensor_right) > 2.0) {
            if((sensor_front / sensor_back ) > 2.0)
                devInfo->set_svng_angle(225);

            else if((sensor_back / sensor_front ) > 2.0)
                devInfo->set_svng_angle(135);

            else
                devInfo->set_svng_angle(180);
        }


        // В тестовом режиме все счетчики == 3, поэтому сразу отправим сигнал в GUI

        if(errorSRHR < 3)  {                              // СРХР-Т исправен, переходим к его опросу
            typeDev = SRHR_T;                             // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
            // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
            processTimer->start(100);                     // Запустили таймер опроса девайсов
        }

        else if(errorCHEMPRO < 3)  {                       // СРХР-Т неисправен, переходим к опросу ChemPro
            typeDev = CHEM_PRO;                            // Изменили тип опрашиваемого девайса на следующий - ChemPro
            // Вставить параметр запроса ????????????????????????????????????????????????????????????????????????????????????????
            processTimer->start(100);                      // Запустили таймер опроса девайсов
        }

        else if(errorAIRMAR < 3)  { // СРХР-Т неисправен, ChemPro неисправен, переходим к опросу AirMar
            typeDev = AIR_MAR;                              // Изменили тип опрашиваемого девайса на следующий - СРХР-Т
             // Открыть СОМ-порт AirMar ????????????????????????????????????????????????????????????????????????????????????????
            processTimer->start(100);                       // Запустили таймер опроса девайсов
        }

        else {  // Все приборы неисправны, отправляем сигнал в GUI
            // Сигнал в GUI - отправляем неизмененный объект

            emit transmitDataObject(devInfo);
        }

        return;
    }

    else {   // CRC не совпало, все ERROR

        /*
        * Запускаем таймер ошибок для повторного запроса
        */
        errorCRCSvngComPort = true;
        devErrorTimer->start(NOANSWER_TIME);
        return;
    }


}

bool Devices::checkSvngCRC(QByteArray &buff, int size)  // ??????????????????????????????????????????
{
    unsigned char CRC = 0;
    quint16 CRC_16 = 0;

    if(!buff.size())
        return false;

    for(int i = 0; i <= size - 2; ++i) {
        CRC    +=  static_cast<unsigned char>(buff.at(i));
        CRC_16 +=  static_cast<unsigned char>(buff.at(i));

        if(CRC_16 > 255) {
            CRC += 1;
            CRC_16 = 0;
        }
    }

    return CRC == static_cast<unsigned char>(buff.at(size - 1));
}


























