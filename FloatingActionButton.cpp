#include "FloatingActionButton.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

FloatingActionButton::FloatingActionButton(QWidget *parent) : QPushButton(parent) {
    setFixedSize(56, 56);

    setIcon(QIcon(":/icons/add.png"));
    setIconSize(QSize(24, 24));

    setStyleSheet(R"(
        QPushButton {
            background-color: #6200EE;
            border-radius: 28px;
            color: white;
        }
        QPushButton:hover {
            background-color: #3700B3;
        }
        QPushButton:pressed {
            background-color: #BB86FC;
        }
    )");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setXOffset(0);
    shadow->setYOffset(4);
    shadow->setColor(QColor(0, 0, 0, 50));
    setGraphicsEffect(shadow);

    connect(this, &QPushButton::clicked, this, &FloatingActionButton::animateClick);
}

void FloatingActionButton::animateClick() {
    QPropertyAnimation *scaleUp = new QPropertyAnimation(this, "geometry");
    scaleUp->setDuration(200);
    QRect startGeometry = geometry();
    int newWidth = startGeometry.width() + 10;
    int newHeight = startGeometry.height() + 10;
    int newX = startGeometry.x() - (newWidth - startGeometry.width()) / 2;
    int newY = startGeometry.y() - (newHeight - startGeometry.height()) / 2;
    QRect endGeometry(newX, newY, newWidth, newHeight);
    scaleUp->setStartValue(startGeometry);
    scaleUp->setEndValue(endGeometry);
    scaleUp->setEasingCurve(QEasingCurve::OutBack);

    QPropertyAnimation *scaleDown = new QPropertyAnimation(this, "geometry");
    scaleDown->setDuration(200);
    scaleDown->setStartValue(endGeometry);
    scaleDown->setEndValue(startGeometry);
    scaleDown->setEasingCurve(QEasingCurve::InBack);

    QSequentialAnimationGroup *scaleGroup = new QSequentialAnimationGroup(this);
    scaleGroup->addAnimation(scaleUp);
    scaleGroup->addAnimation(scaleDown);
    scaleGroup->start(QAbstractAnimation::DeleteWhenStopped);
}
