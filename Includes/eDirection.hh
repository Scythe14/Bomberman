#ifndef __EDIRECTION_HH__
# define __EDIRECTION_HH__

enum eDirection
  {
    NONE = 0,
    LEFT = 1,
    UPPERLEFT = 2,
    UP = 4,
    UPPERRIGHT = 8,
    RIGHT = 16,
    BOTTOMRIGHT = 32,
    BOTTOM = 64,
    BOTTOMLEFT = 128,
    CORNERS = UPPERLEFT | UPPERRIGHT | BOTTOMLEFT | BOTTOMRIGHT,
    NESW = LEFT | UP | RIGHT | BOTTOM,
    ALL = 255
  };

#endif /* !__EDIRECTION_HH__ */
