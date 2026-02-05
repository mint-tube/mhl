#include "../include/mintlog.hpp"

int main() {
  // NOTE - SETTINGS ARE NOT SHARED BETWEEN FILES

  log::level = log::debug;   // ignore if level lower than `debug` (never) - `warning` by default

  log::log(log::info, "Application started");
  log::log(log::debug, "User: {}, ID: {}", "John", 42); // formatting

  int error_code = 404;
  if (error_code != 200) {
    log::log(log::error, "Request failed: {}", error_code);
  }

  log::muted = true;
  log::log(log::fatal, "We are doomed!!!"); // will be ignored
  log::muted = false;

  log::log(log::warning, "Suboptimal memory usage: {:.2f} MB", 145.67);
  log::log(log::fatal, "Critical error in the \"{}\" module", "network");

  // writing to a file
  log::clear_file("app.log"); // completely optional
  log::log_path = "app.log";  // can set to `stdout` (default) or `stderr`
  log::log(log::info, "Configuration loaded");
}