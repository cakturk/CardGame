#include "avahiresolver.h"

AvahiResolver::AvahiResolver(QObject *parent) :
        QObject(parent), dnssref(0), avahiSocket(0), avahiPort(-1)
{ }

AvahiResolver::~AvahiResolver()
{
    cleanupResolve();
}

void AvahiResolver::cleanupResolve()
{
    if (dnssref) {
        DNSServiceRefDeallocate(dnssref);
        dnssref = 0;
        delete avahiSocket;
        avahiPort = -1;
    }
}

void AvahiResolver::resolveAvahiRecord(const AvahiRecord &record)
{
    if (dnssref) {
        qDebug() << "Resolve in process aborting";
        return;
    }
    DNSServiceErrorType err = DNSServiceResolve(&dnssref, 0, 0,
                                                record.servName.toUtf8().constData(),
                                                record.servType.toUtf8().constData(),
                                                record.replyDomain.toUtf8().constData(),
                                                (DNSServiceResolveReply)avahiResolveReply, this);
    qDebug() << "reply domain " << record.replyDomain;
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

void AvahiResolver::socketReadyRead()
{
    DNSServiceErrorType err = DNSServiceProcessResult(dnssref);
    if (err != kDNSServiceErr_NoError)
        emit error(err);
}

void AvahiResolver::avahiResolveReply(DNSServiceRef, DNSServiceFlags,
                                 quint32, DNSServiceErrorType errorCode,
                                 const char *, const char *hosttarget, quint16 port,
                                 quint16, const char *, void *context)
{
    AvahiResolver *resolver = static_cast<AvahiResolver *>(context);
    if (errorCode != kDNSServiceErr_NoError) {
        emit resolver->error(errorCode);
        return;
    }
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    {
        port =  0 | ((port & 0x00ff) << 8) | ((port & 0xff00) >> 8);
    }
#endif

    resolver->avahiPort = port;

    // TODO: desktop.local.
    qDebug() << hosttarget;
    QString hostName(hosttarget);
    hostName = hostName.remove(hostName.size() - 1, 1);

    QHostInfo::lookupHost(hostName, resolver,SLOT(finishConnect(const QHostInfo&)));
}

void AvahiResolver::finishConnect(const QHostInfo &hostinfo)
{
    emit avahiRecordResolved(hostinfo, avahiPort);
    QMetaObject::invokeMethod(this, "cleanupResolve", Qt::QueuedConnection);
}
