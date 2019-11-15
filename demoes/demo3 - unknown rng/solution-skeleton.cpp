#include <stdio.h>
#include <math.h>

void my_srand(int seed) {
  /* TODO: srand? */
}

unsigned int my_rand() {
  /* TODO: rand? */
  return 0;
}

int main(int argc, char *argv[]) {
	my_srand(0); /* TODO: Seed? */

	for(int i = 0; i < 16; i++) {
		printf("%02x", my_rand());
	}
	printf("\n");
}
