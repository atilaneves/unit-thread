#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#    ifndef _WIN32
#        include <unistd.h>
#        define ESC_I(code) (isatty(fileno(stdout)) ? code : "")
#        define ESC_GREEN ESC_I("\033[32;1m")
#        define ESC_RED ESC_I("\033[31;1m")
#        define ESC_CANCEL ESC_I("\033[0;;m")
#    else
#        define ESC_GREEN ""
#        define ESC_RED ""
#        define ESC_CANCEL ""
#    endif

#endif
