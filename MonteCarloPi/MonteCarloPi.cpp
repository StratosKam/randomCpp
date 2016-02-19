#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

/**
* MonteCarlo algorithm for pi approximation
*
**/
double difference(double x,double y){
	if(x>y){
		return x-y;
	}else{
		return y-x;
	}
}

long moteCarloPi(double target,double error){
	int totalAttemps=1000000;
	int pairsPerAttempt=1000000;
	int count;
	double estimation;
	double x,y;
	srand(time(NULL));
	for (int i=0;i<totalAttemps;i++){
		count=0;
		for(int j=0;j<pairsPerAttempt;j++){
			x=double(rand())/double(RAND_MAX);
			y=double(rand())/double(RAND_MAX);
			if(pow(x,2)+pow(y,2)<=1){ 
				++count;
			} 
		}
		estimation=double(double(4)*double(count)/double(pairsPerAttempt));
		if(difference(estimation,target)<=error){
			// cout<<estimation<<endl;
			return (i+1)*pairsPerAttempt;
		}
	}
	return -1;
}

int main(){
	// cout.precision(10);
	cout<<moteCarloPi(3.14159,0.5*pow(10,-5))<<endl;
}
