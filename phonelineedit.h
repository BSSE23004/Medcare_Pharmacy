#ifndef PHONELINEEDIT_H
#define PHONELINEEDIT_H

#include <QApplication>
#include <QLineEdit>
#include <QKeyEvent>
#include <QIntValidator>

class PhoneLineEdit : public QLineEdit {
    Q_OBJECT

public:
    PhoneLineEdit(QWidget *parent = nullptr) : QLineEdit{parent} {
        setMaxLength(12);

        // Set a validator to ensure only numeric input
        QIntValidator *validator = new QIntValidator(0, 99999999999, this);
        setValidator(validator);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        // Only process the key event if it's a digit, backspace, or arrow key
        if ((event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) ||
            event->key() == Qt::Key_Backspace ||
            event->key() == Qt::Key_Left ||
            event->key() == Qt::Key_Right) {
            QLineEdit::keyPressEvent(event);
        } else {
            event->ignore();
            return;
        }

        // Format the text as a phone number
        QString text = this->text();
        text.remove('-');
        if (text.length() > 4) {
            text.insert(4, '-');
        }
        this->setText(text);
        this->setCursorPosition(text.length());
    }
};


#endif // PHONELINEEDIT_H
