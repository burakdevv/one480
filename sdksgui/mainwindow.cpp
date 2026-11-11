/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "mainwindow.h"
#include "scanner.h"
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QProgressBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QApplication>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QDesktopServices>
#include <QUrl>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QInputDialog>
#include "w.cpp"
MainWindow::MainWindow(QWidget*p):QMainWindow(p),scanner(new Scanner),worker(new QThread(this)),tray(nullptr),protection(false){
 setWindowTitle("one480");setMinimumSize(640,500);resize(760,560);setFont(QFont("Segoe UI",10));
 auto *central=new QWidget(this);auto *v=new QVBoxLayout(central);v->setContentsMargins(14,14,14,8);v->setSpacing(12);
 auto *header=new StatusHeader(central);v->addWidget(header);
 auto *grid=new QGridLayout;grid->setSpacing(10);
 const QStringList names={"Tara","Veritabanı Güncelle","Karantina","Gerçek Zamanlı Koruma","Beyaz Liste","Raporlar ve Günlükler"};
 const QStringList icons={"◉","↻","▣","◈","✓","≡"};
 for(int i=0;i<6;++i){auto*b=new TileButton(names[i],icons[i],central);grid->addWidget(b,i/3,i%3);if(i==0)connect(b,&QPushButton::clicked,this,&MainWindow::chooseScan);if(i==2)connect(b,&QPushButton::clicked,this,&MainWindow::showQuarantine);if(i==3)connect(b,&QPushButton::clicked,this,[this]{toggleProtection(!protection);});if(i==1)connect(b,&QPushButton::clicked,this,[this]{QMessageBox::information(this,"Veritabanı","Yerel imza veritabanı: dahili EICAR test kontrolü.\nÇevrimiçi imza indirme bu sürümde etkin değildir.");});if(i==4)connect(b,&QPushButton::clicked,this,[this]{QMessageBox::information(this,"Beyaz Liste","Bu sürümde istisna ekleme devre dışıdır; yanlış pozitifleri rapor günlüğünden inceleyin.");});if(i==5)connect(b,&QPushButton::clicked,this,[this]{QMessageBox::information(this,"Raporlar","Tarama raporları aşağıdaki günlük alanında gösterilir.");});}
 v->addLayout(grid);auto*more=new QPushButton("Daha Fazla Araç",central);more->setStyleSheet("QPushButton{background:#00A88E;color:white;border:0;border-radius:8px;padding:10px 24px;font-weight:600;}");auto*row=new QHBoxLayout;row->addStretch();row->addWidget(more);row->addStretch();v->addLayout(row);
 connect(more,&QPushButton::clicked,this,[this,more]{QMenu m; m.addAction("Sistem Bilgisi",[this]{QMessageBox::information(this,"Sistem",QSysInfo::prettyProductName());});m.addAction("Ayarlar",[this]{QMessageBox::information(this,"Ayarlar","Varsayılan güvenli ayarlar etkin.");});m.addAction("Hakkında",[this]{QMessageBox::about(this,"one480","one480 1.0.0\nMIT License\nEğitim/araştırma amaçlıdır; ticari antivirüsün yerine geçmez.");});m.exec(more->mapToGlobal(QPoint(0,more->height()));});
 progress=new QProgressBar(central);progress->setRange(0,100);progress->setValue(0);v->addWidget(progress);
 log=new QTextEdit(central);log->setReadOnly(true);log->setMaximumHeight(90);v->addWidget(log);setCentralWidget(central);
 scanner->moveToThread(worker);connect(worker,&QThread::finished,scanner,&QObject::deleteLater);connect(this,&MainWindow::destroyed,worker,&QThread::quit);connect(worker,&QThread::started,this,[]{});connect(scanner,&Scanner::logMessage,this,&MainWindow::appendLog,Qt::QueuedConnection);connect(scanner,&Scanner::progress,this,[this](const QString&,int n,int total){progress->setValue(total?int(100.0*n/total):0);},Qt::QueuedConnection);connect(scanner,&Scanner::finished,this,&MainWindow::scanDone,Qt::QueuedConnection);worker->start();
 auto *bottom=statusBar();bottom->showMessage("GitHub  •  Belgeler  •  Lisans: MIT");
 if(QSystemTrayIcon::isSystemTrayAvailable()){tray=new QSystemTrayIcon(style()->standardIcon(QStyle::SP_ComputerIcon),this);auto*menu=new QMenu;menu->addAction("Pencereyi Göster",this,&QWidget::show);menu->addAction("Koruma",this,[this]{toggleProtection(!protection);});menu->addAction("Çıkış",qApp,&QApplication::quit);tray->setContextMenu(menu);tray->show();}
}
MainWindow::~MainWindow(){if(scanner)QMetaObject::invokeMethod(scanner,"cancel",Qt::QueuedConnection);worker->quit();worker->wait();}
void MainWindow::chooseScan(){QString p=QFileDialog::getExistingDirectory(this,"Taranacak klasörü seç");if(!p.isEmpty())startScan(p);}
void MainWindow::startScan(const QString&p){progress->setValue(0);appendLog("Tarama başladı: "+p);QMetaObject::invokeMethod(scanner,"scanPath",Qt::QueuedConnection,Q_ARG(QString,p));}
void MainWindow::appendLog(const QString&s){log->append(s);}
void MainWindow::scanDone(int n,int d,int s){appendLog(QString("Tamamlandı — %1 dosya, %2 tespit, %3 şüpheli.").arg(n).arg(d).arg(s));QMessageBox::information(this,"Tarama tamamlandı",QString("%1 dosya tarandı.\n%2 tespit.\n%3 şüpheli öğe.").arg(n).arg(d).arg(s));}
void MainWindow::showQuarantine(){QMessageBox::information(this,"Karantina","Karantina boş. Bu derlemede otomatik karantina yerine kullanıcı onaylı akış korunur.");}
void MainWindow::toggleProtection(bool on){protection=on;appendLog(on?"Gerçek zamanlı izleme etkinleştirme isteği alındı.":"Gerçek zamanlı izleme kapatıldı.");QMessageBox::information(this,"Gerçek Zamanlı Koruma",on?"Bu sürümde gerçek zamanlı dosya izleme desteklenmiyor; durum yalnızca arayüzde gösterilir.":"Koruma kapalı.");}
