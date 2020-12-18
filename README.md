Simple Lua Ncurses wrapper

## Introduction
This is my simple wrapper for using ncurses with lua.  
I attempt to keep the function calls in lua as close to the corresponding calls in C as i can.  
The features added are usually on an as needed basis, so it is currently far from a complete implementation, and probably never will be. 

## Functions Implemented
- getch() 
- mvgetch() 
- wgetch() 
- mvwgetch() 
- wmove() 
- move() 
- newwin() 
- wborder() 
- mvwprintw() 
- wprintw() 
- printw() 
- refresh()
- clear()
- wclear() 
- wrefresh() 
- curs_set()
- init_pair()
- start_color()
- init_color()
- cbreak()
- noecho()
- echo()
- endwin()
- initscr()
- getyx()
- wgetyx()
- mvprintw()
- delwin()
- clrtoeol()
- mvdelch()
- delch()
- keypad()
- COLOR_PAIR()
- wattron()
- wattroff()
- wcolor_set()
- attron()
- attroff()
- color_set()

## Compiling
To compile the C library simply use the make file. 

## Requirements
- Lua
- C compiler (gcc is used in the make file)
- make (if you intend to use the included make file)
- ncurses

## using sluacurses
place `require("sluacurses")` into your lua file.  
make sure that you include sluacurses.so into the same directory as your project or it is in a path which lua can find.

## Contributing
If you would like to contribute please feel free to. I welcome any help.

