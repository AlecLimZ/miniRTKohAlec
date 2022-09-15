NAME		= miniRT
SRC			= $(wildcard SRC/*.c) $(wildcard SRC/*/*.c)
OBJ			= $(SRC:%.c=%.o)
HEADERDIR	= SRC/INCLUDES
LIBFT		= libft/libft.a
MLXLINUX	= mlx_linux/libmlx.a
MLXMETAL	= mlx_mms_20191025/libmlx.dylib
MLXOPENGL	= minilibx_macos/libmlx.a
LIBMLX		= $(MLXMETAL) # choose MLXOPENGL or MLXMETAL
VPATH		= SRC # ./miniRT from ./SRC/miniRT.c

ASAN		= -fsanitize=address
CFLAGS		= -Wall -Werror -Wextra $(ASAN) #-g3
CPPFLAGS	= $(addprefix -I, $(HEADERDIR) $(dir $(LIBFT) $(LIBMLX)))
LDFLAGS		= $(ASAN)
LDLIBS		= $(LIBFT) $(LIBMLX) -framework OpenGL -framework AppKit

ifeq ($(shell uname), Linux)
	LIBMLX	= $(MLXLINUX)
	LDLIBS	= $(LIBFT) $(LIBMLX) -lXext -lX11 -lm
endif

all		: $(NAME)

$(NAME)	: $(OBJ) | $(LIBMLX) $(LIBFT)

$(LIBFT) $(LIBMLX):
		make -C $(dir $@)
		- @cp $(MLXMETAL) libmlx.dylib

clean	:
		rm -rf $(OBJ) $(OBJC)
		make clean -C $(dir $(LIBFT))
		make clean -C $(dir $(LIBMLX))

fclean	: clean
		rm -rf $(NAME)
		make fclean -C $(dir $(LIBFT))

re		: fclean all

.PHONY	: all clean fclean re debug

debug	:
		: $(COMPILE.c)
		: $(LINK.o) ... $(LOADLIBES) $(LDLIBS) -o ...
		: $(SRC)
		: $(OBJ)
