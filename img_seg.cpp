#include<stdio.h>
#include "std_image.h"
#include<sys/time.h>
#include<omp.h>

using namespace std;

static const double k = 1.0e-6;
double getTime()
{
	struct timeval tval;
	struct timezone tzone;

	const int RC = gettimeofday(&tval, &tzone);
	if(RC==-1)
	{
	return(-1);
	}
	else
	return (((double)tval.tval_sec + k * ((double)tval.tval_usec));

}

int main(int argc,char **argv)
{
	int width,height;
	int pixelWidth;
	int Threshold = 3;
	int numThreads = 4;
	int seed =1 ;
	const char *filename = "input.png";
	const char *outputname = "output.png";
  	for(int ac=1;ac<argc;ac++)
	{
	    if(MATCH("-s")) {Threshold = atoi(argv[++ac]);}
	    else if(MATCH("-t")) {numThreads = atoi(argv[++ac]);}
	    else if(MATCH("-i"))  {filename = argv[++ac];}
	    else if(MATCH("-o"))  {outputname = argv[++ac];}
	    else {
	      printf("Usage: %s [-i < filename>] [-s <threshold>] [-t <numThreads>] [-o outputfilename]\n",argv[0]);
	      return(-1);
	    }
	}
  return 0;
  }
