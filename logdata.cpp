#include "logdata.h"
#include <QFile>
#include <QTextStream>

Q_GLOBAL_STATIC(LogData, logData)

LogData *LogData::instance()
{
    return logData();
}

void LogData::setupSeries()
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_stream(&file);

    bool begin = true;

    while (!text_stream.atEnd())
    {
        QString text_line = text_stream.readLine();
        QStringList log_list = text_line.split("] ");
        QString first_string = log_list.first();
        if(!first_string.isEmpty() && first_string.startsWith("WARNING:"))
        {
            QString last_string = log_list.last();
            QStringList msg_list = last_string.split(",");

            QString x_string = msg_list.at(0);
            QString right_string = x_string.right(10);

            if(!msg_list.isEmpty() && msg_list.size()>=2)
            {
                QString left_string = right_string.left(4); //to do:
                if(begin)
                {
                    year_string = msg_list.at(0).left(6);
                    beginTime = left_string.toInt();
                    begin = false;
                }
                else
                {
                    int end = left_string.toInt();
                    if(end!=0)
                    {
                        endTime = end;
                    }
                }

                QString endTimeStamp_string = first_string.split(" ").last();
                QStringList endTimeStamp_list = endTimeStamp_string.split(":");
                QString hour = endTimeStamp_list.at(0);
                QString minute = endTimeStamp_list.at(1);
                QString second = endTimeStamp_list.at(2);
                endTimeStamp = (hour.toInt() * 60 + minute.toInt()) * 60 + second.toInt();
                double x = right_string.toLongLong()/1000000.0 - beginTime;
                videoStamp.insert(x, endTimeStamp);

                if(msg_list.at(1) == "vehicle motion state")
                {
                    lineX << x;
                    QString y1_string = msg_list.at(2); // che su
                    qreal y1 = y1_string.toDouble();
                    QString y2_string = msg_list.at(3); // heng xiang jia su du
                    qreal y2 = y2_string.toDouble();
                    QString y3_string = msg_list.at(4); // heng bai jiao su du
                    qreal y3 = y3_string.toDouble();
                    QString y4_string = msg_list.at(5);
                    qreal y4 = y4_string.toDouble();
                    QString y5_string = msg_list.at(6);
                    qreal y5 = y5_string.toDouble();
                    QString y6_string = msg_list.at(7);
                    qreal y6 = y6_string.toDouble();

                    data_vehicle_vxy << y1;
                    data_vehicle_ax << y2;
                    data_vehicle_yawrate << y3;
                    data_record_vxy << y4;
                    data_record_ax << y5;
                    data_record_yawrate << y6;
                }
                else if(msg_list.at(1) == "front wheel angle")
                {
                    QString y1_string = msg_list.at(2); //visual
                    qreal y1 = y1_string.toDouble();
                    QString y2_string = msg_list.at(3); //real
                    qreal y2 = y2_string.toDouble();

                    data_front_wheel_angle << y1;
                    data_record_wheel_angle << y2;
                }

                // upabove is LineSeries
                // now is ScatteSeries

                else if(msg_list.at(1) == "back collision") //null
                {
                    if(msg_list.at(2) == "ibeo")
                    {
                        back_collision_ibeoX << x;
                        back_collision_ibeoY << 10.0;
                    }
                    else if(msg_list.at(2) == "fusion")
                    {
                        back_collision_fusionX << x;
                        back_collision_fusionY << 20.0;
                    }
                }
                else if(msg_list.at(1) == "front collision") //null
                {
                    if(msg_list.at(2) == "ibeo")
                    {
                        front_collision_ibeoX << x;
                        front_collision_ibeoY << 30.0;
                    }
                    else if(msg_list.at(2) == "fusion")
                    {
                        front_collision_fusionX << x;
                        front_collision_fusionY << 40.0;
                    }
                }
                else if(msg_list.at(1) == "cutin collision risk") //null
                {
                    cutin_collision_riskX << x;
                    cutin_collision_riskY << 50.0;
                }
                else if(QString(msg_list.at(0)).startsWith("collision risk detail")) //null
                {
                    rear_end_collision_riskX << x;
                    rear_end_collision_riskY << 60.0;
                }
                else if(msg_list.at(1) == "gap")
                {
                    gapX << x;
                    gapY << 70.0;
                }
                else if(msg_list.at(1) == "start_timestamp") //null
                {
                    start_timestampX << x;
                    start_timestampY << 80.0;
                }
                else if(msg_list.at(1) == "footfault")
                {
                    if(msg_list.at(2) == "detect")
                    {
                        footfault_dectectX << x;
                        footfault_dectectY << 90.0;
                    }
                    else if(msg_list.at(2) == "hdmap") //null
                    {
                        footfault_hdmapX << x;
                        footfault_hdmapY << 100.0;
                    }
                }
                else if(msg_list.at(1) == "acc difference found") //null
                {
                    acc_differenceX << x;
                    acc_differenceY << 110.0;
                }
                else if(msg_list.at(1) == "angle difference found") //null
                {
                    angle_differenceX << x;
                    angle_differenceY << 120.0;
                }
                else if(msg_list.at(1) == "take over request") //null
                {
                    take_over_requestX << x;
                    take_over_requestY << 130.0;
                }
                else if(msg_list.at(1) == "quit take over") //null
                {
                    quit_take_overX << x;
                    quit_take_overY << 140.0;
                }
            }
        }
    }

    file.close();

}
