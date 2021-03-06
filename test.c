/*

Simple logger helper -- example

Copyright (c) 2013-2017 Antmicro <www.antmicro.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <stdio.h>
#include "log_helper.h"

void main() {
	printf("log test\n");
	log_msg(ERR, __func__, "This is an error");
	log_msg(WARN, "some_module", "This is a warning");
	log_msg(INFO, __func__, "This is an info about %s", "something");
	log_msg(INFO, __func__, "LOGGER_MAX_LEVEL = %d", LOGGER_MAX_LEVEL);
	log_msg(DEBUG, "some_other_module", "we are debugging file %s at line %d", __FILE__, __LINE__); // this will not be printed unles LOGGER_MAX_LEVEL is >= 3
}

