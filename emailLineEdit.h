#ifndef EMAILLINEEDIT_H
#define EMAILLINEEDIT_H
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QKeyEvent>

class EmailLineEdit : public QLineEdit {
    Q_OBJECT

public:
    EmailLineEdit(QWidget *parent = nullptr) : QLineEdit{parent} {
        // Regular expression for a basic email validation
        QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(emailRegex, this);
        setValidator(validator);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        // Allow input only for valid email characters
        if ((event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) ||
            (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) ||
            (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) ||
            event->key() == Qt::Key_At ||
            event->key() == Qt::Key_Period ||
            event->key() == Qt::Key_Underscore ||
            event->key() == Qt::Key_Minus ||
            event->key() == Qt::Key_Plus ||
            event->key() == Qt::Key_Backspace ||
            event->key() == Qt::Key_Delete ||
            event->key() == Qt::Key_Left ||
            event->key() == Qt::Key_Right) {
            QLineEdit::keyPressEvent(event);
        } else {
            event->ignore();
        }
    }
};

#endif // EMAILLINEEDIT_H
