#pragma once

#include "envoy/access_log/access_log.h"
#include "envoy/common/pure.h"

namespace Upstream {

class Host;
typedef std::shared_ptr<Host> HostPtr;

namespace Outlier {

/**
 * Sink for per host data. Proxy filters should send pertinent data when available.
 */
class DetectorHostSink {
public:
  virtual ~DetectorHostSink() {}

  /**
   * Add an HTTP response code for a host.
   */
  virtual void putHttpResponseCode(uint64_t code) PURE;

  /**
   * Add a response time for a host (in this case response time is generic and might be used for
   * different operations including HTTP, Mongo, Redis, etc.).
   */
  virtual void putResponseTime(std::chrono::milliseconds time) PURE;
};

typedef std::unique_ptr<DetectorHostSink> DetectorHostSinkPtr;

enum class EjectionType { Consecutive5xx };

/**
 * fixfix
 */
class EventLogger {
public:
  virtual ~EventLogger() {}

  /**
   * fixfix
   */
  virtual void logEject(HostPtr host, EjectionType type) PURE;

  /**
   *
   */
  virtual void logUneject(HostPtr host) PURE;
};

typedef std::shared_ptr<EventLogger> EventLoggerPtr;

/**
 * Interface for an outlier detection engine. Uses per host data to determine which hosts in a
 * cluster are outliers and should be ejected.
 */
class Detector {
public:
  virtual ~Detector() {}

  /**
   * Outlier detection change state callback.
   */
  typedef std::function<void(HostPtr host)> ChangeStateCb;

  /**
   * Add a changed state callback to the detector. The callback will be called whenever any host
   * changes state (either ejected or brought back in) due to outlier status.
   */
  virtual void addChangedStateCb(ChangeStateCb cb) PURE;
};

typedef std::unique_ptr<Detector> DetectorPtr;

} // Outlier
} // Upstream
