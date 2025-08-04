NAME = pipex
SRC = srcs/pipex.c srcs/utils.c srcs/processing.c srcs/execution.c
BONUS_SRC = bonus_srcs/pipex_bonus.c bonus_srcs/utils_bonus.c bonus_srcs/execution_bonus.c bonus_srcs/pipes_bonus.c bonus_srcs/pipe_utils_bonus.c
OBJ_DIR = objs
BONUS_OBJ_DIR = bonus_objs
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:bonus_srcs/%.c=$(BONUS_OBJ_DIR)/%.o)
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

bonus: $(LIBFT) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)

$(BONUS_OBJ_DIR)/%.o: bonus_srcs/%.c includes/*.h
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus