#############################################################################################
#############################################################################################
#####                                     sources                                       #####
#############################################################################################
#############################################################################################

SRC_DIR = src

CLIENT_SRC = client.c client_utils.c
SERVER_SRC = server.c server_utils.c

CLIENT_OBJ_DIR = obj/client
SERVER_OBJ_DIR = obj/server

CLIENT_OBJ = $(addprefix $(CLIENT_OBJ_DIR)/, $(CLIENT_SRC:.c=.o))
SERVER_OBJ = $(addprefix $(SERVER_OBJ_DIR)/, $(SERVER_SRC:.c=.o))



SRC_DIR_BONUS = src_bonus

CLIENT_BONUS_SRC = client_bonus.c client_utils_bonus.c
SERVER_BONUS_SRC = server_bonus.c server_utils_bonus.c

CLIENT_BONUS_OBJ_DIR = obj_bonus/client
SERVER_BONUS_OBJ_DIR = obj_bonus/server

CLIENT_BONUS_OBJ = $(addprefix $(CLIENT_BONUS_OBJ_DIR)/, $(CLIENT_BONUS_SRC:.c=.o))
SERVER_BONUS_OBJ = $(addprefix $(SERVER_BONUS_OBJ_DIR)/, $(SERVER_BONUS_SRC:.c=.o))

#############################################################################################
#############################################################################################
#####                                   variables                                       #####
#############################################################################################
#############################################################################################

CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
HEADERS = inc/minitalk.h
INCLUDES = -I inc -I $(LIBFT_DIR)/inc
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#############################################################################################
#############################################################################################
#####                                    commands                                       #####
#############################################################################################
#############################################################################################

all: libft $(CLIENT) $(SERVER)

$(CLIENT_OBJ_DIR):
	@mkdir -p $(CLIENT_OBJ_DIR)

$(SERVER_OBJ_DIR):
	@mkdir -p $(SERVER_OBJ_DIR)

$(CLIENT_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(CLIENT_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(SERVER_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L $(LIBFT_DIR) -lft -o $(CLIENT)

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -L $(LIBFT_DIR) -lft -o $(SERVER)



bonus: libft $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS_OBJ_DIR):
	@mkdir -p $(CLIENT_BONUS_OBJ_DIR)

$(SERVER_BONUS_OBJ_DIR):
	@mkdir -p $(SERVER_BONUS_OBJ_DIR)

$(CLIENT_BONUS_OBJ_DIR)/%.o: $(SRC_DIR_BONUS)/%.c $(HEADERS) | $(CLIENT_BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER_BONUS_OBJ_DIR)/%.o: $(SRC_DIR_BONUS)/%.c $(HEADERS) | $(SERVER_BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) -L $(LIBFT_DIR) -lft -o $(CLIENT_BONUS)

$(SERVER_BONUS): $(SERVER_BONUS_OBJ)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) -L $(LIBFT_DIR) -lft -o $(SERVER_BONUS)



libft:
	@$(MAKE) -C $(LIBFT_DIR)



clean:
	@rm -rf $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR) $(CLIENT_BONUS_OBJ_DIR) $(SERVER_BONUS_OBJ_DIR)
	@rm -rf obj obj_bonus
	@$(MAKE) -C $(LIBFT_DIR) clean



fclean: clean
	@rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean



re: fclean all

.PHONY: all clean fclean re bonus libft