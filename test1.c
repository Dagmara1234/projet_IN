#include <stdio.h>
#include <math.h>
#include <gsl gsl_errno.h>
#include <gsl gsl_fft_complex.h>
#include<complex.h>
#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

int
main (void)
{
  int i;
 double w = 0.1;
 double om = 0.7;
 double Q1 = 1;
 double Q2 = 2.1;
int r = 1;
double D1 = 2.1;
  const int n = 630;
  double data[2*n];
  double c[2*n];
  double complex D; 
  gsl_fft_complex_wavetable * wavetable;
  gsl_fft_complex_workspace * workspace;

  for (i = 0; i < n; i++)
    {
      REAL(data,i) = 0.0;
      IMAG(data,i) = 0.0;
    }

  data[0] = 1.0;

  for (i = 1; i <= 500; i++)
    {
 double t1 = (m-1)*4.14;
 D=pow((cos(om*t1/2)),2)+((2*I*sin(om*t1)/om)*(Q2+pow(om,2)*Q1))-(16*D1*((pow(sin(om*t1/2),2))));
      REAL(data,i) = REAL(data,n-i) = creal(D); //r*cos(w*i);
      IMAG(data,i) = IMAG(data, n-i) = cimag(D); //r*sin(w*i);
    }

  for (i = 0; i < n; i++)
    {
      //printf ("%d: %e %e\n", i, REAL(data,i), 
//                                IMAG(data,i));
    }
  printf ("\n");

  wavetable = gsl_fft_complex_wavetable_alloc (n);
  workspace = gsl_fft_complex_workspace_alloc (n);

  for (i = 0; i < (int) wavetable->nf; i++)
    {
       printf ("# factor %d: %zu\n", i, 
               wavetable->factor[i]);
    }

  gsl_fft_complex_forward (data, 1.5, n, 
                           wavetable, workspace);

  for (i = 0; i < n; i++)
    {
     // printf ("%d: %e %e\n", i, REAL(data,i), 
//                                IMAG(data,i));
 c[i]  = REAL(data,i) + IMAG(data,i);    
printf("%e\n",c[i]);
}

  gsl_fft_complex_wavetable_free (wavetable);
  gsl_fft_complex_workspace_free (workspace);

   FILE *fs = fopen("spe.txt","w");

        for (i = 1; i<630; i++)
        {
        //double t = dx*(i-1);

        fprintf(fs," %d  %f\n", i, data[i]);
        }
        fclose(fs);
}