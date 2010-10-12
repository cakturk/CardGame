#include "avahibrowser.h"
#include <qdebug.h>

AvahiBrowser::AvahiBrowser(QObject *parent) :
        QObject(parent), dnssref(0), avahiSocket(0)
{ }

AvahiBrowser::~AvahiBrowser()
{
    if (dnssref) {
        DNSServiceRefDeallocate(dnssref);
        dnssref = 0;
    }
}

void AvahiBrowser::browseForService(const QString &serviceType)
{
    DNSServiceErrorType err = DNSServiceBrowse(&dnssref, 0, 0,
                                               serviceType.toUtf8().constData(),
                                               0, avahiBrowseReply, this);
    if(err != kDNSServiceErr_NoError) {
        emit error(err);
    } else {
        int sockfd = DNSServiceRefSockFD(dnssref);
        if (sockfd == -1) {
            emit error(kDNSServiceErr_Invalid);
        } else {
            avahiSocket = new QSocketNotifier(sockfd, QSocketNotifier::Read, this);
            connect(avahiSocket, SIGNAL(activated(int)), this, SLOT(socketReadyRead()));
        }
    }
}

/* process data */
void AvahiBrowser::socketReadyRead()
{
    DNSServiceErrorType err = DNSServiceProcessResult(dnssref);
    if (err != kDNSServiceErr_NoError)
        emit error(err);
}

void AvahiBrowser::avahiBrowseReply(DNSServiceRef, DNSServiceFlags flags,
                                    quint32, DNSServiceErrorType errorCode,
                                    const char *serviceName, const char *serviceType,
                                    const char *replyDomain, void *context)
{
    AvahiBrowser *browser = static_cast<AvahiBrowser *>(context);

    if (errorCode != kDNSServiceErr_NoError) {
        browser->error(errorCode);
    } else {
        AvahiRecord record(serviceName, serviceType, replyDomain);
        if(flags & kDNSServiceFlagsAdd) {
            if (! browser->avahiRecords.contains(record))
                browser->avahiRecords.append(record);
        } else {
            /* no longer available remove record */
            browser->avahiRecords.removeAll(record);
        }

        if (! (flags & kDNSServiceFlagsMoreComing)) {
            emit browser->currentAvahiRecordsChanged(browser->avahiRecords);
        }
    }
}
