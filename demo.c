#include <stdio.h>

int main() {
	char buffer[512];
	write(1, "A", 1);
	printf("Hello\n");
	write(1, "B", 1);
	fgets(buffer, sizeof buffer, stdin);
	write(1, "C", 1);
	printf("You wrote: %s\n", buffer);
	write(1, "D", 1);
	printf("Goodbye");
	write(1, "E", 1);
	fgets(buffer, sizeof buffer, stdin);
	write(1, "F", 1);
	printf("You wrote: %s\n", buffer);
	write(1, "G", 1);
}
