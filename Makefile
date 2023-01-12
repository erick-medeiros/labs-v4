CFLAGS = -Wall -Wextra -Werror -Iinclude
RM = rm -fr

SRC = shared_memory.c
SRC += build_tree.c

SRC_ENCODER = $(SRC)
SRC_ENCODER += encoder/main.c

SRC_DECODER = $(SRC)
SRC_DECODER += decoder/main.c

OBJ_ENCODER = $(addprefix obj/, $(SRC_ENCODER:.c=.o))
OBJ_DECODER = $(addprefix obj/, $(SRC_DECODER:.c=.o))

REQUIRED_DIRS = $(sort $(dir obj/ $(OBJ_ENCODER) $(OBJ_DECODER)))

all: encoder decoder

$(REQUIRED_DIRS):
	@mkdir -p $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

encoder: $(REQUIRED_DIRS) $(OBJ_ENCODER)
	$(CC) $(CFLAGS) $(OBJ_ENCODER) -o encoder

decoder: $(REQUIRED_DIRS) $(OBJ_DECODER)
	$(CC) $(CFLAGS) $(OBJ_DECODER) -o decoder

clean:
	$(RM) ./obj/

fclean: clean
	$(RM) ./encoder ./decoder

re: fclean all

install:
	sudo apt install clang-format bear

.PHONY: all clean fclean re