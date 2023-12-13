#include <stdio.h>
#include <unistd.h>

/**
 * main - Pid Function
 *
 * Return: Always 0.
 */

int main(void)
{
	pid_t ppid;

	ppid = getppid();
	printf("%u\n", ppid);
	return (0);
}
