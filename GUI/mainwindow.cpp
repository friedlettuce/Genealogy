#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <iostream>
#include <string>
#include "brother.h"
#include <QTableView>
#include <QStackedWidget>
#include <QPushButton>
#include <QTableWidgetItem>
#include <cstring>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    this->setFixedSize(1000, 600);

    // Sets up the main window
    ui->setupUi(this);
    std::string file = path + "crest.png";
    this->setWindowIcon(QIcon(file.c_str()));

    def = palette();
    // Sets background image
    file = path + "flag.png";
    QPixmap bkgnd(file.c_str());
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Background, bkgnd);

    buttons.push_back(ui->search);
    buttons.push_back(ui->classes);
    buttons.push_back(ui->list);
    buttons.push_back(ui->family);
    buttons.push_back(ui->tree);
    buttons.push_back(ui->line);

    // Sets up bro list
    brotherList = new QStandardItemModel(1, 4, this);
}

MainWindow::~MainWindow(){
    delete ui;
    delete brotherList;
}

void MainWindow::setMain(){
    this->setFixedSize(1000, 600);
    this->setWindowTitle("Psi Archive");
    ui->stack->setCurrentIndex(0);
    this->setPalette(background);
}

void MainWindow::on_search_clicked()
{
    this->setWindowTitle("Brother Directory");
    ui->stack->setCurrentIndex(1);
    this->setPalette(def);
    dir = 1;
}

void MainWindow::on_classes_clicked()
{
    this->setWindowTitle("Psi Classes");
    ui->stack->setCurrentIndex(1);
    this->setPalette(def);
    dir = 2;
}

void MainWindow::on_list_clicked()
{
    this->setWindowTitle("Brother List");
    ui->stack->setCurrentIndex(2);
    this->setPalette(def);

    std::vector<brother*> finds;
    directory.getList(finds);

    brotherList->clear();
    brotherList->setHorizontalHeaderItem(0, new QStandardItem(QString("Year")));
    brotherList->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    brotherList->setHorizontalHeaderItem(2, new QStandardItem(QString("Big Brother")));
    brotherList->setHorizontalHeaderItem(3, new QStandardItem(QString("Little Brothers")));

    for(int i = 0; i < finds.size(); ++i){
        QList<QStandardItem*> entry;

        entry.append(new QStandardItem(
            QString::fromStdString(finds[i]->getYear())));
        entry.append(new QStandardItem(
            QString::fromStdString(finds[i]->getName())));
        entry.append(new QStandardItem(
            QString::fromStdString(finds[i]->getBig())));
        entry.append(new QStandardItem(
            QString::fromStdString(finds[i]->getLittles())));

        brotherList->appendRow(entry);
    }
    ui->broDir->setModel(brotherList);
    ui->broDir->resizeColumnsToContents();
    ui->broDir->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_family_clicked()
{
    this->setWindowTitle("Psi Families");
    ui->stack->setCurrentIndex(3);
    this->setPalette(def);
}

void MainWindow::on_tree_clicked()
{
    this->setWindowTitle("Brother Tree");
    ui->stack->setCurrentIndex(4);
    this->setPalette(def);
}

void MainWindow::on_line_clicked()
{
    this->setWindowTitle("Brother Line");
    ui->stack->setCurrentIndex(5);
    this->setPalette(def);
}

void MainWindow::on_back_clicked(){
    brotherList->clear();
    ui->searchBar->clear();
    setMain();
}

void MainWindow::on_searchBar_textEdited(const QString &arg1){
    if(dir == 2)
        return;

    ui->broList->setEditTriggers(QAbstractItemView::AllEditTriggers);
    std::string search = arg1.toLocal8Bit().constData();

    std::vector<brother*> finds;

    if(arg1.length() != 0 && dir == 1)
        directory.getBrother(search, finds);

    brotherList->clear();
    brotherList->setHorizontalHeaderItem(0, new QStandardItem(QString("Year")));
    brotherList->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    brotherList->setHorizontalHeaderItem(2, new QStandardItem(QString("Big Brother")));
    brotherList->setHorizontalHeaderItem(3, new QStandardItem(QString("Little Brothers")));

    for(int i = 0; i < finds.size(); ++i){
        QList<QStandardItem*> entry;

        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getYear())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getName())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getBig())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getLittles())));

        brotherList->appendRow(entry);
    }
    ui->broList->setModel(brotherList);
    ui->broList->resizeColumnsToContents();
    ui->broList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_searchBar_returnPressed()
{
    ui->broList->setEditTriggers(QAbstractItemView::AllEditTriggers);
    QString arg1 = ui->searchBar->text();
    std::string search = arg1.toLocal8Bit().constData();

    std::vector<brother*> finds;

    if(arg1.length() != 0 && dir == 1)
        directory.getBrother(search, finds);
    else if(arg1.length() != 0 && dir == 2){
        directory.searchClass(search, finds);
        directory.searchFamily(search, finds);
    }

    brotherList->clear();
    brotherList->setHorizontalHeaderItem(0, new QStandardItem(QString("Year")));
    brotherList->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    brotherList->setHorizontalHeaderItem(2, new QStandardItem(QString("Big Brother")));
    brotherList->setHorizontalHeaderItem(3, new QStandardItem(QString("Little Brothers")));

    for(int i = 0; i < finds.size(); ++i){
        QList<QStandardItem*> entry;

        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getYear())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getName())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getBig())));
        entry.append(new QStandardItem(
              QString::fromStdString(finds[i]->getLittles())));

        brotherList->appendRow(entry);
    }
    ui->broList->setModel(brotherList);
    ui->broList->resizeColumnsToContents();
    ui->broList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_back1_clicked()
{
    brotherList->clear();
    setMain();
}

void MainWindow::on_back2_clicked(){ setMain(); }
void MainWindow::on_back3_clicked(){ setMain(); }
void MainWindow::on_back4_clicked(){ setMain(); }
