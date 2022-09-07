#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void sig_chld(int n)
{
	printf("I got SIGCHLD\n");
}

int main()
{
	pid_t	pid;
	pid_t	mypid;
	int	status;

	if ((pid = fork()) < 0)
	{
		printf("fork error\n");
		exit(1);
	}	
	else if (pid == 0)
	{
		mypid = getpid();
		printf("child pid = %d\n", mypid);
	}
	else
	{
		if (signal(SIGCHLD, sig_chld) == SIG_ERR)
			printf("signal error");
		mypid = getpid();
		printf("parent pid = %d\n", mypid);
		waitpid(pid, &status, 0);
	}
	exit(0);
}
