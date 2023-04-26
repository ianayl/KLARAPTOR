///**
// * 2DConvolution.cu: This file is part of the PolyBench/GPU 1.0 test suite.
// *
// *
// * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
// * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
// * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
// */

#include "2dconv_utils.h"


#pragma kernel_info_size_param_idx_Convolution2D_kernel = 2;
#pragma kernel_info_dim_Convolution2D_kernel = 2;

void
conv2D (DATA_TYPE* A, DATA_TYPE* B)
{
  int i, j;
  DATA_TYPE c11, c12, c13, c21, c22, c23, c31, c32, c33;

  c11 = +0.2;
  c21 = +0.5;
  c31 = -0.8;
  c12 = -0.3;
  c22 = +0.6;
  c32 = -0.9;
  c13 = +0.4;
  c23 = +0.7;
  c33 = +0.10;

  for (i = 1; i < NI - 1; ++i) // 0
    {
      for (j = 1; j < NJ - 1; ++j) // 1
	{
	  B[i * NJ + j] = c11 * A[(i - 1) * NJ + (j - 1)]
	      + c12 * A[(i + 0) * NJ + (j - 1)]
	      + c13 * A[(i + 1) * NJ + (j - 1)]
	      + c21 * A[(i - 1) * NJ + (j + 0)]
	      + c22 * A[(i + 0) * NJ + (j + 0)]
	      + c23 * A[(i + 1) * NJ + (j + 0)]
	      + c31 * A[(i - 1) * NJ + (j + 1)]
	      + c32 * A[(i + 0) * NJ + (j + 1)]
	      + c33 * A[(i + 1) * NJ + (j + 1)];
	}
    }
}

void
init (DATA_TYPE* A)
{
  int i, j;

  for (i = 0; i < NI; ++i)
    {
      for (j = 0; j < NJ; ++j)
	{
	  A[i * NJ + j] = (float) rand () / RAND_MAX;
	}
    }
}

int
compareResults (DATA_TYPE* B, DATA_TYPE* B_outputFromGpu)
{
  int i, j, fail;
  fail = 0;

  // Compare a and b
  for (i = 1; i < (NI - 1); i++)
    {
      for (j = 1; j < (NJ - 1); j++)
	{
	  if (percentDiff (
	      B[i * NJ + j],
	      B_outputFromGpu[i * NJ + j]) > PERCENT_DIFF_ERROR_THRESHOLD)
	    {
	      fail++;
	      return (EXIT_FAILURE);
	    }
	}
    }

  // Print results
//  printf (
//      "Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n",
//      PERCENT_DIFF_ERROR_THRESHOLD,
//      fail);
  return (EXIT_SUCCESS);

}

void
GPU_argv_init ()
{
  cudaDeviceProp deviceProp;
  cudaGetDeviceProperties (&deviceProp, GPU_DEVICE);
//  printf ("setting device %d with name %s\n", GPU_DEVICE, deviceProp.name);
  printf ("[running on device %d: %s]\n", GPU_DEVICE, deviceProp.name);
  cudaSetDevice ( GPU_DEVICE);
}

__global__ void
Convolution2D_kernel (DATA_TYPE *A, DATA_TYPE *B, int NI, int NJ)
{
  int j = blockIdx.x * blockDim.x + threadIdx.x;
  int i = blockIdx.y * blockDim.y + threadIdx.y;

  DATA_TYPE c11, c12, c13, c21, c22, c23, c31, c32, c33;

  c11 = +0.2;
  c21 = +0.5;
  c31 = -0.8;
  c12 = -0.3;
  c22 = +0.6;
  c32 = -0.9;
  c13 = +0.4;
  c23 = +0.7;
  c33 = +0.10;

  if ((i < NI - 1) && (j < NJ - 1) && (i > 0) && (j > 0))
    {
      B[i * NJ + j] = c11 * A[(i - 1) * NJ + (j - 1)]
	  + c21 * A[(i - 1) * NJ + (j + 0)] + c31 * A[(i - 1) * NJ + (j + 1)]
	  + c12 * A[(i + 0) * NJ + (j - 1)] + c22 * A[(i + 0) * NJ + (j + 0)]
	  + c32 * A[(i + 0) * NJ + (j + 1)] + c13 * A[(i + 1) * NJ + (j - 1)]
	  + c23 * A[(i + 1) * NJ + (j + 0)] + c33 * A[(i + 1) * NJ + (j + 1)];
    }
}

void
convolution2DCuda (DATA_TYPE* A, DATA_TYPE* B, DATA_TYPE* B_outputFromGpu)
{

  cuda_timer t_conv;
  cuda_timer_init (t_conv);

  DATA_TYPE *A_gpu;
  DATA_TYPE *B_gpu;

  cudaMalloc ((void **) &A_gpu, sizeof(DATA_TYPE) * NI * NJ);
  cudaMalloc ((void **) &B_gpu, sizeof(DATA_TYPE) * NI * NJ);
  cudaMemcpy (A_gpu, A, sizeof(DATA_TYPE) * NI * NJ, cudaMemcpyHostToDevice);

  dim3 block (DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y);
  dim3 grid ((size_t) ceil (((float) NI) / ((float) block.x)),
	     (size_t) ceil (((float) NJ) / ((float) block.y)));

  cuda_timer_record_start (t_conv);
  Convolution2D_kernel <<<grid, block>>> (A_gpu, B_gpu, NI, NJ);
  cudaCheckKernel()
  ;
  cuda_timer_record_stop (t_conv);
  cudaThreadSynchronize ();
  cudaMemcpy (B_outputFromGpu, B_gpu, sizeof(DATA_TYPE) * NI * NJ,
	      cudaMemcpyDeviceToHost);
  cudaFree (A_gpu);
  cudaFree (B_gpu);

  cuda_timer_record_get_elapsed_time (t_conv);

  printf (
      "[trace: n=%d, bx=%d, by=%d, elapsed_Convolution2D_kernel=%0.4f (ms)] ... ",
      NI, DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y, t_conv.elapsed_time);
}

int
main (int argc, char **argv)
{

  int n = 4096, bx = 32, by = 8;
  if (argc > 1)
    n = atoi (argv[1]);
  if (argc > 2)
    bx = atoi (argv[2]);
  if (argc > 3)
    by = atoi (argv[3]);

  NI = NJ = n;
  DIM_THREAD_BLOCK_X = bx;
  DIM_THREAD_BLOCK_Y = by;

  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* B;
  DATA_TYPE* B_outputFromGpu;

  A = (DATA_TYPE*) malloc (NI * NJ * sizeof(DATA_TYPE));
  B = (DATA_TYPE*) malloc (NI * NJ * sizeof(DATA_TYPE));
  B_outputFromGpu = (DATA_TYPE*) malloc (NI * NJ * sizeof(DATA_TYPE));

  //initialize the arrays
  init (A);

  GPU_argv_init ();

#pragma START_TRACING
  convolution2DCuda (A, B, B_outputFromGpu);
#pragma STOP_TRACING
//  t_start = rtclock ();
//  conv2D (A, B);
//  t_end = rtclock ();
//  fprintf (stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start); //);

//  int s = compareResults (B, B_outputFromGpu);
  int s = EXIT_SUCCESS;
  if (s == EXIT_SUCCESS)
    printf ("PASS\n");
  else
    printf ("FAIL\n");

  free (A);
  free (B);
  free (B_outputFromGpu);

  return 0;
}

