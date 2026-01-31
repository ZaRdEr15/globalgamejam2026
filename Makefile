CXX=g++
CXX_FLAGS=-Isrc -Wall -std=c++23 -MMD -MP
LIBS=-lraylib # -lGL -lm -lpthread -ldl -lrt -lX11

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

TARGET=game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LIBS)

src/%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

-include $(DEPS)

.PHONY: clean

clean:
	rm -f src/*.o src/*.d $(TARGET)

web: ${SRCS}
	emcc -o game.html ${SRCS} -Os -Wall /usr/local/lib/libraylib.web.a -I src/ -I/usr/local/include/ -s ASYNCIFY -L src/ -Llibraylib -s USE_GLFW=3 --shell-file web/shell.html -DPLATFORM_WEB
