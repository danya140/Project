#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "QDebug"

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
QString str;
int num;
QStringList list;
QStringList chars;

/*
 * Here goes functions for reading input file
 *
 */

void read_file (){
    QFile file("input.txt");
    QRegExp digit("\\d*"); //reg exp for digits

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"Can't read file",file.errorString());
    } else{

        QTextStream in(&file);
        //input_str = in.readAll();

        QString tmp = in.readLine();
        if(tmp.isEmpty() || !digit.exactMatch(tmp) || tmp.length()>=4){ // TODO: better use switch
            QMessageBox::information(0,"Error","N is empty or not a digit or bigger than 999");
        } else{
            num=tmp.toInt();
        }

        for(; num != 0; num--){
            list<<in.readLine();
        }

        tmp = in.readLine();
        if(tmp.length()>100 || tmp.isEmpty()){
            QMessageBox::information(0,"Errrrror","So much chars or no chars");
        } else{
            chars = tmp.split("");
        }

    }
}

/*
 * Here goes UI functions
 * Just answer button call back
 */
void MainWindow::on_answButt_clicked()
{
    read_file();
    ui->answ->setText(str);
    input_str = input_str+num;
    ui->inp->setText(input_str);
}
