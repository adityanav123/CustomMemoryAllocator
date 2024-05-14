CC = gcc
CFLAGS = -std=c99 -Wall

TARGET = $(firstword $(MAKECMDGOALS))
SRCS = $(TARGET).c MemoryAllocate.c
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(info SRCS: $(SRCS))
$(info OBJS: $(OBJS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning up"
	rm -f $(OBJS) $(TARGET)