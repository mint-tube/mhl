#include "../include/mcfg.hpp"

// read examples/resources/app.cfg for more details

int main() {
  mcfg::config config("examples/resources/app.cfg");
  config.save_as("app.ini");
  return 0;
}
