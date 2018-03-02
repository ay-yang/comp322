//A1 Part2
//Yue Yang
//Algorithm taken gracefully from Wikipedia

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void bubbleSort(int* p, int length){

	for (int j = 0; j < length; j++){
		for(int i = 1; i < (length - j); i++){
			if((p[i-1]) > p[i]){
				int temp = p[i-1];
				p[i-1] = p[i];
				p[i] = temp;
			}
		}
	}
}


void merge(int* right, int *left, int lengthR, int lengthL, int* p){
	
	int indexR = 0; //keeps track of the index in right array
	int indexL = 0; //keeps track of the index in left array
	int index = 0; //keeps track of index of the pointer

	while(indexR < lengthR && indexL < lengthL){ //case both right and left are non-empty
		if(left[indexL] <= right[indexR]){
			p[index] = left[indexL];
			indexL++;
		}
		else {
			p[index] = right[indexR];
			indexR++;
		}
		index++;
	}

	while(indexL < lengthL){ //case only left is non-empty
		p[index] = left[indexL]; 
		indexL++;
		index++;
	}
	while(indexR < lengthR){ //case only right is non-empty
		p[index] = right[indexR];
		indexR++;
		index++;
	}

}

void mergeSort(int* p, int length){

	int *right;
	int *left;
	
	int half = length/2; //the middle value of the list
	int rightArray[half]; //the right array
	int leftArray[(length-half)]; //the left array
	right = rightArray;
	left = leftArray;
	
	if(length <= 1){
		//done 
	}

	else{
		for (int i=0; i < length; i++){
			if(i < half){
				leftArray[i] = p[i];
			}
			else rightArray[i-half] = p[i];
		}

		//recursive calls
		mergeSort(rightArray, (length-half));
		mergeSort(leftArray, half); 

		merge(right, left, (length-half), half, p);

	}

}

int main(){

	int size = 80;

	int array[size] = {749, 793, 1425, 1074, 327, 1900, 1240, 543, 704, 1126, 504, 900, 353, 4, 1381, 610, 358, 1906, 522, 1351, 951, 1236, 1784, 1534, 1640, 1039, 920, 476, 196, 985, 730, 1089, 1988, 193, 635, 1779, 344, 1994, 640, 425, 838, 1883, 198, 457, 611, 1614, 1729, 51, 1368, 1496, 1008, 530, 829, 1727, 1337, 491, 463, 1919, 783, 1233, 1742, 1005, 1465, 1602, 741, 1392, 1621, 1502, 1474, 1317, 140, 206, 1857, 153, 1916, 1632, 775, 134, 1276, 1953};
	int* p = array;

	std:clock_t start;
	double duration; 
	double duration2;

	start = std::clock(); 

	mergeSort(p, size);
	
 	duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	start = std::clock();

	bubbleSort(p, size);

	duration2 = (std::clock() - start) / (double) CLOCKS_PER_SEC;

	cout << "Size of array: ";
	cout << size; 
	cout << "\n";
	cout << "Time of mergeSort: ";
	cout << duration << "\n";
        cout << "Time of bubbleSort: "; 
	cout << duration2 << "\n";

	//For debugging, feel free to comment the following statements out at your leasure
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}

	return 0;

}
