//A3 
//260694712

#include <iostream>
#include <string>
#include <functional>

typedef  bool (*comparator)(int, int);

using namespace std; 
//Note: Feel free to change size of the arrays if you think it's too long/too short

//Part 1: sort with pointers

//compares two ints to see which one is bigger
bool isGreaterThan(int first, int second){
	if(first > second)
		return true;
	
	return false; 
}

//compares two ints to see which one is smaller
bool isLessThan(int first, int second){
	if(first < second)
		return true; 
	
	return false;
}

//to be used by sortWithPointers, aka merge sort
void merge(int* right, int *left, int lengthR, int lengthL, int* p, comparator compare){
	
	int indexR = 0; //keeps track of the index in right array
	int indexL = 0; //keeps track of the index in left array
	int index = 0; //keeps track of index of the pointer

	while(indexR < lengthR && indexL < lengthL){ //case both right and left are non-empty
		if(compare(right[indexR], left[indexL])){
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

//This is merge sort 
void sortWithPointers(int* p, int length, comparator compare){

	int *right;
	int *left;
	
	int half = length/2; //the middle value of the list
	int rightArray[half]; //the right array
	int leftArray[(length-half)]; //the left array
	right = rightArray;
	left = leftArray;
	
	if(length <= 1){
		//done, nothing to do
	}

	else{
		for (int i=0; i < length; i++){//split array into right and left
			if(i < half){
				leftArray[i] = p[i];
			}
			else rightArray[i-half] = p[i];
		}

		//recursive calls
		sortWithPointers(rightArray, (length-half), compare);
		sortWithPointers(leftArray, half, compare); 

		merge(right, left, (length-half), half, p, compare);

	}

}

void testSortWithPointers(){
	int size = 80;

	int array[size] = {749, 793, 1425, 1074, 327, 1900, 1240, 543, 704, 1126, 504, 900, 353, 4, 1381, 610, 358, 1906, 522, 1351, 951, 1236, 1784, 1534, 1640, 1039, 920, 476, 196, 985, 730, 1089, 1988, 193, 635, 1779, 344, 1994, 640, 425, 838, 1883, 198, 457, 611, 1614, 1729, 51, 1368, 1496, 1008, 530, 829, 1727, 1337, 491, 463, 1919, 783, 1233, 1742, 1005, 1465, 1602, 741, 1392, 1621, 1502, 1474, 1317, 140, 206, 1857, 153, 1916, 1632, 775, 134, 1276, 1953};
	int* p = array;
	
	sortWithPointers(p, size, isGreaterThan);
	
	cout <<"Sort with Pointers \n";
	
	cout << "Sorting in increasing order: \n";
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	
	cout << "\n";
	
	sortWithPointers(p, size, isLessThan);
	
	cout << "Sorting in decreasing order: \n"; 
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	
	cout << "\n" << endl;

}
//End of Part1 sortWithPointers--------------------------------------------------------------------------

//Part2 : Sort with Interfaces

//The abstract class
class IComparer{
	public: 
		virtual bool isBefore(int, int) = 0;
};

//Test to see if first is smaller to second
class LessThanComparer : public IComparer{
	public: 
		bool isBefore(int first, int second){
			if(first < second)
				return true;
			return false;
		}
};

//Test to see if first is greater than second
class GreaterThanComparer: public IComparer{
	public: 
		bool isBefore(int first, int second){
			if(first > second)
				return true;
			return false;
		}
};

class isClosestToComparer: public IComparer{
	private:
		int center;
	
	public: 
	
		//test to see if first is closer to center than second
		bool isBefore(int first, int second){
			int firstCenter = first-this->center;
			if(firstCenter < 0) //takes absolute value of firstCenter
				firstCenter = -firstCenter; 
				
			int secondCenter = second-this->center;
			if(secondCenter < 0) //takes absolute value of secondCenter
				secondCenter = -secondCenter;
			
			if(firstCenter < secondCenter)
				return true;
			
			return false;
		}
		
		isClosestToComparer(int cent){
			this->center = cent;
		}
};

//BubbleSort, and sticking with it so the length of my code doesn't discourage you =) 
void sortWithInterfaces(int* p, int length, IComparer* compare){

	for (int j = 0; j < length; j++){
		for(int i = 1; i < (length - j); i++){
			if(compare->isBefore(p[i],p[i-1])){
				int temp = p[i-1];
				p[i-1] = p[i];
				p[i] = temp;
			}
		}
	}
}

void testSortWithInterfaces(){
	int size = 80;

	int array[size] = {749, 793, 1425, 1074, 327, 1900, 1240, 543, 704, 1126, 504, 900, 353, 4, 1381, 610, 358, 1906, 522, 1351, 951, 1236, 1784, 1534, 1640, 1039, 920, 476, 196, 985, 730, 1089, 1988, 193, 635, 1779, 344, 1994, 640, 425, 838, 1883, 198, 457, 611, 1614, 1729, 51, 1368, 1496, 1008, 530, 829, 1727, 1337, 491, 463, 1919, 783, 1233, 1742, 1005, 1465, 1602, 741, 1392, 1621, 1502, 1474, 1317, 140, 206, 1857, 153, 1916, 1632, 775, 134, 1276, 1953};
	int* p = array;
	int center = 500; //feel free to change this value 
	
	cout << "Sorting with Interfaces: \n";
	cout << "Sorting in increasing order: \n";
	sortWithInterfaces(p, size, new LessThanComparer());
	
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	cout << "\n";
	
	p = array;
	
	cout << "Sorting in decreasing order: \n";
	sortWithInterfaces(p, size, new GreaterThanComparer());
		
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	
	cout << "\n";
	
	cout << "Sorting depending on distance from center: " << center<< "\n";
	
	sortWithInterfaces(p, size, new isClosestToComparer(center));
	
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	
	cout << "\n" << endl;
}

//End of Part2--------------------------------------------------------------------------------------------------

//Part 3: With Lambda Expressions

void sortWithStandardFunction(int* p, int length, function<bool(int, int)> compare){

	for (int j = 0; j < length; j++){
		for(int i = 1; i < (length - j); i++){
			if(compare(p[i],p[i-1])){
				int temp = p[i-1];
				p[i-1] = p[i];
				p[i] = temp;
			}
		}
	}
}

function<bool(int, int)> generateNearestTo(int center){
	auto isNearestTo = [center] (int first, int second) {
		int firstCenter = first-center;
		if(firstCenter < 0) //takes absolute value of firstCenter
			firstCenter = -firstCenter; 
				
		int secondCenter = second-center;
		if(secondCenter < 0) //takes absolute value of secondCenter
			secondCenter = -secondCenter;
			
		if(firstCenter < secondCenter)
			return true;
			
		return false;
    };
    
    return isNearestTo; 
}

void testsortWithLambdas(){
	int size = 20;

	int array[size] = {4, 1, 1, 3, 10, 0, -1, -5, 7, 9, 10, 12, 56, 23, 15, 14, 51, 23, 10, 11};
	int* p = array;
	
	cout << "Sort with Lambdas \n"; 
	sortWithStandardFunction(p, 20, generateNearestTo(3));
	
	cout << "With 3 as center:";
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	cout << "\n";
	
	sortWithStandardFunction(p, 20, generateNearestTo(10));
	
	cout << "With 10 as center:";
	for (int i = 0; i < size; i++){
		cout << p[i] << " ";		
	}	
	cout << "\n";
}

//End of Part3-----------------------------------------------------
//int main(){
	
	//testSortWithPointers();
	//testSortWithInterfaces();
	//testsortWithLambdas();
//}
