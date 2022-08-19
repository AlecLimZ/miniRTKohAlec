# Implicit variables
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror $(INCLUDE) -g3 -fsanitize=address

UNAME_S	= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	INCLUDE	=	-Iinclude -Ilibft -Imlx
	FDFLAGS	=	-L. -Llibft -Lmlx
	FDLIBS	=	-lrt -lft -lmlx
	MAC		=	-framework OpenGL -framework AppKit
	LIBX_PATH	=
	LIBX		=
else
	INCLUDE	=	-Iminilibx-linux -Iinclude -Ilibft
	FDLIBS	=	-lrt -lft -lmlx -lXext -lX11 -lm
	FDFLAGS	=	-L. -Llibft -Lminilibx-linux
	MAC		=
	LIBX_PATH	=	./minilibx-linux
	LIBX		=	$(LIBX_PATH)/libmlx.a
endif

# source and object files
DISPLAY_DIR =   display/
ELEMENT_DIR	=	element/
ERROR_DIR	=	error/
IMAGE_DIR	=	image/
LINALG_DIR	=	linalg/
PARSE_DIR	=	parse/
TRACE_DIR	=	trace/
UTILS_DIR	=	utils/


SRCDIR	=	src
SRCS	=	$(addprefix $(DISPLAY_DIR), \
				ft_cam_transform.c \
				ft_display.c \
				ft_draw.c \
				ft_light_transform.c \
				ft_mlx_image.c \
				ft_mlx_key.c \
				ft_mlx.c \
				ft_obj_transform.c \
			) \
			$(addprefix $(ELEMENT_DIR), \
				ft_camera.c \
				ft_light.c \
				ft_light_ambient.c \
				ft_light_point.c \
				ft_light_spot.c \
				ft_obj.c \
				ft_obj_cone.c \
				ft_obj_cylinder.c \
				ft_obj_plane.c \
				ft_obj_sphere.c \
				ft_obj_checkerboard.c \
				ft_obj_norm_map.c \
				ft_ray.c \
			) \
			$(addprefix $(ERROR_DIR), \
				ft_error.c \
			) \
			$(addprefix $(IMAGE_DIR), \
				ft_image.c \
				ft_image8.c \
				ppm_maker.c \
				ppm_reader.c \
			) \
			$(addprefix $(LINALG_DIR), \
				ft_affine_transform.c \
				ft_affine.c \
				ft_mat.c \
				ft_mat_mul.c \
				ft_mat_op.c \
				ft_math.c \
				ft_vec.c \
				ft_vec_mul.c \
				ft_vec_new.c \
				ft_vec_op.c \
			) \
			$(addprefix $(PARSE_DIR), \
				ft_array.c \
				ft_double.c \
				ft_parse_cam_light.c \
				ft_parse_obj.c \
				ft_parse_scene.c \
			) \
			$(addprefix $(TRACE_DIR), \
				ft_hit.c \
				ft_phong.c \
				ft_trace.c \
			)
OBJDIR	=	obj
OBJS	=	$(addprefix $(OBJDIR)/, $(SRCS:%.c=%.o))

# targets
MAIN	=	main.c
NAME	=	miniRT
LIBRT	=	librt.a

LIBFT_PATH	= ./libft

# colour and format
BOLD = \e[1m
PURPLE = \e[1;35m
GREEN = \e[1;32m
PINK_TEXT = \e[38;2;255;124;212m
NEWLINE = \e[1K\r

all: $(NAME)

# set up DISPLAY environment variable
setup_display:
	export DISPLAY=$(shell cat /etc/resolv.conf | grep nameserver | awk '{print $$2}'):0.0

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

$(LIBX):
	git submodule init
	git submodule update
	$(MAKE) -C $(LIBX_PATH)

$(NAME): $(LIBX) $(LIBFT_PATH)/libft.a $(LIBRT) $(MAIN)
	$(CC) $(CFLAGS) $(MAC) -o $(NAME) $(MAIN) $(FDFLAGS) $(FDLIBS)
	@printf "$(NEWLINE)$(GREEN)Successfully created $(GREEN)$@$(GREEN)!\n$(NO_COLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	@printf "$(NEWLINE)Creating object file $@ from $<"

$(LIBRT): $(OBJS)
	$(AR) crs $@ $?

clean:
	@echo "Removing object files..." 
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_PATH) -s

fclean: clean
	@echo "Removing executables and libraries..."
	@$(RM) $(NAME) $(LIBRT)
	@rm -rf $(LIBX_PATH)

re: fclean all

norm:
	norminette include/* src/* *.c

test:
	@gcc  -g3 -fsanitize=address -Iinclude -Ilibft -o 123TEST TEST.c -Llibft -lft
	@./123TEST
	@rm 123TEST

.PHONY: libft clean norm test
