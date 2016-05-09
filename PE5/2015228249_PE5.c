
#include <stdio.h>
#include <signal.h>

main()
{
	void f(int);
	int i;
	signal( SIGINT, f );
	for(i=0; i<5; ++i) {
		printf("hello\n");
		sleep(1);
	}
}

void f(int signum)
{
	printf("Interrupted! OK to quit (y/n)?");
	while(1)
	{
		switch( getchar() )
		{
			case 'y':
			case 'Y':
				exit(1);
				return;
			case 'n':
			case 'N':
				return;
		}
	}
}
