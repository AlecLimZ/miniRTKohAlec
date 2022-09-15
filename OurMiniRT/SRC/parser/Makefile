test:
	gcc -Wall -Werror -Wextra *.c ../get_next_line*.c \
		-I../INCLUDES -I../libft ../libft/libft.a -g3
	@echo =========================
	./a.out sample.rt
	@echo =========================
	- ./a.out sample.rt sample.rt
	@echo =========================
	- ./a.out missing.rt
	@echo =========================
	- ./a.out
	@echo =========================
	- ./a.out Makefile
	@echo =========================
	- norminette *.c
	- norminette ../INCLUDES/*