#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QAbstractItemView>
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    filepaths = new QStringListModel(actualList);
    ui->listView->setModel(filepaths);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->compareView->setModel(filepaths);
    ui->compareView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->compareView->setSelectionMode(QAbstractItemView::MultiSelection);


    filepaths->setStringList(actualList);
    internalImage = new QImage("starry_night.jpg");
    previewLabel = new QLabel(this);
    previewLabel->setPixmap(QPixmap::fromImage(*internalImage));


    compareLabel = new QLabel(this);
    compareLabel->setPixmap(QPixmap::fromImage(*internalImage));
    ui->comparePane->setWidget(compareLabel);
    ui->imagePane->setWidget(previewLabel);

    toCompare = new QStringList();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setImage(QString newimg)
{

    delete internalImage;
    internalImage = new QImage(newimg);
    previewLabel->setPixmap(QPixmap::fromImage(*internalImage));
    compareLabel->setPixmap(QPixmap::fromImage(*internalImage));
}


void MainWindow::on_LoadSingleImage_clicked() {
    auto fileName = QFileDialog::getOpenFileNames(this, tr("Load Single Image"), tr("Image Files (*.png *.jpg *.bmp)"));
    actualList<<fileName;
    filepaths->setStringList(actualList);
}


void MainWindow::on_SaveSelectedFiles_clicked() {
    qDebug()<< filepaths->rowCount();
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    this->setImage(index.data().toString());
    lastSelection=index;
}


void MainWindow::on_compareView_clicked(const QModelIndex &index)
{
    this->setImage(index.data().toString());
    if(toCompare->contains(index.data().toString()))
    {
        toCompare->removeOne(index.data().toString());
    }
    else
        *toCompare<<index.data().toString();
    qDebug()<<*toCompare;

}


void MainWindow::on_removeSelected_clicked()
{
    filepaths->removeRow(lastSelection.row());
}

