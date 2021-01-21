CC := g++
LINK := g++
MOC := /usr/lib/qt5/bin/moc
UIC := /usr/lib/qt5/bin/uic
CFLAGS := -Wall -g -fPIC `pkg-config --cflags --libs Qt5Gui Qt5Core Qt5Charts`
TARGET := test

SRCS := $(wildcard src/*/*.cpp src/*.cpp src/*/*/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

UIS := $(wildcard src/*/*.ui src/*.ui src/*/*/*.ui)
H_UIS := $(patsubst %.ui,%.h,$(UIS))

all: $(H_UIS) $(TARGET)

$(TARGET): $(H_UIS) $(OBJS)
	$(LINK) $(CFLAGS) -o $@ $^

%.h: %.ui
	$(UIC) -o $(patsubst %.ui,%.h,$<) $<

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(patsubst %.cpp,%.o,$<)


## Meta-Object Compiler (moc)

configure: compiler_moc_header_make_all $(H_UIS)

compiler_ui: $(H_UIS)

compiler_moc_header_make_all: moc_mainWindow moc_chartWindow moc_thread

compiler_moc_header_clean:
	rm -f src/gui/main/moc_mainWindow.cpp src/utils/moc_thread.cpp

moc_mainWindow:
	$(MOC) include/gui/mainWindow.h -o src/gui/main/moc_mainWindow.cpp
moc_chartWindow:
	$(MOC) include/gui/chartWindow.h -o src/gui/chart/moc_chartWindow.cpp
moc_thread:
	$(MOC) include/utils/thread.h -o src/utils/moc_thread.cpp

#######

clean: compiler_moc_header_clean
	rm -rf $(TARGET) *.o $(OBJS) $(H_UIS)
	
.PHONY: all clean