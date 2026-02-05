#include "../include/mintlog.hpp"

int main() {
  // REMEMBER - SETTINGS ARE NOT SHARED BETWEEN FILES

  log::level = log::Level::DEBUG; // ignore if level is lower than `debug` (never) - `warning` by default

  log::info("Application started");
  log::debug("User: ", "John", ", ID: ", 42); // all arguments are concatenated

  int error_code = 404;
  if (error_code != 200) {
    log::error("Request failed: ", error_code);
  }

  log::muted = true;
  log::fatal("We are doomed!!!"); // will be ignored
  log::muted = false;

  log::timestamps = false; // disable timestamps
  log::warning("Suboptimal memory usage: ", 145.67, "MB");
  log::fatal("Critical error in the \"", "network", "\" module");

  log::clear("app.log"); // completely optional
  log::path = "app.log";  // may also set to `stdout` (default) or `stderr`

  log::timestamps = true;
  log::time_fmt = "%d.%m %H:%M:%S"; // custom timestamp format
  log::info("Configuration loaded");
}