#include "../include/widgets.h"

Widgets::Widgets(QWidget *parent) : QObject(parent), parentWidget(parent) {}


QLabel* Widgets::createInfoWidget(int beginX, int beginY, int width, int height)
{
    QString infoText = "F1 - Toggle Camera Preview\n"
                       "H - Show/Hide Help\n"
                       "ESC - Exit Application";

    QLabel *infoLabel = new QLabel(infoText, parentWidget);
    infoLabel->setWindowFlags(Qt::ToolTip);
    QFont font = infoLabel->font();
    font.setPointSize(16);
    infoLabel->setFont(font);
    infoLabel->setGeometry(beginX, beginY, width, height);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setWordWrap(true);

    return infoLabel;
}