#include "../include/mainwindow.h"
#include "../cmake-build-debug/ui_mainwindow.h"

#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    loadImage("../test.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage(const QString &fileName)
{
    cv::Mat img = cv::imread(fileName.toStdString());
    if (img.empty()) {
        qDebug() << "Could not read image!";
        return;
    }

    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

    cv::imwrite("../gray_test.jpg", grayImg);

    QImage qImg = QImage(grayImg.data, grayImg.cols, grayImg.rows, grayImg.step, QImage::Format_Grayscale8);
    ui->label->setPixmap(QPixmap::fromImage(qImg));
    ui->label->setScaledContents(true);
    ui->label->show();
}
