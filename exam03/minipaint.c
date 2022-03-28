#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct caracs
{
	int		width;
	int		height;
	char	bg;
}				t_caracs;

typedef struct circles
{
	char	c;
	float	y;
	float 	x;
	float 	radius;
	char	draw;
}				t_circles;

char		**g_map;
t_caracs	carac;
t_circles 	*circles;

int	str_error(char *err, int ret)
{
	while (*err)
		write(1, err++, 1);
	return (ret);
}

void	free_all(int map)
{
	free(circles);
	if (map)
	{
		for (int i = 0; g_map[i]; i++)
			free(g_map[i]);
		free(g_map);
	}
}

char	char_selection(int x, int y)
{
	char	c;
	float 	range;

	c = carac.bg;
	for (int i = 0; circles[i].draw; i++)
	{
		range = sqrtf(powf(x - circles[i].x, 2.) + powf(y - circles[i].y, 2.));
		if (range <= circles[i].radius)
		{
			if (circles[i].c == 'C')
				c = circles[i].draw;
			else if (circles[i].radius - range < 1.000)
				c = circles[i].draw;
		}
	}
	return (c);
}

void 	draw_me_a_circle()
{
	g_map = calloc(carac.width + 1, sizeof(char *));
	for (int j = 0; j < carac.width; j++)
		g_map[j] = calloc(carac.height + 1, sizeof(char));



	for (int x = 0; x < carac.width; x++)
	{
		for (int y = 0; y < carac.height; y ++)
			g_map[x][y] = char_selection(x, y);
	}
	for (int i = 0; g_map[i]; i++)
	{
		for (int j = 0; g_map[i][j]; j++)
			write(1, &g_map[i][j], 1);
		write(1, "\n", 1);
	}
}

int	data_init(FILE *file)
{
	int	ret;
	int	turn;

	fscanf(file, "%d %d %c\n", &carac.height, &carac.width, &carac.bg);
	turn = 0;
	circles = calloc(2, sizeof(t_circles));
	while ((ret = fscanf(file, "%c %f %f %f %c\n", &circles[turn].c, &circles[turn].y, &circles[turn].x, &circles[turn].radius, &circles[turn].draw)) == 5)
	{
//		printf("%c %f %f %f %c\n", circles[turn].c, circles[turn].y, circles[turn].x, circles[turn].radius, circles[turn].draw);
		circles = realloc(circles, (turn + 2) * sizeof(t_circles));
		memset(&circles[turn + 1], 0, sizeof(t_circles));
		turn++;
	}
	if ((carac.width <= 0 && carac.width > 300) || (carac.height <= 0 && carac.height > 300))
		return (0);
	if (ret != EOF)
		return (0);
	for (int i = 0; i < turn; i++)
	{
		if (circles[i].c != 'c' && circles[i].c != 'C')
			return (0);
		if (circles[i].radius <= 0)
			return (0);
		if (!circles[i].draw)
			return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	FILE *file;

	if (argc < 2)
		return (str_error("Error: argument\n", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n", 1));
	if (!data_init(file))
	{
		fclose(file);
		free_all(0);
		return (str_error("Error: Operation file corrupted\n", 1));
	}
	fclose(file);
	draw_me_a_circle();
	free_all(1);
	return (0);
}
