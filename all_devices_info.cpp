#include "all_devices_info.h"

///////////////////////////////////// КОНСТРУКТОРЫ, ОПЕРАТОР = НАЧАЛО /////////////////////////////////////////////////////////



All_Devices_Info::All_Devices_Info(QObject *parent) : QObject(parent)
{

///////////////////////////////////// ОЧИСТКА ОБЩИХ ФЛАГОВ НАЧАЛО /////////////////////////////////////////////////////////


    clear_all_danger_flags(); // Начальное состояние флагов угроз - радиационной, биологической, химической угрозы нет    
    clear_all_proc_flags();   // Начальное состояние флагов готовности инфы и движения машины - false

///////////////////////////////////// ОЧИСТКА ОБЩИХ ФЛАГОВ ОКОНЧАНИЕ /////////////////////////////////////////////////////



///////////////////////////////////// СВНГ-Т НАЧАЛО /////////////////////////////////////////////////////////

    set_svng_angle(0.0);      // начальное состояние угла радиационной угрозы - 0 градусов
    svng_clear_all();   // записываем начальные значения в массивы СВНГ-Т


///////////////////////////////////// СВНГ-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////



}

All_Devices_Info::All_Devices_Info(const All_Devices_Info &obj) // Конструктор копирования
{
    // Выполняем копирование значений
    this->radiationDanger = obj.radiationDanger;
    this->biologyDanger   = obj.biologyDanger;
    this->chemistryDanger = obj.chemistryDanger;

    this->svng_angle   = obj.svng_angle;

    this->errOpenSvngComPort   = obj.errOpenSvngComPort;
    this->errSaveSvngComPort   = obj.errSaveSvngComPort;
    this->errCRCSvngComPort    = obj.errCRCSvngComPort;
    this->errSizePackSvng      = obj.errSizePackSvng;
    this->errNotAnswerSvng     = obj.errNotAnswerSvng;
    this->errGeneralSvng       = obj.errGeneralSvng;

    for(int i = 0; i < 4; ++i) {
        this->svng_value_arr[i] = obj.svng_value_arr[i];
        this->svng_chance_data[i] = obj.svng_chance_data[i];
        this->svng_high_sens_arr[i] = obj.svng_high_sens_arr[i];
        this->svng_low_sens_arr[i] = obj.svng_low_sens_arr[i];
        this->svng_loss_connect_arr[i] = obj.svng_loss_connect_arr[i];
    }

    // Добавлять новые поля ???????????????????????????????????????????????????????????????????

}

All_Devices_Info& All_Devices_Info::operator=(const All_Devices_Info &obj) // Переопределяем оператор присваивания
{
    // Проверка на самоприсваивание
    if (this == &obj)
        return *this;

    // Выполняем копирование значений
    this->radiationDanger = obj.radiationDanger;
    this->biologyDanger   = obj.biologyDanger;
    this->chemistryDanger = obj.chemistryDanger;

    this->svng_angle   = obj.svng_angle;

    this->errOpenSvngComPort   = obj.errOpenSvngComPort;
    this->errSaveSvngComPort   = obj.errSaveSvngComPort;
    this->errCRCSvngComPort    = obj.errCRCSvngComPort;
    this->errSizePackSvng      = obj.errSizePackSvng;
    this->errNotAnswerSvng     = obj.errNotAnswerSvng;
    this->errGeneralSvng       = obj.errGeneralSvng;

    for(int i = 0; i < 4; ++i) {
        this->svng_value_arr[i] = obj.svng_value_arr[i];
        this->svng_chance_data[i] = obj.svng_chance_data[i];
        this->svng_high_sens_arr[i] = obj.svng_high_sens_arr[i];
        this->svng_low_sens_arr[i] = obj.svng_low_sens_arr[i];
        this->svng_loss_connect_arr[i] = obj.svng_loss_connect_arr[i];
    }

    // Добавлять новые поля ???????????????????????????????????????????????????????????????????

    // Возвращаем текущий объект
    return *this;
}


///////////////////////////////////// КОНСТРУКТОРЫ, ОПЕРАТОР = ОКОНЧАНИЕ /////////////////////////////////////////////////////////








///////////////////////////////////// Ф-ЦИИ ФЛАГОВ ОБРАБОТКИ ДАННЫХ НАЧАЛО //////////////////////////////////////////


void All_Devices_Info::clear_all_proc_flags()
{
    need_record_data = false;
    car_movement = false;
}

void All_Devices_Info::set_need_record_data(bool value)
{
    need_record_data = value;
}

bool All_Devices_Info::get_need_record_data()
{
    return need_record_data;
}

void All_Devices_Info::set_car_movement(bool value)
{
    car_movement = value;
}

bool All_Devices_Info::get_car_movement()
{
    return car_movement;
}


///////////////////////////////////// Ф-ЦИИ ФЛАГОВ ОБРАБОТКИ ДАННЫХ ОКОНЧАНИЕ //////////////////////////////////////////



///////////////////////////////////// Ф-ЦИИ ФЛАГОВ УГРОЗ НАЧАЛО /////////////////////////////////////////////////////////


void All_Devices_Info::set_radiation_danger_flag(bool value)
{
    radiationDanger = value;
}

bool All_Devices_Info::get_radiation_danger_flag()
{
    return radiationDanger;
}

void All_Devices_Info::set_biology_danger_flag(bool value)
{
    biologyDanger = value;
}

void All_Devices_Info::set_chemistry_danger_flag(bool value)
{
    chemistryDanger = value;
}

void All_Devices_Info::clear_all_danger_flags()
{
    radiationDanger = false;                 // Радиационная угроза  - нет
    biologyDanger   = false;                 // Биологическая угроза - нет
    chemistryDanger = false;                 // Химическая угроза    - нет
}

int All_Devices_Info::get_type_danger()
{
    /*
    *  Ф-ция выдает тип угрозы ( или угроз )
    * 0   - угрозы нет
    * 1   - Радиационная угроза
    * 2   - Биологическая угроза
    * 3   - Химическая угроза
    * 12  - Радиационная + Биологическая
    * 13  - Радиационная + Химическая
    * 23  - Биологическая + Химическая
    * 123 - Радиационная + Биологическая + Химическая
    */

    if(!radiationDanger && !biologyDanger && !chemistryDanger) {
        return 0;
    }

    else if(radiationDanger && !biologyDanger && !chemistryDanger) {
        return 1;
    }

    else if(!radiationDanger && biologyDanger && !chemistryDanger) {
        return 2;
    }

    else if(!radiationDanger && !biologyDanger && chemistryDanger) {
        return 3;
    }


    else if(radiationDanger && biologyDanger && !chemistryDanger) {
        return 12;
    }


    else if(radiationDanger && !biologyDanger && chemistryDanger) {
        return 13;
    }


    else if(!radiationDanger && biologyDanger && chemistryDanger) {
        return 23;
    }

    else if(radiationDanger && biologyDanger && chemistryDanger) {
        return 123;
    }

    return 0;

}



///////////////////////////////////// Ф-ЦИИ ФЛАГОВ УГРОЗ ОКОНЧАНИЕ /////////////////////////////////////////////////////////




///////////////////////////////////// Ф-ЦИИ СВНГ-Т НАЧАЛО /////////////////////////////////////////////////////////


void All_Devices_Info::svng_clear_all()  // Записываем начальные значения массивов СВНГ-Т
{

    svng_angle = 0;

    for(int i = 0; i < 4; ++i) {
        svng_value_arr[i]        = 0.0;            // Нач. значение ПЕД  - 0.0
        svng_high_sens_arr[i]    = false;          // Нач. значение неисправностей высокочувствительных датчиков - false
        svng_low_sens_arr[i]     = false;          // Нач. значение неисправностей низкочувствительных датчиков - false
        svng_chance_data[i]      = 0;              // Нач. значение стат. ошибки = 0
        svng_loss_connect_arr[i] = false;          // Нач. значение связей с датчиками - false
    }

    errOpenSvngComPort = false;                    // Нач. сброс всех флагов ошибок СВНГ-Т
    errSaveSvngComPort = false;
    errCRCSvngComPort  = false;
    errSizePackSvng    = false;
    errNotAnswerSvng   = false;

    errGeneralSvng     = false;
}

void All_Devices_Info::set_svng_value_arr(float value, int posit)  // Записываем значение датчика № posit
{
    if(posit > 3) return;
    svng_value_arr[posit] = value;
}

float All_Devices_Info::get_svng_value_arr(int posit)          // Получаем значение датчика № posit
{
    if(posit > 3) return 0.0;
    return svng_value_arr[posit];
}

void All_Devices_Info::set_svng_chance_data_arr(int value, int posit)
{
    if(posit > 3) return;
    svng_chance_data[posit] = value;
}

int All_Devices_Info::get_svng_chance_data_arr(int posit)
{
    if(posit > 3) return 0.0;
    return svng_chance_data[posit];
}

void All_Devices_Info::set_svng_high_sens_arr(bool value, int posit)  // Записываем значение исправности высокоч. датчика № posit
{
    if(posit > 3) return;
    svng_high_sens_arr[posit] = value;
}

bool All_Devices_Info::get_svng_high_sens_arr(int posit)    // Получаем значение исправности высокоч. датчика № posit
{
    if(posit > 3) return true;
    return svng_high_sens_arr[posit];
}

void All_Devices_Info::set_svng_low_sens_arr(bool value, int posit)   // Записываем значение исправности низкочув. датчика № posit
{
    if(posit > 3) return;
    svng_low_sens_arr[posit] = value;
}

bool All_Devices_Info::get_svng_low_sens_arr(int posit)      // Получаем значение исправности низкочув. датчика № posit
{
    if(posit > 3) return true;
    return svng_low_sens_arr[posit];
}

void All_Devices_Info::set_svng_loss_connect_arr(bool value, int posit)    // Записываем значение связи с датчиком № posit
{
    if(posit > 3) return;
    svng_loss_connect_arr[posit] = value;
}

bool All_Devices_Info::get_svng_loss_connect_arr(int posit)               // Получаем значение связи с датчиком № posit
{
    if(posit > 3) return true;
    return svng_loss_connect_arr[posit];
}

void All_Devices_Info::set_svng_angle(int value)
{
    svng_angle = value;
}

int All_Devices_Info::get_svng_angle()
{
    return svng_angle;
}



void All_Devices_Info::set_err_open_svng_comport(bool value)     // Записываем значение флага ошибки открытия СОМ-порта
{
    errOpenSvngComPort = value;
}

bool All_Devices_Info::get_err_open_svng_comport()               // Получаем значение флага  ошибки открытия СОМ-порта
{
    return errOpenSvngComPort;
}

void All_Devices_Info::set_err_save_svng_comport(bool value)      // Записываем значение флага  ошибки записи в СОМ-порт
{
    errSaveSvngComPort = value;
}

bool All_Devices_Info::get_err_save_svng_comport()               // Получаем значение флага  ошибки записи в СОМ-порт
{
    return errSaveSvngComPort;
}

void All_Devices_Info::set_err_crc_svng(bool value)              // Записываем значение флага ошибки CRC принятого пакета
{
    errCRCSvngComPort = value;
}

bool All_Devices_Info::get_err_crc_svng()                        // Получаем значение флага  ошибки CRC принятого пакета
{
    return errCRCSvngComPort;
}

void All_Devices_Info::set_err_size_pack_svng(bool value)        // Записываем значение флага  ошибки размера принятого пакета
{
    errSizePackSvng = value;
}

bool All_Devices_Info::get_err_size_pack_svng()                 // Получаем значение флага  ошибки размера принятого пакета
{
    return errSizePackSvng;
}

void All_Devices_Info::set_err_not_answ_svng(bool value)          // Записываем значение флага  неответа прибора
{
    errNotAnswerSvng = value;
}

bool All_Devices_Info::get_err_not_answ_svng()                    // Получаем значение флага  неответа прибора
{
    return errNotAnswerSvng;
}

void All_Devices_Info::set_err_general_svng(bool value)
{
    errGeneralSvng = value;
}

bool All_Devices_Info::get_err_general_svng()
{
    return errGeneralSvng;
}


///////////////////////////////////// Ф-ЦИИ СВНГ-Т ОКОНЧАНИЕ /////////////////////////////////////////////////////

































