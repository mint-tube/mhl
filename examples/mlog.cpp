#include "../include/mlog.hpp"

int main() {
  mlog::level = mlog::Level::Debug; // ignore if level is lower than `debug`; `warning` by default

  mlog::info("Application started");
  mlog::debug("User: ", "John", ", ID: ", 42);             // arguments are concatenated

  int error_code = 404;
  if (error_code != 200)
    mlog::error("Request failed: ", error_code);

  mlog::muted = true;                                      // temporarily mute the logging
  mlog::fatal("We are doomed!!!");
  mlog::muted = false;

  mlog::timestamps = false;                                // timestamps are enabled by default
  mlog::warning("High memory usage: ", 145.67, "MB");
  mlog::fatal("Critical error in the \"network\" module");

  mlog::path = "app.log";                                  // logging to a file
  mlog::clear("app.log");                                  // optional clearing of it 

  mlog::timestamps = true;
  mlog::time_fmt = "%d.%m %H:%M:%S";                       // custom timestamp format
  mlog::info("Configuration loaded");
}
