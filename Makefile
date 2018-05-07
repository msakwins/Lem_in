# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakwins <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/12 20:05:35 by msakwins          #+#    #+#              #
#    Updated: 2017/10/10 22:20:51 by msakwins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

LIBFTA = libft.a

LIBFTDIR = ./libft
OBJDIR = ./obj/
INCDIR = ./includes
SRCDIR = ./srcs/

SRCS_NAME = lem_in.c \
			parse.c \
			check.c \
			parse_more.c \
			parse_room.c \
			engine.c \
			paths.c \
			display.c \
			utils.c \
			errors.c \
			moving.c \
			moving_utils.c \

OBJS = $(addprefix $(OBJDIR),$(SRCS_NAME:.c=.o))
	LIBFT = $(addprefix $(LIBFTDIR)/,$(LIBFTA))
	PRINTF = $(addprefix $(PRINTFDIR)/,)

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

SRCS = $(addprefix $(SRCDIR),$(SRCS_NAME))

all: $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@gcc $(FLAGS) -I $(INCDIR) -I $(LIBFTDIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFTDIR)

$(NAME): $(LIBFT) obj $(OBJS)
	@gcc $(OBJS) $(LIBFT) -lm -o $(NAME)
	@echo "$(GREEN)---------Lem-in compiled---------$(NC)"

norme:
	@norminette includes srcs

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFTDIR)

fclean:	clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "$(GREEN)----Lem-in removed completely----$(NC)"

re: fclean all
