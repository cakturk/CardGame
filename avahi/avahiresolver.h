#ifndef AVAHIRESOLVER_H
#define AVAHIRESOLVER_H

#include <QObject>
#include <QHostInfo>
#include <dns_sd.h>
#include "AvahiRecord.h"

class QSocketNotifier;
class AvahiResolver : public QObject
{
    Q_OBJECT
public:
    AvahiResolver(QObject *parent = 0);
    ~AvahiResolver();

    void resolveAvahiRecord(const AvahiRecord &record);

signals:
    void avahiRecordResolved(const QHostInfo &hostInfo, quint16 port);
    void error(DNSServiceErrorType err);

private slots:
    void socketReadyRead();
    void cleanupResolve();
    void finishConnect(const QHostInfo&);

private:
    static void avahiResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags,
                           quint32 interfaceIndex, DNSServiceErrorType errorCode,
                           const char *fullName, const char *hosttarget, quint16 port,
                           quint16 txtLen, const char *txtRecord, void *context);

    DNSServiceRef dnssref;
    QSocketNotifier *avahiSocket;
    quint16 avahiPort;
};

#endif // AVAHIRESOLVER_H
