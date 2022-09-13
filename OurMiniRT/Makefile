NAME		= MiniRT
SRC			= SRC/*.c
CUR			= main.c
OBJ			= $(SRC:%.c=%.o)
OBJC		= $(CUR:%.c=%.o)
CC			= gcc
LIBPATH		= SRC/libft/
HEADERDIR	= SRC/INCLUDES/

all		: $(NAME)

#Macos
$(OBJ)	: $(SRC)
		make bonus -C $(LIBPATH)
#		make -C mlx_mms_20191025
		make -C minilibx_macos
		$(CC) -Wall -Werror -Wextra -Imlx -c $(SRC) -I$(HEADERDIR)
		mv *.o SRC/

# Convert the main to .o on the main place
$(OBJC)	: $(CUR)
		$(CC) -Wall -Werror -Wextra -Imlx -c $(CUR) -I$(HEADERDIR)

$(NAME)	: $(OBJ) $(OBJC)
		$(CC) -Lminilibx_macos -lmlx -framework OpenGL -framework AppKit $^ $(LIBPATH)libft.a -o $(NAME)

linux	:
		make bonus -C $(LIBPATH)
		make -C mlx_linux
		$(CC) -Wall -Werror -Wextra -Imlx -c $(SRC) $(CUR) -I$(HEADERDIR)
		mv *.o SRC/
		$(CC) SRC/*.o $(LIBPATH)libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o miniRT

clean	:
		rm -rf $(OBJ) $(OBJC)
		make clean -C $(LIBPATH)
		make clean -C mlx_mms_20191025
		make clean -C minilibx_macos
		make clean -C mlx_linux

fclean	: clean
		rm -rf $(NAME)
		make fclean -C $(LIBPATH)

re		: fclean all
		make re -C $(LIBPATH)

.PHONY	: all clean fclean re
