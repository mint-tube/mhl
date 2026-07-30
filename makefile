CXX ?= clang++
CXXFLAGS = -std=c++17 -O1 -DDEBUG -Wall -Wextra -Wpedantic -Werror -fsanitize=address

SRCS = $(wildcard examples/*.cpp)
NAMES = $(notdir $(basename $(SRCS)))

help:
	$(info Select a lib to run the example for:)
	$(info - ${NAMES})

$(NAMES): %: examples/%.cpp include/%.hpp
	mkdir -p .build
	$(CXX) $(CXXFLAGS) $< -o .build/$@
	.build/$@

.SILENT:
.PHONY: help $(NAMES)