#ifndef FORM1_H
#define FORM1_H

#include <QMainWindow>
#include <QtDebug>
//Библиотека для работы с SQL
#include<QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class form1;
}

class form1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit form1(QWidget *parent = nullptr);
    ~form1();

private slots:
    void on_action_17_triggered();
    void on_pushButton_5_clicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();
    void on_action800x600_triggered();
    void on_action960x720_triggered();
    void on_action1024x768_triggered();
    void on_action1360x768_triggered();
    void on_action1366x768_triggered();
    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();
    void on_action_6_triggered();
    void on_tableView_clicked(const QModelIndex &index);
    void on_action_3_triggered();
    void on_action_11_triggered();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_clicked();
    void on_comboBox_9_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_checkBox_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_clicked();

    void on_action_12_triggered();

    void on_action_10_triggered();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_action_7_triggered();

    void on_action1_5_triggered();

    void on_action2_4_triggered();

    void on_action3_4_triggered();

    void on_action4_4_triggered();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_action_13_triggered();

public:
    Ui::form1 *ui;
    //Событие закрытия окна
    void closeEvent(QCloseEvent *clsEvent);
    //Создаем и подключаем объекты
    QSqlDatabase sdb;
    QSqlQuery *query;
    QSqlTableModel *model;
    int row;//Номер активной строки
};

#endif // FORM1_H
