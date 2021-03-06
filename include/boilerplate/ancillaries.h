/*
 * Copyright (C) 2013 Philippe Gerum <rpm@xenomai.org>.
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
#ifndef _BOILERPLATE_ANCILLARIES_H
#define _BOILERPLATE_ANCILLARIES_H

#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <boilerplate/signal.h>
#include <boilerplate/compiler.h>
#include <boilerplate/atomic.h>

extern struct timespec __init_date;

extern pthread_mutex_t __printlock;

struct error_frame;
struct cleanup_block;

struct name_generator {
	const char *radix;
	int length;
	atomic_t serial;
};

#define DEFINE_NAME_GENERATOR(__name, __radix, __type, __member)	\
	struct name_generator __name = {				\
		.radix = __radix,					\
		.length = sizeof ((__type *)0)->__member,		\
		.serial = ATOMIC_INIT(0),				\
	}

#define ONE_BILLION  1000000000

void __namecpy_requires_character_array_as_destination(void);

#define namecpy(__dst, __src)						\
	({								\
		if (!__builtin_types_compatible_p(typeof(__dst), char[])) \
			__namecpy_requires_character_array_as_destination();	\
		strncpy((__dst), __src, sizeof(__dst) - 1);		\
		__dst[sizeof(__dst) - 1] = '\0';			\
		__dst;							\
	 })
	
#ifdef __cplusplus
extern "C" {
#endif

void __run_cleanup_block(struct cleanup_block *cb);

void __printout(const char *name,
		const char *header,
		const char *fmt, va_list ap);

void __noreturn __panic(const char *name,
			const char *fmt, va_list ap);

void early_panic(const char *fmt, ...);

void __noreturn panic(const char *fmt, ...);

void __warning(const char *name,
	       const char *fmt, va_list ap);

void early_warning(const char *fmt, ...);

void warning(const char *fmt, ...);

void __notice(const char *name,
	      const char *fmt, va_list ap);

void early_notice(const char *fmt, ...);

void notice(const char *fmt, ...);

const char *symerror(int errnum);

char *generate_name(char *buf, const char *radix,
		    struct name_generator *ngen);

void error_hook(struct error_frame *ef);

void boilerplate_init(void);

int get_static_cpu_count(void);

pid_t get_thread_pid(void);

#ifdef __cplusplus
}
#endif

extern const char *config_strings[];

#endif /* _BOILERPLATE_ANCILLARIES_H */
