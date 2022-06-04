#include "UI/mainwindow.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::string image_path = samples::findFile("starry_night.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    QString str;
    Mat hslImage;
    cvtColor(img,hslImage,COLOR_RGB2HLS);
    auto i = hslImage.at<Vec3b>(10,10);
    qDebug() <<"stringInutil:"<< i[0]<<i[1]<<i[2];
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    w.show();
    return a.exec();
}
