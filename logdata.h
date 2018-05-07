#ifndef LOGDATA_H
#define LOGDATA_H

// this file is for loading *.log

#include <QList>
#include <QHash>

typedef QList<qreal> Data;

class LogData
{
public:
    static LogData* instance();
    QString fileName;
    void setupSeries();

    QList<qreal> data_vehicle_vxy;
    QList<qreal> data_vehicle_ax;
    QList<qreal> data_vehicle_yawrate;
    QList<qreal> data_record_vxy;
    QList<qreal> data_record_ax;
    QList<qreal> data_record_yawrate;
    QList<qreal> data_front_wheel_angle;
    QList<qreal> data_record_wheel_angle;
    QList<qreal> lineX;

    QList<qreal> back_collision_ibeoX;
    QList<qreal> back_collision_ibeoY;
    QList<qreal> front_collision_ibeoX;
    QList<qreal> front_collision_ibeoY;
    QList<qreal> back_collision_fusionX;
    QList<qreal> back_collision_fusionY;
    QList<qreal> front_collision_fusionX;
    QList<qreal> front_collision_fusionY;
    QList<qreal> cutin_collision_riskX;
    QList<qreal> cutin_collision_riskY;
    QList<qreal> rear_end_collision_riskX;
    QList<qreal> rear_end_collision_riskY;
    QList<qreal> gapX;
    QList<qreal> gapY;
    QList<qreal> start_timestampX;
    QList<qreal> start_timestampY;
    QList<qreal> footfault_hdmapX;
    QList<qreal> footfault_hdmapY;
    QList<qreal> footfault_dectectX;
    QList<qreal> footfault_dectectY;
    QList<qreal> acc_differenceX;
    QList<qreal> acc_differenceY;
    QList<qreal> angle_differenceX;
    QList<qreal> angle_differenceY;
    QList<qreal> take_over_requestX;
    QList<qreal> take_over_requestY;
    QList<qreal> quit_take_overX;
    QList<qreal> quit_take_overY;

    int beginTime;
    int endTime;
    QString year_string;

    QHash<double, int> videoStamp;
    int endTimeStamp;

};

#endif // LOGDATA_H
