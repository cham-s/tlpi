NAME = libtlpi.a
CC = gcc
AR = ar rc
OBJDIR = obj
OBJ = $(OBJDIR)/error_functions.o \
	  $(OBJDIR)/get_num.o 

CFLAGS = -c -I include
.PHONY: all re clean fclean

VPATH= src/

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "removed lib"

re: fclean all
