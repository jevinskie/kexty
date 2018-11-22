CC_IOS = xcrun --sdk iphoneos clang

CFLAGS += -Wall -W -pedantic -std=gnu99 -m32
CFLAGS += -I hdrs -O2 -DMY_LOGGER
LDLIBS += -lsqlite3

CFLAGS_IOS += $(CFLAGS) -arch armv7 -miphoneos-version-min=7.0

TARGETS = kexty makedb kexty-ios makedb-ios kexty-mac makedb-mac

all: $(TARGETS)

.PHONY: clean

kexty-ios: kexty.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -framework IOKit -o $@ $^
	ldid -Stfp0.plist $@

makedb-ios: makedb.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -o $@ $^

kexty-mac: kexty.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

makedb-mac: makedb.c
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

kexty: kexty-ios kexty-mac
	lipo -create -arch armv7 kexty-ios -arch i386 kexty-mac -output $@

makedb: makedb-ios makedb-mac
	lipo -create -arch armv7 makedb-ios -arch i386 makedb-mac -output $@

clean:
	rm -f $(TARGETS)
