#ifndef __SYALIS_UTIL_H__
#define __SYALIS_UTIL_H__
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <zconf.h>
#include <stdint.h>
namespace syalis {

pid_t GetThreadId();
uint32_t GetFiberId();

}

#endif
