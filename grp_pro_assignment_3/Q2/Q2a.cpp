#include <iostream>
#include <stdint.h>
// #include <chrono>
using namespace std;

void Query(int64_t i,int64_t j,int64_t l,int64_t r,int64_t B[]){
	int64_t sum = 0;
	for (int64_t k = i; k <= j; k++)
	{	
		// cout<<"k: "<<k<<endl;
		if((l <= B[k]) && (B[k] <= r))
			{
				sum = sum + B[k];
				// cout<<"sum: "<<sum<<endl;
			}
	}
	cout<<sum<<endl;
}

void Op(int64_t c[],int64_t b[],int64_t low,int64_t high,int64_t offset){
	int64_t n = high - low + 1;
	cout<<"C: ";
	for (int64_t i = low;i <= high;i++){
		cout<<c[i]<<"\t";
	}
	cout<<endl;
	if (n == 1){
		b[offset] = c[offset];
		return;
	}
	if(n < 1) return;

	int64_t two,n_two = n/3;
	int64_t one,n_one = n/3;
	int64_t zero,n_zero = n/3;

	if(n%3 == 1) n_zero += 1;
	if(n%3 == 2) {n_zero +=1;n_one+=1;}
	two = 0;
	one = two + n_two;
	zero = one + n_one;
	cout<<"low: "<<low<<" high: "<<high<<" offset: "<<offset<<endl;
	cout<<"two: "<<two<<" one: "<<one<<" zero: "<<zero<<" offset: "<<offset<<endl;
	cout<<"n_two: "<<n_two<<" n_one: "<<n_one<<" n_zero: "<<n_zero<<" offset: "<<offset<<endl;
	for (int64_t i = low; i <= high; i++){
		if((i-low)%3 == 0)
			{b[zero + offset] = c[i];zero++;cout<<"b_zero: "<<b[zero+offset-1]<<endl;}
		else if((i-low)%3 == 1)
			{b[one + offset] = c[i];one++;cout<<"b_one: "<<b[one+offset-1]<<endl;}
		else if((i-low)%3 == 2)
			{b[two + offset] = c[i];two++;cout<<"b_two: "<<b[two+offset-1]<<endl;}
	}
	// cout<<"two: "<<two<<" one: "<<one<<" zero: "<<zero<<" offset: "<<offset<<endl;
	// cout<<"n_two: "<<n_two<<" n_one: "<<n_one<<" n_zero: "<<n_zero<<" offset: "<<offset<<endl;
	cout<<"b: ";
	for(int i=0;i<4;i++){
		cout<<b[i]<<"\t";
	}
	cout<<endl;
	Op(b,b,0,two - 1,0);
	Op(b,b,two,one -1,n_two-1);
	Op(b,b,one,zero - 1,n_two+n_one-1);
}

int main() {
	int64_t arraySize;
	cin>>arraySize;
	int64_t c[arraySize],b[arraySize];
	for (int64_t i = 0;i < arraySize;i++){
		cin>>c[i];
	}
	// int64_t querySize;
	// cin>>querySize;
	// int64_t queries[4][querySize];
	// for (int64_t i = 0;i < querySize;i++){
	// 	cin>>queries[0][i]>>queries[1][i]>>queries[2][i]>>queries[3][i];
	// 	// cout<<queries[0][i]<<queries[1][i]<<queries[2][i]<<queries[3][i];
	// }


	// for (int64_t i = 0; i < querySize; i++)
	// {
	// 	Op(c,b,0,arraySize-1,0);
	// 	Query(queries[0][i],queries[1][i],queries[2][i],queries[3][i],c);	
	// }

	Op(c,b,0,arraySize-1,0);
	for (int64_t i = 0;i < arraySize;i++){
		cout<<b[i]<<"\t";
	}
	
    return 0;
}