#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    setWindowTitle("QDatabase");

    //![1.0] - Adding Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    //![1.1] - StatusBar
    statusBar()->showMessage(tr("Ready"));
    //![1.2] - Database name
    db.setDatabaseName("./mydb.db");
    //![1.3] - Open database
    db.open();

    //![1.4] - if 'mydb.db' is open, print opened message
    if (db.isOpen())
    {
        qDebug("opened");
    }
    else
    {
        qDebug("couldn't open");
    }


    //![1.5] - Creating query from database
   query = new QSqlQuery(db);
   //!  Creating Table
   query->exec("CREATE TABLE Dataa(Firstname TEXT,Lastname TEXT, Telephone INT, Mail TEXT, Age INT);");
   //! Creating sql-tablemodel  of db
   model = new QSqlTableModel(this,db);
   //! Adding Data in our table
   model->setTable("Dataa");
   //! Update Data
   model->select();

   ui->tableView->setModel(model);

   connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::add_row);
   connect(ui->actionQt, &QAction::triggered, this, &MainWindow::AboutQt);
   connect(ui->actionAbout_Us, &QAction::triggered, this, &MainWindow::AboutUs);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::add_row()
{
    ui->pushButton_2->setEnabled(true);
    int lastRow = model->rowCount();
    model->insertRow(lastRow);
    statusBar()->showMessage(tr("New row forged"));
}


void MainWindow::on_pushButton_2_clicked()
{

    int res = QMessageBox::information(this, tr("Attention"), tr("This will delete the data.\nAre you sure to complete the operation?"),
                                       QMessageBox::Yes, QMessageBox::No);

    switch(res)
    {
        case QMessageBox::Yes:
            model->removeRow(row);

            model->select();
            statusBar()->showMessage(tr("Deleted"));
        default:
            return;
    }


}

void MainWindow::AboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::AboutUs()
{
    QMessageBox::about(this, tr("About Us"), tr("Simple Database II using SQL\n\nVersion 0.1.2"));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();

}

