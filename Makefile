CXX=g++
CXX_FLAGS=-Isrc -Wall -std=c++23
LIBS=-lraylib

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)

TARGET=game

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LIBS)

src/%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f src/*.o $(TARGET)

# Are these used?
#-lGL -lm -lpthread -ldl -lrt -lX11

web: ${SRCS}
	emcc -o game.html ${SRCS} -Os -Wall /usr/local/lib/libraylib.web.a -I src/ -I/usr/local/include/ -s ASYNCIFY -L src/ -Llibraylib -s USE_GLFW=3 --shell-file web/shell.html -DPLATFORM_WEB
