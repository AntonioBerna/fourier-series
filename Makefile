CFLAGS=-Wall -Wextra -ggdb `pkg-config --cflags raylib`
CLIBS=`pkg-config --libs raylib` `pkg-config --libs glfw3` -lm -ldl -lpthread

TARGET=fourier

all:
	@mkdir -p ./bin
	clang $(CFLAGS) -o ./bin/$(TARGET) ./src/main.c ./src/wave.c $(CLIBS) -L./bin/ -I./include/
	@echo "Build complete."

clean:
	$(RM) -r ./bin
	@echo "Clean complete."

run:
	./bin/$(TARGET)

.PHONY: clean run