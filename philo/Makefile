CC=gcc
CFLAGS=-Wall -Wextra -Werror -I $(INCLDIR) #-fsanitize=thread -g3 
RM=rm -rf
MD=mkdir -p

SRCDIR=src
OBJDIR=.obj
INCLDIR=incl

CFILES=main fork_mutex log time util philo
HFILES=philo
BIN=philo

OBJ_FILES=$(addprefix $(OBJDIR)/,$(addsuffix .o,$(CFILES)))
INCL_FILES=$(addprefix $(INCLDIR)/,$(addsuffix .h,$(HFILES)))

all: $(BIN)

re: fclean all

fclean: clean
	$(RM) $(BIN)

clean:
	$(RM) $(OBJDIR)

$(BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCL_FILES) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	$(MD) $@

.PHONY: all clean fclean re
