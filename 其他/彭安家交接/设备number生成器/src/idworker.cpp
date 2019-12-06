#include "idworker.h"
#include "precompiled.h"
#include <QThread>

static const unsigned char CRC7_POLY = 0x91;

unsigned char getCRC(unsigned char message[], unsigned char length)
{
  unsigned char i, j, crc = 0;

  for (i = 0; i < length; i++)
  {
    crc ^= message[i];
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc ^= CRC7_POLY;
      crc >>= 1;
    }
  }
  return crc;
}


IDWorker::IDWorker()
{

}

void IDWorker::start(QString _ver, QString _reserved, ulong _count)
{
    _cancel = false;

    unsigned char id[8]{0};

    //byte 0

    QStringList v = _ver.split(".");
    if(v.length()==4){
        id[0] |= (v[0] == "1" ? 0x80 : 0x00);
        id[0] |= (v[1] == "1" ? 0x40 : 0x00);
        id[0] |= (v[2] == "1" ? 0x20 : 0x00);
        id[0] |= (v[3] == "1" ? 0x10 : 0x00);
    }

    //byte 7

    QByteArray reserved = QByteArray::fromHex(_reserved.toLatin1());
    if( reserved.length() == 1 ){
        id[7] = reserved[0];
    }


    int TIMES =  _count / 256;
    if(_count % 256){TIMES++;}
    ulong totol = 0;
    for(ulong t = 0; t < ulong(TIMES); t++){

        if(_cancel){
            emit callback(QStringList{});
            return;
        }

        QStringList item;

        for(int index=0; index < 256; index++){

            if(_cancel){
                emit callback(QStringList{});
                return;
            }

            if( totol<_count  ){

                //byte 6
                id[6] = index;

                //byte 2~5
                uint nowTimestamp = QDateTime::currentDateTime().toUTC().toTime_t();
                uint benchmarkTimestamp = QDateTime::fromString("2017-01-01 00:00:00","yyyy-MM-dd hh:mm:ss").toUTC().toTime_t();
                int32_t sub = nowTimestamp-benchmarkTimestamp;
                memcpy_s(id+2,4,&sub,4);

                //byte 1
                id[1] = 0x6B;
                id[1] = getCRC(id,8);

                //bytes to string
                item << QString(QByteArray::fromRawData((char*)id,8).toHex()).toUpper();

                totol++;
            }else{
                break;
            }
        }
        emit callback(item);

        QThread::msleep(1000);
    }

    emit callback(QStringList{});
}

void IDWorker::abord()
{
    _cancel = true;
}

