CXX ?= clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Werror -I./include

SRCS = $(wildcard examples/*.cpp)
NAMES = $(notdir $(basename $(SRCS)))

help:
	$(info Select a lib to run the example for:)
	$(info - ${NAMES})

$(NAMES): %: examples/%.cpp include/%.hpp
ifeq ($(OS), Windows_NT)
	if not exist .build mkdir .build
	$(CXX) $(CXXFLAGS) $< -o .build\$@.exe
	.build\$@.exe
else
	mkdir -p .build
	$(CXX) $(CXXFLAGS) $< -o .build/$@
	.build/$@
endif

.SILENT:
.PHONY: help $(NAMES)