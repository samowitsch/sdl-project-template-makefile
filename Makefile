# ========== modify following lines ==========

# your code sign identity
CODESIGN_IDENTITY=2ADE32D28C2898C1C5CB0CE2F06E57F6675945C7

# absolute path to mobileprovision profile file
MOBILEPROVISION_PROFILE=/mobileprovision/ios/SDL2TestChristianSonntagAdHoc.mobileprovision

# bundle identifier
BUNDLE_IDENTIFIER=de.motions-media.SDL2Test

# bundle name
BUNDLE_NAME=SDL2Test

APP_NAME = SDL2 Test
APP_VERSION = 1.0
APP_INFO = © 2016 by example

XCODE_BASE=/Applications/Xcode.app/Contents
SIMULATOR_BASE=$(XCODE_BASE)/Developer/Platforms/iPhoneSimulator.platform
FRAMEWORKS=$(SIMULATOR_BASE)/Developer/SDKs/iPhoneSimulator9.2.sdk/System/Library/Frameworks/
INCLUDES=$(SIMULATOR_BASE)/Developer/SDKs/iPhoneSimulator9.2.sdk/usr/include

# ========== dont modify following lines ==========

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(notdir $(patsubst %/,%,$(dir $(MKFILE_PATH))))

# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:=$(shell uname -s)

#colors
BOLD = \033[0;37m\033[44m***
NORMAL =  ***\033[0;32m\033[40m

FRAMEWORK_PATH=./frameworks/osx
RESOURCES_PATH=./resources
RESOURCES_OSX_PATH=./share/osx
SOURCE_PATH=./src

RM = rm -rf

CXX = g++

include ./makefiles/Makefile.flags

SRCS = $(wildcard $(SOURCE_PATH)/*.cpp) $(wildcard $(SOURCE_PATH)/**/*.cpp) $(wildcard $(SOURCE_PATH)/**/**/*.cpp) $(wildcard $(SOURCE_PATH)/**/**/**/*.cpp)
OBJS = $(SRCS:.cpp=-$(TARGET).o)

all: $(EXECUTABLE) package

build: $(EXECUTABLE) package

include ./makefiles/Makefile.compile
include ./makefiles/Makefile.executable
include ./makefiles/Makefile.clean
include ./makefiles/Makefile.package
include ./makefiles/Makefile.run
