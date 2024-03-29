#include <iostream>
#include <stdint.h>

using namespace std;

void Op(int64_t c[],int64_t low,int64_t high){
	int64_t n = high - low + 1;
	if(n <= 1) return;												//base case

	int64_t n_two = n/3;
	int64_t n_one = n/3;
	int64_t n_zero = n/3;

	if(n%3 == 1) n_zero += 1;
	if(n%3 == 2) {n_zero +=1;n_one+=1;}
	// int64_t two[n_two],one[n_one],zero[n_one];
	int64_t *two = (int64_t*)calloc(n_two , sizeof(int64_t));
	int64_t *one = (int64_t*)calloc(n_one , sizeof(int64_t));
	int64_t *zero = (int64_t*)calloc(n_zero , sizeof(int64_t));
	for (int64_t i = low; i <= high; i++){							//store respective elements in arrays
		if((i-low)%3 == 0)
			zero[(i-low)/3] = c[i];
		else if((i-low)%3 == 1)
			one[(i-low)/3] = c[i];
		else if((i-low)%3 == 2)
			two[(i-low)/3] = c[i];
	}
																	//combining arrays in required order
	for (int64_t i = low; i <= high; i++){
		if((i-low) < n_two)
			c[i] = two[i-low];
		if((i-low) < n_one)
			c[i+n_two] = one[i-low];
		if((i-low) < n_zero)
			c[i+n_two+n_one] = zero[i-low];
	}

	free(two);
	free(one);
	free(zero);														//free memory of array
	Op(c,low+0,low+n_two-1);										//recursive calls of Op for 3 parts of c
	Op(c,low+n_two,low+n_one+n_two-1);
	Op(c,low+n_one+n_two,low+n_zero+n_one+n_two-1);
}

int main() {
	int64_t arraySize;
	cin>>arraySize;														//take Size of array as input 
	int64_t c[arraySize],b[arraySize+1];
	for (int64_t i = 0;i < arraySize;i++){
		cin>>c[i];
	}
	int64_t querySize;
	cin>>querySize;
	int64_t queries[4][querySize];
	Op(c,0,arraySize-1);												//Required operation on array
	for (int64_t i = 0;i < querySize;i++){
		cin>>queries[0][i]>>queries[1][i]>>queries[2][i]>>queries[3][i];
	}
																		//maintaining a auxiliary array for queries
	b[0] = 0;
	for(int64_t i = 0; i < arraySize;i++){
		b[i+1] = b[i] + c[i];
	}

	for (int64_t i = 0; i < querySize; i++)
	{
		cout<<b[queries[1][i]+1] - b[queries[0][i]]<<endl;				//returns sum of ck where i<=k<=j
	}
	
    return 0;
}