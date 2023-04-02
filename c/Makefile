CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -fPIC
LDFLAGS = -Llibs/lib -lasncodec
TARGET = out/libmylibrary.a
SRCDIR = src
OBJDIR = tmp/obj
INCDIR = tmp/generated

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

test:
	$(CC) $(CFLAGS) -I$(INCDIR) -o main.out src/main.c libs/lib/libasncodec.a
