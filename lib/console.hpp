#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#    ifndef WIN32
#        define ESC_GREEN "\033[32;1m"
#        define ESC_RED "\033[31;1m"
#        define ESC_CANCEL "\033[0;;m"
#    else
#        define ESC_GREEN ""
#        define ESC_RED ""
#        define ESC_CANCEL ""
#    endif

#endif
