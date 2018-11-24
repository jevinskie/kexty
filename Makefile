CC_IOS = xcrun --sdk iphoneos clang

CFLAGS += -Wall -W -pedantic -std=gnu99 -m32
CFLAGS += -I hdrs -O2 -DMY_LOGGER
LDLIBS += -lsqlite3

CFLAGS_IOS += $(CFLAGS) -arch armv7 -miphoneos-version-min=7.0

TARGETS = kexty makedb kdb

all: $(TARGETS) kext

.PHONY: clean kext
.INTERMEDIATE: kexty.armv7 kexty.i386 makedb.armv7 makedb.i386 kdb.armv7 kdb.i386

kext:
	$(MAKE) -C kext

kexty.armv7: kexty.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -framework IOKit -o $@ $^
	ldid -Stfp0.plist $@

makedb.armv7: makedb.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -o $@ $^

kdb.armv7: kdb.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -DTOOL_MODE -o $@ $^

kexty.i386: kexty.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

makedb.i386: makedb.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

kdb.i386: kdb.c
	$(CC) $(CFLAGS) $(LDLIBS) -DTOOL_MODE -o $@ $^

kexty: kexty.armv7 kexty.i386
	lipo -create $^ -output $@

%: %.armv7 %.i386
	lipo -create $^ -output $@

clean:
	rm -f $(TARGETS)
	make -C kext clean
