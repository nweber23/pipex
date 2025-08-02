NAME = pipex
SRC = srcs/pipex.c srcs/utils.c
BONUS_SRC = srcs/pipex_bonus.c srcs/utils_bonus.c
OBJ_DIR = objs
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:srcs/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes/ -I./libft/includes/

# Library paths
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c includes/*.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus: ${OBJ} ${BONUS_OBJ}
	ar rcs ${NAME} ${OBJ} ${BONUS_OBJ}

.PHONY: all clean fclean re bonus