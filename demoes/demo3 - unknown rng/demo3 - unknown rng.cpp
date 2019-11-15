#include <stdio.h>
#include <math.h>
#include <windows.h>

#define N 351
#define M 175
#define R 19
#define TEMU 11
#define TEMS 7
#define TEMT 15
#define TEML 17

  // long constants cannot be defined as enum in 16-bit compilers:
#define MATRIX_A 0xE4BD75F5
#define TEMB     0x655E5280
#define TEMC     0xFFD58000



static unsigned long mt[N];                 // state vector
static int mti=N;


extern void my_srand(int seed) {
  unsigned long s = (unsigned long)seed;
  for (mti=0; mti<N; mti++) {
    s = s * 29943829 - 1;
    mt[mti] = s;}
  return;}

extern int my_rand() {
  // generate 32 random bits
  unsigned long y;

  if (mti >= N) {
    // generate N words at one time
    const unsigned long LOWER_MASK = (1u << R) - 1; // lower R bits
    const unsigned long UPPER_MASK = -1 << R;       // upper 32-R bits
    int kk, km;
    for (kk=0, km=M; kk < N-1; kk++) {
      y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
      mt[kk] = mt[km] ^ (y >> 1) ^ (-(signed long)(y & 1) & MATRIX_A);
      if (++km >= N) km = 0;}

    y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
    mt[N-1] = mt[M-1] ^ (y >> 1) ^ (-(signed long)(y & 1) & MATRIX_A);
    mti = 0;}

  y = mt[mti++];

  // Tempering (May be omitted):
  y ^=  y >> TEMU;
  y ^= (y << TEMS) & TEMB;
  y ^= (y << TEMT) & TEMC;
  y ^=  y >> TEML;

  return 0x0FF&y;
}

int main(int argc, char *argv[]) {
	int seed = GetTickCount();
	my_srand(seed);

	printf("Seed: %d\n", seed);
	printf("\nGenerated key: ");
	for(int i = 0; i < 16; i++) {
		printf("%02x", my_rand());
	}
	printf("\n");
}
