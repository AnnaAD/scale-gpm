TARGET ?= GraphCounting.out
SRC_DIRS ?= ./

INCLUDES:=-Iinclude

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS))) VertexSet.o graph-automine.o
DEPS := $(OBJS:.o=.d)

VPATH += common

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -g0 -O3 -march=native -std=c++14 -Wall -Wextra
CPPFLAGS += -g

LDLIBS = -ltbb -pthread

HELPFLAGS = -I$(TBB_INCLUDE) -Wl,-rpath,$(TBB_LIBRARY_RELEASE) -L$(TBB_LIBRARY_RELEASE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

$(TARGET): $(OBJS)
	g++ $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(HELPFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
