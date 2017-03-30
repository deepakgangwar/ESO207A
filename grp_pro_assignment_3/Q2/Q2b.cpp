#include <iostream>
#include <stdint.h>
// #include <chrono>
using namespace std;

void Query(int64_t i,int64_t j,int64_t l,int64_t r,int64_t B[]){
	int64_t sum = 0;
	int64_t mod = 1E9;
	for (int64_t k = i; k <= j; k++)
	{	
		// cout<<"k: "<<k<<endl;
		if((l <= B[k]) && (B[k] <= r))
			{
				sum = (sum + B[k])%mod;
				// cout<<"sum: "<<sum<<endl;
			}
	}
	sum += 7;
	cout<<sum<<endl;
}

void Op(int64_t c[],int64_t b[],int64_t n){
	int64_t zero[n/3],one[n/3],two[n/3];
	for (int i = 0; i < n; ++i)
	{
		
	}
}

int main() {
	int64_t arraySize;
	cin>>arraySize;
	int64_t c[arraySize],b[arraySize];
	for (int64_t i = 0;i < arraySize;i++){
		c[i] = i;
	}
	int64_t querySize;
	cin>>querySize;
	int64_t queries[4][querySize];
	for (int64_t i = 0;i < querySize;i++){
		cin>>queries[0][i]>>queries[1][i]>>queries[2][i]>>queries[3][i];
		// cout<<queries[0][i]<<queries[1][i]<<queries[2][i]<<queries[3][i];
	}


	for (int64_t i = 0; i < querySize; i++)
	{
		// Op(c,b);
		Query(queries[0][i],queries[1][i],queries[2][i],queries[3][i],c);	
	}

    return 0;
}