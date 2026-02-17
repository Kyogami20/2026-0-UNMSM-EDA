CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -pthread -I.
LDFLAGS = -pthread

TARGET = main
SRCS = main.cpp Others/util.cpp Others/pointers.cpp \
       Demos/DemoArray.cpp Demos/DemoLists.cpp Demos/DemoDoubleLinkedList.cpp \
       Demos/DemoCircularLinkedList.cpp Demos/DemoStack.cpp
OBJS = $(SRCS:.cpp=.o)

# ---- Compatibilidad Windows / Unix ----
ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q
    TARGET_EXE = $(TARGET).exe
    OBJS_CLEAN = $(subst /,\,$(OBJS))
else
    RM = rm -f
    TARGET_EXE = $(TARGET)
    OBJS_CLEAN = $(OBJS)
endif
# --------------------------------------

all: $(TARGET_EXE)

$(TARGET_EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJS_CLEAN) $(TARGET_EXE)

.PHONY: all clean