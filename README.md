Simple Lua Ncurses wrapper

## Introduction
This is my simple wrapper for using ncurses with lua.  
I attempt to keep the function calls in lua as close to the corresponding calls in C as i can.  
The fetaures added are usually on an as needed basis, so it is currently far from a complete implementation, and probably never will be.  
This is mostly just for me to play around with. I don't expect any serious usage of this stuff.  

## Functions Implemented
- getch() 
- mvgetch() 
- wgetch() 
- wmvwgetch() 
- wmove() 
- move() 
- newwin() 
- wborder() 
- wmvprintw() 
- wprintw() 
- printw() 
- refresh()
- clear()
- wclear() 
- wrefresh() 
- curs_set()
- init_pair()
- start_color()
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

## Note about newwin and how windows are handled

newwin() takes as its first argument the name for the new window.  
This differs from the C implementation. This is because of how I manage windows.  
I decided that instead of passing ncurses WINDOW back and forth, I would instead store each window into a global array in C.  
The way to access each window is to hash the name and then pass the output of the hash back and forth.  
The program uses the hash as the access token for the window.  
newwin returns the hashed name as its return data. The user just has to store that into a variable or table in lua and then use that for any of the window functions.  


#### example

    local window = newwin("my window",10,10,0,0)
    mvwprint(window,1,1,"this is my window")

Please see 'examples' directory for more examples.

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

