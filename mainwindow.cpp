#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fab(nullptr)
    , chatWindow(nullptr)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->setContentsMargins(16, 16, 16, 16);

    // MaterialCard *card = new MaterialCard(this);
    // layout->addWidget(card, 0, Qt::AlignCenter);

    layout->addStretch();

    // Create the FAB
    fab = new FloatingActionButton(this);
    layout->addWidget(fab, 0, Qt::AlignRight | Qt::AlignBottom);

    // Create the chat window (initially hidden)
    chatWindow = new ChatWindow(this);
    chatWindow->hide();

    // Position the chat window (e.g., bottom-right corner)
    chatWindow->move(centralWidget->width() - chatWindow->width() - 16, centralWidget->height() - chatWindow->height() - 16);

    centralWidget->setStyleSheet("background-color: #F5F5F5;");

    setCentralWidget(centralWidget);
    resize(400, 300);

    // Connect FAB click to show chat window
    connect(fab, &QPushButton::clicked, this, &MainWindow::showChatWindow);
    // Connect chat window close signal to show FAB
    connect(chatWindow, &ChatWindow::closed, this, &MainWindow::onChatWindowClosed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showChatWindow()
{
    fab->hide();

    // Position the chat window off-screen (bottom-right)
    chatWindow->move(centralWidget()->width(), centralWidget()->height());
    chatWindow->show();

    // Animate sliding in from the bottom-right
    QPropertyAnimation *animation = new QPropertyAnimation(chatWindow, "pos");
    animation->setDuration(300);
    animation->setStartValue(chatWindow->pos());
    animation->setEndValue(QPoint(centralWidget()->width() - chatWindow->width() - 16, centralWidget()->height() - chatWindow->height() - 16));
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::onChatWindowClosed()
{
    // Show the FAB when the chat window is closed
    fab->show();
}

#include "mainwindow.moc"
