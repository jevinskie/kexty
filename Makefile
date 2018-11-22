CC_IOS = xcrun --sdk iphoneos clang

CFLAGS += -Wall -W -pedantic -std=gnu11
CFLAGS += -I hdrs -O2
LDLIBS += -lsqlite3

CFLAGS_IOS += $(CFLAGS) -arch armv7 -miphoneos-version-min=7.0

TARGETS = kexty makedb

all: $(TARGETS)

.PHONY: clean

kexty: kexty.c
	$(CC_IOS) $(CFLAGS_IOS) $(LDLIBS) -framework IOKit -o $@ $^
	ldid -Stfp0.plist $@

clean:
	rm -f $(TARGETS)
