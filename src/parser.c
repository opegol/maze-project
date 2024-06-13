#include "maze.h"

/**
 * mapParser - parses file to retrieve 2D map details
 * @filename: path to file conaining map information
 * @map: 2D array of map information to return
 * Return: pointer to 2D array containing map information
 */
//int *mapParser(char *path, int width, int height)
int *mapParser(char *filename, int width, int height)
{
	int *map;
	FILE *fp;
	char buffer[mapWidth * 2];
	char *num;
	int x, y = 0;

	fp = fopen(filename, "r");	
	//fp = fopen(filename, "r");
	if (!fp)
	{
		perror("File could not be opened");
		return (NULL);
	}

	map = (int *)malloc(sizeof(int) * height * width);
	if (map == NULL)
		return (NULL);

	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		if (strlen(buffer) <= 1)
			continue;

		num = strtok(buffer, "\n ");

		x = 0;
		while (num != NULL)
		{
			map[y * width + x] = atoi(num);
			num = strtok(NULL, "\n ");
			x++;
		}
		y++;
	}
	fclose(fp);
	return (map);
}

