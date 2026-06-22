#include "../include/mlog.hpp"

int main() {
  mlog::level = mlog::Level::Debug; // ignore if level is lower than `debug` (never) - `warning` by default

  mlog::info("Application started");
  mlog::debug("User: ", "John", ", ID: ", 42); // all arguments are concatenated

  int error_code = 404;
  if (error_code != 200)
    mlog::error("Request failed: ", error_code);

  mlog::muted = true;
  mlog::fatal("We are doomed!!!"); // will be ignored
  mlog::muted = false;

  mlog::timestamps = false; // disable timestamps
  mlog::warning("Suboptimal memory usage: ", 145.67, "MB");
  mlog::fatal("Critical error in the \"", "network", "\" module");

  mlog::clear("app.log"); // completely optional
  mlog::path = "app.log"; // file to log to (or `stdout` (default), `stderr`)

  mlog::timestamps = true;
  mlog::time_fmt = "%d.%m %H:%M:%S"; // custom timestamp format
  mlog::info("Configuration loaded");
}
