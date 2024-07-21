#pragma once

#include <QObject>
#include <QImage>
#include <QThread>
#include <QDebug>
#include <opencv2/opencv.hpp>

class AppEngine : public QObject
{
    Q_OBJECT

public:
    void start();
    void stop();

    explicit AppEngine(QObject *parent = nullptr);

private:
    bool isRunning;
    cv::VideoCapture cap;

    void openCamConnection();
    void processFrame();

signals:
    void frameReady(const QImage &frame);
};
