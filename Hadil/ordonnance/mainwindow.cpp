#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ordonance.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ordonance A;
    A.setModal(true);
    A.exec();
}
