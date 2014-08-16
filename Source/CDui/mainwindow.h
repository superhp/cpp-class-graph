#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "search.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    search s;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bLoadMakefile_clicked();
    void on_bAnalyse_clicked();
    void on_bDraw_clicked();

private:
    QString makeDir;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
