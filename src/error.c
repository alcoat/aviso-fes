/* This file is part of FES library.

   FES is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   FES is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with FES.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <config.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#ifdef HAVE_BSD_STRING
#include <bsd/string.h>
#endif

#include "fes.h"
#include "fes_int.h"
#include "error.h"

/* Error code message */
static const char* err[] = { "Success", "Not enough memory", "netCDF error",
    "IO error", "Configuration file contains error", "Tide is undefined",
    "Value error" };

/*
 */
void set_fes_error(fes_handler* const fes, const fes_enum_error errcode) {
  fes->last_errno = errcode;
  strlcpy(fes->last_error, err[errcode], sizeof(fes->last_error));
}

/*
 */
void set_fes_extended_error(fes_handler* const fes,
                            const fes_enum_error errcode, const char* format,
                            ...) {
  va_list argp;

  fes->last_errno = errcode;

  va_start(argp, format);
  vsnprintf(fes->last_error, sizeof(fes->last_error), format, argp);
  va_end(argp);
}

/*
 */
fes_enum_error fes_errno(FES fes) {
  return ((fes_handler*) fes)->last_errno;
}

/*
 */
const char*
fes_error(FES fes) {
  return ((fes_handler*) fes)->last_error;
}
