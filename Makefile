NAME = ft_containers

MAIN = main.cpp
TEST = vector.cpp pair.cpp map.cpp
CONT = vector.hpp pair.hpp map.hpp
TREE = Rbtree.hpp

TDIR = tests/
SDIR = containers/
LDIR = log/
RBDIR = rbtree/

TEST_DIR = $(addprefix $(TDIR), $(TEST))
CONT_DIR = $(addprefix $(SDIR), $(CONT))
TREE_DIR = $(addprefix $(RBDIR), $(TREE))

INC = -I./$(SDIR) -I./$(TDIR)
RM	=	rm -rf

MSG1 = @echo "$(GREEN) 🎉 Successfully Compiled ft_container ✔︎ $(DEFAULT)"
MSG2 = @echo "$(GREEN) 🎉 Successfully Compiled ft_containers_stl ✔︎ $(DEFAULT)"
MSG3 = @echo "$(YELLOW)🧹 Cleaned ✔︎ $(DEFAULT)"
MSG4 = @echo "$(YELLOW)🧹 Cleaned Everything fclean ✔︎ $(DEFAULT)"

CXX			=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98 -g

all:	$(NAME) $(NAME)_stl

$(NAME): $(TEST_DIR) $(MAIN) $(CONT_DIR) $(TREE_DIR)
		$(CXX) $(CXXFLAGS) $(INC) $(MAIN) $(TEST_DIR) -o $@ 
		$(MSG1)

$(NAME)_stl: $(TEST_DIR) $(MAIN)
		$(CXX) $(CXXFLAGS) $(INC) $(MAIN) $(TEST_DIR) -D _STL -o $@ 
		$(MSG2) 

exec: all
		mkdir -p $(LDIR)
		./$(NAME) > $(LDIR)ft.log
		./$(NAME)_stl > $(LDIR)stl.log

test:	exec
		diff $(LDIR)ft.log $(LDIR)stl.log; echo ""

leak: $(NAME)
		valgrind --track-origins=yes --leak-check=full -s ./$(NAME) 1> /dev/null

printtree: tests/print_tree.cpp $(CONT_DIR) $(TREE_DIR)
	$(CXX) $(CXXFLAGS) $(INC) tests/print_tree.cpp -o $@

clean:
		@$(RM) $(OBJS)
		@$(RM) $(LDIR)
		$(MSG3)

fclean: clean
		@$(RM) $(NAME)
		@$(RM) $(NAME)_stl
		@$(RM) printtree
		$(MSG4)

re: fclean all

.PHONY: all log logstl test leak clean fclean re

#COLORS
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m