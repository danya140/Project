#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include <QUrl>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void set();

private slots:
    void on_answButt_clicked();

    void on_save_clicked();

    void on_present_clicked();

    void widgetDestroyed();

    void timer_overflow();

    void timer1_overflow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player = new QMediaPlayer;
    QMediaPlayer *player1 = new QMediaPlayer;
    QMediaPlayer mediaPlayer;
    QTimer *timer;
    QTimer *timer1;
};

#endif // MAINWINDOW_H
