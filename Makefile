SHELL = /bin/sh
ARCH  = $(shell uname)
ARCHP = $(shell uname -m)

#############################
# basic numbers 
#############################
package = RAYTRACECTA
version = 9.90
distdir = $(package)-$(version)
#############################
# check root version number
#############################
ROOTVERSION=$(shell root-config --version)
ROOT528=$(shell expr 5.28 \>= `root-config --version | cut -f1 -d \/`)
#############################
# check for root libraries
#############################
ROOT_MLP=$(shell root-config --has-xml)
ROOT_MINUIT2=$(shell root-config --has-minuit2)
ROOT_MYSQL=$(shell root-config --has-mysql)

########################################################################################################################
# compile and linker flags
########################################################################################################################
# compiler and linker general values
ifeq ($(ARCH),Darwin)
ifeq ($(ARCHP),i386)
CXX           = g++ -arch i386
endif
ifeq ($(ARCHP),x86_64)
CXX           = g++ -arch x86_64
endif
endif
ifeq ($(ARCH),Linux)
CXX           = g++ 
endif
CXXFLAGS      = -O3 -g -Wall -fPIC  -fno-strict-aliasing  -D_FILE_OFFSET_BITS=64 -D_LARGE_FILE_SOURCE -D_LARGEFILE64_SOURCE
CXXFLAGS     += -I. -I./inc/
LD            = g++
OutPutOpt     = -o
INCLUDEFLAGS  = -I. -I./inc/

# linux depending flags
ifeq ($(ARCH),Linux)
LDFLAGS       = -O
SOFLAGS       = -shared
endif
# Apple OS X flags
ifeq ($(ARCH),Darwin)
ifeq ($(ARCHP),i386)
LDFLAGS        = -bind_at_load -arch i386
endif
ifeq ($(ARCHP),x86_64)
LDFLAGS       = -bind_at_load -arch x86_64
endif
DllSuf        = dylib
UNDEFOPT      = dynamic_lookup
SOFLAGS       = -dynamiclib -single_module -undefined $(UNDEFOPT)
endif

########################################################
# CXX FLAGS (taken from root)
########################################################
ROOTCFLAGS   = $(shell root-config --auxcflags)
CXXFLAGS     += $(ROOTCFLAGS)
CXXFLAGS     += -I$(shell root-config --incdir) -I$(shell root-config --incdir)
########################################################
# root libs
########################################################
ROOTGLIBS     = $(shell root-config --glibs)
GLIBS         = $(ROOTGLIBS)
GLIBS        += -lMLP -lTreePlayer -lMinuit -lXMLIO
ifeq ($(ROOT_MINUIT2),yes)
   GLIBS     += -lMinuit2
endif

########################################################
# paths
########################################################
VPATH = src:inc


########################################################
# compilation and linking
#
# binaries: ./bin directory
# libraries: ./lib directory
########################################################

all:	causation

########################################################
# eventdisplay
########################################################

MODOBJECTS =	./obj/VReadRunParameter.o \
		./obj/VParameters.o \
		./obj/VLoop.o


########################################################
# implicit rules
########################################################
./obj/%.o:	%.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

./obj/%.o:	./src/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

./obj/%.o:	%.C
	$(CXX) $(CXXFLAGS) -c -o $@ $<

./obj/%.o:	%.c %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

./obj/%_Dict.o:	./inc/%.h ./inc/%LinkDef.h
	@echo "Generating dictionary $@.."
	@echo rootcint -f $(basename $@).cpp -c -p $?
	@rootcint -f $(basename $@).cpp -c -p $?
	$(CXX) $(CXXFLAGS) -c -o $@ $(basename $@).cpp

$(TARGET):	$(OBJECTS) 
#ifeq ($(PLATFORM),macosx)
	$(LD) $(SOFLAGS) $^ $(OutPutOpt) $@
	ln -sf $@ $(subst .$(DllSuf),.so,$@)
#else
#	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)
#endif
	@echo "$@ done"

#######################################################

# finalize
MODOBJECTS += ./obj/causation.o

# compile and link
./obj/causation.o:	./src/causation.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

causation:	$(MODOBJECTS)
	@echo "LINKING"
	$(LD) $(LDFLAGS) $^ $(GLIBS) $(OutPutOpt) ./bin/$@

	@echo "$@ done"


###############################################################################################################################
install:	all
	@echo "causation install: see ./bin/ and ./lib/ directories"

###############################################################################################################################
clean:
	-rm -f ./obj/*.o ./obj/*_Dict.cpp ./obj/*_Dict.h 
###############################################################################################################################

.PHONY: all clean install FORCEDISTDIR 
