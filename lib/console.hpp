#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#    ifndef WIN32
#        define ESC_GREEN "\033[1;32;40m"
#        define ESC_RED "\033[1;31;40m"
#        define ESC_CANCEL "\033[0m"
#    else
#        define ESC_GREEN ""
#        define ESC_RED ""
#        define ESC_CANCEL ""
#    endif

#endif

