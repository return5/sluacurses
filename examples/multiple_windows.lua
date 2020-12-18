--[[
    example file from sluacurses.
    File shows a simple example of creating multiple windows through sluacurses.
--]]

local Curses = require("sluacurses")  --load sluacurses into program

initscr()   --start ncurses
noecho()    --dont display keystrokes to screen
curs_set(0) --dont display cursor
refresh()   --refresh screen

window_table = {}  --tabel to hold windows

-- create a list of 3 windows stored in 'window_table'
table.insert(window_table,newwin(5,10,0,0))
table.insert(window_table,newwin(5,10,0,11))
table.insert(window_table,newwin(5,10,0,23))

--print to each window
for i,window in ipairs(window_table) do
    wprintw(window,string.format("window %d",i))
    mvwprintw(window,4,0,"bottom")
    wrefresh(window)
end

getch()
endwin()  --shut down ncurses
