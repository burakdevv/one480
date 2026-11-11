/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#ifndef ONE480_QT_SCANNER_H
#define ONE480_QT_SCANNER_H
#include <QObject>
#include <QString>
#include <QAtomicInt>
class Scanner : public QObject {
 Q_OBJECT
public:
 explicit Scanner(QObject *parent=nullptr);
 void cancel();
public slots:
 void scanPath(const QString &path);
signals:
 void progress(QString path,int current,int total);
 void logMessage(QString message);
 void finished(int scanned,int detections,int suspicious);
private:
 QAtomicInt cancelled;
};
#endif
