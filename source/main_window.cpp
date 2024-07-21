#include "../include/main_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), previewing(false), helpVisible(false)
{
    QScreen *monitorScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = monitorScreen->geometry();
    this->monitorWidth = screenGeometry.width();
    this->monitorHeight = screenGeometry.height();
    qDebug() << "Monitor width x height: "<< monitorWidth << "x" << monitorHeight;
    this->centerX = monitorWidth / 2,
    this->centerY = monitorHeight / 2;


    widgets = new Widgets(this);
    infoLabel = widgets->createInfoWidget(this->centerX - monitorWidth / 4, this->centerY - monitorHeight / 4, this->centerX, this->centerY);
    infoLabel->setVisible(false);

    showFullScreen();

    label = new QLabel("CapturedFrameLabel", this);
    label->setGeometry(this->centerX - monitorWidth / 4, this->centerY - monitorHeight / 4, this->centerX, this->centerY);
    label->setVisible(false);

    engine = new AppEngine();
    engineThread = new QThread();
    engine->moveToThread(engineThread);

    connect(engine, &AppEngine::frameReady, this, &MainWindow::updateFrame);

    engineThread->start();
    engine->start();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1) {
        togglePreview();
    } else if (event->key() == Qt::Key_H) {
        toggleHelp();
    } else if (event->key() == Qt::Key_Escape) {
        close();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}


/*
 * Toggle camera preview.
 */
void MainWindow::togglePreview()
{
    if (previewing) {
        previewing = false;
    } else {
        previewing = true;
    }
    label->setVisible(previewing);
}


/*
 * Toggle help window preview.
 */
void MainWindow::toggleHelp()
{
    helpVisible = !helpVisible;
    infoLabel->setVisible(helpVisible);
}


void MainWindow::updateFrame(const QImage &frame)
{
    label->setPixmap(QPixmap::fromImage(frame));
    label->setScaledContents(true);
}


MainWindow::~MainWindow()
{
    if (engineThread->isRunning()) {
        engine->stop();
        engineThread->quit();
        engineThread->wait();
    }

    delete widgets;
    delete engine;
    delete engineThread;
}
