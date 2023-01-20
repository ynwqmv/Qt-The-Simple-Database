#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

#include <QDebug>
#include <QSql>
#include <QString>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QStatusBar>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_row();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void AboutQt();
    void AboutUs();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery* query;
    QSqlTableModel* model;

    int row;
};
#endif // MAINWINDOW_H
