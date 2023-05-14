SOURCES = ./main.c \
			./utils/signal.c \
			./utils/garbage_collector.c \

BONUS_FILES = \


HEADER			=	includes/ft_malcolm.h
HEADER_BONUS	=	includes/ft_malcolm_bonus.h

OBJECTS_DIR			=	./build/
OBJECTS        = $(addprefix $(OBJECTS_DIR),$(notdir $(SOURCES:.c=.o)))
OBJECTS_BONUS  = $(addprefix $(OBJECTS_DIR),$(notdir $(BONUS_FILES:.c=.o)))


DEP            = $(OBJECTS:.o=.d)

NAME			=	ft_malcolm

CC				=	gcc
RM				=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

_GREY	=	\e[30m
_RED	=	\e[31m
_GREEN	=	\e[32m
_YELLOW	=	\e[33m
_BLUE	=	\e[34m
_PURPLE	=	\e[35m
_CYAN	=	\e[36m
_WHITE	=	\e[37m

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
%:
    @$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

$(OBJECTS_DIR)%.o: %.c $(HEADER) $(HEADER_BONUS)
				@echo "Compiling $@ ...\t\t\t\c"
				@mkdir -p $(OBJECTS_DIR) 
				$(CC) $(CFLAGS) -MMD -c $< -o $@ >/dev/null
				a.c b.c c.c d.c e.c
				@echo "DONE"

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

-include $(DEP)

bonus:			$(LIBFT) $(OBJECTS_BONUS) $(HEADER_BONUS) fclean
				$(CC) $(CFLAGS) $(OBJECTS) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)


clean:
				@echo "Deleting Objects Directory $(OBJ_DIR) ... \c"
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS_DIR)
				@echo "DONE\n-----"

fclean:			clean
				@echo "Deleting Binary File $(NAME) ... \c"
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
				@echo "DONE\n-----"

re:				fclean all


.PHONY:			all clean fclean re libft bonus