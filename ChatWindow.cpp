#include "ChatWindow.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QDateTime>

ChatWindow::ChatWindow(QWidget *parent) : QWidget(parent) {
    // Set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Chat display area (read-only)
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setStyleSheet(R"(
        QTextEdit {
            background-color: white;
            border: 1px solid #E0E0E0;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
    )");
    mainLayout->addWidget(chatDisplay);

    // Input area (message input + send button)
    QHBoxLayout *inputLayout = new QHBoxLayout();
    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Type a message...");
    messageInput->setStyleSheet(R"(
        QLineEdit {
            background-color: white;
            border: 1px solid #E0E0E0;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
    )");
    inputLayout->addWidget(messageInput);

    sendButton = new QPushButton("Send", this);
    sendButton->setStyleSheet(R"(
        QPushButton {
            background-color: #6200EE;
            color: white;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #3700B3;
        }
        QPushButton:pressed {
            background-color: #BB86FC;
        }
    )");
    inputLayout->addWidget(sendButton);

    mainLayout->addLayout(inputLayout);

    // Close button
    closeButton = new QPushButton("Close", this);
    closeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #E0E0E0;
            color: #202124;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #D0D0D0;
        }
    )");
    mainLayout->addWidget(closeButton, 0, Qt::AlignRight);

    // Style the chat window
    setStyleSheet(R"(
        QWidget {
            background-color: #F5F5F5;
            border-radius: 12px;
        }
    )");

    // Add shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(15);
    shadow->setXOffset(0);
    shadow->setYOffset(2);
    shadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(shadow);

    // Set size and position
    setFixedSize(300, 400);
    setWindowFlags(Qt::FramelessWindowHint); // Remove window frame for a modern look

    // Connect signals
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(closeButton, &QPushButton::clicked, this, &ChatWindow::closeChat);
}

void ChatWindow::sendMessage() {
    QString message = messageInput->text().trimmed();
    if (!message.isEmpty()) {
        // Append the message to the chat display with a timestamp
        QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
        chatDisplay->append(QString("<b>You [%1]:</b> %2").arg(timestamp, message));
        messageInput->clear();

        // Simulate a bot response (for demo purposes)
        chatDisplay->append(QString("<b>Bot [%1]:</b> Hello! How can I help you?").arg(timestamp));
    }
}

void ChatWindow::closeChat() {
    hide();
    emit closed(); // Emit signal to notify MainWindow
}
