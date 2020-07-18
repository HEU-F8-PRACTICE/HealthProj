#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "PlotWidget.h"
#include "GetSerial.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    //注意：由于Qt对象树在销毁时，含有子对象且在栈区的对象，销毁时会把子对象也销毁
    //     而子对象还会销毁一遍，这样就出错了，会无法退出，因此这里用指针将其放在堆区
    //布局Layout
    QVBoxLayout *splitTitle = new QVBoxLayout;
    QVBoxLayout *leftPlotsLayout = new QVBoxLayout;
    QHBoxLayout *leftrightLayout = new QHBoxLayout;
    QGridLayout *rightGrids = new QGridLayout;

    //布局Widget
    QWidget *left = new QWidget(this);
    QWidget *right = new QWidget(this);
    QWidget *mainW = new QWidget(this);

    //待提升的Widget
    QWidget title;
    PlotWidget ecgiiPlot;
    PlotWidget spo2Plot;
    PlotWidget respPlot;

    QWidget hr;
    QWidget st;
    QWidget nibp;
    QWidget spo2;
    QWidget temp;
    QWidget resp;
    QWidget co2;

    GetSerial *gs = new GetSerial("COM30");

    //测试区
    //QTimer *tm;
    //QPushButton *button1 = new QPushButton(this);
    //QLineEdit * lineedit1 = new QLineEdit(this);
    //QLabel *label1 = new QLabel(this);
    //GetSerial *getserial = new GetSerial("COM30");
    //
    //PlotWidget testWidget;
    //QList<int>::iterator iData;
    //QList<int> testData = {2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2008, 2016, 2016, 2016, 2024, 2032, 2048,
    //                        2064, 2064, 2064, 2072, 2080, 2080, 2080, 2088, 2096, 2104,
    //                        2112, 2112, 2112, 2112, 2112, 2112, 2104, 2096, 2088,
    //                        2080, 2080, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2032,
    //                        2032, 2016, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 1992, 1984, 1976,
    //                        1968, 1960, 1952, 1944, 1936, 1944, 1952, 2016, 2080, 2136,
    //                        2192, 2256, 2320, 2376, 2432, 2488, 2544, 2568, 2592, 2536,
    //                        2480, 2424, 2368, 2304, 2240, 2184, 2128, 2072, 2016, 1968,
    //                        1920, 1928, 1936, 1944, 1952, 1960, 1968, 1984, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2008, 2016, 2024, 2032, 2032,
    //                        2032, 2048, 2064, 2064, 2064, 2072, 2080, 2088, 2096, 2104,
    //                        2112, 2112, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2160,
    //                        2160, 2160, 2160, 2168, 2176, 2176, 2176, 2184, 2192,
    //                        2192, 2192, 2192, 2200, 2208, 2208, 2208, 2208, 2208, 2208,
    //                        2208, 2200, 2192, 2192, 2192, 2184, 2176, 2176, 2176, 2168,
    //                        2160, 2160, 2160, 2144, 2128, 2128, 2128, 2128, 2128, 2112,
    //                        2096, 2088, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2024,
    //                        2016, 2016, 2016, 2008, 2000, 2000, 2000, 2000, 2000,
    //                        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};

public slots:
    //void testPlot();
    //void sendString2Port();
    //void testRead(QString str);
};
#endif // MAINWIDGET_H
