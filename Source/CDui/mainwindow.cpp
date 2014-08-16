#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "search.hpp"
#include <QListWidgetItem>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//load dir for makefile
void MainWindow::on_bLoadMakefile_clicked()
{
    ui->bAnalyse->setEnabled(true);
    this->makeDir = QFileDialog::getExistingDirectory(
                this, tr("Open Directory"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
}

void MainWindow::on_bAnalyse_clicked()
{
    ui->bDraw->setEnabled(true);
    ui->lClasses->clear();
    QFile f(QDir::tempPath() + "/readMakeOut");                                 //we have to delete previous sources file
    f.open(QIODevice::WriteOnly | QIODevice::Text);
    f.close();

    QString p1 = QDir::currentPath() + "/readMake";                              //a program to find the sources from 'make' execution (located with this program)
    QString qr = "make CC=" + p1 + " CXX=" + p1 + " -C " + this->makeDir;
    system(qr.toLocal8Bit().data());

    s.findDeps(this->makeDir.toStdString());
    std::string *C = s.getClasses();
    int nC = s.getClassesNum();
    for(int i=0; i<nC; i++) {
        ui->lClasses->addItem(new QListWidgetItem(QString::fromUtf8(C[i].data(), C[i].size())));
    }    
}

void MainWindow::on_bDraw_clicked()
{
    QList<QListWidgetItem*> selectedClasses = ui->lClasses->selectedItems();
    QList<std::string> scstd;
    foreach (QListWidgetItem *it, selectedClasses) {
        scstd.push_back(it->text().toStdString());
    }
    int level = ui->sbLevel->value();
    s.Manage(scstd, level);

    s.showGraph();
}
