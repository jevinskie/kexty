CC = xcrun --sdk iphoneos clang -arch armv7 -miphoneos-version-min=7.0
CXX = xcrun --sdk iphoneos clang++ -arch armv7 -miphoneos-version-min=7.0

KEXTFLAGS = -DKERNEL

CALLFLAGS += -Wall -std=gnu11 -Wno-gnu-anonymous-struct -Wno-c99-extensions -Wno-variadic-macros -Wno-nested-anon-types -Wno-gnu-include-next
# CALLFLAGS += -I ../hdrs -O2
CALLFLAGS += -O2 -DTARGET_OS_EMBEDDED
CFLAGS = $(CALLFLAGS) -I ../hdrs -std=gnu99
CXXFLAGS = $(CALLFLAGS) $(KEXTFLAGS) -nostdinc -I ../hdrs2 -I /Users/jevin/code/ios/kern/prefix-4570.71.2/System/Library/Frameworks/Kernel.framework/Versions/A/PrivateHeaders -I /Users/jevin/code/ios/kern/prefix-4570.71.2/usr/include -O2 -mkernel -std=gnu++11
LDFLAGS = -nostdlib -Xlinker -kext 

TARGETS = SimpleDriver test_serv

all: $(TARGETS)

.PHONY: clean

test_serv: test_serv.c
	$(CC) $(CFLAGS) -framework IOKit -o $@ $^

SimpleDriver: SimpleDriver.o SimpleDriver_info.o SimpleUserClient.o

clean:
	rm -f *.o $(TARGETS)
	rm -rf SimpleDriver.*.ld/
