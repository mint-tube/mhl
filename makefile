CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Werror -I./include

SRCS = $(wildcard examples/*.cpp)
NAMES = $(notdir $(basename $(SRCS)))
EXES = $(addprefix .build/ , $(NAMES))

$(shell mkdir -p .build)

help:
	$(info Select a lib to compile the example for:)
	$(info - 'all' ${NAMES})

all: $(NAMES)

$(NAMES): %: examples/%.cpp include/%.hpp
	$(CXX) $(CXXFLAGS) $< -o .build/$@
	.build/$@

clean:
	rm -rf .build

.SILENT:
.PHONY: all clean help $(NAMES)