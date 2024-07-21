#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QThread>
#include <QVBoxLayout>
#include <QDebug>
#include <QKeyEvent>
#include <QRect>

#include "../include/app_engine.h"
#include "../include/widgets.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int monitorWidth, monitorHeight;
    int centerX, centerY;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateFrame(const QImage &frame);
    void togglePreview();
    void toggleHelp();

private:
    AppEngine *engine;
    QThread *engineThread;
    Widgets *widgets;
    QLabel *label;
    QLabel *infoLabel;
    bool previewing;
    bool helpVisible;
};