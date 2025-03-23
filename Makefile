#############################################################################################
#############################################################################################
#####                                     sources                                       #####
#############################################################################################
#############################################################################################

SRC_DIR = src

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ_DIR = obj/client
SERVER_OBJ_DIR = obj/server

CLIENT_OBJ = $(addprefix $(CLIENT_OBJ_DIR)/, $(CLIENT_SRC:.c=.o))
SERVER_OBJ = $(addprefix $(SERVER_OBJ_DIR)/, $(SERVER_SRC:.c=.o))

#############################################################################################
#############################################################################################
#####                                   variables                                       #####
#############################################################################################
#############################################################################################

CLIENT = client
SERVER = server
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

all: $(CLIENT) $(SERVER)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(CLIENT_OBJ_DIR):
	@mkdir -p $(CLIENT_OBJ_DIR)

$(SERVER_OBJ_DIR):
	@mkdir -p $(SERVER_OBJ_DIR)

$(CLIENT_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(CLIENT_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(SERVER_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(SERVER_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L $(LIBFT_DIR) -lft -o $(CLIENT)

$(SERVER): $(LIBFT) $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -L $(LIBFT_DIR) -lft -o $(SERVER)

clean:
	@rm -rf $(CLIENT_OBJ_DIR) $(SERVER_OBJ_DIR)
	@rm -rf obj
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(CLIENT) $(SERVER)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re