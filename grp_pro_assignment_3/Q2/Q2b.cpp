#include <iostream>
#include <stdint.h>
// #include <chrono>
using namespace std;

void Query(int64_t i,int64_t j,int64_t l,int64_t r,int64_t B[]){
	int64_t sum = 0;
	int64_t mod = 1E9;
	mod += 7;
	for (int64_t k = i; k <= j; k++)
	{	
		// cout<<"k: "<<k<<endl;
		if((l <= B[k]) && (B[k] <= r))
			{
				sum = (sum + B[k])%mod;
				// cout<<"sum: "<<sum<<endl;
			}
	}
	// sum += 7;
	cout<<sum<<endl;
}

void Op(int64_t c[],int64_t low,int64_t high,int64_t offset){
	int64_t n = high - low + 1;
	// cout<<"C: ";
	// for (int64_t i = low;i <= high;i++){
	// 	cout<<c[i]<<"\t";
	// }
	// cout<<endl;
	if(n <= 1) return;

	int64_t n_two = n/3;
	int64_t n_one = n/3;
	int64_t n_zero = n/3;

	if(n%3 == 1) n_zero += 1;
	if(n%3 == 2) {n_zero +=1;n_one+=1;}
	int64_t two[n_two],one[n_one],zero[n_one];
	// int64_t *two = (int64_t*)calloc(n_two , sizeof(int64_t));
	// int64_t *one = (int64_t*)calloc(n_one , sizeof(int64_t));
	// int64_t *zero = (int64_t*)calloc(n_zero , sizeof(int64_t));
	// cout<<"low: "<<low<<" high: "<<high<<" offset: "<<offset<<endl;
	// cout<<"two: "<<two<<" one: "<<one<<" zero: "<<zero<<" offset: "<<offset<<endl;
	// cout<<"n_two: "<<n_two<<" n_one: "<<n_one<<" n_zero: "<<n_zero<<" offset: "<<offset<<endl;
	for (int64_t i = low; i <= high; i++){
		if((i-low)%3 == 0)
			{zero[(i-low)/3] = c[i];/*cout<<"zero: "<<zero[(i-low)/3]<<endl;*/}
		else if((i-low)%3 == 1)
			{one[(i-low)/3] = c[i];/*cout<<"one: "<<one[(i-low)/3]<<endl;*/}
		else if((i-low)%3 == 2)
			{two[(i-low)/3] = c[i];/*cout<<"two: "<<two[(i-low)/3]<<endl;*/}
	}
	for (int64_t i = low; i <= high; i++){
		if((i-low) < n_two)
			c[i] = two[i-low];
		if((i-low) < n_one)
			c[i+n_two] = one[i-low];
		if((i-low) < n_zero)
			c[i+n_two+n_one] = zero[i-low];
	}
	// free(two);
	// free(one);
	// free(zero);
	Op(c,offset+0,offset+n_two-1,offset);
	Op(c,offset+n_two,offset+n_one+n_two-1,offset+n_two);
	Op(c,offset+n_one+n_two,offset+n_zero+n_one+n_two-1,offset+n_two+n_one);

	// Op(two,0,n_two-1,0);
	// Op(one,0,n_one-1,0);
	// Op(zero,0,n_zero-1,0);
	// for (int64_t i = low; i <= high; i++){
	// 	if((i-low) < n_two)
	// 		c[i] = two[i-low];
	// 	if((i-low) < n_one)
	// 		c[i+n_two] = one[i-low];
	// 	if((i-low) < n_zero)
	// 		c[i+n_two+n_one] = zero[i-low];
	// }
}

int main() {
	int64_t arraySize;
	cin>>arraySize;
	int64_t c[arraySize];
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

	Op(c,0,arraySize-1,0);
	for (int64_t i = 0;i < arraySize;i++){
		cout<<c[i]<<" ";
	}
	cout<<endl;
	for (int64_t i = 0; i < querySize; i++)
	{
		Query(queries[0][i],queries[1][i],queries[2][i],queries[3][i],c);	
	}

    return 0;
}