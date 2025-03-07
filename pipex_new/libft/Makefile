# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 20:46:13 by jmehmy            #+#    #+#              #
#    Updated: 2025/03/06 11:08:17 by jmehmy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


files 	   = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c ft_strlcpy.c free_string.c\

b_list	= ft_lstnew.c ft_lstadd_front.c \
				ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c \
				
NAME 		= libft.a

Compiler	= cc

CmpFlags	= -Wall -Wextra -Werror

C_FILES	= $(files)
B_FILES  = $(b_list)
RM		= rm -f
LIB_C	= ar -rcs
O_FILES	= $(C_FILES:.c=.o)
BONUS = $(B_FILES:.c=.o)

$(NAME): $(O_FILES)
	$(LIB_C) $(NAME) $(O_FILES)

bonus: $(BONUS)
	$(LIB_C) $(NAME) $(C_FILES) $(BONUS)

$(O_FILES): $(C_FILES)
			$(Compiler) $(CmpFlags) -c $(C_FILES) -I./

$(BONUS): $(B_FILES)
			$(Compiler) $(CmpFlags) -c $(B_FILES) -I./

all: $(NAME)

clean:
	$(RM) $(O_FILES) $(BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
