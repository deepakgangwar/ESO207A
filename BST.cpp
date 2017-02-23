#include <bits/stdc++.h>
using namespace std;
// #define N 200005
#define N 50
int TOBALANCE=1; // TOBALANCE is 1 when the condition is Perfectly balanced, 0 otherwise. By changing this constant you can change balance condition.
int NEARLY_BALANCED = 0;
int PERFECTLY_BALANCED = 1;
double BALANCE_RATIO = 0.75; //You may change this ratio.
/* structure of a node of the binary tree.
val: value at the node
size: size of subtree rooted at node
left,right:pointers to right and left sub tree 
*/
struct Node{
  int val;
  int size;
  struct Node *left,*right;  
};
/*
This function takes a value and initialises and returns a new node whose value is set to the given parameter.
*/
Node* init(int val){
  Node *curr = (Node *)malloc(sizeof(Node));
  curr->val=val;
  curr->size=1;
  curr->left=curr->right=NULL;
  return curr;
}
/*
SortedArrayFromBST: This function takes as input a node, pointer to an array, and an integer that denotes the next free position in the array.
This function fills in the array all the values in the tree whose root is the given node i.e. output array finally contains the elements in 
increasing order.
This function must return the number of array positions it has filled. i.e. if initial value of parameter fst = p, then after returning from the function the final value must increase by the size of subtree i.e p+curr->size.
*/
int SortedArrayFromBST(Node *curr, int output[], int fst) {
	if (curr == NULL)
		return fst;
    if(curr -> left)
        fst = SortedArrayFromBST(curr->left , output , fst);
    output[fst++] = curr->val;
    if(curr->right)
        fst = SortedArrayFromBST(curr->right , output , fst);
    return fst;
}

/*
This function creates a BST from an array. It takes as parameters input array and the length of array. It returns the root of the BST
that is formed by the array
*/
Node *BSTFromSortedArray(int input[], int len){
    if(len == 0)
        return NULL;
    Node *root = init ( input[len/2] );
    if (len / 2) {
        // root -> size = 1 + len / 2;
        root -> left = BSTFromSortedArray (input, len / 2);
    }
    if (len - (len / 2) >= 0){
        // root -> size = 1 + len / 2;
        root -> right = BSTFromSortedArray (input + (len / 2) + 1, (len - (len / 2) - 1));
    }

    root->size = len;
    return root;
}
/*
This function recursively deletes all the nodes in the tree whose root in pointed by curr
*/
void deleteNode(Node *curr){
  if(curr==NULL) return;
  deleteNode(curr->left); 
  deleteNode(curr->right);
  delete curr;
}
/*
This function returns true if the current node satisfies the nearly balanced condition and false otherwise
*/
bool checkNearBalance(Node *curr){
    if (!(curr -> left || curr -> right)) return 1;
    else if(!(curr -> left) || !(curr -> right)) return 0; 
    return ((curr->left->size <= BALANCE_RATIO * curr->size)&&(curr->right->size <= BALANCE_RATIO * curr->size));
}
/*
This function returns true if the current node satisfies the perfectly balanced condition and false otherwise
*/
bool checkPerfectBalance(Node *curr){
    if (!(curr -> left || curr -> right)) return 1;
    else if(!(curr -> left) || !(curr -> right)) return 0; 
    else return (abs((curr->left->size - curr->right->size))<=1);
}
/*
This function takes as input a pointer to a node and inserts a node in the subtree of the node depending on the value.
out[] array is used as a helper array which will be used when the BST does not satisfy the balanced condition.
-when the insert returns then the tree must satisfy the balanced condition
*/
void insert(Node *&curr,int val,int out[]){

	Node * root = curr;
	
	while(true)
	{
		if (curr == NULL) {
    	    curr = init(val);
    	    return;
		}
    	
    	++(curr->size);
    	if (val < curr -> val)
    	    {
    	    	if (curr->left)
    	    		curr = curr->left;
    	    	else {	
    	        	curr -> left = init (val);
    	        	break;
    	    	}
    	    }
    	else {
    	    	if (curr->right)
    	    		curr = curr->right;
    	    	else {	
    	        	curr -> right = init (val);
    	        	break;
    	    	}
    	    }
	}
	
	curr = root;

	if (!checkNearBalance (root)) {
		
		int len = SortedArrayFromBST (root , out, 0);
		deleteNode (curr); 
		curr = BSTFromSortedArray(out, len);
		}	
}
/*
This function takes as input a node pointer and a val and searches for a node which has value val in the subtree of node.
It returns true if the value is found, false otherwise.
*/
bool search(Node *curr,int val){
    if (curr -> val == val)
       return 1;
    else if (curr -> val > val && curr -> left)
       search (curr -> left, val);
    else if (curr -> val < val && curr -> right)
       search(curr -> right, val);
    else return 0;
}
void print_array(int out[]){
    for(int i=0;i<N;i++){
        cout<<out[i]<<'\t';
    } 
}

int main(){
  Node *root = NULL;
  int out[N] = {0};
  int queries; scanf("%d",&queries);
  while(queries--){
    int c,val; scanf("%d%d",&c,&val);
    if(c==1){
      //insert
      if(root){
        insert(root,val,out);
      }else{
        root = init(val);
      }
    }else{
      //search query
      if(search(root,val)) printf("Yes\n"); else printf("No\n");
    }
  }
  SortedArrayFromBST(root, out, 0);
  print_array(out);
  return 0;
}