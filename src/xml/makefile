# file      : examples/build/cxx/rules.make
# copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

# file      : examples/build/cxx/compilers.make
# copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

CXX := g++

cxx_sign := $(shell t=`$(CXX) -V 2>&1`; if test $$? -eq 0; then echo $$t; fi)

ifeq ($(cxx_sign),)
cxx_sign := $(shell t=`$(CXX) --version 2>&1`; if test $$? -eq 0; then echo $$t; fi)
endif

# IBM XL C++ V7.0 returns error code when called with the -qversion option. This
# complicates our life quite a bit.
#
ifeq ($(cxx_sign),)
cxx_sign := $(shell t=`$(CXX) -qversion 2>/dev/null`; echo $$t)
ifneq ($(shell echo '$(cxx_sign)' | sed -e 's/^.*IBM XL C\/C.. .*$$//'),)
cxx_sign :=
endif
endif

cxx_id :=

ifneq ($(cxx_sign),)

# GNU g++ (g++)
#
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^[^ ]* (GCC) .*$$//'),)
cxx_id := gnu
endif
endif

# g++ 4.3 removed GCC for some reason so check for g++ also.
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^g++.*$$//'),)
cxx_id := gnu
endif
endif

# Clang
#
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^.*clang.*$$//'),)
cxx_id := clang
endif
endif

ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^.*Clang.*$$//'),)
cxx_id := clang
endif
endif

# Sun C++ (CC)
#
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^[^ ]* Sun C.. .*$$//'),)
cxx_id := sun
endif
endif


# HP C++ (aCC)
#
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^[^ ]* HP aC..\/ANSI C .* A\.06\..*$$//'),)
cxx_id := hp
endif
endif

ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^[^ ]* HP C\/aC.. .* A\.06\..*$$//'),)
cxx_id := hp
endif
endif

# Intel C++ (icpc)
#

# 9.x
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^Intel(R) C.. .*$$//'),)
cxx_id := intel
endif
endif

# 8.x
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^8\..$$//'),)
cxx_id := intel
endif
endif


# IBM XL C++
#
ifeq ($(cxx_id),)
ifeq ($(shell echo '$(cxx_sign)' | sed -e 's/^.*IBM XL C\/C.. .*$$//'),)
cxx_id := ibm
endif
endif


# Unknown
#
ifeq ($(cxx_id),)
$(warning unknown C++ compiler signature '$(cxx_sign)', continuing anyway)
endif


else
$(warning unable to obtain compiler signature for '$(CXX)', continuing anyway)
endif

#$(warning $(cxx_sign))
#$(warning $(cxx_id))


# GNU g++
#
ifeq ($(cxx_id),gnu)
  CXXFLAGS := -W -Wall -O3
endif

# Clang
#
ifeq ($(cxx_id),clang)
  CXXFLAGS := -W -O3
endif

# Intel C++
#
ifeq ($(cxx_id),intel)
  CXXFLAGS := -w1 -O2
endif


# Sun C++
#
ifeq ($(cxx_id),sun)
  CXXFLAGS := -O
endif


# HP aCC
#
ifeq ($(cxx_id),hp)

  # By default Xerces-C++ is built with -mt for aCC.
  # 2334 no suitable copy constructor (e.g., for std::auto_ptr)
  #
  CXXFLAGS := -Aa -O -mt +W2334
endif


# IBM XL C++
#
ifeq ($(cxx_id),ibm)
  CXXFLAGS := -qrtti -O
endif


# Rules.
#
%.o: %.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# file      : examples/build/xsd/parser-rules.make
# copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

# file      : examples/build/xsd/common.make
# copyright : Copyright (c) 2006-2014 Code Synthesis Tools CC
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

XSD := $(shell if test -x $(root)/../bin/xsd; \
               then echo $(root)/../bin/xsd; \
               else echo xsd; fi)

override CPPFLAGS += $(shell if test -d $(root)/../libxsd; \
                             then echo -I$(root)/../libxsd; fi)

XML_PARSER := xerces

ifeq ($(XML_PARSER),xerces)
override LIBS := -lxerces-c $(LIBS)
else
override LIBS := -lexpat $(LIBS)
endif

override XSDFLAGS += --xml-parser $(XML_PARSER)

# Rules.
#
.PRECIOUS: %-pskel.hxx %-pskel.ixx %-pskel.cxx

%-pskel.hxx %-pskel.ixx %-pskel.cxx: %.xsd
	$(XSD) cxx-parser $(XSDFLAGS) $<


# Build.
#
molsimInput: molsimInput.o molsimInput-pskel.o

molsimInput.o: molsimInput.cxx molsimInput-pskel.hxx
molsimInput-pskel.o: molsimInput-pskel.cxx molsimInput-pskel.hxx

molsimInput-pskel.hxx molsimInput-pskel.cxx: molsimInput.xsd


# Test.
#
.PHONY: test
test: molsimInput molsimInput.xml
	./molsimInput molsimInput.xml


# Clean.
#
.PHONY: clean
clean:
	rm -f molsimInput-pskel.?xx molsimInput-pskel.o molsimInput.o molsimInput
