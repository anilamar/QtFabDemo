#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

#include "FloatingActionButton.h"
#include "ChatWindow.h"

    namespace Ui {
    class MainWindow;
}


class MaterialCard : public QWidget {
    Q_OBJECT
public:
    MaterialCard(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *title = new QLabel("Card Title", this);
        QLabel *content = new QLabel("This is a Material Design card.", this);

        QFont titleFont;
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        title->setFont(titleFont);
        title->setStyleSheet("color: #202124;");

        QFont contentFont;
        contentFont.setPointSize(14);
        content->setFont(contentFont);
        content->setStyleSheet("color: #5F6368;");

        layout->addWidget(title);
        layout->addWidget(content);
        layout->setContentsMargins(16, 16, 16, 16);

        setStyleSheet(R"(
            QWidget {
                background-color: white;
                border-radius: 8px;
            }
        )");

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(15);
        shadow->setXOffset(0);
        shadow->setYOffset(2);
        shadow->setColor(QColor(0, 0, 0, 60));
        setGraphicsEffect(shadow);

        setFixedSize(200, 100);
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showChatWindow();
    void onChatWindowClosed();

private:
    Ui::MainWindow *ui;
    FloatingActionButton *fab;
    ChatWindow *chatWindow;
};

#endif // MAINWINDOW_H
