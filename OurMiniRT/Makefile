NAME		= miniRT
SRCS			= \
	SRC/app.c \
	SRC/benchmark.c \
	SRC/control.c \
	SRC/control_mouse.c \
	SRC/control_util.c \
	SRC/control_util2.c \
	SRC/gui.c \
	SRC/help.c \
	SRC/miniRT.c \
	SRC/parser/export.c \
	SRC/parser/parser.c \
	SRC/parser/parser_types.c \
	SRC/parser/parser_utils.c \
	SRC/parser/parser_utils_2.c \
	SRC/parser/parse_lights.c \
	SRC/raytracer/cylinder.c \
	SRC/raytracer/plane.c \
	SRC/raytracer/raytrace2.c \
	SRC/raytracer/raytracer.c \
	SRC/raytracer/sphere.c \
	SRC/raytracer/vector.c \
	SRC/raytracer/vector2.c \
	SRC/rotate.c

OBJ			= $(SRCS:%.c=%.o)
DEP			= $(SRCS:%.c=%.d)
HEADERDIR	= SRC/INCLUDES
LIBFT		= libft/libft.a
MLXLINUX	= mlx_linux/libmlx.a
MLXMETAL	= mlx_mms_20200219/libmlx.dylib
MLXOPENGL	= minilibx_macos/libmlx.a
LIBMLX		= $(MLXOPENGL) # choose MLXOPENGL or MLXMETAL
VPATH		= SRC # ./miniRT from ./SRC/miniRT.c

ASAN		= -fsanitize=address
CFLAGS		= -Wall -Werror -Wextra -MMD $(ASAN) -flto -Ofast #-Wno-unused-variable #-g3
CPPFLAGS	= $(addprefix -I, $(HEADERDIR) $(dir $(LIBFT) $(LIBMLX)))
LDFLAGS		= $(ASAN) -flto
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

-include $(DEP)

$(NAME)	: $(OBJ) | $(LIBMLX) $(LIBFT) norm

$(LIBFT) $(LIBMLX):
		make -C $(dir $@)
		- @cp $(MLXMETAL) libmlx.dylib

clean	:
		rm -rf $(OBJ) $(DEP)
		make clean -C $(dir $(LIBFT))
		# make clean -C $(dir $(LIBMLX))

fclean	: clean
		rm -rf $(NAME)
		make fclean -C $(dir $(LIBFT))

re		: fclean all

.PHONY	: all clean fclean re

norm	: $(SRCS) $(wildcard $(HEADERDIR)/*)
		- @ norminette $? && touch $@

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
		: $(SRCS)
		: $(OBJ)

noasan	:
		@if nm $(NAME) | grep asan_init; then make re ASAN=""; fi
		@echo ASAN removed

vg		: noasan
		valgrind --leak-check=full  --show-leak-kinds=all ./$(NAME) scenes/sample.rt
