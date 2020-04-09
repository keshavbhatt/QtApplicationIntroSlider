#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_clicked()
{
    if(slider==nullptr){
        slider = new Slider(this);
        slider->setWindowTitle(QApplication::applicationName()+" | Introduction");
        slider->setWindowFlag(Qt::Dialog);
        slider->setWindowModality(Qt::ApplicationModal);
        slider->setMinimumSize(680,420);
    }
    if(slider->isVisible()==false){
       slider->showNormal();
       slider->start();
    }
}
