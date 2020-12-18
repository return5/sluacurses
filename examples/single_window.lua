
--[[
    example file from sluacurses.
    File shows a simple example of creating a single window through sluacurses.
--]]

local Curses = require("sluacurses")  --load sluacurses into program

initscr()   --start ncurses
noecho()    --dont display keystrokes to screen
curs_set(0) --dont display cursor
refresh()   --refresh screen

--create a new window and save its hashed name to 'w'
--args: name,height,width,starting y, starting x
local w = newwin(15,25,5,5)

--args: window, left,right,bottom,top,tl,tr,bl,br
wborder(w,"|","|","-","-","+","+","+","+")  --create border around window 'w'

wmove(w,4,2)                --move cursor to positon y:4 x:2 in window 'w'

wprintw(w,"hello world!")  --print string to window 'w'

mvwprintw(w,5,2,"enter char")

wrefresh(w)                 --refreesh window 'w'

local c = wgetch(w)         --get input from window 'w'

mvwprintw(w,6,2,c)           --move to y:6 x:2 in window 'w' then print char 'c'

mvwprintw(w,7,2,"press any key to exit")

wrefresh(w)

getch()
endwin()  --shut down ncurses
