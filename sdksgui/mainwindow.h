/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_MAINWINDOW_H
#define ONE480_MAINWINDOW_H
#include <QMainWindow>
class Scanner;class QThread;class QTextEdit;class QProgressBar;class QSystemTrayIcon;
class MainWindow:public QMainWindow{
 Q_OBJECT
public:explicit MainWindow(QWidget *parent=nullptr);~MainWindow();
private slots:void chooseScan();void startScan(const QString&);void appendLog(const QString&);void scanDone(int,int,int);void showQuarantine();void toggleProtection(bool);
private:Scanner *scanner;QThread *worker;QTextEdit *log;QProgressBar *progress;QSystemTrayIcon *tray;bool protection;
};
#endif
