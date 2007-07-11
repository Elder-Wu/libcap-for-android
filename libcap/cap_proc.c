/*
 * $Id: cap_proc.c,v 1.5 1998/05/24 22:54:09 morgan Exp $
 *
 * Copyright (c) 1997-8 Andrew G Morgan <morgan@linux.kernel.org>
 *
 * See end of file for Log.
 *
 * This file deals with setting capabilities on processes.
 */

#include "libcap.h"

cap_t cap_get_proc(void)
{
    cap_t result;

    /* allocate a new capability set */
    result = cap_init();
    if (result) {
	_cap_debug("getting current process' capabilities");

	/* fill the capability sets via a system call */
	if (capget(&result->head, &result->set)) {
	    cap_free(&result);
	}
    }

    return result;
}

int cap_set_proc(cap_t cap_d)
{
    if (!good_cap_t(cap_d)) {
	errno = EINVAL;
	return -1;
    }

    _cap_debug("setting process capabilities");
    return capset(&cap_d->head, &cap_d->set);
}

/* the following two functions are not required by POSIX */

/* read the caps on a specific process */

int capgetp(pid_t pid, cap_t cap_d)
{
    int error;

    if (!good_cap_t(cap_d)) {
	errno = EINVAL;
	return -1;
    }

    _cap_debug("getting process capabilities for proc %d", pid);

    cap_d->head.pid = pid;
    error = capget(&cap_d->head, &cap_d->set);
    cap_d->head.pid = 0;

    return error;
}

/* set the caps on a specific process/pg etc.. */

int capsetp(pid_t pid, cap_t cap_d)
{
    int error;

    if (!good_cap_t(cap_d)) {
	errno = EINVAL;
	return -1;
    }

    _cap_debug("setting process capabilities for proc %d", pid);
    cap_d->head.pid = pid;
    error = capset(&cap_d->head, &cap_d->set);
    cap_d->head.pid = 0;

    return error;
}

/*
 * $Log: cap_proc.c,v $
 * Revision 1.5  1998/05/24 22:54:09  morgan
 * updated for 2.1.104
 *
 * Revision 1.4  1997/05/14 05:17:13  morgan
 * bug-fix from zefram (errno no set on success)
 *
 * Revision 1.3  1997/05/04 05:35:46  morgan
 * fixed errno setting. syscalls do this part
 *
 * Revision 1.2  1997/04/28 00:57:11  morgan
 * fixes and zefram's patches
 *
 * Revision 1.1  1997/04/21 04:32:52  morgan
 * Initial revision
 *
 */
