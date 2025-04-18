NAME = so_long
FLAGS = -Wall -Wextra -Werror -g3
SRCS = src/main.c src/exit_code.c src/check_input.c src/display.c
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:src/%.c=%.o))
LIBFT = ./libft/libft.a
MLX_DIR = ./libft/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

# Cible par défaut
all: $(NAME)

# Cible pour lier les fichiers objets et créer le binaire
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "Linking $(NAME)..."
	@cc $(FLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

# Créer le répertoire obj si nécessaire
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Compiler chaque fichier source en fichier objet
$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR)
	@echo "Compiling $<..."
	@cc $(FLAGS) -I$(MLX_DIR) -c $< -o $@

# Règle pour la librairie libft
$(LIBFT):
	@make -C ./libft

# Règle pour la MinilibX
$(MLX):
	@echo "Compiling MinilibX..."
	@make -C $(MLX_DIR)

# Nettoyage des fichiers objets et du binaire
clean: 
	@rm -rf $(OBJS_DIR)
	@make -C ./libft clean
	@make -C $(MLX_DIR) clean

# Nettoyage complet, y compris la libft et la mlx
fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

# Reconstruction complète
re: fclean all

.PHONY: all clean fclean re