#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <QString>
#include <QAbstractTableModel>

#include <QResource>
#include <QIcon>
#include <QMessageBox>
#include <QTableWidget>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Database");
    setWindowIcon(QIcon("C:/Users/qumar/OneDrive/Desktop/db.pmng.png"));

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addDataToTable);
    ui->pushButton->setIcon(QIcon("C:/Users/qumar/OneDrive/Desktop/add.png"));
    ui->pushButton_2->setIcon(QIcon("C:/Users/qumar/OneDrive/Desktop/t.png"));
    ui->pushButton_3->setIcon(QIcon("C:/Users/qumar/OneDrive/Desktop/exprt.png"));

    ui->pushButton_2->setEnabled(false);

    connect(ui->checkBox, &QCheckBox::toggled, ui->pushButton_3, &QPushButton::setEnabled);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::exportData);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::deleteSelectedRow);
    ui->pushButton_3->setEnabled(false);


}



void MainWindow::addDataToTable()
{



    QString name = ui->lineEdit->text();
    QString address  = ui->lineEdit_2->text();
    QString phone = ui->lineEdit_3->text();


    if (!name.isEmpty() && !address.isEmpty() && !phone.isEmpty())
    {
         ui->pushButton_2->setEnabled(true);

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        // add data to the row
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(address));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(phone));
    }else
    {
        QMessageBox::information(this, tr("Empty fields"), tr("Please, fill all fields"));
    }

    // create a new row

}

void MainWindow::exportData()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);


    // Write the header row
    out << "Name" << "\tAddress"  << "\tPhone" << "\n";

    // Write the data rows
    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();
    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < columnCount; ++col)
        {
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
            if (item != nullptr)
                out << item->text() << "\t";
            else
                out << "\t";
        }
        out << "\n";
    }

    file.close();
}

void MainWindow::importData()
{

}

void MainWindow::deleteSelectedRow()
{
    // Get the selected row


    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow != -1)
    {
        // Remove the row from the table
        ui->tableWidget->removeRow(selectedRow);
    }else
    {
        QMessageBox::information(this, tr("Non-selected row"), tr("Please, select the row to delete."));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

