#ifndef FLOATINGACTIONBUTTON_H
#define FLOATINGACTIONBUTTON_H

#include <QPushButton>

class FloatingActionButton : public QPushButton {
    Q_OBJECT
public:
    explicit FloatingActionButton(QWidget *parent = nullptr);

private slots:
    void animateClick();
};

#endif // FLOATINGACTIONBUTTON_H
