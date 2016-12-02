#pragma once

#include "envoy/common/pure.h"
#include "envoy/filesystem/filesystem.h"

namespace AccessLog {

class AccessLogManager {
public:
  virtual ~AccessLogManager() {}

  /**
   * Reopen all of the access log files.
   */
  virtual void reopen() PURE;

  /**
   * FIXFIX
   */
  virtual Filesystem::FilePtr createAccessLog(const std::string& file_name) PURE;
};

typedef std::unique_ptr<AccessLogManager> AccessLogManagerPtr;

} // AccessLog
