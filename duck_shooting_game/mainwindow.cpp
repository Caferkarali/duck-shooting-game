#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QRandomGenerator>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(olustur()));
    timer->start(400); // Her saniye yeni bir ördek oluştur

    kacanLabel = ui->kacanLabel;
    vurulanLabel = ui->vurulanLabel;

    vurulansayisi = 0;
    kacansayisi = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::olustur()
{
    //  ördek oluştur
    QPushButton *duckButton = new QPushButton("", this);
    duckButton->setStyleSheet("border-image: url(:/re/ordek.png);");

    duckButton->setFixedSize(50, 50);
    duckButton->move(QRandomGenerator::global()->bounded(width() - duckButton->width()), 0);


    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(hareket()));
    timer->setProperty("duckButton", QVariant::fromValue<QPushButton *>(duckButton)); // QPushButton pointer'ını saklamak için

    timer->start(30);

    // tıklandığında
    connect(duckButton, SIGNAL(clicked()), this, SLOT(vurma()));
    duckButton->show();
}

void MainWindow::hareket()
{
    //  objeyi al
    QObject *senderObject = sender();
    if (senderObject)
    {
        //  QTimer ise devam et
        QTimer *timer = qobject_cast<QTimer *>(senderObject);
        if (timer)
        {

            QPushButton *duckButton = timer->property("duckButton").value<QPushButton *>();
            if (duckButton)
            {
                //  aşağı hareket
                duckButton->move(duckButton->x(), duckButton->y() + 7);
                // Eğer ördek ekranın dışına çıkarsa
                if (duckButton->y() > height())
                {

                    kacan();
                    timer->stop();
                    duckButton->deleteLater();
                    timer->deleteLater();
                }
            }
        }
    }
}



void MainWindow::vurma()
{
    QPushButton *duckButton = qobject_cast<QPushButton *>(sender());
    if (duckButton)
    {
        // bağlantıyı kes
        disconnect(duckButton, SIGNAL(clicked()), this, SLOT(vurma()));

        // daha önce vurulup vurulmadığını kontrol et
        if (!duckButton->property("shot").toBool())
        {

            duckButton->setProperty("shot", true);


            vurulansayisi++;
            vurulanLabel->setText("Vurulan Ördek: " + QString::number(vurulansayisi));


            QPixmap hitPixmap(":/re/vurulma.png");
            hitPixmap = hitPixmap.scaled(duckButton->size(), Qt::KeepAspectRatio);

            // vurulma bir QLabel oluştur
            QLabel *vurulmaLabel = new QLabel(this);
            vurulmaLabel->setObjectName("vurulmaLabel");
            vurulmaLabel->setPixmap(hitPixmap);
            vurulmaLabel->setFixedSize(duckButton->size());
            vurulmaLabel->move(duckButton->mapTo(this, QPoint(0, 0)));
            vurulmaLabel->show();

            // Gecikmeyi yönetmek için bir QTimer oluştur
            QTimer *timer = new QTimer(this);
            timer->setSingleShot(true);
            connect(timer, &QTimer::timeout, [=]() {

                vurulmaLabel->hide();

                // etiketi silme
                vurulmaLabel->deleteLater();


                duckButton->setHidden(true);

                // QTimer'ı temizle
                timer->deleteLater();
            });

            //  bir gecikme ile başlat
            timer->start(200);
        }
    }
}

void MainWindow::kacan()
{
    kacansayisi++;
    kacanLabel->setText("Kaçan Ördek: " + QString::number(kacansayisi));
}
