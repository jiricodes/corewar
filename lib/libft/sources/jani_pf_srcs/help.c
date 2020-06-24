/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:16:18 by jmakela           #+#    #+#             */
/*   Updated: 2020/06/24 13:22:37 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_help2(void)
{
	ft_printf("%%{COLOR} text here %%{EOC} for printing text in color\n");
	ft_printf("%{B_WHITE}%{BLACK}BLACK%{EOC} ");
	ft_printf("%{RED}RED %{GREEN}GREEN %{YELLOW}YELLOW %{EOC}");
	ft_printf("%{BLUE}BLUE %{PURPLE}PURPLE %{EOC}");
	ft_printf("%{CYAN}CYAN %{WHITE}WHITE%{EOC}\n\n");
	ft_printf("%%{B_COLOR} background %%{EOC} for text background color\n");
	ft_printf("%{B_BLACK}B_BLACK%{BLACK}%{B_RED}B_RED%{EOC}");
	ft_printf("%{B_GREEN}B_GREEN%{B_YELLOW}B_YELLOW%{EOC}");
	ft_printf("%{BLACK}%{B_BLUE}B_BLUE%{EOC}");
	ft_printf("%{B_PURPLE}B_PURPLE%{EOC}");
	ft_printf("%{BLACK}%{B_CYAN}B_CYAN%{EOC}");
	ft_printf("%{B_WHITE}%{BLACK}B_WHITE%{EOC}\n\n");
	ft_printf("%%{FORMAT} text here %%{EOC} for bold or underline\n");
	ft_printf("%{BOLD}BOLD%{EOC} %{UNDERLINE}UNDERLINE\n");
}

/*
** Provides help for using ft_printf.
** Insert "%h" as format string to see ft_printf usage.
*/

void		check_help(const char *format)
{
	if (ft_strcmp(format, "%h") == 0)
	{
		ft_printf("\n[Functions]\n\nft_printf(""format string"", ...)\n");
		ft_printf("ft_dprintf(""int fd"", ""format string"", ...)\n");
		ft_printf("ft_sprintf(""char *tr"", ""format string"", ...)\n\n");
		ft_printf("[Conversions]\n\nc\tfor char\n");
		ft_printf("s\tfor string\np\tfor pointer\n");
		ft_printf("d/i/D\tfor integer\nu/U\tfor unsigned integer\n");
		ft_printf("b\tfor unsigned binary integer\n");
		ft_printf("o/O\tfor unsigned octal integer\n");
		ft_printf("x/X\tfor unsigned hexadecimal integer\n");
		ft_printf("f/F\tfor double integer\n\n");
		ft_printf("[Flags ] = #, 0, -, +, space\n[Width ] = 123456789, *\n");
		ft_printf("[Preci ] = .123456789, *\n[Length] = h, hh, ");
		ft_printf("l, ll, j, z, L(for double)\n\n");
		check_help2();
		exit(0);
	}
}
