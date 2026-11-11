/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include "scanner.h"
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QDirIterator>
#include <QDateTime>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QDir>
#include <QFileInfoList>
#include <QRegularExpression>

Scanner::Scanner(QObject *p):QObject(p),cancelled(0){}
void Scanner::cancel(){cancelled.storeRelease(1);}
void Scanner::scanPath(const QString &path){
 cancelled.storeRelease(0); int scanned=0,det=0,susp=0;
 QFileInfo root(path);
 if(!root.exists()){emit logMessage("Yol bulunamadı: "+path);emit finished(0,0,0);return;}
 QStringList files;
 if(root.isFile())files<<root.absoluteFilePath();
 else {QDirIterator it(path,QDir::Files|QDir::NoDotAndDotDot,QDirIterator::Subdirectories);while(it.hasNext()&&!cancelled.loadAcquire())files<<it.next();}
 const QByteArray eicar=QByteArray("X5O!P%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*");
 for(const QString &f:files){
  if(cancelled.loadAcquire())break;
  QFile file(f);QFileInfo fi(f);
  if(!file.open(QIODevice::ReadOnly)){emit logMessage("Atlandı (erişim): "+f);continue;}
  if(fi.size()>512ll*1024*1024){emit logMessage("Atlandı (512 MiB sınırı): "+f);continue;}
  QCryptographicHash hash(QCryptographicHash::Sha256);QByteArray sample;bool found=false;
  while(!file.atEnd()){QByteArray chunk=file.read(1024*1024);if(chunk.isEmpty()&&file.error()!=QFile::NoError)break;hash.addData(chunk);if(sample.size()<eicar.size()+64)sample+=chunk.left(eicar.size()+64-sample.size());if(sample.contains(eicar))found=true;}
  ++scanned;
  if(found){++det;emit logMessage("EICAR test imzası tespit edildi: "+f+" (karantina önerilir; otomatik işlem yapılmadı)");}
  else if(fi.suffix().compare("exe",Qt::CaseInsensitive)==0||fi.suffix().compare("dll",Qt::CaseInsensitive)==0){++susp;emit logMessage("İncelenmesi önerilir (PE sezgisel analiz henüz sınırlı): "+f);}
  else emit logMessage("Temiz: "+f);
  emit progress(f,scanned,files.size());
 }
 emit finished(scanned,det,susp);
}
