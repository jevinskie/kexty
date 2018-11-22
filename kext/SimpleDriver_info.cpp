#include <libkern/libkern.h>
#include <mach/mach_types.h>

extern "C" { 

kern_return_t
_start(__attribute__((unused)) kmod_info_t *ki,
              __attribute__((unused)) void *d) {
	printf("SimpleDriver: start\n");
	return KERN_SUCCESS;
}

kern_return_t
_stop(__attribute__((unused)) kmod_info_t *ki,
             __attribute__((unused)) void *d) {
	printf("SimpleDriver: stop\n");
	return KERN_SUCCESS;
}

__attribute__((visibility("default"))) KMOD_EXPLICIT_DECL(com.xerub.driver.SimpleDriver, "1.0.0", _start, _stop)
__private_extern__ kmod_start_func_t *_realmain = 0;
__private_extern__ kmod_stop_func_t *_antimain = 0;
__private_extern__ int _kext_apple_cc = __APPLE_CC__ ;

};
