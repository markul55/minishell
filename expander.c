/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkozlows <wiktor292929@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:56:40 by wkozlows          #+#    #+#             */
/*   Updated: 2025/09/27 17:56:40 by wkozlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_var(char *c)
{
    int i;

    i = 1;
    if (ft_isalpha((unsigned char)c[0]) || c[0] == '_')
    while (c[i])
        if (ft_isalpha((unsigned char)c[i]) || c[i] == '_' || (c[i] > 47 && c[i] < 58))
            {
                i++;
            }
        else
            return (-1);
    return (1);
}