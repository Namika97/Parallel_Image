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
		void img_seg(int *labels, unsigned char *data, int wid, int hgt, int nthreads)
{
	int maxN = std::max(wid,hgt);
	int phases = (int) ceil(log(maxN)/log(2)) + 1;
	
  	for(int p = 0; p <= phases; p++)
	{
	    
		bool correction = true;
   
		#pragma omp parallel for num_threads(nthreads) //to find neighbors with better labels
	 	for (int i = hgt - 1; i >= 0; i--) 
	 	{
	      	for (int j = wid - 1; j >= 0; j--) 
	      	{
				int idx = i*wid + j;
				int idx3 = idx*pixel_wid;

				if (labels[idx] == 0)
				  continue;
				  
				int ll = labels[idx]; // save previous label

				//Next, we make comparisons for labels in each of the eight direction listed

				//west
				if (j != 0 && abs((int)data[(i*wid + j - 1)*pixel_wid] - (int)data[idx3]) < thres)
				  labels[idx] = std::max(labels[idx], labels[i*wid + j - 1]);

				//east
				if (j != wid-1 && abs((int)data[(i*wid + j + 1)*pixel_wid] - (int)data[idx3]) < thresh)
				  labels[idx] = std::max(labels[idx], labels[i*wid + j + 1]);
				
				//south 
				if(i != height-1 && abs((int)data[((i+1)*wid + j)*pixel_wid] - (int)data[idx3]) < thresh)
				  labels[idx] = std::max(labels[idx], labels[(i+1)*wid + j]);

				//north 
				if(i != 0 && abs((int)data[((i-1)*wid + j)*pixel_wid] - (int)data[idx3]) < Threshold)
				  labels[idx] = std::max(labels[idx], labels[(i-1)*wid + j]);

				//south east
				if(i != hgt-1 && j != wid-1 && abs((int)data[((i+1)*wid + j + 1)*pixel_wid] - (int)data[idx3]) < thresh)
				  labels[idx] = std::max(labels[idx], labels[(i+1) * wid + j + 1]);

				//north east
				if(i != 0 && j != wid-1 && abs((int)data[((i-1)*wid + j + 1)*pixel_wid] - (int)data[idx3]) < thresh)
				  labels[idx] = std::max(labels[idx], labels[(i-1) * wid + j + 1]);

				//south west 
				if(i != hgt-1 && j!= 0 && abs((int)data[((i+1)*wid + j - 1)*pixel_wid] - (int)data[idx3]) < thresh)
				  labels[idx] = std::max(labels[idx], labels[(i+1) * wid + j - 1]);

				//north west
				if(i != 0 && j != 0 && abs((int)data[((i-1)*wid + j - 1)*pixel_wid] - (int)data[idx3]) < Threshold)
				  labels[idx] = std::max(labels[idx], labels[(i-1) * wid + j - 1]);

				if (ll < labels[idx]) {
				  labels[ll - 1] = std::max(labels[idx],labels[ll - 1]);	
				  correction = false;	  
				} // this condition is to check if the previously found labels were better than the labels recently found
	      	}
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
