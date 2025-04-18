# 42 Get Next Line

This project is about writing a function in C that reads and returns one line at a time from a file descriptor. It introduces a key concept in C programming — **static variables** — and serves as a solid exercise in memory management.

## Status

- ✅ Validated: 08.11.2024.
- 🎓 Grade: 125/100.
- 💧 Leak-free on [francinette](https://github.com/xicodomingues/francinette) as of November 2024.
- 🚦 Compliant with [42 Norm](#note) rules.

## Usage

`get_next_line` is not a standalone program and should be compiled as part of another project. When called in a loop, it reads the given file descriptor line by line until reaching the end of the file.

##### Example `main.c`:

``` c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

This will read the file `example.txt` line by line and print each line to the console.

##### Compilation:
```
cc main.c get_next_line.c get_next_line_utils.c -o gnl
```

You can also define a custom BUFFER_SIZE at compile time:

```
cc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl
```
##### Execution:
```
./gnl
```

## Bonus:

The bonus part uses linked lists to handle multiple file descriptors in parallel, preserving the reading state of each without mixing up the output.

##### Example `main_bonus.c`:
``` c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (perror("Error opening files"), 1);
	while (true)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break ;
		if (line1)
		{
			printf("file1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("file2: %s", line2);
			free(line2);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
}
```

This will keep reading `file1.txt` and `file2.txt` and print a line from each to the console until it reaches end of both files.

##### Compilation:

The program has to be compiled with the `*_bonus.c` files and an optional `BUFFER_SIZE`:

```
cc -D BUFFER_SIZE=42 main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```
##### Execution:
```
./gnl_bonus
```

### Constraints

<a id="note"></a>

> 🛠️ **Note:**
> 42 project requirements that impact structure and readability:
> - Functions must be no longer than 25 lines.
> - A file may contain a maximum of 5 functions.
> - `for`, `do..while`, `switch`, ternary operators, and VLAs are forbidden.
> - Standard C library functions are not allowed (unless a few specific ones are explicitly permitted for a project).
> - Variables cannot be declared and assigned in the same line.

⚠️ P.S. Don't copy, learn!

Made by: nkhamich@student.codam.nl | LinkedIn: [nkhamichonak](https://www.linkedin.com/in/nkhamichonak/)
