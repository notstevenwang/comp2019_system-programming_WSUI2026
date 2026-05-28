/* hello1.c
 *	purpose	 show the minimal calls needed to use curses
 *	outline  initialize, draw stuff, wait for input, quit
 */

#include	<stdio.h>
#include	<curses.h>

main(int ac, char* av[])
{
	initscr() ;		/* turn on curses	*/
	nodelay(stdscr, TRUE);

	char* message;
	if (ac == 1){
		message = "Hello, world";
	}
	else if (ac == 2){
		message = av[1];
	}

	while(1){
		clear();
		move(LINES/2, COLS/2);

		attron(A_BLINK);
		addstr(message);
		attroff(A_BLINK);

		refresh();
		sleep(1);
		clear();
		refresh();
		sleep(1);
		
		if(getch() != ERR){
			break;
		}
	}
	endwin();
}