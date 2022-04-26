
#include <unistd.h>

typedef struct s_process
{
	int fds[2];
	const char *path;
	char **argv;
	int argc;
	pid_t pid;
} t_process;

int create_pipes(t_process *plist, int len)
{
	int i;
	int p[2];

	i = 1;
	while (i < len)
	{
		if (pipe(p) < 0)
		{
			return -1;
		}
		plist[i - 1].fds[1] = p[1];
		plist[i].fds[0] = p[0];
		i++;
	}
	return 0;
}


int create_and_run(t_process *plist, int len)
{
	int i;
	int p[2];

	i = 0;
	while (i < (len - 1))
	{
		if (pipe(p) < 0)
		{
			return -1;
		}
		plist[i].fds[1] = p[1];
		plist[i + 1].fds[0] = p[0];

		run_process(plist[i]);

		i++;
	}
	return 0;
}

void wait_processes(t_process *plist, int len)
{
	pour chqaue
		waitpid()
}
