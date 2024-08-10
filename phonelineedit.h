#include <QApplication>
#include <QLineEdit>
#include <QKeyEvent>

class PhoneLineEdit : public QLineEdit {
    Q_OBJECT

public:
    PhoneLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {
        setMaxLength(12);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        QLineEdit::keyPressEvent(event);
        QString text = this->text();
        text.remove('-');
        if (text.length() > 4) {
            text.insert(4, '-');
        }
        this->setText(text);
        this->setCursorPosition(text.length());
    }
};
