CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -O2 -std=c11 -pthread
LDFLAGS := -lrt -pthread

INCDIR  := include
SRCDIR  := src
BINDIR  := bin

INCS := -I$(INCDIR)

SRC := $(SRCDIR)/main.c \
       $(SRCDIR)/aggregator.c \
       $(SRCDIR)/producer.c \
       $(SRCDIR)/signals.c \
       $(SRCDIR)/ipc_mq.c \
       $(SRCDIR)/ipc_shm.c \
       $(SRCDIR)/ipc_fifo.c \
       $(SRCDIR)/logio.c \
       $(SRCDIR)/thread_queue.c

OBJ := $(SRC:.c=.o)

TARGET := $(BINDIR)/smart_factory_sim

.PHONY: all clean run test dirs

all: dirs $(TARGET)

dirs:
    mkdir -p $(BINDIR)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) $(INCS) -c $< -o $@

run: all
    $(TARGET) --producers 3 --duration 12 --rate 10 --seed 42

test: all
    bash tests/run_smoke.sh && bash tests/run_stress.sh

clean:
    rm -rf $(OBJ) $(TARGET) $(BINDIR) *.log *.txt