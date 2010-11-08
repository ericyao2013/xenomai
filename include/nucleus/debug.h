/*
 * Copyright (C) 2010 Philippe Gerum <rpm@xenomai.org>.
 *
 * Xenomai is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * Xenomai is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Xenomai; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _XENO_NUCLEUS_DEBUG_H
#define _XENO_NUCLEUS_DEBUG_H

#include <nucleus/assert.h>

struct xnthread;

#ifdef CONFIG_XENO_OPT_DEBUG

int xndebug_init(void);

void xndebug_cleanup(void);

void xndebug_shadow_init(struct xnthread *thread);

#else  /* !XENO_OPT_DEBUG */

static inline int xndebug_init(void)
{
	return 0;
}

static inline void xndebug_cleanup(void)
{
}

static inline void xndebug_shadow_init(struct xnthread *thread)
{
}

#endif  /* !XENO_OPT_DEBUG */

#ifdef CONFIG_XENO_OPT_DEBUG_TRACE_RELAX
void xndebug_notify_relax(struct xnthread *thread);
void xndebug_trace_relax(int nr, unsigned long __user *u_backtrace);
#else
static inline void xndebug_notify_relax(struct xnthread *thread)
{
}
static inline
void xndebug_trace_relax(int nr, unsigned long __user *u_backtrace)
{
	/* Simply ignore. */
}
#endif

#endif /* !_XENO_NUCLEUS_DEBUG_H */
