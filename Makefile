########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Thu Oct  3 21:53:53 CEST 2019                                        #
# Autor: Rita Kvitochka                                                #
#                                                                      #
# Script description:                                                  #
#                     This make file compiles convertor.               #
#                                                                      #
# Input paramete: NON                                                  #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

# add xml files
ROOTLIBS += -lMLP -lXMLIO

OUTLIB = ./obj/
CXX  = g++
CXX += -I./     

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)

PATHTOSHAREDLIB=$(OUTLIB)

#----------------------------------------------------#

all: makedir convertTXT2root analyzer

makedir:
	mkdir -p $(OUTLIB);
	#mkdir -p tmp;

printmakeinfo:
	$(info CXX          = "$(CXX)")
	$(info CXXFLAGS     = "$(CXXFLAGS)")

printmakehelp_and_reminder: convertTXT2root.cc  Makefile
	$(info  /********************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: convertTXT2root.cc  Makefile *)
	$(info  * $$@ ----> $@                               *)
	$(info  * $$< --------------------------------> $<           *)
	$(info  * $$^ --------------------------------> $^  *)
	$(info  /********************************************************************/)

convertTXT2root: convertTXT2root.cc
	$(CXX) -o $@ $< $(CXXFLAGS)

HistoPlot: HistoPlot.cc
	$(CXX) -o $@ $< $(CXXFLAGS)

analyzer: analyzer.c obj/Analyze.o
	$(CXX) -o analyzer analyzer.c $(OUTLIB)*.o $(CXXFLAGS)

obj/Analyze.o: Analyze.C Analyze.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)Analyze.o $<
clean: 
	rm -f *~
	rm -f convertTXT2root
	rm -f HistoPlot
	rm -rf $(OUTLIB)
	rm -f analyzer
