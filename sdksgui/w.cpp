/*
 * one480 — MIT License
 * TR: Bu dosya MIT Lisansı kapsamında sunulur.
 * EN: This file is distributed under the MIT License.
 * Copyright (c) 2026 one480 contributors
 */
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
class StatusHeader final:public QWidget{
 Q_OBJECT
public: explicit StatusHeader(QWidget *p=nullptr):QWidget(p){setMinimumHeight(170);}
protected:void paintEvent(QPaintEvent*)override{QPainter q(this);QLinearGradient g(0,0,width(),height());g.setColorAt(0,QColor("#00A88E"));g.setColorAt(1,QColor("#00967F"));q.fillRect(rect(),g);q.setPen(QPen(QColor(255,255,255,35),1));for(int x=20;x<width();x+=45)for(int y=15;y<height();y+=38)q.drawEllipse(QPoint(x,y),2,2);q.setPen(Qt::white);q.setFont(QFont("Segoe UI",18,QFont::DemiBold));q.drawText(QRect(190,40,width()-210,38),Qt::AlignLeft,"Bilgisayarınız korunuyor");q.setFont(QFont("Segoe UI",10));q.drawText(QRect(190,82,width()-210,26),Qt::AlignLeft,"one480 tarama ve güvenlik merkezi");q.setPen(QPen(Qt::white,4));q.drawRoundedRect(QRect(42,38,100,82),12,12);q.drawLine(66,78,83,94);q.drawLine(83,94,119,55);}
};
class TileButton final:public QPushButton{
 Q_OBJECT
public:TileButton(const QString &s,const QString &ico,QWidget*p=nullptr):QPushButton(ico+"\n"+s,p){setMinimumHeight(104);setCursor(Qt::PointingHandCursor);setAccessibleName(s);setStyleSheet("QPushButton{background:white;border:1px solid #E5EAED;border-radius:12px;padding:12px;color:#2B3A42;font:10pt 'Segoe UI';} QPushButton:hover{background:#F4F8F7;border-color:#00A88E;} QPushButton:pressed{background:#E5F3F0;} QPushButton:focus{border:2px solid #007F70;}");}
};
class ProgressRing final:public QWidget{
 Q_OBJECT
public:explicit ProgressRing(QWidget*p=nullptr):QWidget(p){setMinimumSize(70,70);}
protected:void paintEvent(QPaintEvent*)override{QPainter p(this);p.setRenderHint(QPainter::Antialiasing);p.setPen(QPen(QColor("#DDE7E4"),7));p.drawEllipse(rect().adjusted(8,8,-8,-8));p.setPen(QPen(QColor("#00A88E"),7));p.drawArc(rect().adjusted(8,8,-8,-8),90*16,-90*16);}
};
class LogPanel final:public QWidget{
 Q_OBJECT
public:explicit LogPanel(QWidget*p=nullptr):QWidget(p){auto*l=new QVBoxLayout(this);auto*t=new QLabel("Tarama günlüğü",this);l->addWidget(t);}
};
#include "w.moc"
