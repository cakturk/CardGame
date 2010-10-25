#ifndef AVAHIBROWSER_H
#define AVAHIBROWSER_H

#include <QObject>
#include <QSocketNotifier>
#include <dns_sd.h>
#include "AvahiRecord.h"

class AvahiBrowser : public QObject
{
    Q_OBJECT
public:
    AvahiBrowser(QObject *parent = 0);
    ~AvahiBrowser();

    void browseForService(const QString &serviceType);

signals:
    void error(DNSServiceErrorType err);
    void currentAvahiRecordsChanged(const QList<AvahiRecord> &records);

private slots:
    void socketReadyRead();

private:
    DNSServiceRef dnssref;
    QSocketNotifier *avahiSocket;
    QList<AvahiRecord> avahiRecords;

    static void avahiBrowseReply(DNSServiceRef, DNSServiceFlags flags, quint32,
                                 DNSServiceErrorType errorCode, const char *serviceName,
                                 const char *serviceType, const char *replyDomain, void *context);
};

#endif // AVAHIBROWSER_H
