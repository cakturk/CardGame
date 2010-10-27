#ifndef AVAHIREGISTRAR_H
#define AVAHIREGISTRAR_H

#include <QObject>
#include <QSocketNotifier>
#include <QDebug>
#include "AvahiRecord.h"
#include "dns_sd.h"

class AvahiRegistrar : public QObject
{
    Q_OBJECT

public:
    AvahiRegistrar(QObject *parent = 0);
    ~AvahiRegistrar();

    void registerService(const AvahiRecord &record, quint16 servicePort);
    AvahiRecord registeredRecord() const { return finalRecord; }

signals:
    void error(DNSServiceErrorType error);
    void serviceRegistered(const AvahiRecord &record);

private slots:
    void avahiSocketReadyRead();

private:
    static void avahiRegisterService(DNSServiceRef sdRef, DNSServiceFlags,
                                     DNSServiceErrorType errorCode, const char *name,
                                     const char *servType, const char *domain,
                                     void *context);

    DNSServiceRef dnssref;
    QSocketNotifier *avahiSocket;
    AvahiRecord finalRecord;
};

#endif // AVAHIREGISTRAR_H
