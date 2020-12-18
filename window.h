//-------------------------------- description ------------------------------------------------

// File contains structs which are used to hold the array of windows, and to hold attributes of a  new window
    
//-------------------------------- include gurads ---------------------------------------------
#ifndef WINDOWARRAY_H

//-------------------------------- macros -----------------------------------------------------
#define WINDOWARRAY_H

//-------------------------------- includes ---------------------------------------------------
#include <ncurses.h>

//-------------------------------- structs ----------------------------------------------------

//struct to hold the array of windows
//has the current index, max length of the array, and the array itself
typedef struct WINDOW_ARRAY {
    int index,max_length;
    WINDOW **windows;   //array of WINDOW_STRUCT pointers
}WINDOW_ARRAY;

//struct holds info for makign a new window
//contains height, width, starting y, starting x, and name of window.
typedef struct WIN_INFO {
    int h,w,y,x;
}WIN_INFO;

//-------------------------------- global vars ------------------------------------------------
extern WINDOW_ARRAY *window_array; 

//-------------------------------- function prototypes -----------------------------------------

#endif

