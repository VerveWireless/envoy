#pragma once

#include "envoy/access_log/access_log.h"

namespace AccessLog {

class MockAccessLogManager : public AccessLogManager {
public:
  MockAccessLogManager();
  ~MockAccessLogManager();

  // AccessLog::AccessLogManager
  MOCK_METHOD0(reopen, void());
  MOCK_METHOD1(createAccessLog, Filesystem::FilePtr(const std::string& file_name));
};

} // AccessLog
