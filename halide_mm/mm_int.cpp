#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdint.h>

//HALIDE
#include "HalideBuffer.h"
#include "mm.h"

#include "halide_mm.h"

using Halide::Runtime::Buffer;

int main(void)
{
	uint8_t* ma = (uint8_t*)malloc(sizeof(uint8_t)*TEST_K*TEST_M);
	uint8_t* mb = (uint8_t*)malloc(sizeof(uint8_t)*TEST_N*TEST_K);
	uint32_t* mc = (uint32_t*)malloc(sizeof(uint32_t)*TEST_N*TEST_M);
	uint32_t* chk = (uint32_t*)malloc(sizeof(uint32_t)*TEST_N*TEST_M);

	for(int y = 0; y < TEST_M; y++){
		for(int x = 0; x < TEST_K; x++){
			ma[y*TEST_K + x] = (uint8_t)(rand()%256);
		}
	}
	for(int y = 0; y < TEST_K; y++){
		for(int x = 0; x < TEST_N; x++){
			mb[y*TEST_N + x] = (uint8_t)(rand()%256);
		}
	}
	for(int y = 0; y < TEST_M; y++){
		for(int x = 0; x < TEST_N; x++){
			mc[y*TEST_N + x] = 0;
			chk[y*TEST_N + x] = 0;
		}
	}

	struct timeval stime, etime;
	gettimeofday(&stime, NULL);
	{
		Buffer<uint8_t> ma_buf(ma, TEST_K, TEST_M);
		Buffer<uint8_t> mb_buf(mb, TEST_N, TEST_K);
		Buffer<uint32_t> mc_buf(mc, TEST_N, TEST_M);
		halide_mm(ma_buf, mb_buf, TEST_K, mc_buf);
	}
	gettimeofday(&etime, NULL);
	printf("Halide MM: %ld us\n", (etime.tv_sec - stime.tv_sec)*1000000 + (etime.tv_usec - stime.tv_usec));

	gettimeofday(&stime, NULL);
	for(int m = 0; m < TEST_M; m++){
		for(int n = 0; n < TEST_N; n++){
			float val = 0.0;
			for(int k = 0; k < TEST_K; k++){
				val += ma[m*TEST_K + k]*mb[k*TEST_N+n];
			}
			chk[m*TEST_N + n] = val;
		}
	}
	gettimeofday(&etime, NULL);
	printf("NAIVE: %ld us\n", (etime.tv_sec - stime.tv_sec)*1000000 + (etime.tv_usec - stime.tv_usec));

	for(int m = 0; m < TEST_M; m++){
		for(int n = 0; n < TEST_N; n++){
			int val = chk[m*TEST_N + n] - mc[m*TEST_N + n];
			if( val ){
				printf("(%d,%d), %u %u\n", m, n, chk[m*TEST_N + n], mc[m*TEST_N + n]);
			}
		}
	}

	free(ma);
	free(mb);
	free(mc);
	free(chk);
	printf("DONE!\n");
	return 0;
}
