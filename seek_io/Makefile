NAME 		= seek_io 
CC 			= gcc 
LIB 		= ../libtlpi/libtlpi.a
INCLUDES 	= -I ../libtlpi/include
OBJDIR		= obj
OBJS 		= $(OBJDIR)/seek_io.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(INCLUDES) $(OBJS) $(LIB) -o $(NAME)

$(LIB):
	make -C libft/

$(OBJDIR)/%.o : %.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all
