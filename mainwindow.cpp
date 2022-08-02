#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}

MainWindow::~MainWindow()
{
    delete ui;
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

