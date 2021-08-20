#include "form1.h"
#include "ui_form1.h"
#include <QMessageBox>
#include <QCloseEvent>
//Библиотеки для работы с шифратором
#include <iostream>
#include <vector>
//Библиотека для работы с SQL
#include<QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

form1::form1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::form1)
{
    ui->setupUi(this);
    //Задание размеров формы и тд.
    ui->widget->setVisible(false);
    ui->widget_2->setVisible(false);
    ui->widget_3->setVisible(false);
    ui->widget_4->setVisible(false);
    ui->widget_5->setVisible(false);
    ui->widget_6->setVisible(false);
    ui->widget_7->setVisible(false);
    ui->widget_8->setVisible(false);
    this->resize(301,150);
    this->ui->menubar->setVisible(false);
    this->ui->frame->setVisible(false);
    this->setWindowTitle("Авторизация");
    //Инициализация Базы данных
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("my_db.sqlite");
    //Проверка подключения БД
        if (!dbase.open()) {
            qDebug() << "Что-то пошло не так!";
        }
     QSqlQuery a_query;
        //Создание Таблицы студентов в базе данных
        QString str = "CREATE TABLE my_table ("
                "ID integer PRIMARY KEY NOT NULL, "
                "`Специальность` VARCHAR(255), "
                "`Форма обучения` VARCHAR(255), "
 "`ОБО/ОСО` VARCHAR(255), "
 "`Курс` VARCHAR(255), "
"`Номер учебной группы` VARCHAR(255), "
"`Бюджет/Коммерч` VARCHAR(255), "
"`Проживет в общежитии(адрес общежития)` VARCHAR(255), "
"`Пол` VARCHAR(255), "
"`Фамилия` VARCHAR(255), "
"`Имя` VARCHAR(255), "
"`Отчество` VARCHAR(255), "
"`Дата рождения` VARCHAR(255), "
"`Паспортные данные` VARCHAR(255), "
"`Средний балл после окончания школы` VARCHAR(255), "
"`Ин/Яз` VARCHAR(255), "
"`Мобильный телефон/Домашний телефон` VARCHAR(255), "
"`Область` VARCHAR(255), "
"`Город` VARCHAR(255), "
"`Район` VARCHAR(255), "
"`Адрес проживания/Адрес прописки` VARCHAR(255), "
"`Средний бал` VARCHAR(255), "
"`Целевик` VARCHAR(255), "
"`Родители` VARCHAR(255), "
"`Место работы` VARCHAR(255), "
"`Льготы` VARCHAR(255), "
"`Примечание` VARCHAR(255), "
"`Номер приказа` VARCHAR(255), "
"`Дата перевода` VARCHAR(255)"
                ");";
        //Проверка таблицы на наличие
        bool b = a_query.exec(str);
        if (!b) {
            qDebug() << "Видимо таблица my_table уже созданна";
        }
        //Создание Таблицы отчисленных студентов в базе данных
        QString str2 = "CREATE TABLE otchislen ("
                "ID integer PRIMARY KEY NOT NULL, "
                "`Специальность` VARCHAR(255), "
                "`Форма обучения` VARCHAR(255), "
 "`ОБО/ОСО` VARCHAR(255), "
 "`Курс` VARCHAR(255), "
"`Номер учебной группы` VARCHAR(255), "
"`Бюджет/Коммерч` VARCHAR(255), "
"`Проживет в общежитии(адрес общежития)` VARCHAR(255), "
"`Пол` VARCHAR(255), "
"`Фамилия` VARCHAR(255), "
"`Имя` VARCHAR(255), "
"`Отчество` VARCHAR(255), "
"`Дата рождения` VARCHAR(255), "
"`Паспортные данные` VARCHAR(255), "
"`Средний балл после окончания школы` VARCHAR(255), "
"`Ин/Яз` VARCHAR(255), "
"`Мобильный телефон/Домашний телефон` VARCHAR(255), "
"`Область` VARCHAR(255), "
"`Город` VARCHAR(255), "
"`Район` VARCHAR(255), "
"`Адрес проживания/Адрес прописки` VARCHAR(255), "
"`Средний бал` VARCHAR(255), "
"`Целевик` VARCHAR(255), "
"`Родители` VARCHAR(255), "
"`Место работы` VARCHAR(255), "
"`Льготы` VARCHAR(255), "
"`Примечание` VARCHAR(255), "
"`Номер приказа` VARCHAR(255), "
"`Дата отчисления` VARCHAR(255)"
                ");";
        //Проверка таблицы на наличие
        bool c = a_query.exec(str2);
        if (!c) {
            qDebug() << "Видимо таблица otchislen уже созданна";
        }

        //Создание таблицы с данными авторизации
        QString str3 = "CREATE TABLE autorize ("
                "ID integer PRIMARY KEY NOT NULL, "
                "`Логин` VARCHAR(255), "
                "`Пароль` VARCHAR(255)"
                ");";
        //Проверка таблицы на наличие
        bool d = a_query.exec(str3);
        if (!d) {
            qDebug() << "Видимо таблица autorize уже созданна";
        }

}

form1::~form1()
{
    delete ui;
}

//Метод шифрования
std::string encrypt(std::string input) {
    std::vector<char> word(input.begin(), input.end());
    std::string alphabet = "zabcdefghijklmnopqrstuvwxyz";
    for (int i = 1; i < (int)input.length(); i++) {
        for (int j = 1; j < (int)alphabet.length(); j++) {
            if (word[i] == alphabet[j]) {
                word[i] = alphabet[(j + 1) % 26];
                break;
            }
        }
    }
    std::string str(word.begin(), word.end());
    return str;
}

//Номер таблицы 1-неотчисленные, 2-отчисленные
qint32 num_table;

//Номер юзера 1-админ, 2-пользователь
qint32 user_num;

//Вызов диалога при выходе из программы
void form1::on_action_17_triggered()
{
    QMessageBox::StandardButton questions = QMessageBox::information(this,"Выход","Вы действительно хотите выйти из программы?",QMessageBox::Yes | QMessageBox::No);
    if(questions ==QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else{}
}

//Вызов диалога при закрытии формы на крестик
void form1::closeEvent(QCloseEvent *clsEvent)
{
    clsEvent->ignore();
    QMessageBox::StandardButton questions = QMessageBox::information(this,"Выход","Вы действительно хотите выйти из программы?",QMessageBox::Yes | QMessageBox::No);
    if(questions ==QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else
    {
       clsEvent->ignore();
    }
}

//Вывод информации о программе
void form1::on_pushButton_5_clicked()
{
    /*
    //Модуль заполнения данных об авторизации в таблицу
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    model->insertRow(row);
    model->setData(model->index(0, 1),"utfs");
    model->setData(model->index(0, 2),"utfs");
    model->submitAll();
    model->select();
    this->ui->tableView->setModel(model);
    */

    QMessageBox::information(this,"О программе","Программа для упрощения ведения учета студентов.",QMessageBox::Ok);
}

//Смена пароля админа
void form1::on_action_triggered()
{
    this->ui->widget_5->setVisible(true);
    this->ui->widget_5->move(0,0);
}

//Смена пароля пользователя
void form1::on_action_2_triggered()
{
    this->ui->widget_7->setVisible(true);
    this->ui->widget_7->move(0,0);

}

//Смена логина админа
void form1::on_action_4_triggered()
{
    this->ui->widget_4->setVisible(true);
    this->ui->widget_4->move(0,0);
}

//Смена логина пользователя
void form1::on_action_5_triggered()
{
    this->ui->widget_6->setVisible(true);
    this->ui->widget_6->move(0,0);
}

//Изменение размера рабочего окна и размеров элементов и тд.
void form1::on_action800x600_triggered()
{
    this->resize(800,600);
    this->ui->frame->resize(800,26);
    this->ui->pushButton_3->move(628,0);
    this->ui->pushButton_6->move(628,0);
    this->ui->pushButton_11->move(540,0);
    this->ui->tableView->resize(800,521);
}

void form1::on_action960x720_triggered()
{
    this->resize(960,720);
    this->ui->frame->resize(960,26);
    this->ui->pushButton_3->move(787,0);
    this->ui->pushButton_6->move(787,0);
    this->ui->pushButton_11->move(700,0);
    this->ui->tableView->resize(960,631);

}

void form1::on_action1024x768_triggered()
{
    this->resize(1024,720);
    this->ui->frame->resize(1024,26);
    this->ui->pushButton_3->move(852,0);
    this->ui->pushButton_6->move(852,0);
    this->ui->pushButton_11->move(764,0);
    this->ui->tableView->resize(1024,631);
}

void form1::on_action1360x768_triggered()
{
    this->resize(1360,720);
    this->ui->frame->resize(1360,26);
    this->ui->pushButton_3->move(1188,0);
    this->ui->pushButton_6->move(1188,0);
    this->ui->pushButton_11->move(1100,0);
    this->ui->tableView->resize(1360,631);
}

void form1::on_action1366x768_triggered()
{
    this->resize(1366,720);
    this->ui->frame->resize(1366,26);
    this->ui->pushButton_3->move(1194,0);
    this->ui->pushButton_6->move(1194,0);
    this->ui->pushButton_11->move(1106,0);
    this->ui->tableView->resize(1366,631);
}

//Блокировка формы и вызов виджета для разблокировки рабочего окна
void form1::on_pushButton_3_clicked()
{
    this->ui->tabWidget->setVisible(false);
    this->ui->menubar->setVisible(false);
    this->ui->frame->setVisible(false);
    this->ui->widget_2->setVisible(true);
    this->resize(301,165);
    this->ui->widget_2->move(0,0);
    this->statusBar()->clearMessage();
}

//Блокировка формы и вызов виджета для разблокировки рабочего окна от имени пользователя
void form1::on_pushButton_6_clicked()
{
    this->ui->tabWidget->setVisible(false);
    this->ui->menubar->setVisible(false);
    this->ui->frame->setVisible(false);
    this->ui->widget_3->setVisible(true);
    this->resize(301,165);
    this->ui->widget_3->move(0,0);
    this->statusBar()->clearMessage();
}

//Удаление выбранной строки в таблице
void form1::on_action_6_triggered()
{
    if(num_table == 1)
    {
        //Удаление
        model = new QSqlTableModel(this,sdb);
        model->setTable("my_table");
        model->select();
        model->removeRow(row);
        //Обновление таблицы
        model = new QSqlTableModel(this,sdb);
        model->setTable("my_table");
        model->select();
        ui->tableView->setModel(model);
        //Вывод данных в статусбар
        this->statusBar()->showMessage(tr("Запись удалена"));
    }
    if(num_table ==2)
    {
        //Удаление
        model = new QSqlTableModel(this,sdb);
        model->setTable("otchislen");
        model->select();
        model->removeRow(row);
        //Обновление таблицы
        model = new QSqlTableModel(this,sdb);
        model->setTable("otchislen");
        model->select();
        ui->tableView->setModel(model);
        //Вывод данных в статусбар
        this->statusBar()->showMessage(tr("Запись удалена"));
    }
}

//Присваивает номер выбранной строке
void form1::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

//Вызов окна добавление студента
void form1::on_action_3_triggered()
{
    this->ui->tableView->setVisible(false);
    this->ui->pushButton->setVisible(false);
    this->ui->pushButton_2->setVisible(false);
    this->ui->pushButton_4->setVisible(false);
    this->ui->pushButton_5->setVisible(false);
    this->ui->pushButton_11->setVisible(false);
    this->ui->menubar->setVisible(false);
    this->setWindowTitle("Добавление студента");
    //Отображаем необходимые елементы
    this->ui->label->setVisible(true);
    this->ui->label_2->setVisible(true);
    this->ui->label_3->setVisible(true);
    this->ui->label_4->setVisible(true);
    this->ui->label_5->setVisible(true);
    this->ui->label_6->setVisible(true);
    this->ui->label_8->setVisible(true);
    this->ui->label_9->setVisible(true);
    this->ui->label_10->setVisible(true);
    this->ui->label_11->setVisible(true);
    this->ui->label_12->setVisible(true);
    this->ui->label_13->setVisible(true);
    this->ui->label_14->setVisible(true);
    this->ui->label_15->setVisible(true);
    this->ui->label_16->setVisible(true);
    this->ui->label_17->setVisible(true);
    this->ui->label_18->setVisible(true);
    this->ui->label_19->setVisible(true);
    this->ui->label_20->setVisible(true);
    this->ui->label_21->setVisible(true);
    this->ui->label_22->setVisible(true);
    this->ui->label_23->setVisible(true);
    this->ui->label_24->setVisible(true);
    this->ui->label_25->setVisible(true);
    this->ui->label_26->setVisible(true);
    this->ui->label_27->setVisible(true);
    this->ui->pushButton_7->setVisible(true);
    this->ui->pushButton_8->setVisible(true);
    this->ui->comboBox->setVisible(true);
    this->ui->comboBox_2->setVisible(true);
    this->ui->comboBox_3->setVisible(true);
    this->ui->comboBox_4->setVisible(true);
    this->ui->comboBox_5->setVisible(true);
    this->ui->comboBox_6->setVisible(true);
    this->ui->comboBox_7->setVisible(true);
    this->ui->comboBox_8->setVisible(true);
    this->ui->comboBox_9->setVisible(true);
    this->ui->comboBox_10->setVisible(true);
    this->ui->comboBox_11->setVisible(true);
    this->ui->lineEdit_11->setVisible(true);
    this->ui->comboBox_13->setVisible(true);
    this->ui->doubleSpinBox->setVisible(true);
    this->ui->doubleSpinBox_2->setVisible(true);
    this->ui->lineEdit->setVisible(true);
    this->ui->lineEdit_2->setVisible(true);
    this->ui->lineEdit_3->setVisible(true);
    this->ui->lineEdit_4->setVisible(true);
    this->ui->lineEdit_5->setVisible(true);
    this->ui->lineEdit_6->setVisible(true);
    this->ui->lineEdit_7->setVisible(true);
    this->ui->lineEdit_8->setVisible(true);
    this->ui->lineEdit_9->setVisible(true);
    this->ui->lineEdit_10->setVisible(true);
    this->ui->dateEdit->setVisible(true);
    //Заполнение комбобоксов
    //Специальности
    ui->comboBox->addItem("",0);
    ui->comboBox->addItem("Мелиорация и водное хозяйство",1);
    ui->comboBox->addItem("Техническое обеспечение мелиоративных и водохозяйственных работ",2);
    ui->comboBox->addItem("Ремонтно-обслуживающее производство в сельском хозяйстве",3);
    ui->comboBox->addItem("Промышленное и гражданское строительство",4);
    ui->comboBox->addItem("Строительство дорог и транспортных объектов",5);
    //Форма обучения
    ui->comboBox_2->addItem("",0);
    ui->comboBox_2->addItem("ДФО",1);
    ui->comboBox_2->addItem("ЗФО",2);
    //ОБО\ОСО
    ui->comboBox_3->addItem("",0);
    ui->comboBox_3->addItem("ОБО",1);
    ui->comboBox_3->addItem("ОСО",2);
    //Курс
    ui->comboBox_4->addItem("",0);
    ui->comboBox_4->addItem("1",1);
    ui->comboBox_4->addItem("2",2);
    ui->comboBox_4->addItem("3",3);
    ui->comboBox_4->addItem("4",4);
    //Бюджет или комерч
    ui->comboBox_5->addItem("",0);
    ui->comboBox_5->addItem("Бюджет",1);
    ui->comboBox_5->addItem("Комерч",2);
    //Адрес общежития
    ui->comboBox_6->addItem("",0);
    ui->comboBox_6->addItem("г.Пинск, ул. Партизанская, 13.",1);
    ui->comboBox_6->addItem("г.Пинск, ул. Кирова, 34.",2);
    //Пол
    ui->comboBox_7->addItem("",0);
    ui->comboBox_7->addItem("М",1);
    ui->comboBox_7->addItem("Ж",2);
    //Ин.яз
    ui->comboBox_8->addItem("",0);
    ui->comboBox_8->addItem("Английский",1);
    ui->comboBox_8->addItem("Немецкий",2);
    ui->comboBox_8->addItem("Французский",3);
    //Область
    ui->comboBox_9->addItem("",0);
    ui->comboBox_9->addItem("Брестская",1);
    ui->comboBox_9->addItem("Витебская",2);
    ui->comboBox_9->addItem("Гомельская",3);
    ui->comboBox_9->addItem("Гродненская",4);
    ui->comboBox_9->addItem("Минская",5);
    ui->comboBox_9->addItem("Могилевская",6);
    //Целевик
    ui->comboBox_13->addItem("",0);
    ui->comboBox_13->addItem("Да",1);
    ui->comboBox_13->addItem("Нет",2);
}

//Вызов настроек справочника функция появится в дальнейшем
void form1::on_action_11_triggered()
{

}

//Отмена добавления студента
void form1::on_pushButton_8_clicked()
{
    this->ui->tableView->setVisible(true);
    this->ui->pushButton->setVisible(true);
    this->ui->pushButton_2->setVisible(true);
    this->ui->pushButton_4->setVisible(true);
    this->ui->pushButton_5->setVisible(true);
    this->ui->pushButton_11->setVisible(true);
    this->ui->menubar->setVisible(true);
    this->setWindowTitle("Учащиеся");
    //Скрываем ненужные элементы
    this->ui->label->setVisible(false);
    this->ui->label_2->setVisible(false);
    this->ui->label_3->setVisible(false);
    this->ui->label_4->setVisible(false);
    this->ui->label_5->setVisible(false);
    this->ui->label_6->setVisible(false);
    this->ui->label_8->setVisible(false);
    this->ui->label_9->setVisible(false);
    this->ui->label_10->setVisible(false);
    this->ui->label_11->setVisible(false);
    this->ui->label_12->setVisible(false);
    this->ui->label_13->setVisible(false);
    this->ui->label_14->setVisible(false);
    this->ui->label_15->setVisible(false);
    this->ui->label_16->setVisible(false);
    this->ui->label_17->setVisible(false);
    this->ui->label_18->setVisible(false);
    this->ui->label_19->setVisible(false);
    this->ui->label_20->setVisible(false);
    this->ui->label_21->setVisible(false);
    this->ui->label_22->setVisible(false);
    this->ui->label_23->setVisible(false);
    this->ui->label_24->setVisible(false);
    this->ui->label_25->setVisible(false);
    this->ui->label_26->setVisible(false);
    this->ui->label_27->setVisible(false);
    this->ui->pushButton_7->setVisible(false);
    this->ui->pushButton_8->setVisible(false);
    this->ui->comboBox->setVisible(false);
    this->ui->comboBox_2->setVisible(false);
    this->ui->comboBox_3->setVisible(false);
    this->ui->comboBox_4->setVisible(false);
    this->ui->comboBox_5->setVisible(false);
    this->ui->comboBox_6->setVisible(false);
    this->ui->comboBox_7->setVisible(false);
    this->ui->comboBox_8->setVisible(false);
    this->ui->comboBox_9->setVisible(false);
    this->ui->comboBox_10->setVisible(false);
    this->ui->comboBox_11->setVisible(false);
    this->ui->lineEdit_11->setVisible(false);
    this->ui->comboBox_13->setVisible(false);
    this->ui->doubleSpinBox->setVisible(false);
    this->ui->doubleSpinBox_2->setVisible(false);
    this->ui->lineEdit->setVisible(false);
    this->ui->lineEdit_2->setVisible(false);
    this->ui->lineEdit_3->setVisible(false);
    this->ui->lineEdit_4->setVisible(false);
    this->ui->lineEdit_5->setVisible(false);
    this->ui->lineEdit_6->setVisible(false);
    this->ui->lineEdit_7->setVisible(false);
    this->ui->lineEdit_8->setVisible(false);
    this->ui->lineEdit_9->setVisible(false);
    this->ui->lineEdit_10->setVisible(false);
    this->ui->dateEdit->setVisible(false);
    //Отчистка полей
    this->ui->comboBox->clear();
    this->ui->comboBox->clear();
    this->ui->comboBox_2->clear();
    this->ui->comboBox_3->clear();
    this->ui->comboBox_4->clear();
    this->ui->lineEdit_10->clear();
    this->ui->comboBox_5->clear();
    this->ui->comboBox_6->clear();
    this->ui->comboBox_7->clear();
    this->ui->lineEdit->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
    this->ui->dateEdit->clear();
    this->ui->lineEdit_4->clear();
    this->ui->doubleSpinBox_2->clear();
    this->ui->comboBox_8->clear();
    this->ui->lineEdit_6->clear();
    this->ui->comboBox_9->clear();
    this->ui->comboBox_10->clear();
    this->ui->comboBox_11->clear();
    this->ui->lineEdit_5->clear();
    this->ui->doubleSpinBox->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_11->clear();
    this->ui->lineEdit_9->clear();
    this->ui->comboBox_13->clear();
}

//Добавление студента
void form1::on_pushButton_7_clicked()
{
    this->ui->tableView->setVisible(true);
    this->ui->pushButton->setVisible(true);
    this->ui->pushButton_2->setVisible(true);
    this->ui->pushButton_4->setVisible(true);
    this->ui->pushButton_5->setVisible(true);
    this->ui->pushButton_11->setVisible(true);
    this->ui->menubar->setVisible(true);
    this->setWindowTitle("Учащиеся");
    //Скрываем ненужные элементы
    this->ui->label->setVisible(false);
    this->ui->label_2->setVisible(false);
    this->ui->label_3->setVisible(false);
    this->ui->label_4->setVisible(false);
    this->ui->label_5->setVisible(false);
    this->ui->label_6->setVisible(false);
    this->ui->label_8->setVisible(false);
    this->ui->label_9->setVisible(false);
    this->ui->label_10->setVisible(false);
    this->ui->label_11->setVisible(false);
    this->ui->label_12->setVisible(false);
    this->ui->label_13->setVisible(false);
    this->ui->label_14->setVisible(false);
    this->ui->label_15->setVisible(false);
    this->ui->label_16->setVisible(false);
    this->ui->label_17->setVisible(false);
    this->ui->label_18->setVisible(false);
    this->ui->label_19->setVisible(false);
    this->ui->label_20->setVisible(false);
    this->ui->label_21->setVisible(false);
    this->ui->label_22->setVisible(false);
    this->ui->label_23->setVisible(false);
    this->ui->label_24->setVisible(false);
    this->ui->label_25->setVisible(false);
    this->ui->label_26->setVisible(false);
    this->ui->label_27->setVisible(false);
    this->ui->pushButton_7->setVisible(false);
    this->ui->pushButton_8->setVisible(false);
    this->ui->comboBox->setVisible(false);
    this->ui->comboBox_2->setVisible(false);
    this->ui->comboBox_3->setVisible(false);
    this->ui->comboBox_4->setVisible(false);
    this->ui->comboBox_5->setVisible(false);
    this->ui->comboBox_6->setVisible(false);
    this->ui->comboBox_7->setVisible(false);
    this->ui->comboBox_8->setVisible(false);
    this->ui->comboBox_9->setVisible(false);
    this->ui->comboBox_10->setVisible(false);
    this->ui->comboBox_11->setVisible(false);
    this->ui->lineEdit_11->setVisible(false);
    this->ui->doubleSpinBox->setVisible(false);
    this->ui->doubleSpinBox_2->setVisible(false);
    this->ui->lineEdit->setVisible(false);
    this->ui->lineEdit_2->setVisible(false);
    this->ui->lineEdit_3->setVisible(false);
    this->ui->lineEdit_4->setVisible(false);
    this->ui->lineEdit_5->setVisible(false);
    this->ui->lineEdit_6->setVisible(false);
    this->ui->lineEdit_7->setVisible(false);
    this->ui->lineEdit_8->setVisible(false);
    this->ui->lineEdit_9->setVisible(false);
    this->ui->lineEdit_10->setVisible(false);
    this->ui->dateEdit->setVisible(false);
    this->ui->comboBox_13->setVisible(false);
    //Работа с БД
    model = new QSqlTableModel(this,sdb);
    model->setTable("my_table");
    model->select();
    //Вставка пустой строки
    model->insertRow(row);
    //Вставка данных
    model->setData(model->index(row, 1),this->ui->comboBox->currentText());
    model->setData(model->index(row, 2),this->ui->comboBox_2->currentText());
    model->setData(model->index(row, 3),this->ui->comboBox_3->currentText());
    model->setData(model->index(row, 4),this->ui->comboBox_4->currentText());
    model->setData(model->index(row, 5),this->ui->lineEdit_10->text());
    model->setData(model->index(row, 6),this->ui->comboBox_5->currentText());
    model->setData(model->index(row, 7),this->ui->comboBox_6->currentText());
    model->setData(model->index(row, 8),this->ui->comboBox_7->currentText());
    model->setData(model->index(row, 9),this->ui->lineEdit->text());
    model->setData(model->index(row, 10),this->ui->lineEdit_2->text());
    model->setData(model->index(row, 11),this->ui->lineEdit_3->text());
    model->setData(model->index(row, 12),this->ui->dateEdit->text());
    model->setData(model->index(row, 13),this->ui->lineEdit_4->text());
    model->setData(model->index(row, 14),this->ui->doubleSpinBox_2->text());
    model->setData(model->index(row, 15),this->ui->comboBox_8->currentText());
    model->setData(model->index(row, 16),this->ui->lineEdit_6->text());
    model->setData(model->index(row, 17),this->ui->comboBox_9->currentText());
    model->setData(model->index(row, 18),this->ui->comboBox_10->currentText());
    model->setData(model->index(row, 19),this->ui->comboBox_11->currentText());
    model->setData(model->index(row, 20),this->ui->lineEdit_5->text());
    model->setData(model->index(row, 21),this->ui->doubleSpinBox->text());
    model->setData(model->index(row, 22),this->ui->comboBox_13->currentText());
    model->setData(model->index(row, 23),this->ui->lineEdit_7->text());
    model->setData(model->index(row, 24),this->ui->lineEdit_8->text());
    model->setData(model->index(row, 25),this->ui->lineEdit_11->text());
    model->setData(model->index(row, 26),this->ui->lineEdit_9->text());
    model->setData(model->index(row, 27),"");
    model->setData(model->index(row, 28),"");
    //Подтверждение вставки
    model->submitAll();
    //Отображение данных
    model->select();
    ui->tableView->setModel(model);
    //Отчистка полей
    this->ui->comboBox->clear();
    this->ui->comboBox->clear();
    this->ui->comboBox_2->clear();
    this->ui->comboBox_3->clear();
    this->ui->comboBox_4->clear();
    this->ui->lineEdit_10->clear();
    this->ui->comboBox_5->clear();
    this->ui->comboBox_6->clear();
    this->ui->comboBox_7->clear();
    this->ui->lineEdit->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
    this->ui->dateEdit->clear();
    this->ui->lineEdit_4->clear();
    this->ui->doubleSpinBox_2->clear();
    this->ui->comboBox_8->clear();
    this->ui->lineEdit_6->clear();
    this->ui->comboBox_9->clear();
    this->ui->comboBox_10->clear();
    this->ui->comboBox_11->clear();
    this->ui->lineEdit_5->clear();
    this->ui->doubleSpinBox->clear();
    this->ui->lineEdit_7->clear();
    this->ui->lineEdit_8->clear();
    this->ui->lineEdit_11->clear();
    this->ui->comboBox_13->clear();
    this->ui->lineEdit_9->clear();
    //Вывод данных в статусбар
    this->statusBar()->showMessage(tr("Студент добавлен"));
}

//Вход в программу под администратором
void form1::on_pushButton_9_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString login = model->data(model->index(0, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->loginTextBox->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(login == qstr)
    {
        //Таже процедура для файла с паролем
        model = new QSqlTableModel(this,sdb);
        model->setTable("autorize");
        model->select();
        //Присваиваем переменной значение логина из базы данных
        QString password = model->data(model->index(0, 2)).toString();
        QString textBoxPassword = ui->passwordTextBox->text();
        //Конвертируем текст из QString в String
        std::string convText = textBoxPassword.toStdString();
        //Шифруем конвертируемый текст
        std::string encryptText = encrypt(convText);
        //Конвертируем зашифрованный текст обратно в QString
        QString qstr = QString::fromStdString(encryptText);
        if(password == qstr)
        {
            //Указываем в статус баре профиль(Администратор/Пользователь)
            this->statusBar()->showMessage(tr("Ваш текущий профиль: Администратор"));
            //Скрываем ненужные элементы
            this->ui->pushButton_6->setVisible(false);
            this->ui->tableView->resize(800,521);
            this->ui->pushButton_6->move(540,0);
            this->ui->pushButton_7->setVisible(false);
            this->ui->pushButton_8->setVisible(false);
            this->ui->label->setVisible(false);
            this->ui->label_2->setVisible(false);
            this->ui->label_3->setVisible(false);
            this->ui->label_4->setVisible(false);
            this->ui->label_5->setVisible(false);
            this->ui->label_6->setVisible(false);
            this->ui->label_8->setVisible(false);
            this->ui->label_9->setVisible(false);
            this->ui->label_10->setVisible(false);
            this->ui->label_11->setVisible(false);
            this->ui->label_12->setVisible(false);
            this->ui->label_13->setVisible(false);
            this->ui->label_14->setVisible(false);
            this->ui->label_15->setVisible(false);
            this->ui->label_16->setVisible(false);
            this->ui->label_17->setVisible(false);
            this->ui->label_18->setVisible(false);
            this->ui->label_19->setVisible(false);
            this->ui->label_20->setVisible(false);
            this->ui->label_21->setVisible(false);
            this->ui->label_22->setVisible(false);
            this->ui->label_23->setVisible(false);
            this->ui->label_24->setVisible(false);
            this->ui->label_25->setVisible(false);
            this->ui->label_26->setVisible(false);
            this->ui->label_27->setVisible(false);
            this->ui->comboBox->setVisible(false);
            this->ui->comboBox_2->setVisible(false);
            this->ui->comboBox_3->setVisible(false);
            this->ui->comboBox_4->setVisible(false);
            this->ui->comboBox_5->setVisible(false);
            this->ui->comboBox_6->setVisible(false);
            this->ui->comboBox_7->setVisible(false);
            this->ui->comboBox_8->setVisible(false);
            this->ui->comboBox_9->setVisible(false);
            this->ui->comboBox_10->setVisible(false);
            this->ui->comboBox_11->setVisible(false);
            this->ui->lineEdit_11->setVisible(false);
            this->ui->doubleSpinBox->setVisible(false);
            this->ui->doubleSpinBox_2->setVisible(false);
            this->ui->lineEdit->setVisible(false);
            this->ui->lineEdit_2->setVisible(false);
            this->ui->lineEdit_3->setVisible(false);
            this->ui->lineEdit_4->setVisible(false);
            this->ui->lineEdit_5->setVisible(false);
            this->ui->lineEdit_6->setVisible(false);
            this->ui->lineEdit_7->setVisible(false);
            this->ui->lineEdit_8->setVisible(false);
            this->ui->lineEdit_9->setVisible(false);
            this->ui->lineEdit_10->setVisible(false);
            this->ui->dateEdit->setVisible(false);
            this->ui->tabWidget->setVisible(false);
            this->resize(800,600);
            this->ui->menubar->setVisible(true);
            this->ui->frame->setVisible(true);
            this->setWindowTitle("Учащиеся");
            this->ui->comboBox_13->setVisible(false);
            //Запрет на изменение данных
            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            //Присваивание переменной номера админа
            user_num =1;
        }else
        {
            QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
    }
}

//Вход в программу под пользователем
void form1::on_pushButton_10_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString userlogin = model->data(model->index(1, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->loginTextBox_2->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(userlogin == qstr)
    {
        //Таже процедура для файла с паролем
        model = new QSqlTableModel(this,sdb);
        model->setTable("autorize");
        model->select();
        //Присваиваем переменной значение логина из базы данных
        QString userpassword = model->data(model->index(1, 2)).toString();
        QString textBoxPassword = ui->passwordTextBox_2->text();
        //Конвертируем текст из QString в String
        std::string convText = textBoxPassword.toStdString();
        //Шифруем конвертируемый текст
        std::string encryptText = encrypt(convText);
        //Конвертируем зашифрованный текст обратно в QString
        QString qstr = QString::fromStdString(encryptText);
        if(userpassword==qstr)
        {
            //Прячем функционал который будет недоступен простому юзеру
            this->ui->pushButton->hide();
            this->ui->menu_17->menuAction()->setVisible(false);
            this->ui->action->setVisible(false);
            this->ui->action_11->setVisible(false);
            this->ui->action_2->setVisible(false);
            this->ui->pushButton_3->setVisible(false);
            this->ui->action_4->setVisible(false);
            this->ui->action_5->setVisible(false);
            this->ui->pushButton_2->move(0,0);
            this->ui->pushButton_4->move(92,0);
            this->ui->pushButton_4->setVisible(false);
            this->ui->pushButton_3->move(628,0);
            this->ui->pushButton_6->move(628,0);
            this->ui->pushButton_7->setVisible(false);
            this->ui->pushButton_8->setVisible(false);
            this->ui->label->setVisible(false);
            this->ui->label_2->setVisible(false);
            this->ui->label_3->setVisible(false);
            this->ui->label_4->setVisible(false);
            this->ui->label_5->setVisible(false);
            this->ui->label_6->setVisible(false);
            this->ui->label_8->setVisible(false);
            this->ui->label_9->setVisible(false);
            this->ui->label_10->setVisible(false);
            this->ui->label_11->setVisible(false);
            this->ui->label_12->setVisible(false);
            this->ui->label_13->setVisible(false);
            this->ui->label_14->setVisible(false);
            this->ui->label_15->setVisible(false);
            this->ui->label_16->setVisible(false);
            this->ui->label_17->setVisible(false);
            this->ui->label_18->setVisible(false);
            this->ui->label_19->setVisible(false);
            this->ui->label_20->setVisible(false);
            this->ui->label_21->setVisible(false);
            this->ui->label_22->setVisible(false);
            this->ui->label_23->setVisible(false);
            this->ui->label_24->setVisible(false);
            this->ui->label_25->setVisible(false);
            this->ui->label_26->setVisible(false);
            this->ui->label_27->setVisible(false);
            this->ui->comboBox->setVisible(false);
            this->ui->comboBox_2->setVisible(false);
            this->ui->comboBox_3->setVisible(false);
            this->ui->comboBox_4->setVisible(false);
            this->ui->comboBox_5->setVisible(false);
            this->ui->comboBox_6->setVisible(false);
            this->ui->comboBox_7->setVisible(false);
            this->ui->comboBox_8->setVisible(false);
            this->ui->comboBox_9->setVisible(false);
            this->ui->comboBox_10->setVisible(false);
            this->ui->comboBox_11->setVisible(false);
            this->ui->lineEdit_11->setVisible(false);
            this->ui->doubleSpinBox->setVisible(false);
            this->ui->doubleSpinBox_2->setVisible(false);
            this->ui->lineEdit->setVisible(false);
            this->ui->lineEdit_2->setVisible(false);
            this->ui->lineEdit_3->setVisible(false);
            this->ui->lineEdit_4->setVisible(false);
            this->ui->lineEdit_5->setVisible(false);
            this->ui->lineEdit_6->setVisible(false);
            this->ui->lineEdit_7->setVisible(false);
            this->ui->lineEdit_8->setVisible(false);
            this->ui->lineEdit_9->setVisible(false);
            this->ui->lineEdit_10->setVisible(false);
            this->ui->dateEdit->setVisible(false);
            this->statusBar()->showMessage(tr("Ваш текущий профиль: Пользователь"));
            this->ui->tableView->resize(800,521);
            this->ui->tabWidget->setVisible(false);
            this->resize(800,600);
            this->ui->menubar->setVisible(true);
            this->ui->frame->setVisible(true);
            this->setWindowTitle("Учащиеся");
            this->ui->comboBox_13->setVisible(false);
            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui->pushButton_2->move(0,0);
            this->ui->pushButton_5->move(92,0);
            //Присваивание переменной номера пользователя
            user_num =2;
        }else
        {
            QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
    }
}

//Заполнение комбобокса городами при выборе области
void form1::on_comboBox_9_currentIndexChanged(int index)
{
    //Области
    QString brestskaya = "Брестская";
    QString vitebskaya = "Витебская";
    QString gomelskaya = "Гомельская";
    QString grodnenskaya = "Гродненская";
    QString minskaya = "Минская";
    QString mogilevskaya = "Могилевская";
    //Присваивание переменной выбранного значения
    QString oblast =ui->comboBox_9->itemText(index);
    //Брестская
    if(oblast == brestskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Брест",1);
        ui->comboBox_10->addItem("Барановичи",2);
        ui->comboBox_10->addItem("Пинск",3);
        ui->comboBox_10->addItem("Кобрин",4);
        ui->comboBox_10->addItem("Берёза",5);
        ui->comboBox_10->addItem("Лунинец",6);
        ui->comboBox_10->addItem("Ивацевичи",7);
        ui->comboBox_10->addItem("Пружаны",8);
        ui->comboBox_10->addItem("Иваново",9);
        ui->comboBox_10->addItem("Дрогичин",10);
        ui->comboBox_10->addItem("Ганцевичи",11);
        ui->comboBox_10->addItem("Жабинка",12);
        ui->comboBox_10->addItem("Микашевичи",13);
        ui->comboBox_10->addItem("Белоозёрск",14);
        ui->comboBox_10->addItem("Столин",15);
        ui->comboBox_10->addItem("Малорита",16);
        ui->comboBox_10->addItem("Ляховичи",17);
        ui->comboBox_10->addItem("Каменец",18);
        ui->comboBox_10->addItem("Давид-Городок",19);
        ui->comboBox_10->addItem("Высокое",20);
        ui->comboBox_10->addItem("Коссово",21);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Барановичский",1);
        ui->comboBox_11->addItem("Берёзовский",2);
        ui->comboBox_11->addItem("Брестский",3);
        ui->comboBox_11->addItem("Брест - Ленинский",4);
        ui->comboBox_11->addItem("Брест - Московский",5);
        ui->comboBox_11->addItem("Ганцевичский",6);
        ui->comboBox_11->addItem("Дрогичинский",7);
        ui->comboBox_11->addItem("Жабинковский",8);
        ui->comboBox_11->addItem("Ивановский",9);
        ui->comboBox_11->addItem("Ивацевичский",10);
        ui->comboBox_11->addItem("Каменецкий",11);
        ui->comboBox_11->addItem("Кобринский",12);
        ui->comboBox_11->addItem("Лунинецкий",13);
        ui->comboBox_11->addItem("Ляховичский",14);
        ui->comboBox_11->addItem("Малоритский",15);
        ui->comboBox_11->addItem("Пинский",16);
        ui->comboBox_11->addItem("Пружанский",17);
        ui->comboBox_11->addItem("Столинский",18);
    }
    //Витебская
    if(oblast == vitebskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Витебск",1);
        ui->comboBox_10->addItem("Орша",2);
        ui->comboBox_10->addItem("Новополоцк",3);
        ui->comboBox_10->addItem("Полоцк",4);
        ui->comboBox_10->addItem("Поставы",5);
        ui->comboBox_10->addItem("Глубокое",6);
        ui->comboBox_10->addItem("Лепель",7);
        ui->comboBox_10->addItem("Новолукомль",8);
        ui->comboBox_10->addItem("Городок",9);
        ui->comboBox_10->addItem("Барань",10);
        ui->comboBox_10->addItem("Толочин",11);
        ui->comboBox_10->addItem("Браслав",12);
        ui->comboBox_10->addItem("Чашники",13);
        ui->comboBox_10->addItem("Миоры",14);
        ui->comboBox_10->addItem("Дубровно",15);
        ui->comboBox_10->addItem("Сенно",16);
        ui->comboBox_10->addItem("Верхнедвинск",17);
        ui->comboBox_10->addItem("Докшицы",18);
        ui->comboBox_10->addItem("Дисна",19);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Бешенковичский",1);
        ui->comboBox_11->addItem("Браславский",2);
        ui->comboBox_11->addItem("Верхнедвинский",3);
        ui->comboBox_11->addItem("Витебский",4);
        ui->comboBox_11->addItem("Витебск - Железнодорожный",5);
        ui->comboBox_11->addItem("Витебск - Первомайский",6);
        ui->comboBox_11->addItem("Витебск - Октябрьский",7);
        ui->comboBox_11->addItem("Глубокский",8);
        ui->comboBox_11->addItem("Городокский",9);
        ui->comboBox_11->addItem("Докшицкий",10);
        ui->comboBox_11->addItem("Дубровенский",11);
        ui->comboBox_11->addItem("Лепельский",12);
        ui->comboBox_11->addItem("Лиозненский",13);
        ui->comboBox_11->addItem("Миорский",14);
        ui->comboBox_11->addItem("Оршанский",15);
        ui->comboBox_11->addItem("Полоцкий",16);
        ui->comboBox_11->addItem("Поставский",17);
        ui->comboBox_11->addItem("Россонский",18);
        ui->comboBox_11->addItem("Сенненский",19);
        ui->comboBox_11->addItem("Толочинский",20);
        ui->comboBox_11->addItem("Ушачский",21);
        ui->comboBox_11->addItem("Чашникский",22);
        ui->comboBox_11->addItem("Шарковщинский",23);
        ui->comboBox_11->addItem("Шумилинский",24);
    }
    //Гомельская
    if(oblast == gomelskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Гомель",1);
        ui->comboBox_10->addItem("Мозырь",2);
        ui->comboBox_10->addItem("Жлобин",3);
        ui->comboBox_10->addItem("Светлогорск",4);
        ui->comboBox_10->addItem("Речица",5);
        ui->comboBox_10->addItem("Калинковичи",6);
        ui->comboBox_10->addItem("Рогачёв",7);
        ui->comboBox_10->addItem("Добруш",8);
        ui->comboBox_10->addItem("Житковичи",9);
        ui->comboBox_10->addItem("Хойники",10);
        ui->comboBox_10->addItem("Петриков",11);
        ui->comboBox_10->addItem("Ельск",12);
        ui->comboBox_10->addItem("Буда-Кошелёво",13);
        ui->comboBox_10->addItem("Наровля",14);
        ui->comboBox_10->addItem("Ветка",15);
        ui->comboBox_10->addItem("Чечерск",16);
        ui->comboBox_10->addItem("Василевичи",17);
        ui->comboBox_10->addItem("Туров",18);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Брагинский",1);
        ui->comboBox_11->addItem("Буда-Кошелевский",2);
        ui->comboBox_11->addItem("Ветковский",3);
        ui->comboBox_11->addItem("Гомельский",4);
        ui->comboBox_11->addItem("Гомель - Новебелицкий",5);
        ui->comboBox_11->addItem("Гомель - Советский",6);
        ui->comboBox_11->addItem("Гомель - Центральный",7);
        ui->comboBox_11->addItem("Добрушский",8);
        ui->comboBox_11->addItem("Ельский",9);
        ui->comboBox_11->addItem("Житковичский",10);
        ui->comboBox_11->addItem("Жлобинский",11);
        ui->comboBox_11->addItem("Калинковичский",12);
        ui->comboBox_11->addItem("Кормянский",13);
        ui->comboBox_11->addItem("Лельчицкий",14);
        ui->comboBox_11->addItem("Лоевский",15);
        ui->comboBox_11->addItem("Мозырский",16);
        ui->comboBox_11->addItem("Наровлянский",17);
        ui->comboBox_11->addItem("Октябрьский",18);
        ui->comboBox_11->addItem("Петриковский",19);
        ui->comboBox_11->addItem("Речицкий",20);
        ui->comboBox_11->addItem("Рогачевский",21);
        ui->comboBox_11->addItem("Светлогорский",22);
        ui->comboBox_11->addItem("Хойникский",23);
        ui->comboBox_11->addItem("Чечерский",24);
    }
    //Гродненская
    if(oblast == grodnenskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Гродно",1);
        ui->comboBox_10->addItem("Лида",2);
        ui->comboBox_10->addItem("Слоним",3);
        ui->comboBox_10->addItem("Волковыск",4);
        ui->comboBox_10->addItem("Сморгонь",5);
        ui->comboBox_10->addItem("Новогрудок",6);
        ui->comboBox_10->addItem("Мосты",7);
        ui->comboBox_10->addItem("Щучин",8);
        ui->comboBox_10->addItem("Ошмяны",9);
        ui->comboBox_10->addItem("Скидель",10);
        ui->comboBox_10->addItem("Берёзовка",11);
        ui->comboBox_10->addItem("Островец",12);
        ui->comboBox_10->addItem("Ивье",13);
        ui->comboBox_10->addItem("Дятлово",14);
        ui->comboBox_10->addItem("Свислочь",15);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Берестовицкий",1);
        ui->comboBox_11->addItem("Волковысский",2);
        ui->comboBox_11->addItem("Вороновский",3);
        ui->comboBox_11->addItem("Гродненский",4);
        ui->comboBox_11->addItem("Гродно - Ленинский",5);
        ui->comboBox_11->addItem("Гродно - Октябрьский",6);
        ui->comboBox_11->addItem("Дятловский",7);
        ui->comboBox_11->addItem("Зельвенский",8);
        ui->comboBox_11->addItem("Ивьевский",9);
        ui->comboBox_11->addItem("Кореличский",10);
        ui->comboBox_11->addItem("Лидский",11);
        ui->comboBox_11->addItem("Мостовский",12);
        ui->comboBox_11->addItem("Новогрудский",13);
        ui->comboBox_11->addItem("Островецкий",14);
        ui->comboBox_11->addItem("Ошмянский",15);
        ui->comboBox_11->addItem("Свислочский",16);
        ui->comboBox_11->addItem("Слонимский",17);
        ui->comboBox_11->addItem("Сморгонский",18);
        ui->comboBox_11->addItem("Щучинский",19);
    }
    //Минская
    if(oblast == minskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Минск",1);
        ui->comboBox_10->addItem("Борисов",2);
        ui->comboBox_10->addItem("Солигорск",3);
        ui->comboBox_10->addItem("Молодечно",4);
        ui->comboBox_10->addItem("Жодино",5);
        ui->comboBox_10->addItem("Слуцк",6);
        ui->comboBox_10->addItem("Вилейка",7);
        ui->comboBox_10->addItem("Дзержинск",8);
        ui->comboBox_10->addItem("Марьина Горка",9);
        ui->comboBox_10->addItem("Столбцы",10);
        ui->comboBox_10->addItem("Смолевичи",11);
        ui->comboBox_10->addItem("Несвиж",12);
        ui->comboBox_10->addItem("Заславль",13);
        ui->comboBox_10->addItem("Фаниполь",14);
        ui->comboBox_10->addItem("Березино",15);
        ui->comboBox_10->addItem("Любань",16);
        ui->comboBox_10->addItem("Старые Дороги",17);
        ui->comboBox_10->addItem("Логойск",18);
        ui->comboBox_10->addItem("Клецк",19);
        ui->comboBox_10->addItem("Воложин",20);
        ui->comboBox_10->addItem("Узда",21);
        ui->comboBox_10->addItem("Червень",22);
        ui->comboBox_10->addItem("Копыль",23);
        ui->comboBox_10->addItem("Крупки",24);
        ui->comboBox_10->addItem("Мядель",25);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Березинский",1);
        ui->comboBox_11->addItem("Борисовский",2);
        ui->comboBox_11->addItem("Вилейский",3);
        ui->comboBox_11->addItem("Воложинский",4);
        ui->comboBox_11->addItem("Дзержинский",5);
        ui->comboBox_11->addItem("Клецкий",6);
        ui->comboBox_11->addItem("Копыльский",7);
        ui->comboBox_11->addItem("Крупский",8);
        ui->comboBox_11->addItem("Логойский",9);
        ui->comboBox_11->addItem("Любанский",10);
        ui->comboBox_11->addItem("Минский",11);
        ui->comboBox_11->addItem("Минск - Заводской",12);
        ui->comboBox_11->addItem("Минск - Ленинский",13);
        ui->comboBox_11->addItem("Минск - Московский",14);
        ui->comboBox_11->addItem("Минск - Октябрьский",15);
        ui->comboBox_11->addItem("Минск - Партизанский",16);
        ui->comboBox_11->addItem("Минск - Первомайский",17);
        ui->comboBox_11->addItem("Минск - Советский",18);
        ui->comboBox_11->addItem("Минск - Фрунзенский",19);
        ui->comboBox_11->addItem("Минск - Центральный",20);
        ui->comboBox_11->addItem("Молодечненский",21);
        ui->comboBox_11->addItem("Мядельский",22);
        ui->comboBox_11->addItem("Несвижский",23);
        ui->comboBox_11->addItem("Пуховичский",24);
        ui->comboBox_11->addItem("Слуцкий",25);
        ui->comboBox_11->addItem("Смолевичский",26);
        ui->comboBox_11->addItem("Солигорский",27);
        ui->comboBox_11->addItem("Стародорожский",28);
        ui->comboBox_11->addItem("Столбцовский",29);
        ui->comboBox_11->addItem("Узденский",30);
        ui->comboBox_11->addItem("Червенский",31);
    }
    //Могилевская
    if(oblast == mogilevskaya)
    {
        //Города
        ui->comboBox_10->clear();
        ui->comboBox_11->clear();
        ui->comboBox_10->addItem("",0);
        ui->comboBox_10->addItem("Могилёв",1);
        ui->comboBox_10->addItem("Бобруйск",2);
        ui->comboBox_10->addItem("Горки",3);
        ui->comboBox_10->addItem("Осиповичи",4);
        ui->comboBox_10->addItem("Кричев",5);
        ui->comboBox_10->addItem("Быхов",6);
        ui->comboBox_10->addItem("Климовичи",7);
        ui->comboBox_10->addItem("Шклов",8);
        ui->comboBox_10->addItem("Костюковичи",9);
        ui->comboBox_10->addItem("Чаусы",10);
        ui->comboBox_10->addItem("Мстиславль",11);
        ui->comboBox_10->addItem("Белыничи",12);
        ui->comboBox_10->addItem("Кировск",13);
        ui->comboBox_10->addItem("Чериков",14);
        ui->comboBox_10->addItem("Славгород",15);
        ui->comboBox_10->addItem("Круглое",16);
        ui->comboBox_10->addItem("Кличев",17);
        //Районы
        ui->comboBox_11->addItem("",0);
        ui->comboBox_11->addItem("Белыничский",1);
        ui->comboBox_11->addItem("Бобруйский",2);
        ui->comboBox_11->addItem("Бобруйск - Ленинский",3);
        ui->comboBox_11->addItem("Бобруйск - Первомайский",4);
        ui->comboBox_11->addItem("Быховский",5);
        ui->comboBox_11->addItem("Глусский",6);
        ui->comboBox_11->addItem("Горецкий",7);
        ui->comboBox_11->addItem("Дрибинский",8);
        ui->comboBox_11->addItem("Кировский",9);
        ui->comboBox_11->addItem("Климовичский",10);
        ui->comboBox_11->addItem("Кличевский",11);
        ui->comboBox_11->addItem("Костюковичский",12);
        ui->comboBox_11->addItem("Краснопольский",13);
        ui->comboBox_11->addItem("Кричевский",14);
        ui->comboBox_11->addItem("Круглянский",15);
        ui->comboBox_11->addItem("Могилевский",16);
        ui->comboBox_11->addItem("Могилев - Ленинский",17);
        ui->comboBox_11->addItem("Могилев - Октябрьский",18);
        ui->comboBox_11->addItem("Мстиславский",19);
        ui->comboBox_11->addItem("Осиповичский",20);
        ui->comboBox_11->addItem("Славгородский",21);
        ui->comboBox_11->addItem("Хотимский",22);
        ui->comboBox_11->addItem("Чаусский",23);
        ui->comboBox_11->addItem("Чериковский",24);
        ui->comboBox_11->addItem("Шкловский",25);
    }
}

//Увеличение выделенной ячейки
void form1::on_pushButton_11_clicked()
{
    //Получение данных из выделенной ячейки
    QString s = model->data(model->index(ui->tableView->currentIndex().row(), ui->tableView->currentIndex().column())).toString();
    QMessageBox::information(this,"Просмотр",s,QMessageBox::Ok);
}

//Отчисление
void form1::on_pushButton_clicked()
{
    this->ui->widget->setVisible(true);
    this->ui->widget->move(0,0);
    this->ui->pushButton->setVisible(false);
}

//Показывает таблицу с отчисленными студентами
void form1::on_action_12_triggered()
{
    if(user_num == 1)
    {
        this->ui->action_3->setVisible(false);
        this->ui->pushButton->setVisible(false);
        this->ui->pushButton_2->move(0,0);
        this->ui->pushButton_5->move(92,0);
        this->ui->pushButton_4->setVisible(false);
        num_table =2;
        //Обновление таблицы с данными
        model = new QSqlTableModel(this,sdb);
        model->setTable("otchislen");
        model->select();
        ui->tableView->setModel(model);
        this->statusBar()->showMessage(tr("Просмотр отчисленных студентов"));
    }
    if(user_num == 2)
    {
        this->ui->action_3->setVisible(false);
        this->ui->pushButton->setVisible(false);
        this->ui->pushButton_2->move(0,0);
        this->ui->pushButton_5->move(92,0);
        this->ui->pushButton_4->setVisible(false);
        num_table =2;
        //Обновление таблицы с данными
        model = new QSqlTableModel(this,sdb);
        model->setTable("otchislen");
        model->select();
        ui->tableView->setModel(model);
        this->statusBar()->showMessage(tr("Просмотр отчисленных студентов"));
    }

}

//Показывает всех неотчисленных студентов
void form1::on_action_10_triggered()
{
    if(user_num == 1)
    {
        this->ui->action_3->setVisible(true);
        this->ui->pushButton->setVisible(true);
        this->ui->pushButton_4->setVisible(true);
        this->ui->pushButton_2->move(170,0);
        this->ui->pushButton_5->move(370,0);
        num_table =1;
        //Обновление таблицы с данными
        model = new QSqlTableModel(this,sdb);
        model->setTable("my_table");
        model->select();
        ui->tableView->setModel(model);
        this->statusBar()->showMessage(tr("Просмотр всей базы данных"));
    }
    if(user_num == 2)
    {
        this->ui->action_3->setVisible(false);
        this->ui->pushButton->setVisible(false);
        this->ui->pushButton_4->setVisible(false);
        this->ui->pushButton_2->move(0,0);
        this->ui->pushButton_5->move(92,0);
        num_table =1;
        //Обновление таблицы с данными
        model = new QSqlTableModel(this,sdb);
        model->setTable("my_table");
        model->select();
        ui->tableView->setModel(model);
        this->statusBar()->showMessage(tr("Просмотр всей базы данных"));
    }
}

//Отчислить
void form1::on_pushButton_12_clicked()
{
    //Получение данных из колонок выделенной строки строки
    model = new QSqlTableModel(this,sdb);
    model->setTable("my_table");
    model->select();
    QString a1 = model->data(model->index(this->ui->tableView->currentIndex().row(), 1)).toString();
    QString a2 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 2)).toString();
    QString a3 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 3)).toString();
    QString a4 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 4)).toString();
    QString a5 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 5)).toString();
    QString a6 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 6)).toString();
    QString a7 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 7)).toString();
    QString a8 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 8)).toString();
    QString a9 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 9)).toString();
    QString a10 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 10)).toString();
    QString a11 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 11)).toString();
    QString a12 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 12)).toString();
    QString a13 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 13)).toString();
    QString a14 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 14)).toString();
    QString a15 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 15)).toString();
    QString a16 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 16)).toString();
    QString a17 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 17)).toString();
    QString a18 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 18)).toString();
    QString a19 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 19)).toString();
    QString a20 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 20)).toString();
    QString a21 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 21)).toString();
    QString a22 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 22)).toString();
    QString a23 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 23)).toString();
    QString a24 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 24)).toString();
    QString a25 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 25)).toString();
    QString a26 = model->data(this->model->index(this->ui->tableView->currentIndex().row(), 26)).toString();
    //Удаление отчисленного студента из основной таблицы
    model = new QSqlTableModel(this,sdb);
    model->setTable("my_table");
    model->select();
    model->removeRow(row);
    //Обновление таблицы с данными
    model = new QSqlTableModel(this,sdb);
    model->setTable("otchislen");
    model->select();
    //Вставка пустой строки
    model->insertRow(row);
    //Вставка данных
    model->setData(model->index(row, 1), a1);
    model->setData(model->index(row, 2), a2);
    model->setData(model->index(row, 3), a3);
    model->setData(model->index(row, 4), a4);
    model->setData(model->index(row, 5), a5);
    model->setData(model->index(row, 6), a6);
    model->setData(model->index(row, 7), a7);
    model->setData(model->index(row, 8), a8);
    model->setData(model->index(row, 9), a9);
    model->setData(model->index(row, 10), a10);
    model->setData(model->index(row, 11), a11);
    model->setData(model->index(row, 12), a12);
    model->setData(model->index(row, 13), a13);
    model->setData(model->index(row, 14), a14);
    model->setData(model->index(row, 15), a15);
    model->setData(model->index(row, 16), a16);
    model->setData(model->index(row, 17), a17);
    model->setData(model->index(row, 18), a18);
    model->setData(model->index(row, 19), a19);
    model->setData(model->index(row, 20), a20);
    model->setData(model->index(row, 21), a21);
    model->setData(model->index(row, 22), a22);
    model->setData(model->index(row, 23), a23);
    model->setData(model->index(row, 24), a24);
    model->setData(model->index(row, 25), a25);
    model->setData(model->index(row, 26), a26);
    model->setData(model->index(row, 27), this->ui->lineEdit_12->text());
    model->setData(model->index(row, 28), this->ui->dateEdit_2->text());
    //Подтверждение вставки
    model->submitAll();
    //Отображение данных
    model->select();
    this->ui->tableView->setModel(model);
    //Вывод данных в статусбар
    this->statusBar()->showMessage(tr("Студент отчислен"));
    //Скрытие ненужных элементов
    this->ui->widget->setVisible(false);
    this->ui->pushButton_4->setVisible(false);
    this->ui->lineEdit_12->clear();
    this->ui->dateEdit_2->clear();
}

//Отмена отчисления
void form1::on_pushButton_13_clicked()
{
    this->ui->pushButton->setVisible(true);
    this->ui->widget->setVisible(true);
    this->ui->lineEdit_12->clear();
    this->ui->dateEdit_2->clear();
    this->ui->widget->setVisible(false);
}

//Разблокировка сесии от администратора
void form1::on_pushButton_14_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString login = model->data(model->index(0, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->loginTextBox_3->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(login == qstr)
    {
        model = new QSqlTableModel(this,sdb);
        model->setTable("autorize");
        model->select();
        //Присваиваем переменной значение логина из базы данных
        QString password = model->data(model->index(0, 2)).toString();
        QString textBoxPassword = ui->passwordTextBox_3->text();
        //Конвертируем текст из QString в String
        std::string convText = textBoxPassword.toStdString();
        //Шифруем конвертируемый текст
        std::string encryptText = encrypt(convText);
        //Конвертируем зашифрованный текст обратно в QString
        QString qstr = QString::fromStdString(encryptText);
        if(password==qstr)
        {
            //Указываем в статус баре профиль(Администратор/Пользователь)
            this->statusBar()->showMessage(tr("Сессия востановлена, ваш текущий профиль: Администратор"));
            //Скрываем ненужные элементы
            this->ui->pushButton_6->setVisible(false);
            this->ui->tableView->resize(800,521);
            this->ui->pushButton_7->setVisible(false);
            this->ui->pushButton_8->setVisible(false);
            this->ui->label->setVisible(false);
            this->ui->label_2->setVisible(false);
            this->ui->label_3->setVisible(false);
            this->ui->label_4->setVisible(false);
            this->ui->label_5->setVisible(false);
            this->ui->label_6->setVisible(false);
            this->ui->label_8->setVisible(false);
            this->ui->label_9->setVisible(false);
            this->ui->label_10->setVisible(false);
            this->ui->label_11->setVisible(false);
            this->ui->label_12->setVisible(false);
            this->ui->label_13->setVisible(false);
            this->ui->label_14->setVisible(false);
            this->ui->label_15->setVisible(false);
            this->ui->label_16->setVisible(false);
            this->ui->label_17->setVisible(false);
            this->ui->label_18->setVisible(false);
            this->ui->label_19->setVisible(false);
            this->ui->label_20->setVisible(false);
            this->ui->label_21->setVisible(false);
            this->ui->label_22->setVisible(false);
            this->ui->label_23->setVisible(false);
            this->ui->label_24->setVisible(false);
            this->ui->label_25->setVisible(false);
            this->ui->label_26->setVisible(false);
            this->ui->label_27->setVisible(false);
            this->ui->comboBox->setVisible(false);
            this->ui->comboBox_2->setVisible(false);
            this->ui->comboBox_3->setVisible(false);
            this->ui->comboBox_4->setVisible(false);
            this->ui->comboBox_5->setVisible(false);
            this->ui->comboBox_6->setVisible(false);
            this->ui->comboBox_7->setVisible(false);
            this->ui->comboBox_8->setVisible(false);
            this->ui->comboBox_9->setVisible(false);
            this->ui->comboBox_10->setVisible(false);
            this->ui->comboBox_11->setVisible(false);
            this->ui->lineEdit_11->setVisible(false);
            this->ui->doubleSpinBox->setVisible(false);
            this->ui->doubleSpinBox_2->setVisible(false);
            this->ui->comboBox_13->setVisible(false);
            this->ui->lineEdit->setVisible(false);
            this->ui->lineEdit_2->setVisible(false);
            this->ui->lineEdit_3->setVisible(false);
            this->ui->lineEdit_4->setVisible(false);
            this->ui->lineEdit_5->setVisible(false);
            this->ui->lineEdit_6->setVisible(false);
            this->ui->lineEdit_7->setVisible(false);
            this->ui->lineEdit_8->setVisible(false);
            this->ui->lineEdit_9->setVisible(false);
            this->ui->lineEdit_10->setVisible(false);
            this->ui->dateEdit->setVisible(false);
            this->ui->tabWidget->setVisible(false);
            this->resize(800,600);
            this->ui->menubar->setVisible(true);
            this->ui->frame->setVisible(true);
            this->setWindowTitle("Учащиеся");
            this->ui->widget_2->setVisible(false);
            this->ui->loginTextBox_3->clear();
            this->ui->passwordTextBox_3->clear();
            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }else
        {
            QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
            //Закрываем файл и поток
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
        //Закрываем файл и поток
    }
}

//Разблокировка сесии от пользователя
void form1::on_pushButton_15_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString userlogin = model->data(model->index(1, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->loginTextBox_4->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(userlogin == qstr)
    {
        model = new QSqlTableModel(this,sdb);
        model->setTable("autorize");
        model->select();
        //Присваиваем переменной значение логина из базы данных
        QString userpassword = model->data(model->index(1, 2)).toString();
        QString textBoxPassword = ui->passwordTextBox_4->text();
        //Конвертируем текст из QString в String
        std::string convText = textBoxPassword.toStdString();
        //Шифруем конвертируемый текст
        std::string encryptText = encrypt(convText);
        //Конвертируем зашифрованный текст обратно в QString
        QString qstr = QString::fromStdString(encryptText);
        if(userpassword==qstr)
        {
            //Прячем функционал который будет недоступен простому юзеру
            this->ui->pushButton->hide();
            this->ui->menu_17->menuAction()->setVisible(false);
            this->ui->action->setVisible(false);
            this->ui->action_11->setVisible(false);
            this->ui->action_2->setVisible(false);
            this->ui->pushButton_3->setVisible(false);
            this->ui->pushButton_4->setVisible(false);
            this->ui->action_4->setVisible(false);
            this->ui->action_5->setVisible(false);
            this->ui->pushButton_2->move(0,0);
            this->ui->pushButton_4->move(92,0);
            this->ui->pushButton_5->move(92,0);
            this->ui->pushButton_7->setVisible(false);
            this->ui->pushButton_8->setVisible(false);
            this->ui->label->setVisible(false);
            this->ui->label_2->setVisible(false);
            this->ui->label_3->setVisible(false);
            this->ui->label_4->setVisible(false);
            this->ui->label_5->setVisible(false);
            this->ui->label_6->setVisible(false);
            this->ui->label_8->setVisible(false);
            this->ui->label_9->setVisible(false);
            this->ui->label_10->setVisible(false);
            this->ui->label_11->setVisible(false);
            this->ui->label_12->setVisible(false);
            this->ui->label_13->setVisible(false);
            this->ui->label_14->setVisible(false);
            this->ui->label_15->setVisible(false);
            this->ui->label_16->setVisible(false);
            this->ui->label_17->setVisible(false);
            this->ui->label_18->setVisible(false);
            this->ui->label_19->setVisible(false);
            this->ui->label_20->setVisible(false);
            this->ui->label_21->setVisible(false);
            this->ui->label_22->setVisible(false);
            this->ui->label_23->setVisible(false);
            this->ui->label_24->setVisible(false);
            this->ui->label_25->setVisible(false);
            this->ui->label_26->setVisible(false);
            this->ui->label_27->setVisible(false);
            this->ui->comboBox->setVisible(false);
            this->ui->comboBox_2->setVisible(false);
            this->ui->comboBox_3->setVisible(false);
            this->ui->comboBox_4->setVisible(false);
            this->ui->comboBox_5->setVisible(false);
            this->ui->comboBox_6->setVisible(false);
            this->ui->comboBox_7->setVisible(false);
            this->ui->comboBox_8->setVisible(false);
            this->ui->comboBox_9->setVisible(false);
            this->ui->comboBox_10->setVisible(false);
            this->ui->comboBox_11->setVisible(false);
            this->ui->lineEdit_11->setVisible(false);
            this->ui->doubleSpinBox->setVisible(false);
            this->ui->doubleSpinBox_2->setVisible(false);
            this->ui->comboBox_13->setVisible(false);
            this->ui->lineEdit->setVisible(false);
            this->ui->lineEdit_2->setVisible(false);
            this->ui->lineEdit_3->setVisible(false);
            this->ui->lineEdit_4->setVisible(false);
            this->ui->lineEdit_5->setVisible(false);
            this->ui->lineEdit_6->setVisible(false);
            this->ui->lineEdit_7->setVisible(false);
            this->ui->lineEdit_8->setVisible(false);
            this->ui->lineEdit_9->setVisible(false);
            this->ui->lineEdit_10->setVisible(false);
            this->ui->dateEdit->setVisible(false);
            this->statusBar()->showMessage(tr("Сессия востановлена, ваш текущий профиль: Пользователь"));
            this->ui->tableView->resize(800,521);
            this->ui->tabWidget->setVisible(false);
            this->resize(800,600);
            this->ui->menubar->setVisible(true);
            this->ui->frame->setVisible(true);
            this->setWindowTitle("Учащиеся");
            this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui->widget_3->setVisible(false);
            this->ui->loginTextBox_4->clear();
            this->ui->passwordTextBox_4->clear();
        }else
        {
            QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
            //Закрываем файл и поток
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
        //Закрываем файл и поток
    }
}

//Перевод студентов
void form1::on_pushButton_4_clicked()
{
    ui->widget_8->setVisible(true);
    ui->widget_8->move(0,0);
    //Курсы
    ui->comboBox_12->clear();
    ui->comboBox_12->addItem("-",0);
    ui->comboBox_12->addItem("1",1);
    ui->comboBox_12->addItem("2",2);
    ui->comboBox_12->addItem("3",3);
    ui->comboBox_12->addItem("4",4);
    //Специальности
    ui->comboBox_14->clear();
    ui->comboBox_14->addItem("-",0);
    ui->comboBox_14->addItem("Мелиорация и водное хозяйство",1);
    ui->comboBox_14->addItem("Техническое обеспечение мелиоративных и водохозяйственных работ",2);
    ui->comboBox_14->addItem("Ремонтно-обслуживающее производство в сельском хозяйстве",3);
    ui->comboBox_14->addItem("Промышленное и гражданское строительство",4);
    ui->comboBox_14->addItem("Строительство дорог и транспортных объектов",5);
}

//Подтверждение смены логина администратора
void form1::on_pushButton_16_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString login = model->data(model->index(0, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->lineEdit_15->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(login == qstr)
    {
        if(ui->lineEdit_13->text() == ui->lineEdit_14->text())
        {
            QString t  =ui->lineEdit_13->text();
            //Конвертируем текст из QString в String
            std::string convText = t.toStdString();
            //Шифруем конвертируемый текст
            std::string encryptText = encrypt(convText);
            //Конвертируем зашифрованный текст обратно в QString
            QString qstr = QString::fromStdString(encryptText);
            //Вставка нового логина
            model = new QSqlTableModel(this,sdb);
            model->setTable("autorize");
            model->select();
            model->setData(model->index(0, 1),qstr);
            model->submitAll();
            model->select();
            QMessageBox::StandardButton questions = QMessageBox::information(this,"Успех","Логин изменен",QMessageBox::Yes);
            if(questions ==QMessageBox::Yes)
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Логин администратора изменен"));
                this->ui->widget_4->setVisible(false);
            }else
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Логин администратора изменен"));
                this->ui->widget_4->setVisible(false);
            }
        }else
        {
            QMessageBox::information(this,"Ошибка","Логины не совпадают!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
    }
}

//Отмена смены логина администратора
void form1::on_pushButton_17_clicked()
{
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->widget_4->setVisible(false);
}

//Смена пароля администратора
void form1::on_pushButton_19_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение пароля из базы данных
    QString passw = model->data(model->index(0, 2)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->lineEdit_16->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(passw == qstr)
    {
        if(ui->lineEdit_18->text() == ui->lineEdit_17->text())
        {
            QString t  =ui->lineEdit_18->text();
            //Конвертируем текст из QString в String
            std::string convText = t.toStdString();
            //Шифруем конвертируемый текст
            std::string encryptText = encrypt(convText);
            //Конвертируем зашифрованный текст обратно в QString
            QString qstr = QString::fromStdString(encryptText);
            //Вставка нового пароля
            model = new QSqlTableModel(this,sdb);
            model->setTable("autorize");
            model->select();
            model->setData(model->index(0, 2),qstr);
            model->submitAll();
            model->select();
            QMessageBox::StandardButton questions = QMessageBox::information(this,"Успех","Пароль изменен",QMessageBox::Yes);
            if(questions ==QMessageBox::Yes)
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Пароль администратора изменен"));
                this->ui->widget_5->setVisible(false);
            }else
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Пароль администратора изменен"));
                this->ui->widget_5->setVisible(false);
            }
        }else
        {
            QMessageBox::information(this,"Ошибка","Пароли не совпадают!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
    }
}

//Отмена смены пароля администратора
void form1::on_pushButton_18_clicked()
{
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_18->clear();
    ui->widget_5->setVisible(false);
}

//Смена логина пользователя
void form1::on_pushButton_20_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение логина из базы данных
    QString login = model->data(model->index(1, 1)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->lineEdit_20->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(login == qstr)
    {
        if(ui->lineEdit_19->text() == ui->lineEdit_21->text())
        {
            QString t  =ui->lineEdit_19->text();
            //Конвертируем текст из QString в String
            std::string convText = t.toStdString();
            //Шифруем конвертируемый текст
            std::string encryptText = encrypt(convText);
            //Конвертируем зашифрованный текст обратно в QString
            QString qstr = QString::fromStdString(encryptText);
            //Вставка нового логина
            model = new QSqlTableModel(this,sdb);
            model->setTable("autorize");
            model->select();
            model->setData(model->index(1, 1),qstr);
            model->submitAll();
            model->select();
            QMessageBox::StandardButton questions = QMessageBox::information(this,"Успех","Логин изменен",QMessageBox::Yes);
            if(questions ==QMessageBox::Yes)
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Логин пользователя изменен"));
                this->ui->widget_6->setVisible(false);
            }else
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Логин пользователя изменен"));
                this->ui->widget_6->setVisible(false);
            }
        }else
        {
            QMessageBox::information(this,"Ошибка","Логины не совпадают!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный логин!",QMessageBox::Ok);
    }
}

//Отмена смены логина пользователя
void form1::on_pushButton_21_clicked()
{
    ui->lineEdit_19->clear();
    ui->lineEdit_20->clear();
    ui->lineEdit_21->clear();
    ui->widget_6->setVisible(false);
}

//Отмена смены пароля пользователя
void form1::on_pushButton_23_clicked()
{
    ui->lineEdit_22->clear();
    ui->lineEdit_23->clear();
    ui->lineEdit_24->clear();
    ui->widget_7->setVisible(false);
}

//Смена пароля пользователя
void form1::on_pushButton_22_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("autorize");
    model->select();
    //Присваиваем переменной значение пароля из базы данных
    QString passw = model->data(model->index(1, 2)).toString();
    //Присваеваем переменной значение LineEdit
    QString textBoxLogin = ui->lineEdit_24->text();
    //Конвертируем текст из QString в String
    std::string convText = textBoxLogin.toStdString();
    //Шифруем конвертируемый текст
    std::string encryptText = encrypt(convText);
    //Конвертируем зашифрованный текст обратно в QString
    QString qstr = QString::fromStdString(encryptText);
    //Сравниваем значения
    if(passw == qstr)
    {
        if(ui->lineEdit_22->text() == ui->lineEdit_23->text())
        {
            QString t  =ui->lineEdit_22->text();
            //Конвертируем текст из QString в String
            std::string convText = t.toStdString();
            //Шифруем конвертируемый текст
            std::string encryptText = encrypt(convText);
            //Конвертируем зашифрованный текст обратно в QString
            QString qstr = QString::fromStdString(encryptText);
            //Вставка нового пароля
            model = new QSqlTableModel(this,sdb);
            model->setTable("autorize");
            model->select();
            model->setData(model->index(1, 2),qstr);
            model->submitAll();
            model->select();
            QMessageBox::StandardButton questions = QMessageBox::information(this,"Успех","Пароль изменен",QMessageBox::Yes);
            if(questions ==QMessageBox::Yes)
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Пароль пользователя изменен"));
                this->ui->widget_7->setVisible(false);
            }else
            {
                //Вывод данных в статусбар
                this->statusBar()->showMessage(tr("Пароль пользователя изменен"));
                this->ui->widget_7->setVisible(false);
            }
        }else
        {
            QMessageBox::information(this,"Ошибка","Пароли не совпадают!",QMessageBox::Ok);
        }
    }else
    {
        QMessageBox::information(this,"Ошибка","Неверный пароль!",QMessageBox::Ok);
    }
}

//Изменить данные в таблице
void form1::on_action_7_triggered()
{
    this->statusBar()->showMessage(tr("Изменение данных разрешено!!!"));
    this->ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

//Сортировка по специальностям
//Мелиорация и водное хозяйство 1 курс
void form1::on_action1_5_triggered()
{

}

//Мелиорация и водное хозяйство 2 курс
void form1::on_action2_4_triggered()
{

}

//Мелиорация и водное хозяйство 3 курс
void form1::on_action3_4_triggered()
{

}

//Мелиорация и водное хозяйство 4 курс
void form1::on_action4_4_triggered()
{

}

//Перевод студента на другой курс или в другую группу
void form1::on_pushButton_24_clicked()
{
    model = new QSqlTableModel(this,sdb);
    model->setTable("my_table");
    model->select();
    //Проверка на пустые поля
    if(ui->lineEdit_25->text() == NULL)
    {
        QMessageBox::information(this,"Внимание","Введите номер приказа!",QMessageBox::Ok);
    }else
    {
        if(ui->lineEdit_26->text() == NULL)
        {
            QMessageBox::information(this,"Внимание","Введите номер группы!",QMessageBox::Ok);
        }else
        {
            //Изменение специальности
            if(ui->comboBox_14->currentText() == "-")
            {
            }
            if(ui->comboBox_14->currentText() == "Мелиорация и водное хозяйство")
            {
                model->setData(model->index(row, 1), ui->comboBox_14->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_14->currentText() == "Техническое обеспечение мелиоративных и водохозяйственных работ")
            {
                model->setData(model->index(row, 1), ui->comboBox_14->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_14->currentText() == "Ремонтно-обслуживающее производство в сельском хозяйстве")
            {
                model->setData(model->index(row, 1), ui->comboBox_14->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_14->currentText() == "Промышленное и гражданское строительство")
            {
                model->setData(model->index(row, 1), ui->comboBox_14->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_14->currentText() == "Строительство дорог и транспортных объектов")
            {
                model->setData(model->index(row, 1), ui->comboBox_14->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            //Изменение курса
            if(ui->comboBox_12->currentText() == "-")
            {
            }
            if(ui->comboBox_12->currentText() == "1")
            {
                model->setData(model->index(row, 4), ui->comboBox_12->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_12->currentText() == "2")
            {
                model->setData(model->index(row, 4), ui->comboBox_12->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_12->currentText() == "3")
            {
                model->setData(model->index(row, 4), ui->comboBox_12->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            if(ui->comboBox_12->currentText() == "4")
            {
                model->setData(model->index(row, 4), ui->comboBox_12->currentText());
                model->submitAll();
                model->select();
                ui->tableView->setModel(model);
            }
            //Вставка номера группы
            model->setData(model->index(row, 5), ui->lineEdit_26->text());
            //Вставка номера приказа
            model->setData(model->index(row, 27), ui->lineEdit_25->text());
            //Вставка даты перевода
            model->setData(model->index(row, 28), ui->dateEdit_3->text());
            model->submitAll();
            model->select();
            ui->tableView->setModel(model);
            ui->widget_8->setVisible(false);
            ui->lineEdit_25->clear();
            ui->lineEdit_26->clear();
            //Вывод данных в статусбар
            this->statusBar()->showMessage(tr("Данные пользователя изменены"));
        }
    }
}

//Отмена перевода студента
void form1::on_pushButton_25_clicked()
{
    ui->widget_8->setVisible(false);
    ui->lineEdit_25->clear();
    ui->lineEdit_26->clear();
}

