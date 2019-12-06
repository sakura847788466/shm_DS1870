#ifndef IDSTRUCTS_H
#define IDSTRUCTS_H

struct IDOutline{
    IDOutline(QString tablename,QString ver,QString reserve,uint count,QString remark,QString time)
        : _tablename(tablename),
          _ver(ver),
          _reserve(reserve),
          _count(count),
          _remark(remark),
          _time(time)
    {

    }

    IDOutline(QString ver,QString reserve,uint count,QString remark)
        : _ver(ver),
          _reserve(reserve),
          _count(count),
          _remark(remark)
    {

    }

    IDOutline(){}

    QString _tablename;
    QString _ver;
    QString _reserve;
    uint _count;
    QString _remark;
    QString _time;
};


struct IDStatistics{
    IDStatistics(uint created,uint uploaded)
        : _created(created),
          _uploaded(uploaded)
    {

    }


    IDStatistics(){}

    uint _created;
    uint _uploaded;
};

#endif // IDSTRUCTS_H

