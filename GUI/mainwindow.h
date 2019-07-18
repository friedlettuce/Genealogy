#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "archive.h"
#include <string>
#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QtGui>
#include <fstream>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMain();

private slots:
    // Main slots
    void on_search_clicked();
    void on_classes_clicked();
    void on_list_clicked();
    void on_family_clicked();
    void on_tree_clicked();
    void on_line_clicked();
    // Search slots
    void on_searchBar_textEdited(const QString &arg1);
    void on_searchBar_returnPressed();

    void on_back_clicked();
    void on_back1_clicked();
    void on_back2_clicked();
    void on_back3_clicked();
    void on_back4_clicked();

private:
    Ui::MainWindow *ui;
    archive directory;
    const std::string path = "C:/Users/garet/Documents/Projects/Psi/";

    QPalette def;
    QPalette background;
    std::vector<QPushButton*> buttons;
    QStandardItemModel* brotherList;

    int dir;
};

#endif // MAINWINDOW_H
