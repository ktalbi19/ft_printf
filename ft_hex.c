#include "ft_printf.h"

char	*ft_itoa_pointer(unsigned long int nb, int base)
{
	char				*str;
	unsigned long int	tmp;
	int					len;

	len = 1;
	tmp = nb;
	while (tmp / base > 0)
	{
		tmp = tmp / base;
		len++;
	}
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if (nb % base < 10)
			str[len] = nb % base + '0';
		else
			str[len] = nb % base + 'a' - 10;
		nb = nb / base;
	}
	return (str);
}

void	ft_pre_zero(t_flags *flags, int *zero, int *len_pointer, char *pointer)
{
	if (pointer && flags->precision > (*len_pointer))
		(*zero) = flags->precision - (*len_pointer);
	else
		(*zero) = 0;
	if (pointer && flags->dot && !flags->precision && *pointer == '0')
		(*len_pointer) = 2;
	else
		(*len_pointer) = (*len_pointer) + 2;
}

void	ft_pre_space(t_flags *flags, int *space, int *len_pointer,
		char *pointer)
{
	if (pointer && flags->width > (*len_pointer))
		(*space) = flags->width - (*len_pointer);
	else
		(*space) = 0;
}

void	ft_pointer_hex(t_flags *flags, char *pointer)
{
	int	len_pointer;
	int	space;
	int	zero;
	int	i;

	i = 0;
	len_pointer = ft_strlen(pointer);
	ft_pre_zero(flags, &zero, &len_pointer, pointer);
	ft_pre_space(flags, &space, &len_pointer, pointer);
	flags->ret = flags->ret + len_pointer + space + zero;
	if (!flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	write(1, "0x", 2);
	while (zero-- > 0)
		ft_putchar_fd('0', 1);
	if (len_pointer > 2)
		while (pointer[i])
			ft_putchar_fd(pointer[i++], 1);
	if (flags->dash)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	ft_hex(va_list ap, t_flags *flags)
{
	char	*pointer;

	pointer = ft_itoa_pointer(va_arg(ap, unsigned long int), 16);
	ft_pointer_hex(flags, pointer);
	free(pointer);
}
