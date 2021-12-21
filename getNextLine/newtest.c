/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:12:11 by mmakinen          #+#    #+#             */
/*   Updated: 2021/12/21 14:21:49 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(void)
{
	int		fd;
	char	*line;
	char	filename[] = "monkeybusiness.txt"
	int		read;

	fd = open(filename,"w+");
	write(fd, "abcdefghijklmnop\n", 17);
    write(fd, "qrstuvwxyzabcdef\n", 17);
    write(fd, "ghijklmnopqrstuv\n", 17);
    write(fd, "wxyzabcdefghijkl\n", 17);
    write(fd, "mnopqrstuvwxyzab\n", 17);
    write(fd, "cdefghijklmnopqr\n", 17);
    write(fd, "stuvwxzabcdefghi\n", 17);
}
