#include "nvimfy.hpp"

NVimfy::NVimfy(const std::string& file){
  
  lines.push_back("");
  x = y = 0;
  mode = 'n';
  status = "NORMAL";

  if(file.empty()){
    filename = "untitled";
  }else{
    filename = file;
  }

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
  while(mode != 'q'){
    update();
    statusline();
    print();
    int c = getch();
    input(c);
  }
}

void NVimfy::update(){
  switch (mode){
    case 27:
    case 'n':
      status = "NORMAL";
      break;
    case 'i':
      status = "INSERT";
      break;
    case 'q':
      break;
  }
}

void NVimfy::statusline(){
  attron(A_REVERSE);
  mvprintw(LINES - 1, 0, status.c_str());
  attroff(A_REVERSE);
}

void NVimfy::input(int c){
  switch (c){
    case KEY_UP:
      up();
      return;
    case KEY_LEFT:
      left();
      return;
    case KEY_RIGHT:
      right();
      return;
    case KEY_DOWN:
      down();
      return;
  }

  switch (mode){
    case 27:
    case 'n':
      switch (c){
        case 27:
        case 'q':
          mode = 'q';
          break;
        case 'i':
          mode = 'i';
          break;
        case 'w':
          mode = 'w';
          break;
      }
    break;
    case 'i':
      switch(c){
        case 27:
          mode = 'n';
          break;
        case 127:
        case KEY_BACKSPACE:
          if( x == 0 && y > 0){
            x = lines[y - 1].length();
            lines[y - 1] += lines[y];
            m_remove(y);
            up();
          }else if( x > 0 ){
            lines[y].erase(--x, 1);
          }
        break;
        case KEY_DC:
          if( x == lines[y].length() && y != lines.size() - 1 ){
            lines[y] += lines[y + 1];
          } else {
            lines[y].erase(x, 1);
          }
        break;
        case KEY_ENTER:
        case 10:
          if(x < lines[y].length()){
            m_insert(lines[y].substr(x, lines[y].length() - x), y + 1);
            lines[y].erase(x, lines[y].length() - x);
          } else {
            m_insert("", y + 1);
          }
          x = 0;
          down();
        break;
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
        case 9:
          lines[y].insert(x, 2, ' ');
          x += 2;
        break;
        default:
          lines[y].insert(x, 1, c);
          ++x;
      }
  } 
}

void NVimfy::print(){
  for (size_t i = 0; i < (size_t)LINES - 1; ++i){
    if(i >= lines.size()){
      move(i, 0);
      clrtoeol();
    }else{
      mvprintw(i, 0, lines[i].c_str());
    }
    clrtoeol();
  }
  move(y, x);
}

void NVimfy::m_remove(int number){
  lines.erase(lines.begin() + number);
}

std::string NVimfy::m_tabs(std::string& line){
  std::size_t tab = line.find('\t');
  return tab == line.npos ? line : m_tabs(line.replace(tab, 1, "  "));
}

void NVimfy::m_insert(std::string line, int number){
  line = m_tabs(line);
  lines.insert(lines.begin() + number, line);
}

void NVimfy::m_append(std::string& line){
  line = m_tabs(line);
  lines.push_back(line);
}

void NVimfy::up(){
  if(y > 0){
    --y;
  }

  if(x >= lines[y].length()){
    x = lines[y].length();
  }
  move(y, x);
}

void NVimfy::left(){
  if(x > 0){
    --x;
    move(y, x);
  }
}

void NVimfy::right(){
  if(x <= COLS && x <= lines[y].length() - 1){
    ++x;
    move(y, x);
  }
}

void NVimfy::down(){
  if(x < LINES && y < lines.size() - 1){
    ++y;
  }
  if(x >= lines[y].length()){
    x = lines[y].length();
  }
  move(y, x);
}
