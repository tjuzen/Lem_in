# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 16:28:36 by tjuzen            #+#    #+#              #
#    Updated: 2020/01/20 13:27:48 by tjuzen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
FLAGS = -Wall -Wextra -Werror -Wunused
LIBFT = $(LIBDIR)libft.a
SRCDIR = ./src/
OBJDIR = ./obj/
LIBDIR = ./libft/
INCL = ./includes/

FILES = $(shell find src -type f | grep -E "\.c$$" | sed 's/src//g')
SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(addprefix $(OBJDIR), $(FILES:.c=.o))
SRCSUBDIR = $(shell find ./src -type d)
OBJSUBDIR = $(SRCSUBDIR:./src%=./obj%)
LONGEST = $(shell echo $(notdir $(SRC)) | tr " " "\n" | \
	awk ' { if ( lenght > x ) { x = lenght; y = $$0 } }END{ print y }' | wc -c )

C_CYAN = \033[96m
C_GREEN = \033[32m
C_RED = \033[32m
C_MAG = \033[1;35m
C_RESET = \033[1;39

all: lib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCL)
	@printf "$(C_MAG)Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $<
	@printf "  $(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"
	@printf "\r"

lib:
	@make -C $(LIBDIR)
	@echo "$(C_CYAN)Libft compilation           [$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"

$(OBJSUBDIR):
	@mkdir $@

$(NAME): $(OBJSUBDIR) $(OBJ)
	@echo "$(C_CYAN)lem-in OBJ creation         [$(C_GREEN)✔$(C_CYAN)] $(C_RESET)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo "$(C_CYAN)lem-in OBJ compilation      [$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(C_CYAN)Deleting lem-in OBJ         [$(C_GREEN)✔$(C_CYAN)]"
	@make -C $(LIBDIR) clean
	@echo "$(C_CYAN)Deleting Libft OBJ          [$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(C_CYAN)Deleting lem-in             [$(C_GREEN)✔$(C_CYAN)]"
	@rm -rf $(LIBFT)
	@echo "$(C_CYAN)Deleting libft.a            [$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"

re: fclean all

norm:
	@norminette $(./src/) $(INCL)

.PHONY: norm clean fclean re all
