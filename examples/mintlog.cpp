#include "../include/mintlog.hpp"

int main() {
  // REMEMBER - SETTINGS ARE NOT SHARED BETWEEN FILES

  log::level = log::debug; // ignore if level is lower than `debug` (never) - `warning` by default

  log::log(log::info, "Application started");
  log::log(log::debug, "User: ", "John", ", ID: ", 42); // all arguments are concatenated

  int error_code = 404;
  if (error_code != 200) {
    log::log(log::error, "Request failed: ", error_code);
  }

  log::muted = true;
  log::log(log::fatal, "We are doomed!!!"); // will be ignored
  log::muted = false;

  log::log(log::warning, "Suboptimal memory usage: ", 145.67, "MB");
  log::log(log::fatal, "Critical error in the \"", "network", "\" module");

  log::clear_file("app.log"); // completely optional
  log::log_path = "app.log";  // may also set to `stdout` (default) or `stderr`

  log::time_fmt = "%d.%m %H:%M:%S"; // custom timestamp format
  log::log(log::info, "Configuration loaded");
}