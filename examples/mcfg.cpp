#include "../include/mcfg.hpp"

int main() {
  mcfg::config config("examples/resources/app.cfg");
  config.save_as("app.ini");
}