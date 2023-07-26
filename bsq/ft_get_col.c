
int ft_get_col(char **map)
{
    int j;

    j = 0;
    while(map[1][j] != '\0')
    {
        j++;
    }
    return (j + 1);
}