#include "GetSerial.h"

GetSerial::GetSerial(QString portName_, QObject *parent) : QSerialPort(parent), portName(portName_)
{
}

QList<QString> GetSerial::getPortsName()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator iPort;
    QList<QString> portsName;
    for(iPort=ports.begin();iPort<=ports.end();iPort++)
    {
        portsName.append(iPort->portName());
    }
    return portsName;
}

void GetSerial::connectPort()
{
    this->setPortName(portName);
    if(!this->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(NULL, "串口错误", "串口连接失败，错误代码"+QString::number(this->error()));
        return;
    }
    this->setBaudRate(QSerialPort::Baud115200);
    this->setDataBits(QSerialPort::Data8);
    this->setFlowControl(QSerialPort::NoFlowControl);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    connect(this, &QSerialPort::readyRead, this, &GetSerial::readMessage);
}

void GetSerial::statusMachine(char data)
{
    char tempData = data & 0xff;
    char mask = data & 0x80;
    if(mask == 0x00)
    {
        status = 0;
    }
    switch(status)
    {
    case 0:
        if(tempData == 0x08)
        {
            status = 1;
            pkgType = data;
            pkgDataHead = 0x00;
            dataLength = 7;
        }
        else if(tempData == 0x09 || tempData == 0x0a)
        {
            status = 1;
            pkgType = data;
            pkgDataHead = 0x00;
            dataLength = 1;
        }
        break;
    case 1:
        pkgDataHead = tempData;
        pkgDataCnt = 0;
        status = 2;
        break;
    case 2:
        if(pkgType == 0x08)
        {
            tempData = tempData & 0x7f;
            tempData = tempData | (char)(((pkgDataHead >> pkgDataCnt) & 0x1) << 7);
            pkgData[pkgDataCnt] = tempData;
            pkgDataCnt += 1;
            if(pkgDataCnt >= 7)
            {
                status = 3;
            }
        }
        else if(pkgType == 0x09 || tempData == 0x0a)
        {
            tempData = tempData | (pkgDataHead << 7);
            pkgData[0] = (tempData);
            status = 3;
        }
        break;
    case 3:
        if(pkgType == 0x08) //ECG
        {
            //拼接
            pkgDataInt[0] = ((this->pkgData[0] << 8) | (unsigned int)(this->pkgData[1] & 0xff));
            pkgDataInt[1] = ((this->pkgData[2] << 8) | (unsigned int)(this->pkgData[3] & 0xff));
            pkgDataInt[2] = ((this->pkgData[4] << 8) | (unsigned int)(this->pkgData[5] & 0xff));
            if((char)(pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2]) == (tempData & 0x7f)) //校验
            {
                dataForSending = (pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2])/3;
                if(flagCount == false) //压缩
                {
                  emit receivedECGdata(dataForSending);
                  //qDebug()<<(pkgDataInt[0]+pkgDataInt[1]+pkgDataInt[2])/3;
                }
                flagCount = !flagCount;
                //flagCount++;
                //if(flagCount==flagCountMax)
                //    flagCount = 0;
                //qDebug()<<pkgDataInt[0];
                //qDebug()<<pkgDataInt[1];
                //qDebug()<<pkgDataInt[2];
            }

        }
        else if(tempData == 0x09 || tempData == 0x0a) //SPO2&BP
        {
            pkgDataInt[0] = ((unsigned int)(pkgData[0] & 0xff));
            if(((char)(pkgDataInt[0])) == tempData)
            {
                dataForSending = pkgDataInt[0];
                if(tempData == 0x09) //SPO2
                    emit receivedSPO2data(dataForSending);
                if(tempData == 0x0a) //BP
                    emit receivedBPdata(dataForSending);
            }
        }
        status = 0;
        pkgData[0] = 0;
        pkgData[1] = 0;
        pkgData[2] = 0;
        pkgData[3] = 0;
        pkgData[4] = 0;
        pkgData[5] = 0;
        pkgData[6] = 0;
        pkgDataInt[0] = 0;
        pkgDataInt[1] = 0;
        pkgDataInt[2] = 0;
        break;
    default:
        break;
    }
}

//bool GetSerial::sendString(QString str)
//{
//    if(comPort->write(str.toStdString().c_str()))
//        return true;
//    else
//        return false;
//}

void GetSerial::readMessage()
{
    QByteArray data;
    data = this->read(1);
    statusMachine(data[0]);
    if (this->bytesAvailable()>0)
    {
        readMessage();
    }
}
