/*
	File:			SimpleDriver.h
	
	Description:	This file shows how to implement a basic I/O Kit driver kernel extension (KEXT).

	Copyright:		Copyright © 2001-2008 Apple Inc. All rights reserved.
*/

#include <IOKit/IOService.h>
#include "UserKernelShared.h"

class XerubDriver : public IOService
{
	// Declare the metaclass information that is used for runtime type checking of I/O Kit objects.

	OSDeclareDefaultStructors(XerubDriver)

public:
	// IOService methods
	virtual bool start(IOService *provider) override;
	virtual void stop(IOService *provider) override;
	// virtual bool init(OSDictionary *dict) override;
	virtual void free(void) override;

#ifdef DEBUG_REFCOUNT
	virtual void taggedRetain(const void* tag) const override;
	virtual void taggedRelease(const void* tag) const override;
#endif

	// SimpleDriver methods
	virtual IOReturn testMe(uint32_t *demo);
};

#ifdef DEBUG_REFCOUNT
#define CLASS_OBJECT_FORMAT_STRING "[%s@%p:%dx]"
#define CLASS_OBJECT_FORMAT(obj) myClassName(obj), obj, myRefCount(obj)

inline int myRefCount(const OSObject* obj)
{
    return obj ? obj->getRetainCount() : 0;
}

inline const char* myClassName(const OSObject* obj)
{
    if (!obj) return "(null)";
    return obj->getMetaClass()->getClassName();
}
#endif
