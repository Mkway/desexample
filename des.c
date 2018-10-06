#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void des(int ,char *,char *); 
void fun(int ,int *,int *);
void mkey(int *);

int IP[64]={58,50,42,34,26,18,10,2,
	    60,52,44,36,28,20,12,4,
	    62,54,46,38,30,22,14,6,
	    64,56,48,40,32,24,16,8,
	    57,49,41,33,25,17,9,1,
	    59,51,43,35,27,19,11,3,
	    61,53,45,37,29,21,13,5,
	    63,55,47,39,31,23,15,7};

int IPI[64]={40,8,48,16,56,24,64,32,
	     39,7,47,15,55,23,63,31,
	     38,6,46,14,54,22,62,30,
	     37,5,45,13,53,21,61,29,
	     36,4,44,12,52,20,60,28,
	     35,3,43,11,51,19,59,27,
	     34,2,42,10,50,18,58,26,
	     33,1,41,9,49,17,57,25};	

int E[48]={32,1,2,3,4,5,
	   4,5,6,7,8,9,
	   8,9,10,11,12,13,
	   12,13,14,15,16,17,
	   16,17,18,19,20,21,
	   20,21,22,23,24,25,
	   24,25,26,27,28,29,
	   28,29,30,31,32,1};

int P[32]={16,7,20,21,29,12,28,17,
	   1,15,23,26,5,18,31,10,
	   2,8,24,14,32,27,3,9,
	   19,13,30,6,22,11,4,25};
	
int SBOX[8][4][16]={{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
	   	     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

		    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
		     
		    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

		    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

		    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

		    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

		    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

		    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

int PC_1[56]={57,49,41,33,25,17,9,
	      1,58,50,42,34,26,18,
	      10,2,59,51,43,35,27,
	      19,11,3,60,52,44,36,
	      63,55,47,39,31,23,15,
	      7,62,54,46,38,30,22,
	      14,6,61,53,45,37,29,
	      21,13,5,28,20,12,4};			 

int PC_2[48]={14,17,11,24,1,5,3,28,
	      15,6,21,10,23,19,12,4,
	      26,8,16,7,27,20,13,2,
	      41,52,31,37,47,55,30,40,
              51,45,33,48,44,49,39,56,
	      34,53,46,42,50,36,29,32};

int subkey[16][48];
char End[8];

void main(){
	char* plaintext[8], key[8];
	printf("평문을 입력하세요 :");
	scanf("%s",plaintext);
	printf("키를 입력하세요 : ");
	scanf("%s",key);

	des(1,plaintext,key);
//printf("\n%s",End);


}

void des(int type,char *plaintext,char *key){
	char ptemp[8]={0};			// plaintext temp
	char De[8]={0};				// Decryption result 
	int i,j ;					 // repeat variable 
	int btemp[64]={0}; 			// bit temp
	int temp[64]={0} ;			 // end temp 
	int ktemp[64]={0} ;			// key temp
	int IP_A[64]={0}; 			// ip array
	int L[32]={0},R[32]={0};	// Left array , right array
	int Lk[28]={0},Rk[28]={0}; 	// Left key array , right key array
	int PCkey[56]; 				// permuted choie key
	int intemp=1,chtemp=0; 		// int temp , chartemp 
	

	strcpy(ptemp,plaintext); 					// plaintext input 
	printf("input plantext :  %s\n",ptemp);	
//	printf("\n***********Char2BINARY***********\n");
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
		btemp[(8*i)+j]=ptemp[i]&0x01; 			// plain text -> binary
		ptemp[i]=ptemp[i] >>1;
//		printf("%d",btemp[(8*i)+j]);
		}
//		printf("\n");
	}
//	printf("\n***********Char2BINARY***********\n");
	
	strcpy(ptemp,key);
	printf("input key :   %s",ptemp);	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
		ktemp[(8*i)+j]=ptemp[i]&0x01;
		ptemp[i]=ptemp[i] >>1;
		}
	}
	
	// Initial permutation	
	for(i=0;i<64;i++){
		IP_A[i]=btemp[IP[i]-1];
	}
	
	// 32bit 
	for(i=0;i<32;i++){
		L[i]=IP_A[i];
		R[i]=IP_A[i+32];
	}
		
	for(i=0;i<56;i++){
		PCkey[i]=ktemp[PC_1[i]-1];	
	}

	mkey(PCkey); 				// function  make subkey
	
	for(i=0;i<16;i++){
		fun(i,L,R);				// des Function  encryption 
	}

	for(i=0;i<64;i++){
		if(i<32){	
		btemp[i]=R[i];
		}
		else{
		btemp[i]=L[i-32];
		}	
	}

	for(i=0;i<64;i++){
		temp[i]=btemp[IPI[i]-1];
	}
	printf("\n**************ENCRYPTION**************\n");
	for(i=0;i<8;i++){					// binary 2 character 
		for(j=0;j<8;j++){
			chtemp+=temp[(i*8)+j]*intemp;
			intemp*=2;
			}
			End[i]=chtemp;
			chtemp=0;
			intemp=1;
		printf("%c",End[i]);
	}
	
	
	printf("\n**************ENCRYTION***************\n");
	//decryption 

	for(i=0;i<64;i++){
		IP_A[i]=temp[IP[i]-1];
	}
	
	for(i=0;i<32;i++){
		L[i]=IP_A[i];
		R[i]=IP_A[i+32];
	}
	
	for(i=0;i<16;i++){
		fun((15-i),L,R);				// decryption function 
	}

	for(i=0;i<64;i++){
		if(i<32){	
		btemp[i]=R[i];
		}
		else{
		btemp[i]=L[i-32];
		}	
	}

	for(i=0;i<64;i++){
	temp[i]=btemp[IPI[i]-1];
	}
	chtemp=0;
	printf("\n**************DECRYPTTION**************\n");
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			chtemp+=temp[(i*8)+j]*intemp;
			intemp*=2;
			}
			De[i]=chtemp;
			chtemp=0;
			intemp=1;
		printf("%c",De[i]);
	}
	
	printf("\n**************DECRYPTTION**************\n");
}

void fun(int num,int *L,int *R){
	int EP[48]; 						// expansion permutation
	int XOR[48];						// xor 
	int i,j;
	int SboxRow=0,SboxCol=0,SboxR=0;	 // sbox row col Result
	int SboxArr[32]={0};				//sbox array
	int EndF[32]={0,};					//end function
	int Result[32]={0,};				// last result

	
	//expansion
	for(i=0;i<48;i++){
		EP[i]=R[E[i]-1];
	}
	for(j=0;j<48;j++){
		XOR[j]=EP[j]^subkey[num][j];
	}
	for(i=0,j=0;i<8;i++,j++){
		SboxRow=(XOR[i*6]*2)+XOR[(i*6)+5];
		SboxCol=(XOR[(i*6)+1]*8)+(XOR[(i*6)+2]*4)+(XOR[(i*6)+3]*2)+XOR[(i*6)+4];
		SboxR=SBOX[i][SboxRow][SboxCol];
		SboxArr[j*4]=((SboxR&8)? 1:0);
		SboxArr[(j*4)+1]=((SboxR&4)? 1:0);	
		SboxArr[(j*4)+2]=((SboxR&2)? 1:0);	
		SboxArr[(j*4)+3]=((SboxR&1)? 1:0);	
	}
	for(i=0;i<32;i++){
		EndF[i]=SboxArr[P[i]];
	}
	for(i=0;i<32;i++){
		Result[i]=EndF[i]^L[i];	
	}
	for(i=0;i<32;i++){
	L[i]=R[i];									// right in left  
	R[i]=Result[i];								// last result in Right
	}
}

void mkey(int *key){ 							// make sub key
	int i,j,k;
	int temp1,temp2;
	int keysch[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1}; // key schedule

	for(i=0;i<16;i++){
		for(j=0;j<keysch[i];j++){
		temp1=key[0];
		temp2=key[28];
		
			for(k=1;k<28;k++){
			key[k-1]=key[k];
			key[k+27]=key[k+28];
			}
			key[28]=temp1;
			key[56]=temp2;
		}
		for(j=0;j<48;j++){
			subkey[i][j]=key[PC_2[j]-1];
		}
	}
}
