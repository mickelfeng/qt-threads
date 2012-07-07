#ifndef LOGPACKET_H
#define LOGPACKET_H

#include <string>
#include <vector>
#include <memory>

struct LogPacket
{
  std::string severity;
  std::vector<std::string> tags;
  std::string message;
  long long int timestamp;
};

std::unique_ptr<LogPacket> createSimplePacket(const std::string& severity,
  const std::string& message);

#endif // LOGPACKET_H

