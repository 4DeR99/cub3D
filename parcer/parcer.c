#include "../cub3d.h"

char *map_read(int fd)
{
    if(fd < 0)
        return(NULL);
    char line[1000000] = "";
    char buf[2] = "";
    int i = 0;
    int n = 0;
    while((n = read(fd,buf,1)) > 0)
    {
        buf[n] = '\0';
        line[i] = buf[0];
        if(buf[0] == '\n')
        {
            line[i + 1] = '\0';
            return(ft_strdup(line));
        }
        i++;
    }
    if(n < 0)
        return(NULL);
    line[i] = '\0';
    if(line[0] == '\0')
        return(NULL);
    return(ft_strdup(line));
}
void    ft_make_matrix(int fd,t_item *map_items)
{
	char	*str;
	char	*temp;
    int     M = 0;
    int     W = 0;
    int     C = 0;
    char    *map = NULL;
    char    *walls = NULL;
    char    *colors = NULL;

	str = map_read(fd);
	while (str)
	{
        if(is_color(str) == 1 && M == 0)
        {
            if(C < 2)
            {
		        if (!colors)
			    	colors = ft_strdup(str);
		        else
		        {
			    	temp = colors;
			    	colors = ft_strjoin(colors, str);
			    	free(temp);
		    	}
        	}
			else
			{
				printf("Error:\n Duplicated color row.\n");
                free(map);
                free(walls);
                free(colors);
                free(str);
				exit(1);
			}
			C++;
		}
        else if(is_wall(str) == 1 && M == 0)
        {
			if(W < 4)
			{
		    	if (!walls)
				    walls = ft_strdup(str);
		    	else
		    	{
				    temp = walls;
				    walls = ft_strjoin(walls, str);
				    free(temp);
		    	}
        	}
			else
			{
				printf("Error:\n Duplicated walls.\n");
                free(map);
                free(walls);
                free(colors);
                free(str);
				exit(1);
			}
			W++;
		}
        else if(M == 1 || is_line(str) == 1)
        {
            M = 1;
            if(str[0] == '\n' || is_empty(str) == 1)
            {
                printf("Error:\n Empty line\n");
                exit(0);
            }
             if (!map)
			    map = ft_strdup(str);
		    else
		    {
			    temp = map;
			    map = ft_strjoin(map, str);
			    free(temp);
		    }
        }
		free(str);
		str = map_read(fd);
	}
    if(map == NULL)
    {
        printf("Error\n");
        exit(1);
    }
    map_items->map = ft_split(map,'\n');
    if(take_color(map_items,colors) == 3)
    {
        free(map);
        free(colors);
        free(walls);
        free_str(map_items->map);
        exit(1);
    }
    take_walls(map_items,walls);
    free(map);
    free(colors);
    free(walls);
}

t_item    *parser(void)
{
    t_item *item;

	item = (t_item*)calloc(1, sizeof(t_item));
    int fd = open("map",O_RDONLY);
    ft_make_matrix(fd,item);
    map_parser(item);
	return (item);
}