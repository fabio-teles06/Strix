#pragma once
#include <string>
#include <vector>
#include <memory>

#include "engine/include/engine_export.h"
namespace engine {
class ENGINE_EXPORT Logger {
 public:
  enum class Level {
    kDebug,
    kInfo,
    kWarning,
    kError,
    kFatal,
  };

  static void SetLevel(Level level);
  static Level GetLevel();

  static void Log(Level level, const std::string& message);
  static void Log(Level level, const std::string& message, const std::vector<std::string>& tags);

 private:
  static Level current_level_;
};

}  // namespace engine