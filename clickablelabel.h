#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(const QString &text, QWidget *parent = nullptr);

signals:
    void clicked();  // Signal emitted when the label is clicked

protected:
    void mousePressEvent(QMouseEvent *event) override;  // Override mouse press event

};

#endif // CLICKABLELABEL_H
