NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror

INCLUDE = -I include/pipex.h -I libft
INCLUDE_BONUS = -I include/pipex_bonus.h -I libft
LIB = -Llibft -lft
LIBFT = libft/libft.a

RM = rm -f

SRCS_FILES = 	main.c \
				init.c \
				utils.c \
				process.c \
				error_exit.c

SRCS = $(addprefix ./src/, $(SRCS_FILES))
OBJS = $(SRCS:%.c=%.o)

BONUS_FILES = 	main_bonus.c \
				init_files_bonus.c \
				init_bonus.c \
				utils_bonus.c \
				process_bonus.c \
				error_exit_bonus.c

BONUS_SRCS = $(addprefix ./bonus/, $(BONUS_FILES))
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)

%.o : %.c
			@$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@echo " [ .. ] | Compiling pipex.."
			@($(CC) $(FLAGS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME))
			@echo " [ OK ] | pipex ready!"

bonus:		$(LIBFT) $(BONUS_OBJS)
			@echo " [ .. ] | Compiling pipex.."
			@($(CC) $(FLAGS) $(INCLUDE_BONUS) $(BONUS_OBJS) $(LIB) -o $(NAME))
			@echo " [ OK ] | pipex bonus ready!"

$(LIBFT):
			@echo " [ .. ] | Compiling libft.."
			@make -s -C libft
			@echo " [ OK ] | Libft ready!"

clean:
			@echo " [ .. ] | Cleaning objects.."
			@make -s -C libft clean
			@($(RM) $(OBJS) $(BONUS_OBJS))
			@echo " [ OK ] | Objects removed!"

fclean: 	clean
			@echo " [ .. ] | Cleaning libraries and executable.."
			@make -s -C libft fclean
			@($(RM) $(NAME))
			@echo " [ OK ] | Everything is clean!"

re: 		fclean all

reb: 		fclean bonus

.PHONY:		all clean fclean re
