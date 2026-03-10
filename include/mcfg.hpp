#pragma once
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>
#include <stdexcept>

namespace mcfg {
  class config {
    std::filesystem::path path;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> content;

    static std::string strip(std::string str) {
      return str.erase(str.find_last_not_of(" \t\r\f\v") + 1).erase(0, str.find_first_not_of(" \t\r\f\v"));
    }

  public:
    // Parse the config at given path.
    // @throws `std::invalid_argument` - invalid config; see what().
    // @throws `std::runtime_error` - failed to read the config.
    config(std::filesystem::path filepath) : path(filepath) {
      std::ifstream fin(path);
      if (!fin) throw std::runtime_error("Failed to open \"" + std::string(path) + '"');

      size_t lineno = 1;
      std::string current_section_name;
      std::unordered_map<std::string, std::string> current_section_content;

      for (std::string line; std::getline(fin, line); lineno++) {
        line = strip(line);

        if (line.empty() || line[0] == '#' || line[0] == ';') {
          continue;
        } else if (line[0] == '[') {
          if (!current_section_content.empty()) {
            content[current_section_name].merge(current_section_content);
            current_section_content.clear();
          }
          size_t rsb_pos = line.find_last_of(']');
          if (rsb_pos == std::string::npos)
            throw std::invalid_argument(std::string(path) + ":" + std::to_string(lineno) + ": '[' was never closed.");
          current_section_name = line.substr(1, rsb_pos - 1);
        } else {
          size_t equal_pos = line.find_first_of('=');
          if (equal_pos == std::string::npos)
            throw std::invalid_argument(std::string(path) + ":" + std::to_string(lineno) + ": no '=' after field's name.");
          if (equal_pos == 0)
            throw std::invalid_argument(std::string(path) + ":" + std::to_string(lineno) + ": field has no name");
          std::string name = strip(line.substr(0, equal_pos));
          std::string value = strip(line.substr(equal_pos + 1));
          current_section_content[name] = value;
        }
      }
      if (!current_section_content.empty()) content[current_section_name].merge(current_section_content);
    }

    // Return the value of a given field.
    // If no such section or field - return an empty string.
    const std::string get(const std::string& section_name, const std::string& field_name) const {
      try {
        return content.at(section_name).at(field_name);
      } catch (std::out_of_range& _) {
        return "";
      }
    }

    // Set the value of a given field.
    // If no such section or field exists - create one.
    void set(const std::string& section_name, const std::string& field_name, const std::string& value) {
      content[strip(section_name)][strip(field_name)] = strip(value);
    }

    // Get a list of sections in the config
    std::vector<std::string> sections() const {
      std::vector<std::string> keys;
      keys.reserve(content.size());
      for (const auto& section : content)
        keys.push_back(section.first);
      return keys;
    }

    // Get a list of fields in a given section
    std::vector<std::string> fields(const std::string& section_name) const {
      std::vector<std::string> keys;
      try {
        keys.reserve(content.at(section_name).size());
      } catch (std::out_of_range& _) {
        return keys;
      }
      for (const auto& field : content.at(section_name))
        keys.push_back(field.first);
      return keys;
    }

    bool has_section(const std::string& section_name) const {
      return content.find(section_name) != content.end();
    }

    bool has_field(const std::string& section_name, const std::string& field_name) const {
      auto section = content.find(section_name);
      return section != content.end() && section->second.find(field_name) != section->second.end();
    }


    // Erase a section and all it's fields.
    void erase_section(const std::string& section_name) {
      content.erase(section_name);
    }

    // Erase a field.
    // If it was the only field in the section - erase the section as well.
    void erase(const std::string& section_name, const std::string& field_name) {
      auto sec_it = content.find(section_name);
      if (sec_it != content.end()) {
        sec_it->second.erase(field_name);
        if (sec_it->second.empty())
          content.erase(sec_it);
      }
    }


    // Save the current state of the config into a file.
    // Won't keep any comments.
    // @throws `std::runtime_error` - failed to open the file
    void save_as(std::filesystem::path filepath) const {
      std::ofstream fout(filepath);
      if (!fout) throw std::runtime_error("Failed to open \"" + std::string(filepath) + '"');

      auto global = content.find("");
      if (global != content.end()) for (const auto& parameter : global->second)
        fout << parameter.first << " = " << parameter.second << '\n';

      for (const auto& section : content) {
        if (section.first.empty()) continue;
        fout << "\n[" << section.first << "]\n";
        for (const auto& parameter : section.second)
          fout << parameter.first << " = " << parameter.second << '\n';
      }
    }

    // Save the config to the path it was read from. Remove any comments.
    // @throws `std::runtime_error` - failed to open the file
    void save() const { save_as(path); }
  };
}