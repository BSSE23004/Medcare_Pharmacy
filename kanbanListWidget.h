#ifndef KANBANLISTWIDGET_H
#define KANBANLISTWIDGET_H

#endif // KANBANLISTWIDGET_H

#include <QApplication>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>

class KanbanListWidget : public QListWidget{
    Q_OBJECT

public:
    // QListWidgetItem *newItem;
    // QListWidgetItem *currentSelectedItem;
    KanbanListWidget(QWidget *parent = nullptr) : QListWidget(parent)
    {
        setDragEnabled(true);
        setAcceptDrops(true);
    }
    // ~KanbanListWidget(){
    //     delete newItem;
    //     delete currentSelectedItem;
    // }

protected :
    // void dragEnterEvent(QDragEnterEvent *event) override {
    //     if (event->mimeData()->hasText()) {
    //         event->acceptProposedAction();
    //     } else {
    //         event->ignore();
    //     }
    // }

    // void dragMoveEvent(QDragMoveEvent *event) override {
    //     if (event->mimeData()->hasText()) {
    //         event->acceptProposedAction();
    //     } else {
    //         event->ignore();
    //     }
    // }

    // void dropEvent(QDropEvent *event) override {
    //     if (event->mimeData()->hasText()) {
    //         QString itemText = event->mimeData()->text();
    //         newItem = new QListWidgetItem(QIcon(":/delivery-bike.ico"),itemText);
    //         this->addItem(newItem);
    //         // Retrieve the source widget
    //         KanbanListWidget *sourceWidget = qobject_cast<KanbanListWidget *>(event->source());
    //         if (sourceWidget) {
    //             QList<QListWidgetItem *> items = sourceWidget->findItems(itemText, Qt::MatchExactly);
    //             if (!items.isEmpty()) {
    //                 QListWidgetItem *itemToDelete = items.first();
    //                 int row = sourceWidget->row(itemToDelete);

    //                 // Safely remove the item from the source list and delete it
    //                 sourceWidget->takeItem(row);
    //             }
    //         }

    //         event->acceptProposedAction();
    //     } else {
    //         event->ignore();
    //     }
    // }

    // void startDrag(Qt::DropActions supportedActions) override {
    //     currentSelectedItem = currentItem();
    //     if (currentSelectedItem) {
    //         QDrag *drag = new QDrag(this);
    //         QMimeData *mimeData = new QMimeData;
    //         mimeData->setText(currentSelectedItem->text());
    //         drag->setMimeData(mimeData);
    //         drag->exec(supportedActions);
    //     }
    // }
};
