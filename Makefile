CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes
SRC_DIRS = src llibtf
OBJS_DIR = build
SRCS = $(shell find $(SRC_DIRS) -name "*.c")
OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

.PHONY: all clean fclean re
all: pipex

pipex: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f pipex

re: fclean all
