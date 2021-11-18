#include "ft_printf.h"

static void	ft_dash_zero(const char *format, t_flags *flags, int *count)
{
	while (format[(*count)] == '-' || format[(*count)] == '0')
	{
		if (format[(*count)] == '-')
			flags->dash = 1;
		if (format[(*count)] == '0' && !flags->dash)
		{
			flags->zero_per = 1;
			flags->zero = 1;
		}
		else
			flags->zero = 0;
		(*count)++;
	}
}

static int	ft_len(const char *format, int *count)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(format[(*count)]))
	{
		nbr = nbr * 10 + format[(*count)] - '0';
		(*count)++;
	}
	return (nbr);
}

static void	ft_width(const char *format, va_list ap, t_flags *flags, int *count)
{
	if (format[(*count)] == '*')
	{
		flags->width = va_arg(ap, int);
		if (flags->width < 0)
		{
			flags->dash = 1;
			flags->zero = 0;
			flags->width *= -1;
		}
		(*count)++;
	}
	else
		flags->width = ft_len(format, count);
}

static void	ft_precision(const char *format, va_list ap, t_flags *flags,
		int *count)
{
	while (format[(*count)] == '.')
	{
		flags->dot = 1;
		(*count)++;
	}
	if (format[(*count)] == '*')
	{
		flags->precision = va_arg(ap, int);
		if (flags->precision >= 0)
			flags->zero = 0;
		(*count)++;
	}
	else
	{
		if (ft_isdigit(format[(*count)]))
			flags->zero = 0;
		flags->precision = ft_len(format, count);
	}
}

void	ft_verif_flags(const char *format, va_list ap, t_flags *flags,
		int *count)
{
	if (format[(*count)] == '-' || format[(*count)] == '0')
		ft_dash_zero(format, flags, count);
	ft_width(format, ap, flags, count);
	if (format[(*count)] == '.')
		ft_precision(format, ap, flags, count);
}
