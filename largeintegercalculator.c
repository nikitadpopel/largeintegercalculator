/* Large Integer Calculator
Fall 2018
Mikita Popel */
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXDIGITS 101 // cell 0 is sign bit: 0 = positive, 1 = negative
//#define EXTRACREDIT // uncomment this line to test extra functionality (subtract/multiplication)

// This function reads in the input integer as an array of shorts
int readInt(short num[]){
	char a[MAXDIGITS*2];
	int i, size = 0;

	scanf("%s", &a);
	if(a[0] == '-'){
		for(i = 1; a[i] != '\0'; i++){
			size++;
		}
		if(size > 100){
			printf("\nError - the number exceeds 100 digits\n");
			exit(0);
		}
		num[0] = 1;
		for(i = 1; i <= size; i++){
			num[i] = a[size + 1 - i] - 48;
		}
		for(i = size + 1; i < MAXDIGITS; i++){
			num[i] = -1;
		}
	}
	else{
		for(i = 0; a[i] !='\0'; i++){
			size++;
		}
		if(size > 100){
			printf("\nError - the number exceeds 100 digits\n");
			exit(0);
		}
		num[0] = 0;
		for(i = 1; i < MAXDIGITS; i++){
			num[i] = a[size - i] - 48;
		}
		for(i = size + 1; i < MAXDIGITS; i++){
			num[i] = -1;
		}
	}
	return size;
}

// This function writes in a new array of shorts for the answer to a problem
void writeInt(const short num[]){
	int i;
	int size = 0;
	for(i = 1; num[i] != -1; i++){
		size++;
	}
	if(num[0] == 1){
		printf("-");
		for(i = size;i > 0; i--){
			printf("%d", num[i]); 
		}
	}
	else{
		for(i = size; i > 0; i--){
			printf("%d", num[i]); 
		}
	}
	return;
}
int len(const short num[]){
	int i, size = 0;
	for(i = 1; num[i] != -1; i++){
		size++;
	}
	return size;
}

// This function calculates the sum of two arrays of shorts
void addInt(const short num1[], const short num2[], short num3[]){
	int tempnum, i, addone = 0, endofnums, endofnumsfound = 0, lastdigitaddone = 0, subtractone = 0;
	int num1v2[MAXDIGITS], num2v2[MAXDIGITS];
	for(i = 0; i < MAXDIGITS; i++){
		num1v2[i] = num1[i];
		if(num1v2[i] == -1){
		num1v2[i] = 0;	
		}
	}
	for(i = 0; i < MAXDIGITS; i++){
		num2v2[i] = num2[i];
		if(num2v2[i] == -1){
		num2v2[i] = 0;	
		}
	}
	for(i = 1; i < MAXDIGITS; i++){
		if((num1[i] == -1) && (num2[i] == -1) && endofnumsfound == 0){
			endofnums = i;
			endofnumsfound = 1;
		}
	}
	if((num1[0] == 0) && (num2[0] == 0)){
		for(i = 1; i < endofnums + 1; i++){
			tempnum = num1v2[i] + num2v2[i] + addone;
			addone = 0;
			if(tempnum > 9){
				tempnum = tempnum % 10;
				addone = 1;
				if(i == endofnums-1){
					lastdigitaddone++;
				}
				if(i == 101){
					printf("Error - added number more than 100 digits\n");
					exit(0);
				}
			}
			num3[i] = tempnum;
		}
		for(i = endofnums; i < MAXDIGITS; i++){
				num3[i+lastdigitaddone] = -1;
		}
	}
	if((num1[0] == 1) && (num2[0] == 1)){
		for(i = 1; i < endofnums + 1; i++){
			tempnum = num1v2[i] + num2v2[i] + addone;
			addone = 0;
			if(tempnum > 9){
				tempnum = tempnum % 10;
				addone = 1;
				if(i == endofnums - 1){
					lastdigitaddone++;
				}
			}
			num3[i] = tempnum;
		}
		for(i = endofnums + lastdigitaddone; i < MAXDIGITS; i++){
				num3[i] = -1;
		}
		num3[0] = 1;
	}
	if((num1[0] == 0) && (num2[0] == 1)){
		for(i = 1; i < endofnums; i++){
			tempnum = num1v2[i] - num2v2[i] - subtractone;
			subtractone = 0;
			if(tempnum < 0){
				tempnum = 10 + tempnum;
				subtractone = 1;
			}
			num3[i] = tempnum;
		}
		if(num3[endofnums-1] == 0){
			num3[endofnums-1] = -1;
		}
		for(i = endofnums; i < MAXDIGITS; i++){
			num3[i] = -1;
		}
	}
	if((num1[0] == 1) && (num2[0] == 0)){
		for(i = 1; i < endofnums; i++){
			tempnum = num2v2[i] - num1v2[i] - subtractone;
			subtractone = 0;
			if(tempnum < 0){
				tempnum = 10 + tempnum;
				subtractone = 1;
			}
			num3[i] = tempnum;
		}
		if(num3[endofnums-1] == 0){
			num3[endofnums-1] = -1;
		}
		for(i = endofnums; i < MAXDIGITS; i++){
			num3[i] = -1;
		}
	}
	return;
}

//These functions definied below are extra functions that I got to work that allow the user to do subtraction and multiplication
#ifdef EXTRA

//This function allows you to subtract two arrays of shorts and store it in another array of shorts
void subInt(const short num1[], const short num2[], short num3[]){
	int tempnum, i, addone = 0, endofnums, endofnumsfound = 0, subtractone = 0;
	int num1v2[MAXDIGITS], num2v2[MAXDIGITS];
	for(i = 0; i < MAXDIGITS; i++){
		num1v2[i] = num1[i];
		if(num1v2[i] == -1){
		num1v2[i] = 0;	
		}
	}
	for(i = 0; i < MAXDIGITS; i++){
		num2v2[i] = num2[i];
		if(num2v2[i] == -1){
		num2v2[i] = 0;	
		}
	}
	for(i = 1; i < MAXDIGITS; i++){
		if((num1[i] == -1) && (num2[i] == -1) && endofnumsfound == 0){
			endofnums = i;
			endofnumsfound = 1;
		}
	}
	for(i = 1; i < endofnums; i++){
		tempnum = num1v2[i] - num2v2[i] - subtractone;
		subtractone = 0;
		if(tempnum < 0){
			tempnum = 10 + tempnum;
			subtractone = 1;
		}
		num3[i] = tempnum;
	}
	if(num3[endofnums-1] == 0){
		num3[endofnums-1] = -1;
		
	}
	for(i = endofnums; i < MAXDIGITS; i++){
		num3[i] = -1;
	}
	return;
}

// This function allows you to calculate the product of two arrays of shorts
void mulInt(const short num1[], const short num2[], short num3[]){
	int tempnum, i, j, k, add = 0, endofnums, endofnumsfound = 0;
	int num1v2[MAXDIGITS], num2v2[MAXDIGITS], temp[MAXDIGITS + 1];
	for(i = 0; i < MAXDIGITS; i++){
		num1v2[i] = num1[i];
		if(num1v2[i] == -1){
		num1v2[i] = 0;	
		}
	}
	for(i = 0; i < MAXDIGITS; i++){
		num2v2[i] = num2[i];
		if(num2v2[i] == -1){
		num2v2[i] = 0;	
		}
	}
	for(i = 1; i < MAXDIGITS; i++){
		if((num1[i] == -1) && (num2[i] == -1) && endofnumsfound == 0){
			endofnums = i;
			endofnumsfound = 1;
		}
	}
	for(i = 0; i < MAXDIGITS + 1; i++){
		num3[i] = 0;
	}
	for(i = 1; i < len(num2) + len(num1); i++){
		for(k = 0; k < MAXDIGITS + 1; k++){
			temp[k] = 0;
		}
		for(j = 1; j < len(num1) + len(num2); j++){
			
			tempnum = (num1v2[j] * num2v2[i]) + add;
			add = 0;
			if(tempnum > 9){
				add = tempnum / 10;
				tempnum = tempnum % 10;
			}
			temp[j] = tempnum;
		}
		for(j = 1; j < MAXDIGITS; j++){
			num3[i + j - 1] = temp[j] + num3[j + i - 1];
			printf("%d ", num3[j]);
		}
	}
	return;
}

#endif

// This function below returns whether or not the first value inputted is smaller than the second
bool lessThan(const short num1[], const short num2[]){
	int i, length1, length2;
	bool less;
	length1 = len(num1);
	length2 = len(num2);
	if((num1[0] == 0) && (num2[0] == 0)){
		if(length1 < length2){
			less = 1;
			return less;
		}
		else if(length1 > length2){
			less = 0;
			return less;
		}
		else{
			for(i = length1; i > 0; i--){
				if(num1[i] < num2[i]){
					less = 1;
					return less;
				}
				if(num1[i] > num2[i]){
					less = 0;
					return less;
				}
			}
			if(i == 0){
			less = 0;
			return less;
			}
		}
	}
	else if((num1[0] == 1) && (num2[0] == 1)){
		if(length1 < length2){
			less = 0;
			return less;
		}
		else if(length1 > length2){
			less = 1;
			return less;
		}
		else{
			for(i = length1; i > 0; i--){
				if(num1[i] < num2[i]){
					less = 0;
					return less;
				}
				if(num1[i] > num2[i]){
					less = 1;
					return less;
				}
			}
			if(i == 0){
				less = 0;
				return less;
			}
		}
	}
	else if((num1[0] == 0) && (num2[0] == 1)){
		less = 0;
		return less;
	}
	else if((num1[0] == 1) && (num2[0] == 0)){
		less = 1;
		return less;
	}
}

// This function returns whether or not the first value inputed is larger than the second value inputted
bool greaterThan(const short num1[], const short num2[]){
	int i, length1, length2;
	bool greater;
	length1 = len(num1);
	length2 = len(num2);
	if((num1[0] == 0) && (num2[0] == 0)){
		if(length1 < length2){
			greater = 0;
			return greater;
		}
		else if(length1 > length2){
			greater = 1;
			return greater;
		}
		else{
			for(i = length1; i > 0; i--){
				if(num1[i] < num2[i]){
					greater = 0;
					return greater;
				}
				if(num1[i] > num2[i]){
					greater = 1;
					return greater;
				}
			}
			if(i == 0){
			greater = 0;
			return greater;
			}
		}
	}
	else if((num1[0] == 1) && (num2[0] == 1)){
		if(length1 < length2){
			greater = 1;
			return greater;
		}
		else if(length1 > length2){
			greater = 0;
			return greater;
		}
		else{
			for(i = length1; i > 0; i--){
				if(num1[i] < num2[i]){
					greater = 1;
					return greater;
				}
				if(num1[i] > num2[i]){
					greater = 0;
					return greater;
				}
			}
			if(i == 0){
				greater = 0;
				return greater;
			}
		}
	}
	else if((num1[0] == 0) && (num2[0] == 1)){
		greater = 1;
		return greater;
	}
	else if((num1[0] == 1) && (num2[0] == 0)){
		greater = 0;
		return greater;
	}
}

// This function checks whether ot not the two inputed values are equivalent
bool equal(const short num1[], const short num2[]){
	int i, length1, length2;
	bool equal = 1;
	length1 = len(num1);
	length2 = len(num2);
	if((num1[0] == 0) && (num2[0] == 0)){
		if(length1 == length2){
			for(i = length1; i > 0; i--){
				if(num1[i] != num2[i]){
					equal = 0;
					return equal;
				}
			}
			if(i == 0){
			equal = 1;
			return equal;	
			}
		}
		else{
		equal = 0;	
		return equal;
		}
	}
	else if((num1[0] == 1) && (num2[0] == 1)){
		if(length1 == length2){
			for(i = length1; i > 0; i--){
				if(num1[i] != num2[i]){
					equal = 0;
					return equal;
				}
			}
			if(i == 0){
			equal = 1;
			return equal;	
			}
		}
		else{
		equal = 0;	
		return equal;
		}
	}
	else{
	equal = 0;
	return equal;
	}
}
