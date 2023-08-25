CC:=gcc
FLAGS:=-Wall -Werror -pedantic -Iheap/ -I./ 
SRC:= ./huffman_driver.c
NAME:=huffman

all:
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	find -type f -executable -delete
