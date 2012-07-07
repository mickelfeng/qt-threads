#ifndef LOGPACKET_H
#define LOGPACKET_H

#include <QString>
#include <vector>
#include <memory>

struct LogPacket
{
  QString severity;
  std::vector<QString> tags;
  QString message;
  long long int timestamp;
};

std::unique_ptr<LogPacket> createSimplePacket(const QString& severity,
  const QString& message);

#endif // LOGPACKET_H

