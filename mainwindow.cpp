#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    


////////////////////////////////////////////////// НИКИТА /////////////////////////////////////////////////////////////


    ui->stackedWidget->setStyleSheet("font-size: 16px;");
    ui->topBarFrame->setStyleSheet("font-size: 12px;");
    ui->bottomFrame->setStyleSheet("font-size: 12px;");

    QFile file("://styles/styleSheetDarkBlue.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    ui->centralwidget->setStyleSheet(styleSheet);

    //скрываем статус бар внизу
    statusBar()->hide();


    QButtonGroup* menuGroup = new QButtonGroup(ui->centralwidget);

    menuGroup->addButton(ui->pushButtonDevices);
    menuGroup->addButton(ui->pushButtonSV);
    menuGroup->addButton(ui->pushButtonSR);
    menuGroup->addButton(ui->pushButtonAirMar);
    menuGroup->addButton(ui->pushButtonChemPro);
    menuGroup->addButton(ui->pushButtonSettings);


    connect(ui->pushButtonDevices, &QPushButton::clicked, this, [=]() {
        //set page ALL
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->pushButtonSV, &QPushButton::clicked, this, [=]() {
        //set page SVNG-T
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->pushButtonSR, &QPushButton::clicked, this, [=]() {
        //set page SRXBR-T
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->pushButtonAirMar, &QPushButton::clicked, this, [=]() {
        //set page AirMar
        ui->stackedWidget->setCurrentIndex(4);
    });

    connect(ui->pushButtonChemPro, &QPushButton::clicked, this, [=]() {
        //set page ChemPro
        ui->stackedWidget->setCurrentIndex(3);
    });

    connect(ui->pushButtonSettings, &QPushButton::clicked, this, [=]() {
        //set page settings
        ui->stackedWidget->setCurrentIndex(5);
    });


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    autoReqMode = false; // false - ручной режим

    startDevicesThread();





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAngleSvng(int value)
{
    //correct to 0 was on north
        const short correctAngle = -90;

    //width of arc
    int spanAngle = 46;

    //load image and size of image
    QPixmap pixmap(":/images/car.png");
    QPainter painter(&pixmap);
    QRect rectangle = pixmap.rect();  //if drawPie
    QPainterPath path;

    const short center = pixmap.width()/2;
    const short radius = pixmap.width()/3;


    //font of RADIATION symbol
    QFont font;
    font.setPixelSize(pixmap.width()/3.5);
    painter.setFont(font);

    //direction of ray with correcting angle (spanAngle/2 - makes ray centered)
    int startAngle = (value + correctAngle - spanAngle/2);


    //move to center of image
    path.moveTo(center, center);
    //draw arc
    path.arcTo(rectangle, startAngle, spanAngle);
    //arc color
    //painter.fillPath(path,QColorConstants::Svg::orange);
    painter.fillPath(path,Qt::yellow);

    //draw text over arc with position depending on angle
    int x = cos((value + correctAngle) *M_PI/180) * radius;
    int y = sin((value + correctAngle)*M_PI/180) * radius;

    //show symbol
    QRect textPos( x, -y, pixmap.width(), pixmap.height());
    painter.drawText(textPos, Qt::AlignCenter, tr("☢"));

    //refresh data
    ui->labelCarEmitDirection->setPixmap(pixmap);
    ui->labelCarEmitDirectionValue->setText("Кут опром.\n" + QString::number(value) + " °");
}

QString MainWindow::calculatePrefix(float der)
{
    QString tmp;

    if(der < 1000.0)
        tmp = QString::number(der,'g',3)+ " мкЗв/г";
    if(der >= 1000.0 && der < 1000000) {
        der/=1000.0f;
        tmp = QString::number(der,'g',3)+ " мЗв/г";
    }
    if(der > 1000000.0){
        der/=1000000.0f;
        tmp = QString::number(der,'g',3) + " Зв/г";
    }

    return tmp;
}

void MainWindow::on_comboBoxFontSize_currentIndexChanged(int index)
{
switch (index) {
    case 0:
    {       ui->stackedWidget->setStyleSheet("font-size: 12px;");
            ui->topBarFrame->setStyleSheet("font-size: 12px;");
            ui->bottomFrame->setStyleSheet("font-size: 12px;");
            break;
    }
    case 1:
    {       ui->stackedWidget->setStyleSheet("font-size: 16px;");
            ui->topBarFrame->setStyleSheet("font-size: 12px;");
            ui->bottomFrame->setStyleSheet("font-size: 12px;");
            break;
    }
    case 2:
    {       ui->stackedWidget->setStyleSheet("font-size: 24px;");
            ui->topBarFrame->setStyleSheet("font-size: 12px;");
            ui->bottomFrame->setStyleSheet("font-size: 12px;");
            break;
    }
    case 3:
    {       ui->stackedWidget->setStyleSheet("font-size: 30px;");
            ui->topBarFrame->setStyleSheet("font-size: 12px;");
            ui->bottomFrame->setStyleSheet("font-size: 12px;");
            break;
    }
    default: break;
}
}

bool MainWindow::startDevicesThread()   // Ф-ция старта потока для работы с девайсами
{
    devices = new Devices();
    devicesThread = new QThread();   // Cоздали объект и поток для объекта работы с девайсами

    devices->moveToThread(devicesThread);  // Переместили  объект в поток

    /*
    * Коннект старта потока девайсов  и стартовой ф-ции &Devices - создание СОМ-портов, таймеров и коннектов
    */
    connect(devicesThread, &QThread::started, devices, &Devices::startDeviceThread);

    /*
    * Коннект финиша потока девайсов и удаления объекта потока
    */
    connect(devicesThread, &QThread::finished, devicesThread, &QObject::deleteLater);

    /*
    * Коннект финиша потока девайсов и удаления объекта работы с девайсами
    */
    connect(devicesThread, &QThread::finished, devices, &QObject::deleteLater);

    /*
    * Коннект слота передачи указателя на объект данных из Devices в MainWindow
    */
    connect(devices, &Devices::transmitDataObject, this, &MainWindow::receiveDataObject); // //   send_req_command      exec_req_command

    /*
    * Коннект слота старта опроса девайсов  из MainWindow в Devices
    */
    connect(this, &MainWindow::send_req_command, devices, &Devices::exec_req_command);


    /*
    * Коннект установки мин. значения ПЕД
    */
    connect(this, &MainWindow::setMinPed, devices, &Devices::setMinPed);

    /*
    * Запускаем поток и возвращаем активность потока
    */
    devicesThread->start();
    return devicesThread->isRunning();
}



void MainWindow::receiveDataObject(All_Devices_Info *dataObj)  // Слот приема и обработки объекта данных девайсов
{
    /*
    * Создаем копию информационного объекта
    * Проверяем, или есть исправные приборы:
    *     Если есть:
    *         - очищаем копию
    *         - если авторежим, отправляем команду на следующий запрос
    *         - если ручной режим , не отправляем команду  get_err_general_svng
    *
    */

    All_Devices_Info copyDataObj(dataObj);




//////////////////////////////////////// ОЧИСТКА ПОЛЕЙ ВСЕХ ПРИБОРОВ НАЧАЛО //////////////////////////////////////////////////////////////

    bool svng    = false;
//         srhr    = false,
//         airmar  = false,
//         chempro = false;

    if(!dataObj->get_err_general_svng())  {
        svng = true;
        dataObj->svng_clear_all();   // СВНГ-Т исправен, очищаем его поля

    }

    // Добавлять очистку девайсов ??????????????????????????????????????????????????????????????????????????????????????
  // clear_all_danger_flags(), clear_all_proc_flags();


    // Продумать проверку при очистке общих флагов
    dataObj->clear_all_danger_flags();
    dataObj->clear_all_proc_flags();

//////////////////////////////////////// ОЧИСТКА ПОЛЕЙ ВСЕХ ПРИБОРОВ ОКОНЧАНИЕ//////////////////////////////////////////////////////////////




//////////////////////////////// ПРОВЕРЯЕМ ИСПРАВНОСТЬ ВСЕХ ПРИБОРОВ НАЧАЛО/////////////////////////////////////////////////////////////////

    if(!svng   ) {
        // Если все приборы неисправны, регистрируем это и выходим
    }

//////////////////////////////// ПРОВЕРЯЕМ ИСПРАВНОСТЬ ВСЕХ ПРИБОРОВ ОКОНЧАНИЕ //////////////////////////////////////////////////////////////




//////////////////////////////// ОТПРАВЛЯЕМ КОМАНДУ НА ОПРОС(АВТОРЕЖИМ)  НАЧАЛО/////////////////////////////////////////////////////////////////

    if(autoReqMode  ) {
        // Если авторежим, отправляем запрос

        emit send_req_command();
    }

//////////////////////////////// ОТПРАВЛЯЕМ КОМАНДУ НА ОПРОС(АВТОРЕЖИМ) ОКОНЧАНИЕ //////////////////////////////////////////////////////////////



//////////////////////////////// ОБРАБАТЫВАЕМ КОПИЮ ИНФОРМ. ОБЪЕКТА ДЛЯ GUI НАЧАЛО/////////////////////////////////////////////////////////////////

    float ped;
    int stat;
    bool high_sens,
         low_sens,
         loss_connect;
    QString res;

    if(copyDataObj.get_radiation_danger_flag())  {
        int angle = copyDataObj.get_svng_angle();
        showAngleSvng(angle);                       // Вывели угол (при наличии угрозы)
    }

// 1. Передний датчик

    ped = copyDataObj.get_svng_value_arr(0);
    stat = copyDataObj.get_svng_chance_data_arr(0);
    high_sens = copyDataObj.get_svng_high_sens_arr(0);
    low_sens = copyDataObj.get_svng_low_sens_arr(0);
    loss_connect = copyDataObj.get_svng_loss_connect_arr(0);

    res.clear();
    res = "Пер. БД\n" + calculatePrefix(ped) + "\n";
    res += "Cтат. пох " + QString::number(stat) + "\n";
    if(!high_sens){
        res += "Вис.чут. - справний\n ";
    }
    else {
        res += "Вис.чут. - несправний\n ";
    }

    if(!low_sens){
        res += "Низ.чут. - справний\n ";
    }
    else {
        res += "Низ.чут. - несправний\n ";
    }

    if(!loss_connect){
        res += "Зв'язок є\n ";
    }
    else {
        res += "Зв'язку немає\n ";
    }
    ui->labelSVFrontDER->setText(res);

// 2. Задний датчик

    ped = copyDataObj.get_svng_value_arr(1);
    stat = copyDataObj.get_svng_chance_data_arr(1);
    high_sens = copyDataObj.get_svng_high_sens_arr(1);
    low_sens = copyDataObj.get_svng_low_sens_arr(1);
    loss_connect = copyDataObj.get_svng_loss_connect_arr(1);

    res.clear();
    res = "Пер. БД\n" + calculatePrefix(ped) + "\n";
    res += "Cтат. пох " + QString::number(stat) + "\n";
    if(!high_sens){
        res += "Вис.чут. - справний\n ";
    }
    else {
        res += "Вис.чут. - несправний\n ";
    }

    if(!low_sens){
        res += "Низ.чут. - справний\n ";
    }
    else {
        res += "Низ.чут. - несправний\n ";
    }

    if(!loss_connect){
        res += "Зв'язок є\n ";
    }
    else {
        res += "Зв'язку немає\n ";
    }
    ui->labelSVBackDER->setText(res);

// 3. Левый датчик

    ped = copyDataObj.get_svng_value_arr(2);
    stat = copyDataObj.get_svng_chance_data_arr(2);
    high_sens = copyDataObj.get_svng_high_sens_arr(2);
    low_sens = copyDataObj.get_svng_low_sens_arr(2);
    loss_connect = copyDataObj.get_svng_loss_connect_arr(2);

    res.clear();
    res = "Пер. БД\n" + calculatePrefix(ped) + "\n";
    res += "Cтат. пох " + QString::number(stat) + "\n";
    if(!high_sens){
        res += "Вис.чут. - справний\n ";
    }
    else {
        res += "Вис.чут. - несправний\n ";
    }

    if(!low_sens){
        res += "Низ.чут. - справний\n ";
    }
    else {
        res += "Низ.чут. - несправний\n ";
    }

    if(!loss_connect){
        res += "Зв'язок є\n ";
    }
    else {
        res += "Зв'язку немає\n ";
    }
    ui->labelSVLeftDER->setText(res);


// 4. Правый датчик

    ped = copyDataObj.get_svng_value_arr(3);
    stat = copyDataObj.get_svng_chance_data_arr(3);
    high_sens = copyDataObj.get_svng_high_sens_arr(3);
    low_sens = copyDataObj.get_svng_low_sens_arr(3);
    loss_connect = copyDataObj.get_svng_loss_connect_arr(3);

    res.clear();
    res = "Пер. БД\n" + calculatePrefix(ped) + "\n";
    res += "Cтат. пох " + QString::number(stat) + "\n";
    if(!high_sens){
        res += "Вис.чут. - справний\n ";
    }
    else {
        res += "Вис.чут. - несправний\n ";
    }

    if(!low_sens){
        res += "Низ.чут. - справний\n ";
    }
    else {
        res += "Низ.чут. - несправний\n ";
    }

    if(!loss_connect){
        res += "Зв'язок є\n ";
    }
    else {
        res += "Зв'язку немає\n ";
    }
    ui->labelSVRightDER->setText(res);



//////////////////////////////// ОБРАБАТЫВАЕМ КОПИЮ ИНФОРМ. ОБЪЕКТА ДЛЯ GUI ОКОНЧАНИЕ //////////////////////////////////////////////////////////////


}
























void MainWindow::on_checkBoxManualMode_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)  {   // Авторежим опроса
        autoReqMode = true;
        emit send_req_command();
    }

    else if(arg1 == Qt::Unchecked)    // Ручной режим опроса
         autoReqMode = false;

    else
        return;
}

