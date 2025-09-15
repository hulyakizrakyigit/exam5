
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct elements
{
	int lines;
	char empty;
	char obstacle;
	char full;
} t_elements;

typedef struct map
{
	char **map;
	int width;
	int height;
	int best;
	int start_i;
	int start_j;
} t_map;


int load_elements(FILE *f, t_elements *elements)
{
	int num = fscanf(f, "%d %c %c %c", &(elements->lines), &(elements->empty), &(elements->obstacle), &(elements->full));
	if (num != 4)
		return -1;

	if (elements->lines < 0)
		return -1;
	if (elements->empty < 32 || elements->empty > 126 || elements->obstacle < 32 || elements->obstacle > 126 || elements->full < 32 || elements->full > 126)
		return -1;
	if (elements->empty == elements->obstacle || elements->empty == elements->full || elements->obstacle == elements->full)
		return -1;
	return 0;
}

int free_map(t_map *map)
{
	if (!map) //sinavda burayi !(map->map) yapmistim ki gereksiz bi satir sanki
		return -1;
	for (int i = 0; map->map[i]; i++)
		free(map->map[i]);
	free(map->map);
	return -1;
}

char *ft_substr(char *s, int start, int end)
{
	if (!s)
		return 0;
	int len = end - start + 1;
	char *res = malloc(sizeof(char) * len);
	res[len - 1] = 0;
	int i = 0;
	while (start + i < end)
	{
		res[i] = s[start + i];
		i++;
	}
	return res;
}
int load_map(FILE *f, t_map *map)
{
	map->map = (char**)malloc(sizeof(char *) * (map->height + 1));
	if (!(map->map))
		return -1;
	map->map[map->height] = 0;
	int read;
	size_t len;
	char *line =NULL;
	if (getline(&line, &len, f) == -1)
		return free_map(map);

	for (int i = 0; i < map->height; i++)
	{
		read = getline(&line, &len, f);
		if (read == -1) // sinavda read < 0 yapmistim
			return free_map(map);

		if (read > 0 && line[read - 1] == '\n')
			read -= 1;

		map->map[i] = ft_substr(line, 0, read);
		if (!(map->map[i]))
		{
			free(line);
			return free_map(map);
		}

		if (i == 0)
			map->width = read;
		else if (map->width != read)
		{
			free(line);
			return free_map(map);
		}
	}
	free(line);
	return 0;
}

int check_map(t_map *map, char c1, char c2)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->map[i][j] != c1 && map->map[i][j] != c2)
				return -1;
		}
	}
	return 0;
}

int min(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return a;
}
void find_square(t_map *map, t_elements *elements)
{
	int matrix[map->height][map->width];
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			matrix[i][j] = 0;
			if ((i == 0 || j == 0) && map->map[i][j] == elements->empty)
				matrix[i][j] = 1;

		}
	}
	map->best = 0;
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (i > 0 && j > 0 && map->map[i][j] == elements->empty)
				matrix[i][j] = min(matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]) + 1;

			if (matrix[i][j] > map->best)
			{
				map->best = matrix[i][j];
				map->start_i = i - matrix[i][j] + 1;
				map->start_j = j - matrix[i][j] + 1;
			}
		}
	}
}

void print_res(t_map *map, t_elements *elements)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j ++)
		{
			if (map->start_i <= i && i < map->start_i + map->best && map->start_j <= j && j < map->start_j + map->best)
				fprintf(stdout, "%c", elements->full);
			else
				fprintf(stdout, "%c", map->map[i][j]);
		}
		fprintf(stdout, "\n");
	}
}

int execute(FILE *f)
{
	t_elements elements;
	if (load_elements(f, &elements) == -1)
		return -1;

	t_map map;
	map.height = elements.lines;

	if (load_map(f, &map) == -1)
		return -1;

	if (check_map(&map, elements.empty, elements.obstacle) == -1)
		return free_map(&map);

	find_square(&map, &elements);
	print_res(&map, &elements);
	free_map(&map);
	return 0;
	}


int open_execute(char *s)
{
	FILE *file = fopen(s, "r");
	if (!file)
		return -1;
	int res = execute(file);
	fclose(file);
	return res;
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (execute(stdin) == -1)
			fprintf(stdout, "Error: invalid map\n");
	}
	else if (argc == 2)
	{
		if (open_execute(argv[1]) == -1)
			fprintf(stdout, "Error: invalid map\n");
	}
	return 0;
}