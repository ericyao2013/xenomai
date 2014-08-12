/*
 * Copyright (C) 2014 Philippe Gerum <rpm@xenomai.org>.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */
#ifndef _XENOMAI_TRANK_TRANK_H
#define _XENOMAI_TRANK_TRANK_H

#ifdef __XENO_COMPAT__

#define trank_warning(__fmt, __args...)	\
	warning("%s: " __fmt, __func__, ##__args)

#define __CURRENT(call)		__hidden_ ## call

#define COMPAT_DECL(T, P)	__typeof__(T) P
#define CURRENT_DECL(T, P)	__typeof__(T) __CURRENT(P)

#else /* !__XENO_COMPAT__ */

#include <boilerplate/compiler.h>

#define __CURRENT(call)		call

#define COMPAT_DECL(T, P)
#define CURRENT_DECL(T, P)	__typeof__(T) P;	\
				__typeof__(T) __hidden_ ## P

#define CURRENT_IMPL(T, I, A)		\
__typeof__(T) I A __attribute__((alias("__hidden_" __stringify(I)), weak)); \
__typeof__(T) __hidden_ ## I A

#endif /* !__XENO_COMPAT__ */

#endif /* _XENOMAI_TRANK_TRANK_H */