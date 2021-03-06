/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#include <stdio.h>  // fprintf(), NULL
#include <stdlib.h> // exit(), EXIT_SUCCESS
#include <string.h>
#include <dlfcn.h>

#include "test.h" // PASS(), FAIL(), XPASS(), XFAIL()


///
/// This tests that TLD_NOW binds all lazy symbols.
/// We do this by making sure a lazy symbol does not exist
/// and dlopen() errors out with a message string
/// that contains the missing symbol name.
///


int main()
{
	void* handle = dlopen("test.bundle", RTLD_NOW);
	if ( handle == NULL ) {
		const char* msg = dlerror();
		if ( strstr(msg, "foo2") != NULL ) {
			PASS("dlopen-RTLD_NOW");
			exit(0);
		}
		FAIL("dlopen(test.bundle, RTLD_NOW) failed but error message did not contain foo2: %s", msg);
		exit(0);
	}
	FAIL("dlopen(test.bundle, RTLD_NOW) succeed but should have failed because foo2 does not exist");
	exit(0);
}
