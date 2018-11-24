/*
	File:			SimpleDriver.cpp
	
	Description:	This file shows how to implement a basic I/O Kit driver kernel extension (KEXT).

	Copyright:		Copyright © 2001-2008 Apple Inc. All rights reserved.
	Copyright:		Copyright © 2016 xerub
*/


#include <IOKit/IOLib.h>
#include <libkern/OSDebug.h>
#include "SimpleDriver.h"

#define super IOService

// Even though we are defining the convenience macro super for the superclass, you must use the actual class name
// in the OS*MetaClass macros. Note that the class name is different when supporting Mac OS X 10.4.

OSDefineMetaClassAndStructors(XerubDriver, IOService)

bool
XerubDriver::start(IOService *provider)
{
	bool success;

	IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);

	success = super::start(provider);

	if (success) {
		// Publish ourselves so clients can find us
		registerService();
	}

	return success;
}

void
XerubDriver::stop(IOService *provider)
{
	IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, provider);

	super::stop(provider);
}

#if 0
bool
XerubDriver::init(OSDictionary *dict)
{
	bool success;

	IOLog("%s[%p]::%s(%p)\n", getName(), this, __FUNCTION__, dict);

	success = super::init(dict);

	return success;
}
#endif

void
XerubDriver::free(void)
{
	IOLog("%s[%p]::%s\n", getName(), this, __FUNCTION__);

	super::free();
}

IOReturn
XerubDriver::testMe(uint32_t *demo)
{
	IOLog("%s[%p]::%s()\n", getName(), this, __FUNCTION__);

	*demo = 0xdeaf0000;

	return kIOReturnSuccess;
}


void XerubDriver::taggedRetain(const void* tag) const
{
	clock_sec_t nows;
	clock_usec_t nowus;
	clock_get_system_microtime(&nows, &nowus);
	uint64_t now = (uint64_t)nowus + (uint64_t)nows * 1000000;
	OSReportWithBacktrace(
		"%lld XerubDriver" CLASS_OBJECT_FORMAT_STRING "::taggedRetain(tag=%p)\n", now, CLASS_OBJECT_FORMAT(this), tag);
	IOService::taggedRetain(tag);
	int count = getRetainCount();
	// int count = 243;
	IOLog("%lld XerubDriver::taggedRetain(tag=%p) %d final done\n", now, tag, count);
}
void XerubDriver::taggedRelease(const void * tag) const
{
	clock_sec_t nows;
	clock_usec_t nowus;
	clock_get_system_microtime(&nows, &nowus);
	uint64_t now = (uint64_t)nowus + (uint64_t)nows * 1000000;
	OSReportWithBacktrace(
		"%lld XerubDriver" CLASS_OBJECT_FORMAT_STRING "::taggedRelease(tag=%p)\n", now, CLASS_OBJECT_FORMAT(this), tag);
	int count = getRetainCount();
	IOService::taggedRelease(tag);
	if (count == 1)
		IOLog(
			"%lld XerubDriver::taggedRelease(tag=%p) count: %d final done\n", now, tag, count);
	else
		IOLog(
			"%lld XerubDriver" CLASS_OBJECT_FORMAT_STRING "::taggedRelease(tag=%p) count: %d done\n", now, CLASS_OBJECT_FORMAT(this), tag, count);
}
