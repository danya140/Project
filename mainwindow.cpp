#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"

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

QString input_str;
/*
 * Here goes functions for reading input file
 * and some actions with gathered information
 */
void read_file (){
    QFile file("input.txt");

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"Can't read file",file.errorString());
    } else{
        QTextStream in(&file);
        input_str = in.readAll();
    }

    //input_str = in.readLine();
}

/*
 * Here goes UI functions
 * Just answer button call back
 */
void MainWindow::on_answButt_clicked()
{
    ui->answ->setText("Ответ");
    read_file();
    ui->inp->setText(input_str);
}
