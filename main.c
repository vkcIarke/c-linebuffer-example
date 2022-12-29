#include <stdio.h>
#include <stdlib.h>

#define nil  (void *)(0)
#define pint size_t

char *readline(FILE *f)
{
	int  ch;
	char *ln, *new;
	pint max, sz;

	if (feof(f)) {
		return nil;
	}
	max = 256;
	if ((ln = malloc(max)) == nil) {
		return nil;
	}
	for (sz = 1; (ch = fgetc(f)) != EOF; sz++) {
		if (ch == '\n') {
			break;
		}
		if (ch == '\r') {
			if ((ch = fgetc(f)) != '\n') {
				ungetc(ch, f);
			}
			break;
		}
		if (sz == max) {
			max += max;
			if ((new = realloc(ln, max)) == nil) {
				/* abort */
				free(ln);
				return nil;
			}
			ln = new;
		}
		ln[sz-1] = ch;
	}
	ln[sz-1] = '\0';
	if ((new = realloc(ln, sz)) != nil) {
		ln = new;
	}
	return ln;
}

int main(int argc, char *argv[])
{
	int  i;
	FILE *in;
	char *line;

	if (argc < 2) {
		in = stdin;
	} else if ((in = fopen(argv[1], "rb")) == nil) {
		return -1;
	}
	for (i = 0; (line = readline(in)) != nil; i++) {
		printf("%d:\t%s\n", i, line);
		free(line);
	}
	fclose(in);
}
