#include <libkern/libkern.h>
#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
// #include <libkern/c++/OSKext.h>
#include <libkern/OSKextLib.h>

extern "C" { 

kern_return_t
_start(__attribute__((unused)) kmod_info_t *ki,
              __attribute__((unused)) void *d) {
	printf("SimpleDriver: start printf refcnt: %d addr: %p name: '%s' id: %d\n", ki->reference_count, (void*)ki->address, (const char *)ki->name, ki->id);
	IOLog("SimpleDriver: start IOLog refcnt: %d addr: %p name: '%s' id: %d\n", ki->reference_count, (void*)ki->address, (const char *)ki->name, ki->id);
#ifdef TARGET_OS_EMBEDDED
	OSKextReleaseKextWithLoadTag(ki->id); // for kexty's withPrelinkedInfoDict call that xnu's KLDBootstrap::readPrelinkedExtensions() normally releases
#endif
	return KERN_SUCCESS;
}

kern_return_t
_stop(__attribute__((unused)) kmod_info_t *ki,
             __attribute__((unused)) void *d) {
	printf("SimpleDriver: stop printf\n");
	IOLog("SimpleDriver: stop IOLog\n");
	return KERN_SUCCESS;
}

__attribute__((visibility("default"))) KMOD_EXPLICIT_DECL(com.xerub.driver.SimpleDriver, "1.0.0", _start, _stop)
__private_extern__ kmod_start_func_t *_realmain = 0;
__private_extern__ kmod_stop_func_t *_antimain = 0;
__private_extern__ int _kext_apple_cc = __APPLE_CC__ ;

};
