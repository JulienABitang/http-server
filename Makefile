CC = gcc
CFLAGS = -MMD -MP
CFLAGS += -Wall -Wextra -g
LDFLAGS =

SDIR = src
BDIR = build

SRCS := $(shell find $(SDIR) -name '*.c')
OBJS := $(patsubst $(SDIR)/%.c, $(BDIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

TRGT = $(BDIR)/app



.PHONY: all clean run gdb

all: $(TRGT)

$(TRGT): $(OBJS)
	@mkdir -p $(BDIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TRGT)
	@echo "Built target :$@"

$(BDIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -rf $(BDIR)

run: $(TRGT)
	./$(TRGT)

gdb: $(TRGT)
	gdb $(TRGT)

-include $(DEPS)
