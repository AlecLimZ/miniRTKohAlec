# Implicit variables
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I../include -I../libft -I../minilibx-linux -g -fsanitize=address
LDFLAGS	=	-L.. -L../libft -L../minilibx-linux
LDLIBS	=	-lrt -lft -lmlx -lm
SRCS	=	$(wildcard */test*.c)
FILES	=	$(notdir $(SRCS))
MAINS	=	$(FILES:test_%.c=%)

all: $(MAINS)

echo:
	echo $(MAINS)

librt:
	@make --no-print-directory -C .. librt.a

%: */test_%.c librt
	@$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)
	@echo Testing $<:
	@./$@
	@$(RM) $@

clean:
	@echo "Removing test executables..."
	$(RM) $(MAINS)

fclean: clean
	@$(MAKE) --no-print-directory -C .. fclean

re: fclean all

norm:
	norminette */*.c

.PHONY: clean librt norm
