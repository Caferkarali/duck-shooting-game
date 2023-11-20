#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QRandomGenerator>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void olustur();
    void hareket();
    void vurma();

    void kacan();


private:
    Ui::MainWindow *ui;
    QLabel *vurulanLabel;
    QLabel *kacanLabel;
    int vurulansayisi;
    int kacansayisi;
   QTimer *timer;
   QTimer *deleteTimer;
};

#endif // MAINWINDOW_H
