#ifndef AVAHIRECORD_H
#define AVAHIRECORD_H

#include <QtCore/QMetaType>
#include <QtCore/QString>

class AvahiRecord
{
public:
    AvahiRecord() { }

    AvahiRecord(const QString &server_name, const QString &serverType, const QString &domain) :
            servName(server_name), servType(serverType), replyDomain(domain)
    {}

    AvahiRecord(const char *name, const char *sType, const char *domain)
    {
        servName = QString::fromUtf8(name);
        servType = QString::fromUtf8(sType);
        replyDomain = QString::fromUtf8(domain);
    }

    QString servName;
    QString servType;
    QString replyDomain;

    /** Equals operator */
    bool operator==(const AvahiRecord &other) const {
        return servName == other.servName
                && servType == other.servType
                && replyDomain == other.replyDomain;
    }
};

Q_DECLARE_METATYPE(AvahiRecord)

#endif // AVAHIRECORD_H
