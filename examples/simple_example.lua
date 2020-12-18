--[[
    example file from sluacurses.
    File shows a simple example of starting ncurses through sluacurses.
--]]

local Curses = require("sluacurses")  --load sluacurses into program

initscr()                 --start ncurses
noecho()                  --dont display keystrokes to screen
curs_set(0)               --dont display cursor
printw("hello world!\n")  --print to stdscr at currentl cursor location
local c = getch()         --get char from user input
printw("\nc is: ")
printw(c)
printw("\npress any key to exit.\n")
getch()
endwin()  --shut down ncurses
