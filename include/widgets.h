#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

class Widgets : public QObject
{
    Q_OBJECT

public:
    explicit Widgets(QWidget *parent = nullptr);

    QLabel* createInfoWidget(int beginX, int beginY, int width, int height);

private:
    QWidget *parentWidget;
};