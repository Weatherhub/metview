/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#ifndef ODB_API_TOOLS_C_H

/**
 * \file odb_api_tools_c.h
 *
 * @author Piotr Kuchta, September 2015
 *
 */

#include <stddef.h>
#include <sys/types.h>
// For off_t on Cray:
#include <unistd.h>

#if defined(__cplusplus) || defined(c_plusplus) || defined(SWIGPYTHON)
extern "C" {
#endif

int import_text(const char* text, const char* output_file);

#if defined(__cplusplus) || defined(c_plusplus) || defined(SWIGPYTHON)
}
#endif
#endif

