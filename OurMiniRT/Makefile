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

# WSL only
ifeq ($(shell uname), Linux)
	LIBMLX	= $(MLXLINUX)
	LDLIBS	= $(LIBFT) $(LIBMLX) -lXext -lX11 -lm
wsl_run: all | wsl_pre
	@if test -d /run/WSL; then \
		export DISPLAY=$$(cat /etc/resolv.conf | grep nameserver | awk '{print $$2}'):0.0; \
	else \
		export DISPLAY=localhost:0.0; \
	fi; \
	echo export DISPLAY=$$DISPLAY; \
	./$(NAME) scenes/sample.rt
wsl_pre:
	@echo \"sudo apt-get install gcc make xorg libxext-dev libbsd-dev\" if cannot compile
endif

all		: $(NAME)

$(NAME)	: $(OBJ) | $(LIBMLX) $(LIBFT) norm

$(LIBFT) $(LIBMLX):
		make -C $(dir $@)
		- @cp $(MLXMETAL) libmlx.dylib

clean	:
		rm -rf $(OBJ) $(OBJC)
		make clean -C $(dir $(LIBFT))
		# make clean -C $(dir $(LIBMLX))

fclean	: clean
		rm -rf $(NAME)
		make fclean -C $(dir $(LIBFT))

re		: fclean all

.PHONY	: all clean fclean re

norm	: $(SRC) $(wildcard $(HEADERDIR)/*)
		- @ if [ "$@" == "norm" ]; then norminette $? && touch $@; fi

test	: $(NAME)
		@echo =========================
		- ./miniRT scenes/sample.rt sample.rt
		@echo =========================
		- ./miniRT missing.rt
		@echo =========================
		- ./miniRT
		@echo =========================
		- ./miniRT Makefile
		@echo =========================
		./miniRT scenes/sample.rt

info	:
	: $(SRC)
	: $(OBJ)
