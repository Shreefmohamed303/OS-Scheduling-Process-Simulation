#include "listreader.h"
#include "notifier.h"
#include <QDebug>

extern Notifier notify;

extern QList<qreal> BurstTime;
extern QList<qreal> ArrivalTime;
extern QList<unsigned int> Priority;
extern QList <QString> ScheduledId;
extern QList <qreal> ScheduledTime;
extern QList <qreal> WaitingTimePerProcess;
extern QString ProcessType;
extern bool isPreemptive;
extern int NUmberOfProcess;
extern int TimeQuantum;


ListReader::ListReader(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(configrationGenerated()),this,SLOT(setGuiList()));
    connect(this,SIGNAL(readyToLoadSimulator()),&notify,SLOT(callSimulator()));
    connect(&notify,SIGNAL(goToListReader()),this,SLOT(setSimulationList()));
}

void ListReader::setIDs(QVariantList list)
{
    QVariant list_var(list);
    processid.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        processid.append(v.value<QString>());
    }
}

QVariantList ListReader::readIDs()
{
    return processid;
}

QVariantList ListReader::readTimes()
{
    return processid;
}

void ListReader::setAverage(QVariantList list)
{
    QVariant list_var(list);
    processaverage.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        processaverage.append(v.value<qreal>());
    }
}

QVariantList ListReader::readAverage()
{
    return processaverage;
}

void ListReader::setArrival(QVariantList list)
{
    QVariant list_var(list);
    arrivaltime.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        arrivaltime.append(v.value<qreal>());
    }
}

QVariantList ListReader::readArrival()
{
    return arrivaltime;
}

void ListReader::setBurst(QVariantList list)
{
    QVariant list_var(list);
    bursttime.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        bursttime.append(v.value<qreal>());
    }
}

QVariantList ListReader::readBurst()
{
    return bursttime;
}

void ListReader::setPriority(QVariantList list)
{
    QVariant list_var(list);
    priority.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        priority.append(v.value<unsigned int>());
    }
}

QVariantList ListReader::readPriority()
{
    return priority;
}

void ListReader::setConfigrations(QString processtype, int numbers, int rrTime, bool Preemptive)
{
    processType = processtype;
    numberOfprocess = numbers;
    if(processType == "Round Robin")
        timeQuantum = rrTime;
    if(processType == "Priority" || processType == "SJF")
        preemptive = Preemptive;
}


void ListReader::setTimes(QVariantList timeList)
{
    QVariant list_var(timeList);
    processtime.clear();
    foreach(QVariant v, list_var.value<QVariantList>())
    {
        processtime.append(v.value<qreal>());
    }
}

void ListReader::setGuiList()
{
    QVariant list_arrival(arrivaltime);
    ArrivalTime.clear();
    BurstTime.clear();
    foreach(QVariant v, list_arrival.value<QVariantList>())
    {
        ArrivalTime.append(v.value<qreal>());
    }
    QVariant list_burst(bursttime);
    foreach(QVariant v, list_burst.value<QVariantList>())
    {
        BurstTime.append(v.value<qreal>());
    }
    if(this->processType == "Priority")
    {
        QVariant list_priority(priority);
        Priority.clear();
        foreach(QVariant v, list_priority.value<QVariantList>())
        {
            Priority.append(v.value<unsigned int>());
        }
    }
    if(this->processType == "Priority" || this->processType == "SJF")
    {
        isPreemptive = this->preemptive;
    }
    if(this->processType == "Round Robin")
    {
        TimeQuantum = this->timeQuantum;
    }
    ProcessType = this->processType;
    NUmberOfProcess = this->numberOfprocess;
    emit readyToLoadSimulator();
}

void ListReader::setSimulationList()
{
    processid.clear();
    processtime.clear();
    processaverage.clear();
    for(int i = 0 ; i < ScheduledId.size(); i++)
    {
        processid.append(ScheduledId[i]);
        processtime.append(ScheduledTime[i]);
        //processaverage.append(WaitingTimePerProcess[i]);
    }
    emit listNotifier();
}
