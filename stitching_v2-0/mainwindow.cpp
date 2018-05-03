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

void MainWindow::on_imageStitchingBtn_clicked()
{
    imageStitching *i=new imageStitching();
    i->show();
}

void MainWindow::on_videoStitchingBtn_clicked()
{
    videoStitching *v=new videoStitching();
    v->show();
}
