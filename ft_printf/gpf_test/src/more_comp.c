/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atenhune <atenhune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:31:46 by atenhune          #+#    #+#             */
/*   Updated: 2022/04/13 16:06:34 by atenhune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>

int main(void)
{
	int i = 0;
	printf("test%i |%+12d|\n", i++, 42);
	printf("test%i |%+12d|\n", i++, -42);
	printf("test%i |%+12d|\n", i++, 0);
	printf("test%i |%+ 12d|\n", i++, 42);
	printf("test%i |%+ 12d|\n", i++, -42);
	printf("test%i |%+ -12d|\n", i++, 0);
	printf("test%i |%+12d|\n", i++, 42);
	printf("test%i |%+12d|\n", i++, -42);
	printf("test%i |%-+100d|\n", i++, 42);
	printf("test%i |%+12d|\n", i++, 42);
	printf("test%i |%+12d|\n", i++, 42);
	printf("test%i|%+012d|\n", i++, 42);
	printf("test%i |%+012d|\n", i++, -42);
	printf("test%i |%+ 012d|\n", i++, -42);
	printf("test%i |%+0132d|\n", i++, -42);
	printf("test%i|%-0013d|\n", i++, -42);
	printf("test%i |%+012d|\n", i++, -42);
	printf("test%i |%++++0+012d|\n", i++, -42);
	printf("test%i |%++++0+012d|\n", i++, 42);
	printf("test%i |%++++0+072d|\n", i++, 2147483647);
	printf("test%i |%++++0+-012d|\n", i++, 2147483647);
	printf("test%i |%++++0+0122d|\n", i++, 2147483647);
	printf("test%i |%++++0+ 012d|\n", i++, 2147483647);
	printf("test%i |%++++0+032d|\n", i++, -2147483648);
	printf("test%i |%++++0+ 012d|\n", i++, -2147483648);
	printf("test%i |%+ -3d|\n", i++, -2147483648);

	printf("test%i |%+12i|\n", i++, 42);
	printf("test%i |%+12i|\n", i++, -42);
	printf("test%i |%+12i|\n", i++, 0);
	printf("test%i |%+ 12i|\n", i++, 42);
	printf("test%i |%+ 12i|\n", i++, -42);
	printf("test%i |%+ -12i|\n", i++, 0);
	printf("test%i |%+12i|\n", i++, 42);
	printf("test%i |%+12i|\n", i++, -42);
	printf("test%i |%-+100i|\n", i++, 42);
	printf("test%i |%+12i|\n", i++, 42);
	printf("test%i |%+12i|\n", i++, 42);
	printf("test%i|%+012i|\n", i++, 42);
	printf("test%i |%+012i|\n", i++, -42);
	printf("test%i |%+ 012i|\n", i++, -42);
	printf("test%i |%+0132i|\n", i++, -42);
	printf("test%i|%-0013i|\n", i++, -42);
	printf("test%i |%+012i|\n", i++, -42);
	printf("test%i |%++++0+01i|\n", i++, -42);
	printf("test%i |%++++0+012i|\n", i++, 42);
	printf("test%i |%++++0+072i|\n", i++, 2147483647);
	printf("test%i |%++++0+-012i|\n", i++, 2147483647);
	printf("test%i |%++++0+0122i|\n", i++, 2147483647);
	printf("test%i |%++++0+ 012i|\n", i++, 2147483647);
	printf("test%i |%++++0+032i|\n", i++, -2147483648);
	printf("test%i |%++++0+ 012i|\n", i++, -2147483648);
	printf("test%i |%+ -3i|\n", i++, -2147483648);

	printf("test%i |%-12u|\n", i++, 2147483648u);
	printf("test%i |%-12u|\n", i++, 0u);
	printf("test%i |%u|\n", i++, 0u);
	printf("test%i |%32u|\n", i++, 0u);
	printf("test%i |%-12u|\n", i++, 0u);
	printf("test%i |%-12u|\n", i++, 0u);
	printf("test%i |%-12u|\n", i++, -0u);
	printf("test%i |%-12u|\n", i++, -1u);
	printf("test%i |%-012u|\n", i++, 23423u);
	printf("test%i |%02u|\n", i++, 3467u);
	printf("test%i |%000000002u|\n", i++, 3467u);
	printf("test%i |%0000---000---2u|\n", i++, 3467u);
	printf("test%i |%0000---000---2u|\n", i++, 3467u);
	printf("test%i |%0000---000---2u|\n", i++, 3467u);
	printf("test%i |%0-2u|\n", i++, -1u);
	printf("test%i |%0u|\n", i++, -1u);
	printf("test%i |%0-u|\n", i++, -1u);

	printf("test%i |%o|\n", i++, 0);
	printf("test%i |%#o|\n", i++, 0);
	printf("test%i |%12o|\n", i++, 0);
	printf("test%i |%#1o|\n", i++, 0);
	printf("test%i |%#12o|\n", i++, 0);
	printf("test%i |%#-12o|\n", i++, 123456);
	printf("test%i |%#-12o|\n", i++, -123);
	printf("test%i |%#---22o|\n", i++, 432);
	printf("test%i |%#-01o|\n", i++, 0);
	printf("test%i |%#01o|\n", i++, 432);
	printf("test%i |%#-032o|\n", i++, 534234522);

	printf("test%i |%X|\n", i++, 0);
	printf("test%i |%0#122X|\n", i++, 0);
	printf("test%i |%0#122X|\n", i++, 123);
	printf("test%i |%0#1X|\n", i++, 123123);
	printf("test%i |%-0#1X|\n", i++, 1234322);
	printf("test%i |%-0####1X|\n", i++, 1234322);
	printf("test%i |%-0000---####1X|\n", i++, 1234322);
	printf("test%i |%-00-0-0-0-0-0-0#112X|\n", i++, 1234322);
	printf("test%i |%-2X|\n", i++, 14322);
	printf("test%i |%2X|\n", i++, 122);

	printf("test%i |%x|\n", i++, 0);
	printf("test%i |%0#122x|\n", i++, 0);
	printf("test%i |%0#122x|\n", i++, 123);
	printf("test%i |%0#1x|\n", i++, -123123);
	printf("test%i |%-0#1x|\n", i++, 1234322);
	printf("test%i |%-0####1x|\n", i++, 1234322);
	printf("test%i |%-0000---####1x|\n", i++, 1234322);
	printf("test%i |%-00-0-0-0-0-0-0#112x|\n", i++, 1234322);
	printf("test%i |%-2x|\n", i++, 14322);
	printf("test%i |%2x|\n", i++, 122);



}