#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QAbstractItemView>
#include <ctime>
/*!
 * Another prime example of the "Hey man if it works approach" to software engineering
 * This constructor does so much because i would've had to reimplement way to many functions if i had promoted ui objects to their own types
 * Mostly initializes Ui related attributes
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {

    difKeyList = new QStringList();
    ui->setupUi(this);
    filepaths = new QStringListModel(actualList);
    difKeyModel = new QStringListModel(*difKeyList);
    ui->listView->setModel(filepaths);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->compareView->setModel(difKeyModel);
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

    difKeyList = new QStringList();
    lastSelection = new QStringList();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setImage(QString newimg) {
    delete internalImage;
    internalImage = new QImage(newimg);
    previewLabel->setPixmap(QPixmap::fromImage(*internalImage));
    compareLabel->setPixmap(QPixmap::fromImage(*internalImage));
}


void MainWindow::on_LoadSingleImage_clicked() {
    auto fileName = QFileDialog::getOpenFileNames(this, tr("Load Single Image"), tr("Image Files (*.png *.jpg *.bmp)"));
    actualList << fileName;
    filepaths->setStringList(actualList);
    for (const auto &i: fileName) {
        knownImages.insert(i, new ImToQuadTree<cv::Vec3b>(i.toStdString()));
    }
    setImage(fileName[0]);
}


void MainWindow::on_SaveSelectedFiles_clicked() {
    qDebug() << filepaths->rowCount();
}

void MainWindow::on_listView_clicked(const QModelIndex &index) {
    this->setImage(index.data().toString());
    if (lastSelection->contains(index.data().toString())) {
        lastSelection->removeOne(index.data().toString());
    } else
        *lastSelection << index.data().toString();
}


void MainWindow::on_compareView_clicked(const QModelIndex &index) {
    this->setImage(index.data().toString());
    if (difKeyList->contains(index.data().toString())) {
        difKeyList->removeOne(index.data().toString());
    } else
        *difKeyList << index.data().toString();
    qDebug() << *difKeyList;
}


void MainWindow::on_removeSelected_clicked() {
    for(auto name : *lastSelection)
    {
    delete knownImages[name];
    knownImages.remove(name);
    filepaths->removeRow(filepaths->stringList().indexOf(name));
    }
}


void MainWindow::on_compareSelection_clicked() {
    qDebug()<<*difKeyList;

}


void MainWindow::on_createComparison_clicked()
{
    for(int i=0;i<lastSelection->size()-1;i++)
    {
        for(int j=i+1;j<lastSelection->size();j++)
        {
            auto hash = (*lastSelection)[i] +"|" + (*lastSelection)[j];
            auto first = knownImages[(*lastSelection)[i]];
            auto second = knownImages[(*lastSelection)[j]];
            clock_t time = clock();
            auto di = first->getDiff(second,0);
            time -=clock();
            qDebug()<<"Generating differences for "<<hash<<"took: " <<abs(float(time)/CLOCKS_PER_SEC);
            knownDiffs.insert(hash,first->getDiff(second,0));
            auto temp= knownDiffs[hash];
            first->showDifVect(temp);
        }
    }
    *difKeyList = knownDiffs.keys();
    qDebug()<<knownDiffs.keys();

    difKeyModel->setStringList(*difKeyList);
}

