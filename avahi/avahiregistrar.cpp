#include "avahiregistrar.h"
#include <QSocketNotifier>

AvahiRegistrar::AvahiRegistrar(QObject *parent) :
        QObject(parent), dnssref(0), avahiSocket(0)
{
    qWarning() << "in the constructor";
}

AvahiRegistrar::~AvahiRegistrar()
{
    if (dnssref) {
        DNSServiceRefDeallocate(dnssref);
        dnssref = 0;
    }
    qDebug() << "hasta la vista baby";
}

void AvahiRegistrar::registerService(const AvahiRecord &record, quint16 servicePort)
{
    if (dnssref) {
        return;
    }

    quint16 port = servicePort;

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    {
        port =  0 | ((servicePort & 0x00ff) << 8) | ((servicePort & 0xff00) >> 8);
    }
#endif

    DNSServiceErrorType err = DNSServiceRegister(&dnssref, 0, 0, record.servName.toUtf8(),
                                                 record.servType.toUtf8().constData(), record.replyDomain.isEmpty() ? 0
                                                     : record.replyDomain.toUtf8().constData(), 0,
                                                     port, 0, 0, avahiRegisterService, this);
    if (err != kDNSServiceErr_NoError) {
        emit error(err);
    } else {
        int sockfd = DNSServiceRefSockFD(dnssref);
        if (sockfd == -1) {
            emit error(kDNSServiceErr_Invalid);
        } else {
            avahiSocket = new QSocketNotifier(sockfd, QSocketNotifier::Read, this);
            connect(avahiSocket, SIGNAL(activated(int)), this, SLOT(avahiSocketReadyRead()));
        }
    }
}

void AvahiRegistrar::avahiSocketReadyRead()
{
    DNSServiceErrorType err = DNSServiceProcessResult(dnssref);
    if (err != kDNSServiceErr_NoError)
        emit error(err);
}

void AvahiRegistrar::avahiRegisterService(DNSServiceRef, DNSServiceFlags,
                                          DNSServiceErrorType errorCode, const char *name,
                                          const char *servType, const char *domain, void *context)
{
    AvahiRegistrar *registrar = static_cast<AvahiRegistrar *>(context);
    if (errorCode != kDNSServiceErr_NoError) {
        emit registrar->error(errorCode);
    } else {
        registrar->finalRecord = AvahiRecord(QString::fromUtf8(name),
                                             QString::fromUtf8(servType),
                                             QString::fromUtf8(domain));
        qDebug() << "Service registered";
        emit registrar->serviceRegistered(registrar->finalRecord);
    }
}
