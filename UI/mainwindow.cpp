#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
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



void MainWindow::on_LoadSingleImage_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Load Single Image"), tr("Image Files (*.png *.jpg *.bmp)"));
}

