# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 13:26:22 by mfischer          #+#    #+#              #
#    Updated: 2019/10/20 23:17:23 by mfischer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		Makefiles/default_vars.mk

CFLAGS += -O3

.PHONY:		install_dep obj clean fclean all GEN_SOURCES test

all: install_dep $(OBJS) $(NAME)

$(OBJS):	| obj

obj:
	@echo "$(_BLUE)Creating object directories...$(_END)"
	@mkdir -p $@ $(SRC_DIR)

obj/%.o: srcs/%.cpp
	@echo "$(_YELLOW)Compiling $(notdir $<)...$(_END)"
	$(CC) $(CFLAGS) $(INC_DIRS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(_BLUE)Linking binary...$(_END)"
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LIBDEP) -o $@ $(CLIBS)
	@echo "$(_GREEN)Done!$(_END)"

ifeq ($(UNAME), Linux)
install_dep:
	@echo "$(_BLUE)Fetching dependencies...$(_END)"
	@sudo apt-get install libsfml-dev
endif

test:	all
	./$(NAME)

clean:
	@echo "$(_YELLOW)Cleaning OBJs...$(_END)"
	rm -rf obj

fclean: clean
	@echo "$(_YELLOW)Deleting executable...$(_END)"
	rm -rf $(NAME)

re: fclean all

GEN_SOURCES:
	@echo "${_BLUE}Generating source list...${_END}"
	@-rm .srcs
	@find . -type f | grep "\.c$$" $(foreach V, $(BLACK_LIST_SRCS), | grep -v "$(V)") | cut -f2- -d/ | grep -v " " | sed "s/$$/ \\\\/" | sed "1s/^       //" | sed "$$ s/..$$//" >> .srcs
	@echo "${_GREEN}Done!${_END}"

