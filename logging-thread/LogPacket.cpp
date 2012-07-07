#include "LogPacket.h"

std::unique_ptr<LogPacket> createSimplePacket(
  const std::string& severity,
  const std::string& message)
{
  std::unique_ptr<LogPacket> packet(new LogPacket);
  packet->severity = severity;
  packet->message = message;
  return std::move(packet);
}

