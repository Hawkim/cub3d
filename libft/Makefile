# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nal-haki <nal-haki@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 22:39:56 by nal-haki          #+#    #+#              #
#    Updated: 2024/09/26 22:40:21 by nal-haki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar -rcs
RM			= rm -rf

SRCS_PATH = ./src/
OBJS_PATH = ./libft_objects/

INCLUDES	= ./include/
SOURCES		= ft_atoi.c ft_bzero.c ft_calloc.c\
			ft_isalnum.c ft_isalpha.c ft_isdigit.c\
			ft_if_eof.c ft_itoa.c ft_memcpy.c ft_split.c\
			ft_strchr.c ft_strdup.c ft_strjoin.c\
			ft_strlcpy.c ft_strlen.c ft_strncmp.c\
			ft_strndup.c ft_strnjoin.c ft_strrchr.c\
			ft_substr.c ft_atol.c ft_long.c ft_space.c\
			ft_putstr_fd.c ft_putchar_fd.c ft_cap_num.c\
			ft_strtrim.c

# Object file creation
OBJECTS		= $(addprefix $(OBJS_PATH), $(notdir $(SOURCES:.c=.o)))

# Default rule for compiling .c files to .o files in the libft_objects directory
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
		mkdir -p $(OBJS_PATH)
		$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

all: 		$(NAME)

$(NAME):	$(OBJECTS)
			$(AR) $(NAME) $(OBJECTS)

clean:
			$(RM) $(OBJS_PATH)/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
