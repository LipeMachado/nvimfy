#pragma once
#pragma clang diagnostic ignored "-Wformat-security"

#include <ncurses.h>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

class NVimfy {

  size_t x, y;
  char mode;

  std::string filename, status, section;
  std::vector<std::string> lines;

  void m_remove(int);
  std::string m_tabs(std::string&);
  void m_insert(std::string, int);
  void m_append(std::string&);

  public:
    NVimfy(const std::string&);
    ~NVimfy();
    void run();
  
  protected:
    void update();
    void statusline();
    void input(int);
    void print();

    void up();
    void left();
    void right();
    void down();

    void open();
    void save();
};