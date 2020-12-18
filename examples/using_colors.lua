
--[[
    example file from sluacurses.
    File shows a simple example of using colors through sluacurses.
--]]

local Curses = require("sluacurses")  --load sluacurses into program

initscr()     --start ncurses
start_color() --enable colors
curs_set(0)   --dont display cursor
refresh()     --refresh screen

--create a new window and save its hashed name to 'w'
--args: name,height,width,starting y, starting x
local w = newwin(15,25,5,5)
local red = 1                          --store number for the color pair
init_pair(red,COLOR_RED,COLOR_BLACK)   --create color pair. red foreground with black background

local green = 2
init_pair(green,COLOR_WHITE,COLOR_GREEN)  --white on green background

attron(COLOR_PAIR(red))      --use the color pair 'red' when printing to stdscr
printw("this is red text")
attroff(COLOR_PAIR(red))    --stop using color pair 'red'

wcolor_set(w,green)        --set window 'w' to use color pair 'green'. could have also used wattron(w,COLOR_PAIR(green))
wprintw(w,"hello world!")  --print string to window 'w'
wrefresh(w)                 --refreesh window 'w'
getch()
endwin()  --shut down ncurses
