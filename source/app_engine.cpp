#include "../include/app_engine.h"


AppEngine::AppEngine(QObject *parent)
    : QObject(parent), isRunning(false)
{}


void AppEngine::start()
{
    openCamConnection();
    isRunning = true;

    QThread *mainThread = new QThread;
    connect(mainThread, &QThread::started, this, &AppEngine::processFrame);
    moveToThread(mainThread);
    mainThread->start();
}

void AppEngine::stop()
{
    isRunning = false;
}

void AppEngine::openCamConnection()
{
    cap.open(0);
    if (!cap.isOpened()) {
        qDebug() << "Could not open the camera!";
        return;
    }
    else
    {
        qDebug() << "Camera connection enabled!";
    }
}

void AppEngine::processFrame()
{
    while (isRunning) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            qDebug() << "Captured empty frame!";
            continue;
        }

        cv::Mat flippedFrame;
        cv::flip(frame, flippedFrame, 1);

        cv::Mat rgbFrame;
        cv::cvtColor(flippedFrame, rgbFrame, cv::COLOR_BGR2RGB);

        QImage qImg(rgbFrame.data, rgbFrame.cols, rgbFrame.rows, rgbFrame.step, QImage::Format_RGB888);

        // Copying img obj to avoid memory issues
        QImage imgCopy = qImg.copy();

        emit frameReady(imgCopy);

        QThread::msleep(30);
    }
}