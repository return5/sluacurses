//-------------------------------- description ------------------------------------------------
    //simple wrappers for using ncurses through lua.
    //hosted at www.github.com/return5/sluacurses
//-------------------------------- license ----------------------------------------------------
/*
    Copyright (c) <2020> <github.com/return5>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
//-------------------------------- includes ---------------------------------------------------
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "window.h"

//-------------------------------- global vars ------------------------------------------------
WINDOW_ARRAY *window_array;

//-------------------------------- function prototypes ----------------------------------------
static int l_mvprintw(lua_State *L);
static int l_wcolor_set(lua_State *L);
static int l_wattron(lua_State *L);
static int l_wattroff(lua_State *L);
static int l_color_set(lua_State *L);
static int l_attron(lua_State *L);
static int l_attroff(lua_State *L);
static int l_keypad(lua_State *L);
static int l_mvdelch(lua_State *L);
static int l_delch(__attribute__((unused)) lua_State *L);
static int l_clrtoeol(__attribute__ ((unused)) lua_State *L);
static int makeWindow(const WIN_INFO *const win_info);
static void removeFromArray(const int index);
static WINDOW *getWindow(const int index);
static int l_newwin(lua_State *L);
static int l_wborder(lua_State *L);
static int l_mvwprintw(lua_State *L);
static int l_wprintw(lua_State *L);
static int l_printw(lua_State *L);
static int l_refresh(__attribute__((unused)) lua_State *L);
static int l_clear(__attribute__((unused)) lua_State *L) ;
static int l_wclear(lua_State *L);
static int l_wrefresh(lua_State *L);
static int l_wmove(lua_State *L);
static int l_move(lua_State *L);
static int l_getyx(lua_State *L);
static int l_wgetyx(lua_State *L);
static void reorderArray(const int index);
static int l_getch(lua_State *L);
static int l_mvgetch(lua_State *L);
static int l_wgetch(lua_State *L);
static int l_mvwgetch(lua_State *L);
static WINDOW **resizeWindowArray(void);
static WINDOW_ARRAY *createWindowArray(void);
static void addToWindowArray(const WIN_INFO *const win_info);
static int l_curs_set(lua_State *L);
static int l_init_pair(lua_State *L);
static int l_start_color(__attribute__((unused)) lua_State *L);
static int l_cbreak(__attribute__((unused)) lua_State *L);
static int l_noecho(__attribute__((unused)) lua_State *L);
static int l_echo(__attribute__((unused)) lua_State *L);
static int l_endwin(__attribute__((unused)) lua_State *L);
static int l_initscr(__attribute__((unused)) lua_State *L);
static int l_delwin(lua_State *L);
static int l_color_pair(lua_State *L);
static int addColorValue(lua_State *L);
static int l_init_color(lua_State *L);

//-------------------------------- code -------------------------------------------------------

static int addColorValue(lua_State *L) {
    lua_pushinteger(L,COLOR_RED);
    lua_setglobal(L,"COLOR_RED");
    lua_pushinteger(L,COLOR_BLACK);
    lua_setglobal(L,"COLOR_BLACK");
    lua_pushinteger(L,COLOR_GREEN);
    lua_setglobal(L,"COLOR_GREEN");
    lua_pushinteger(L,COLOR_MAGENTA);
    lua_setglobal(L,"COLOR_MAGENTA");
    lua_pushinteger(L,COLOR_YELLOW);
    lua_setglobal(L,"COLOR_YELLOW");
    lua_pushinteger(L,COLOR_BLUE);
    lua_setglobal(L,"COLOR_BLUE");
    lua_pushinteger(L,COLOR_CYAN);
    lua_setglobal(L,"COLOR_CYAN");
    lua_pushinteger(L,COLOR_WHITE);
    lua_setglobal(L,"COLOR_WHITE");
    return 8;
}

int luaopen_sluacurses(lua_State *L) {
    addColorValue(L);
    lua_register(L,"getch",l_getch); 
    lua_register(L,"mvgetch",l_mvgetch); 
    lua_register(L,"wgetch",l_wgetch); 
    lua_register(L,"mvwgetch",l_mvwgetch); 
    lua_register(L,"wmove",l_wmove); 
    lua_register(L,"move",l_move); 
    lua_register(L,"newwin",l_newwin); 
    lua_register(L,"wborder",l_wborder); 
    lua_register(L,"mvwprintw",l_mvwprintw); 
    lua_register(L,"wprintw",l_wprintw); 
    lua_register(L,"printw",l_printw); 
    lua_register(L,"refresh",l_refresh);
    lua_register(L,"clear",l_clear) ;
    lua_register(L,"wclear",l_wclear); 
    lua_register(L,"wrefresh",l_wrefresh); 
    lua_register(L,"curs_set",l_curs_set);
    lua_register(L,"init_pair",l_init_pair);
    lua_register(L,"start_color",l_start_color);
    lua_register(L,"cbreak",l_cbreak);
    lua_register(L,"noecho",l_noecho);
    lua_register(L,"echo",l_echo);
    lua_register(L,"endwin",l_endwin);
    lua_register(L,"initscr",l_initscr);
    lua_register(L,"getyx",l_getyx);
    lua_register(L,"wgetyx",l_wgetyx);
    lua_register(L,"mvprintw",l_mvprintw);
    lua_register(L,"delwin",l_delwin);
    lua_register(L,"clrtoeol",l_clrtoeol);
    lua_register(L,"mvdelch",l_mvdelch);
    lua_register(L,"delch",l_delch);
    lua_register(L,"keypad",l_keypad);
    lua_register(L,"COLOR_PAIR",l_color_pair);
    lua_register(L,"wattron",l_wattron);
    lua_register(L,"wattroff",l_wattroff);
    lua_register(L,"wcolor_set",l_wcolor_set);
    lua_register(L,"attron",l_attron);
    lua_register(L,"attroff",l_attroff);
    lua_register(L,"color_set",l_color_set);
    lua_register(L,"init_color",l_init_color);
    return 0;
}

static int l_initscr(__attribute__((unused)) lua_State *L) {
    initscr();
    return 0;
}

static int l_endwin(__attribute__((unused)) lua_State *L) { 
    endwin();
    return 0;
}

static int l_echo(__attribute__((unused)) lua_State *L) { 
    echo();
    return 0;
}

static int l_noecho(__attribute__((unused)) lua_State *L) { 
    noecho();
    return 0;
}

static int l_cbreak(__attribute__((unused)) lua_State *L) { 
    cbreak();
    return 0;
}

static int l_clrtoeol(__attribute__ ((unused)) lua_State *L) {
    clrtoeol();
    return 0;
}

static int l_start_color(__attribute__((unused)) lua_State *L) { 
    start_color();
    return 0;
} 

static int l_delch(__attribute__((unused)) lua_State *L) {
    delch();
    return 0;
}

static int l_keypad(lua_State *L) {
    const int b = lua_toboolean(L,2);
    keypad(stdscr,b);
    return 0;
}

static int l_mvdelch(lua_State *L) {
   l_move(L);
   return l_delch(L);
}

static int l_delwin(lua_State *L) {
    const int index = luaL_checknumber(L,-1);
    delwin(getWindow(index));
    removeFromArray(index);
    return 0;
}

static int l_init_pair(lua_State *L) {
    const int color      = luaL_checknumber(L,1);
    const int foreground = luaL_checknumber(L,2);
    const int background = luaL_checknumber(L,3);
    init_pair(color,foreground,background);
    return 0;
}

static int l_curs_set(lua_State *L) { 
    const int a = luaL_checknumber(L,-1);
    curs_set(a);
    return 0;
} 

static WINDOW_ARRAY *createWindowArray(void) {
    WINDOW_ARRAY *tmp = malloc(sizeof(WINDOW_ARRAY));
    tmp->index        = -1;
    tmp->max_length   = 5;
    tmp->windows      = malloc(sizeof(WINDOW) * tmp->max_length);
    return tmp;
}

static WINDOW **resizeWindowArray(void) {
    WINDOW **tmp = realloc(window_array->windows,sizeof(WINDOW) * window_array->max_length);
    if (tmp == NULL) {
        tmp = realloc(window_array->windows,sizeof(WINDOW) * window_array->max_length);
    }
    return tmp;
}

static void addToWindowArray(const WIN_INFO *const win_info) {
    if(window_array->index >= window_array->max_length) {
        window_array->max_length += 5;
        window_array->windows     = resizeWindowArray();
    }
    window_array->windows[++(window_array->index)] = newwin(win_info->h,win_info->w,win_info->y,win_info->x);

}

static void reorderArray(const int index) {
    window_array->index--;
    for(int i = index; i < window_array->index; i++) {
        window_array->windows[i] = window_array->windows[i+1];
    }
}

void removeFromArray(const int index) {
    if(index >= 0) {
        WINDOW *tmp = window_array->windows[index];
        reorderArray(index);
        free(tmp);
    }
}

WINDOW *getWindow(const int index) {
    if (index >= 0 && index <= window_array->index) {
        return window_array->windows[index];
    }
    return NULL;
}

int makeWindow(const WIN_INFO *const win_info) {
    if(window_array == NULL) {
        window_array = createWindowArray(); 
    }
    addToWindowArray(win_info);
    return window_array->index;
}

static int l_newwin(lua_State *L) {
    const int h     = luaL_checknumber(L,-4);
    const int w     = luaL_checknumber(L,-3);
    const int y     = luaL_checknumber(L,-2);
    const int x     = luaL_checknumber(L,-1);
    WIN_INFO tmp    = {h,w,y,x};
    const int index = makeWindow(&tmp);
    lua_pushnumber(L,index);
    return 1;
}

static int l_wborder(lua_State *L) {
    const int index          = luaL_checknumber(L,-9);
    const char left          = luaL_checkstring(L,-8)[0];
    const char right         = luaL_checkstring(L,-7)[0];
    const char top           = luaL_checkstring(L,-6)[0];
    const char bottom        = luaL_checkstring(L,-5)[0];
    const char top_left      = luaL_checkstring(L,-4)[0];
    const char top_right     = luaL_checkstring(L,-3)[0];
    const char bottom_left   = luaL_checkstring(L,-2)[0];
    const char bottom_right  = luaL_checkstring(L,-1)[0];
    wborder(getWindow(index),left,right,top,bottom,top_left,top_right,bottom_left,bottom_right);
    return 0;
}

static int l_wrefresh(lua_State *L) {
    const int index = luaL_checknumber(L,-1);
    wrefresh(getWindow(index));
    return 0;
}

static int l_wclear(lua_State *L) {
    const int index = luaL_checknumber(L,-1);
    wclear(getWindow(index));
    return 0;
}

static int l_clear(__attribute__((unused)) lua_State *L) { 
    clear();
    return 0;
} 

static int l_refresh(__attribute__((unused)) lua_State *L) {
    refresh();
    return 0;
}
static int l_printw(lua_State *L) {
    const char *const str = luaL_checkstring(L,-1);
    printw(str);
    return 0;
}

static int l_wprintw(lua_State *L) {
    const int index       = luaL_checknumber(L,1);
    const char *const str = luaL_checkstring(L,2);
    wprintw(getWindow(index),str);
    return 0;
}

static int l_mvwprintw(lua_State *L) {
    l_wmove(L);
    lua_remove(L,2);
    lua_remove(L,2);
    return l_wprintw(L);
}

static int l_mvprintw(lua_State *L) {
    l_move(L);
    lua_remove(L,1);
    lua_remove(L,1);
    return l_printw(L);
}

static int l_wgetyx(lua_State *L) {
    const int index = luaL_checknumber(L,-1);
    int x,y;
    getyx(getWindow(index),y,x);
    lua_pushnumber(L,y);
    lua_pushnumber(L,x);
    return 2;
}

static int l_getyx(lua_State *L) {
    int x,y;
    getyx(stdscr,y,x);
    lua_pushnumber(L,y);
    lua_pushnumber(L,x);
    return 2;
}

static int l_wmove(lua_State *L) {
    const int index = luaL_checknumber(L,1);
    const int y     = luaL_checknumber(L,2);
    const int x     = luaL_checknumber(L,3);
    wmove(getWindow(index),y,x);
    return 0;
}
static int l_move(lua_State *L) {
    const int y = luaL_checknumber(L,1);
    const int x = luaL_checknumber(L,2);
    move(y,x);
    return 0;
}

static int l_getch(lua_State *L) {
    lua_pushfstring(L,"%c",getch());
    return 1;
}

static int l_mvgetch(lua_State *L) {
    l_move(L);
    return l_getch(L);
}

static int l_wgetch(lua_State *L) {
    const int index = luaL_checknumber(L,-1);
    lua_pushfstring(L,"%c",wgetch((getWindow(index))));
    return 1;
}

static int l_mvwgetch(lua_State *L) {
    l_wmove(L);
    lua_remove(L,-1);
    lua_remove(L,-1);
    return l_wgetch(L);
}

static int l_init_color(lua_State *L) {
    const int color = luaL_checknumber(L,1);
    const int r     = luaL_checknumber(L,2);
    const int g     = luaL_checknumber(L,3);
    const int b     = luaL_checknumber(L,4);
    init_color(color,r,g,b);
    return 0;
}

static int l_color_pair(lua_State *L) {
    const int color = luaL_checknumber(L,1);
    lua_pushnumber(L,COLOR_PAIR(color));
    return 1;
}

static int l_wattron(lua_State *L) {
    const int index = luaL_checknumber(L,1);
    const int attr  = luaL_checknumber(L,2);
    wattron(getWindow(index),attr);
    return 0;
}

static int l_wattroff(lua_State *L) {
    const int index = luaL_checknumber(L,1);
    const int attr  = luaL_checknumber(L,2);
    wattroff(getWindow(index),attr);
    return 0;
}

static int l_wcolor_set(lua_State *L) {
    const int index  = luaL_checknumber(L,1);
    const int attr   = luaL_checknumber(L,2);
    wcolor_set(getWindow(index),attr,NULL);
    return 0;
}

static int l_attron(lua_State *L) {
    const int attr = luaL_checknumber(L,1);
    attron(attr);
    return 0;
}

static int l_attroff(lua_State *L) {
    const int attr = luaL_checknumber(L,1);
    attroff(attr);
    return 0;
}

static int l_color_set(lua_State *L) {
    const int attr = luaL_checknumber(L,1);
    color_set(attr,NULL);
    return 0;
}

