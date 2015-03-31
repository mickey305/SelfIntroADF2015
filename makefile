CC = gcc
RM = rm
CFLAGS = -c -Wall
NCURSESW = -lncursesw
CS = main.c share/rank_module.c share/set_color.c select/select.c help/help.c rank/rank.c game/game.c game/init_game.c game/run_status.c game/print_package.c game/add_rank.c game/transXY_point.c
OBJS = main.o share/rank_module.o share/set_color.o select/select.o help/help.o rank/rank.o game/game.o game/init_game.o game/run_status.o game/print_package.o game/add_rank.o game/transXY_point.o
TARGET = minesweeper
#
# create(link) executable binary file (default)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(NCURSESW)
# create(compile) object files
main.o: main.c main.h
	$(CC) $(CFLAGS) main.c
rank_module.o: share/rank_module.c main.h
	$(CC) $(CFLAGS) share/rank_module.c
set_color.o: share/set_color.c main.h
	$(CC) $(CFLAGS) share/set_color.c
select.o: select/select.c main.h
	$(CC) $(CFLAGS) select/select.c
help.o: help/help.c main.h
	$(CC) $(CFLAGS) help/help.c
rank.o: rank/rank.c main.h
	$(CC) $(CFLAGS) rank/rank.c
game.o: game/game.c main.h
	$(CC) $(CFLAGS) game/game.c
init_game.o: game/init_game.c main.h
	$(CC) $(CFLAGS) game/init_game.c
add_rank.o: game/add_rank.c main.h
	$(CC) $(CFLAGS) game/add_rank.c
print_package.o: game/print_package.c main.h
	$(CC) $(CFLAGS) game/print_package.c
run_status.o: game/run_status.c main.h
	$(CC) $(CFLAGS) game/run_status.c
transXY_point.o: game/transXY_point.o main.h
	$(CC) $(CFLAGS) game/transXY_point.c
# remove files
rm:
	$(RM) -f $(OBJS) $(TARGET)
rm-target:
	$(RM) -f $(TARGET)
rm-obj:
	$(RM) -f $(OBJS)
# build(compile the project and remove central files)
build: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(NCURSESW)
	$(RM) -f $(OBJS)
#delelte trash dir and file
#実行は慎重に！！
delete-samples:
	$(RM) -fr sample/ logs/
# sample text
# sample text 2
# sample text 3

