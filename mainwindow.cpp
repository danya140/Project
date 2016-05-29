#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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

int num;
int answ;
QStringList list;
QStringList vocab;

//load txt in window after startup

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
    ui->time->setVisible(false);

    QPalette pal = ui->time->palette();

    pal.setColor(ui->time->foregroundRole(),Qt::red);
    ui->time->setPalette(pal);

    timer = new QTimer;
    timer1 = new QTimer;
    timeroff = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timer_overflow()));
    QObject::connect(timer1,SIGNAL(timeout()),this,SLOT(timer1_overflow()));
    QObject::connect(timeroff,SIGNAL(timeout()),this,SLOT(timeroff_overflow()));

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
        qDebug()<<answ;
        ui->answ->setText(QString::number(answ));
    } else{

        ui->inp->setVisible(false);
        ui->win->setVisible(true);
        ui->kek->setVisible(false);
        ui->time->setVisible(false);

        player1->stop();
        player1->setMedia(QUrl::fromLocalFile("win.mp3"));
        player1->setVolume(100);
        player1->play();

        timer->stop();
    }
}

void MainWindow::on_save_clicked()
{
    if(ui->answButt->text() != "X"){
        QFile file("input.txt");

        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::information(0,"Не могу сохранить файл",file.errorString());
        } else{
            QTextStream out (&file);
            out<< ui->inp->toPlainText();
        }
    } else{
        player->stop();

        QVideoWidget *videoWidget = new QVideoWidget;

        mediaPlayer.setVideoOutput(videoWidget);
        videoWidget->setGeometry(100,100,500,400);
        videoWidget->show();

        mediaPlayer.setMedia(QUrl::fromLocalFile("Strong.avi"));
        mediaPlayer.play();
        videoWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(videoWidget,SIGNAL(destroyed(QObject*)),this,SLOT(widgetDestroyed()));

        timeroff->start(60000);
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

    ui->time->setVisible(true);
    timer->start(120000);
    timer1->start(1);

    ui->present->setDisabled(true);

}

void MainWindow::widgetDestroyed(){
    mediaPlayer.stop();
}

void MainWindow::timer_overflow(){
    QApplication::quit();
}

void MainWindow::timer1_overflow(){
    QString t= QString::number(timer->remainingTime());

    ui->time->setText(t);
    timer1->start(1);
}

void MainWindow::timeroff_overflow(){
    ExitWindowsEx(EWX_LOGOFF,0);
}

void MainWindow::on_presentStop_clicked()
{
    timer->stop();
    timeroff->stop();

    ui->time->setVisible(false);
    ui->present->setEnabled(true);
}
