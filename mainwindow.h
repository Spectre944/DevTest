#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>

#include <QThread>


#include "devices.h"





#include "chempro.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    bool autoReqMode;

    void showAngleSvng(int);

    QString calculatePrefix(float);



public slots:

    void receiveDataObject(All_Devices_Info *);



private slots:

    void on_comboBoxFontSize_currentIndexChanged(int index);

    void on_checkBoxManualMode_stateChanged(int arg1);

private:

    Ui::MainWindow *ui;


    /*
    * Указатель на объект для работы с девайсами
    */
    Devices *devices;

    /*
    * Поток для объекта работы с девайсами
    */
    QThread *devicesThread;


    /*
    *  Функция старта потока СОМ-порта
    */
    bool startDevicesThread();



signals:

    void send_req_command();

    void setMinPed(float);


};
#endif // MAINWINDOW_H
