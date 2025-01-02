#include "nvimfy.hpp"

NVimfy::NVimfy(){
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
}

NVimfy::~NVimfy(){
  refresh();
  endwin();
}

void NVimfy::run(){
  printw("Funcionando!");
  getch();
}