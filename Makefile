NAME = Webserver

CXXFLAGS = -Wall -Wextra -Werror
#-fsanitize=address

CC = c++ 

STD = -std=c++98 

SRC = Location.cpp config.cpp Server.cpp Socket.cpp Client.cpp Webserver.cpp Parser.cpp Request.cpp Response.cpp main.cpp

INC = include.h Location.hpp config.hpp Server.hpp Socket.hpp Client.hpp Webserver.hpp Parser.hpp Request.hpp Response.hpp

#OBJ = $(SRC:.cpp=.o)
OBJ = $(SRC:%.c=obj/%.o)

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(CXXFLAGS) $(STD) $(OBJ) -o $(NAME)
	@mkdir obj

obj%.o : %.cpp $(INC)

	$(CC) $(CXXFLAGS) -c $< -o $@ 

clean :
	rm -rf $(OBJ) 

fclean : clean
	rm -rf obj
	#rm -rf $(NAME)

re : fclean all 

.PHONY : all clean fclean re
