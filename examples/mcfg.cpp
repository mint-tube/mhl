#include <iostream>
#include "../include/mcfg.hpp"

/*** read examples/resources/app.cfg for more details ***/

int main() {
  mcfg::config cfg("examples/resources/app.cfg"); // **throws**; empty file is a valid config

  std::cout << cfg.get("", "new_path") << '\n';   // fields in the beggining are put in this section

  std::cout << cfg.get("Server", "host") << '\n'; // the last occurence of the fields is prevalent

  cfg.set("Server", "port", "8080");              // serializing and deserializing is up to you

  if (!cfg.has_field("Server", "app_name"))
    cfg.set("Server", "app_name", "mclip");       // won't execute - empty field is a valid field.

  for (const auto &s : cfg.list_sections())
    std::cout << s << '\n';

  cfg.save_as(cfg.get("", "new_path"));           // erases the comments
}
