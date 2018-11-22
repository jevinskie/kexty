CC = xcrun --sdk iphoneos clang -arch armv7 -miphoneos-version-min=7.0
CXX = xcrun --sdk iphoneos clang++ -arch armv7 -miphoneos-version-min=7.0

KEXTFLAGS = -DKERNEL -DKERNEL_PRIVATE

CALLFLAGS += -Wall -std=gnu11 -Wno-gnu-anonymous-struct -Wno-c99-extensions -Wno-variadic-macros -Wno-nested-anon-types -Wno-gnu-include-next
CALLFLAGS += -I ../hdrs -O2
CFLAGS = $(CALLFLAGS) -std=c99
CXXFLAGS = $(CALLFLAGS) $(KEXTFLAGS) -mkernel -std=c++11
LDFLAGS = -nostdlib -Xlinker -kext 

TARGETS = SimpleDriver test_serv

all: $(TARGETS)

.PHONY: clean

test_serv: test_serv.c
	$(CC) $(CFLAGS) -framework IOKit -o $@ $^

SimpleDriver: SimpleDriver.o SimpleDriver_info.o SimpleUserClient.o

clean:
	rm -f $(TARGETS)
	rm -rf SimpleDriver.*.ld/
