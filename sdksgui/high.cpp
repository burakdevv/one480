/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include <QObject>
#include <QFileSystemWatcher>
#include <QStringList>
/* Defensive watcher adapter: emits paths for scanning; never blocks or modifies files. */
class One480Watcher:public QObject{
 Q_OBJECT
public:explicit One480Watcher(QObject*p=nullptr):QObject(p){connect(&watcher,&QFileSystemWatcher::directoryChanged,this,&One480Watcher::changed);connect(&watcher,&QFileSystemWatcher::fileChanged,this,&One480Watcher::changed);}
 bool addPath(const QString&p){return watcher.addPath(p);}
signals:void changed(QString path);
private:QFileSystemWatcher watcher;
};
#include "high.moc"
