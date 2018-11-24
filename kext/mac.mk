PKG = com.xerub.driver.SimpleDriver

KFWK = $(shell xcrun --show-sdk-path)/System/Library/Frameworks/Kernel.framework
IOKITFWK = $(shell xcrun --show-sdk-path)/System/Library/Frameworks/IOKit.framework

KEXTFLAGS = -DKERNEL -nostdinc -I $(IOKITFWK)/Headers -I $(KFWK)/Headers

CALLFLAGS += -Wall -Wno-gnu-anonymous-struct -Wno-c99-extensions -Wno-variadic-macros -Wno-nested-anon-types -Wno-gnu-include-next
CALLFLAGS += -O2
CFLAGS = $(CALLFLAGS) -std=gnu11
CXXFLAGS = $(CALLFLAGS) $(KEXTFLAGS) -O2 -mkernel -std=gnu++11 -Wno-inconsistent-missing-override
LDFLAGS = -nostdlib -Xlinker -kext 

TARGETS = $(PKG).kext/Contents/MacOS/SimpleDriver $(PKG).kext/Contents/Info.plist test_serv-mac

all: $(TARGETS)

.PHONY: clean

test_serv-mac: test_serv.c
	$(CC) $(CFLAGS) -framework IOKit -o $@ $^

SimpleDriver-mac: SimpleDriver.o SimpleDriver_info.o SimpleUserClient.o
	$(CXX) $(LDFLAGS) -o $@ $^

$(PKG).kext/Contents/MacOS/SimpleDriver: SimpleDriver-mac | $(PKG).kext/Contents/MacOS
	cp $^ $@

$(PKG).kext/Contents/Info.plist: Info-SimpleUserClient.plist | $(PKG).kext/Contents/MacOS
	cp $^ $@

$(PKG).kext/Contents/MacOS:
	mkdir -p $@

clean:
	rm -f *.o $(TARGETS)
	rm -rf SimpleDriver.*.ld/
	rm -rf $(PKG).kext
