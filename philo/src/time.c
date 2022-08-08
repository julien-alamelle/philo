#include <sys/time.h>

int	ft_get_time(int init)
{
	static struct timeval	start;
	struct timeval			curr;

	if (init)
	{
		gettimeofday(&start, 0);
		return (0);
	}
	gettimeofday(&curr, 0);
	return ((curr.tv_sec - start.tv_sec) * 1000
		+ (curr.tv_usec - curr.tv_usec) / 1000);
}
