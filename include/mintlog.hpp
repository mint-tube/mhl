#pragma once
#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>

namespace log {
  enum class Level { DEBUG, INFO, WARNING, ERROR, FATAL };

  // Configuration is not shared between files
  inline std::string log_path = "stdout"; // "stdout" and "stderr" have colors
  inline std::string time_fmt = "%d-%m-%Y %H:%M:%S";
  inline Level level = Level::WARNING;
  inline bool timestamps = true;
  inline bool muted = false;

  inline void clear(const std::string& path) { std::remove(path.c_str()); }

  inline const std::string level_to_string(Level lvl) {
    switch (lvl) {
      case Level::DEBUG:   return "DEBUG  ";
      case Level::INFO:    return "INFO   ";
      case Level::WARNING: return "WARNING";
      case Level::ERROR:   return "ERROR  ";
      case Level::FATAL:   return "FATAL  ";
      default:             return "UNKNOWN";
    }
  }
  inline const std::string level_to_color(Level lvl) {
    switch (lvl) {
      case Level::DEBUG:   return "\x1b[36m";
      case Level::INFO:    return "\x1b[32m";
      case Level::WARNING: return "\x1b[33m";
      case Level::ERROR:   return "\x1b[31m";
      case Level::FATAL:   return "\x1b[1;31m";
      default:             return "";
    }
  }

  inline std::string get_timestr() {

    time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buffer[64];
    std::strftime(buffer, sizeof(buffer), time_fmt.c_str(), std::localtime(&time));
    return std::string(buffer);
  }

  template<typename... Args>
  void write(Level lvl, Args&&... args) {
    if (lvl < level || muted) return;

    bool use_color = (path == "stdout" || path == "stderr");
    std::string color_start = use_color ? level_to_color(lvl) : "";
    std::string color_end = use_color ? "\x1b[00m" : "";

    std::ostringstream stream;
    if (timestamps) stream << get_timestr() << " | ";                    // timestamp
    stream << color_start << level_to_string(lvl) << color_end << " | "; // level
    ((stream << std::forward<Args>(args)), ...);                         // message

    if (log_path == "stdout") std::cout << stream.str() << '\n';
    else if (log_path == "stderr") std::cerr << stream.str() << '\n';
    else {
      std::ofstream file(log_path, std::ios::app);
      if (file.is_open()) {
        file << stream.str() << '\n';
      } else {
        std::cerr << "Failed to open log file: " << log_path;
      }
    }
  }

  template<typename... Args>
  void debug(Args&&... args) { write(Level::DEBUG, std::forward<Args>(args)...); }
  template<typename... Args>
  void info(Args&&... args) { write(Level::INFO, std::forward<Args>(args)...); }
  template<typename... Args>
  void warning(Args&&... args) { write(Level::WARNING, std::forward<Args>(args)...); }
  template<typename... Args>
  void error(Args&&... args) { write(Level::ERROR, std::forward<Args>(args)...); }
  template<typename... Args>
  void fatal(Args&&... args) { write(Level::FATAL, std::forward<Args>(args)...); }
}

/*
  Copyright (c) 2026 mint_tube <mmooyrs@gmail.com>

  Redistribution and use of this file, with or without modification,
  are permitted in any medium without royalty provided the copyright
  notice and this notice are preserved. This file is offered as-is,
  without any form of warranty.
*/