#include <ncurses.h>

int main()
{
	initscr();
	cbreak();
	printw("Hello There!");
	move(12,13);
	printw("Here");
	attron(A_STANDOUT);
	mvprintw(15,20, "Now here");
	attroff(A_STANDOUT);
	WINDOW *win;
	win = newwin(64, 64, 0, 0);
	refresh();
	box(win, 0, 0);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_MAGENTA);
	attron(COLOR_PAIR(1));
	mvwprintw(win, 1, 1, "Colored text");
	attroff(COLOR_PAIR(1));
	wrefresh(win);

	getch();
	endwin();
	return (0);
}