NAME 		= ft_tee 
CC 			= gcc 
LIB 		= ../libtlpi/libtlpi.a
INCLUDES 	= -I ../libtlpi/include
OBJDIR		= obj
OBJS 		= $(OBJDIR)/ft_tee.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDES) $(OBJS) $(LIB) -o $(NAME)


$(OBJDIR)/%.o : %.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
