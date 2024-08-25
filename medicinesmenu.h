#ifndef MEDICINESMENU_H
#define MEDICINESMENU_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <inputdialog.h>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QStackedLayout>
#include <QRect>
class MedicinesMenu : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;
    QTableWidget *medicinesTable;
    QPushButton *searchButton;
    QLineEdit *searchBar;
    QTableWidgetItem *itemTable;
    QPushButton *addButton;
    QPushButton *removeButton;
    InputDialog *inputMedicine;
    QRect medicineTableGeometry;
    explicit MedicinesMenu(QWidget *parent = nullptr);
    ~MedicinesMenu();
    void filterTable(const QString &text);
    void writeMedicinesTableToJson();
    void readMedicineTableFromJson();
    void settingColumnsWidth();

private slots:
    void handleSearchBarAndButton();
    void handleRemoveRowButton();
    void handleAddRowButton();

signals:
};

#endif // MEDICINESMENU_H
