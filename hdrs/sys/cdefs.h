#pragma once

#ifdef KERNEL
#define	__DARWIN14_ALIAS(sym)

typedef struct upl_page_info	upl_page_info_t;
typedef upl_page_info_t		*upl_page_info_array_t;
// typedef struct ipc_port	        *ipc_port_t;
// typedef struct task			*task_t;
#endif

#include_next <sys/cdefs.h>