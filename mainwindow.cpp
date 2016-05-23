#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include <QUrl>

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

//TODO: clear this shit
int num;
QStringList list;
QStringList vocab;
int answ;

//load txt in window after

void MainWindow::set(){
    QFile file("input.txt");

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"Не могу прочитать файл",file.errorString());
    } else{
        QTextStream in(&file);

        QString tmp = in.readAll();

        ui->inp->setText(tmp);
        in.flush();
    }

    ui->kek->setVisible(false);
    ui->win->setVisible(false);

    file.close();
}

/*
 * Here goes main logic
 *
 */

void calc(){

    answ = 0;

    QString tmp;
    int len=0;
    for(int j = 0; j != num; j++){
        tmp = list.at(j);
        for(int i = vocab.length()-2; i != 0; i--){

            if(tmp.length() != len ){
                tmp.contains(vocab.at(i)) ? len++ : true;
            }
        }

        tmp.length()==len ? answ++ : false;
        len = 0;
    }
}

/*
 * Here goes functions for reading input file
 */

void read_file (){
    QFile file("input.txt");
    QRegExp digit("\\d*"); //reg exp for digits

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"Не могу прочитать файл",file.errorString());
    } else{

        QTextStream in(&file);
        //input_str = in.readAll();

        QString tmp = in.readLine();
        if(tmp.isEmpty() || !digit.exactMatch(tmp) || tmp.length()>=4){ // TODO: better use switch
            QMessageBox::information(0,"Ошибка","N пустой или не цифра или больше 999");
        } else{
            num=tmp.toInt();
        }

        for(int i = num; i != 0; i--){
            list<<in.readLine();
        }

        tmp = in.readLine();
        if(tmp.length()>100 || tmp.isEmpty()){
            QMessageBox::information(0,"Errrrror","So much chars or no chars");
        } else{
            vocab = tmp.split("");
        }

        in.flush();
        file.close();

        calc();

    }
}

/*
 * Here goes UI functions
 * Just answer button call back
 */

void MainWindow::on_answButt_clicked()
{
    if(ui->answButt->text()!="X"){
        read_file();
        ui->answ->setText(QString::number(answ));
    } else{

        ui->inp->setVisible(false);
        ui->win->setVisible(true);
        ui->kek->setVisible(false);

        player1->stop();
        player1->setMedia(QUrl::fromLocalFile("win.mp3"));
        player1->setVolume(100);
        player1->play();
    }
}

void MainWindow::on_save_clicked()
{
    QFile file("input.txt");

    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(0,"Не могу сохранить файл",file.errorString());
    } else{
        QTextStream out (&file);
        out<< ui->inp->toPlainText();
    }
}

//just for fun

void MainWindow::on_present_clicked()
{
    player->setMedia(QUrl::fromLocalFile("7army.mp3"));
    player->setVolume(100);
    player->play();

    ui->kek->setVisible(true);
    ui->answButt->setText("X");

    ui->present->setDisabled(true);

}
