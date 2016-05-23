#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

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

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player = new QMediaPlayer;
};

#endif // MAINWINDOW_H
