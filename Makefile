CC      = gcc
TARGET  = TicTacToe
SRCDIR  = src
OBJDIR  = $(SRCDIR)
SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

$(TARGET): $(OBJS)
	$(CC) -Wall -o $@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -Wall -o $@ -c $<

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET) *.d

