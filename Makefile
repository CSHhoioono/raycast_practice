NAME = raycasting_practice

RM			= rm -rf

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

HEADER_DIR = ./include/
HEADER_LIST	= 
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))


MLX_URL 	= https://github.com/42paris/minilibx-linux.git
MLX_DIR		= ./minilibx-linux/
MLX	= $(addprefix $(MLX_DIR), libmlx_Linux.a)

INCLUDE	= -I$(MLX_DIR) -I$(HEADER_DIR)
LIBRARY	= -L$(MLX_DIR) -libmlx_Linux -lXert -lX11 -lm -lz

SRC_DIR		= ./srcs/
SRCS_LIST	= init.c loop.c draw.c\
			  raycast.c input.c util.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

MAIN	= $(addprefix $(SRC_DIR), main.c)

OBJ_DIR		= ./objs/
OBJS		= $(addprefix $(OBJ_DIR), $(SRCS_LIST:.c=.o))

all	: $(NAME)

$(NAME)	: $(MLX) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBRARY) -o $@

$(OBJ_DIR) : $(SRC_DIR)
	@if [ ! -d "$(OBJS_DIR)" ]; then\
		mkdir -p $@;\
	fi

$(OBJ_DIR)$.o : $(SRCS_DIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(MLX) : clone_mlx
	@if [ ! -f "$(MLX)" ]; then\
		$(MAKE) -C $(MLX_DIR);\
	fi

clone_mlx :
	@if [ ! -d "$(MLX_DIR)" ]; then\
		git clone $(MLX_URL) $(MLX_DIR);\
	fi

clean :
	$(RM) $(OBJ_DIR)
	@if [ -d "$(MLX_DIR)" ]; then\
		$(MAKE) -C $(MLX_DIR) clean;\
	fi

fclean : clean
	$(RM) $(NAME) $(MLX_DIR)

re : fclean all

.PHONY : all clean fclean re
