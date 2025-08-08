/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:21:55 by wkozlows          #+#    #+#             */
/*   Updated: 2025/08/04 01:21:55 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_intro(void)
{
    printf(
 "___ ___ __       __ _______ __          __ __                 ___ ___ _______  \n"
 "|   Y   |__.-----|__|   _   |  |--.-----|  |  |               |   Y   |       |\n"
 "|.      |  |     |  |   1___|     |  -__|  |  |               |   |   |___|   |\n"
 "|. \\_/  |__|__|__|__|____   |__|__|_____|__|__|               |____   |/  ___/ \n"
 "|:  |   |           |:  1   |                                     |:  |:  1  \\ \n"
 "|::.|:. |           |::.. . |                                     |::.|::.. . |\n"
 "`--- ---'           `-------'                                     `---`-------'\n"
 " __                                                                            \n"
 "|  |--.--.--.                                                                  \n"
 "|  _  |  |  |                                                                  \n"
 "|_____|___  |                                                                  \n"
 "  ___ |_____|             __          __                                      _\n"
 ".'  _.--------.---.-.----|  |--.--.--|  |                   .---.-.-----.--|  |\n"
 "|   _|        |  _  |   _|    <|  |  |  |                   |  _  |     |  _  |\n"
 "|__| |__|__|__|___._|__| |__|__|_____|__|                   |___._|__|__|_____|\n"
 "          __                __                                                 \n"
 ".--.--.--|  |--.-----.-----|  .-----.--.--.--.-----.                           \n"
 "|  |  |  |    <|  _  |-- __|  |  _  |  |  |  |__ --|                           \n"
 "|________|__|__|_____|_____|__|_____|________|_____|\n");
}

// char    **get_tokens(char *line)
// {
//     int i;

//     i = 0;
//     while (line)
//     {

//     }
// }

void    ft_pwd(void)
{
    char    path[BUFSIZ];

    if (getcwd(path, sizeof(path)) != NULL)
        printf("%s\n", path);
    else
        printf("pwd error\n");
}
int    skip_spaces(char *text, int i)
{
    while(text[i] && text[i] <= 32)
    {
        i++;
    }
    return(i);
}
void    ft_echo(char *text)
{
    char    *tmp;
    int check_n;
    int i;
    int j;

    i = 0;
    j = 0;
    tmp = 0;
    check_n = 0;
    if (text[0] == 'e' && text[1] == 'c' && text[2] == 'h' && text[3] == 'o')
        {
            i = skip_spaces(text, 4);
            if(text[i] == '-' && text[i + 1] == 'n')
            {
                check_n = 1;
                i = skip_spaces(text, i + 2);
            }
            tmp = malloc(sizeof(char) * (strlen(text) - i + 1));
            while (text[i])
            {
                tmp[j] = text[i];
                j++;
                i++;
            }
            tmp[j] = '\0';
        if(check_n == 0)
            printf("%s\n", tmp);
        else
            printf("%s", tmp);
        free(tmp);
        }
}
