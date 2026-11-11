/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "mainwindow.h"
#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
int main(int argc,char **argv){
 QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
 QApplication app(argc,argv);QSharedMemory lock("one480-single-instance");
 if(!lock.create(1)){QMessageBox::information(nullptr,"one480","Uygulama zaten çalışıyor.");return 0;}
 MainWindow w;w.show();return app.exec();
}
