/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarkul <fmarkul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:12:23 by fmarkul           #+#    #+#             */
/*   Updated: 2025/06/13 18:52:47 by fmarkul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_process_format(char specifier, va_list args, int *count)
{
	if (specifier == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (specifier == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (specifier == 'p')
		ft_putpointer(va_arg(args, void *), count);
	else if (specifier == 'd' || specifier == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (specifier == 'u')
		ft_putunsigned(va_arg(args, unsigned int), count);
	else if (specifier == 'x' || specifier == 'X')
		ft_puthex(va_arg(args, unsigned int), specifier, count);
	else if (specifier == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format)
		return (0);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			ft_process_format(format[++i], args, &count);
		else
			ft_putchar(format[i], &count);
		i++;
	}
	va_end(args);
	return (count);
}
