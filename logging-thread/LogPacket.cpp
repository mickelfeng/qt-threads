#include "LogPacket.h"
#include <QDateTime>

std::unique_ptr<LogPacket> createSimplePacket(
  const QString& severity,
  const QString& message)
{
  std::unique_ptr<LogPacket> packet(new LogPacket);
  packet->severity = severity;
  packet->message = message;
  packet->timestamp = QDateTime::currentMSecsSinceEpoch();
  return std::move(packet);
}

