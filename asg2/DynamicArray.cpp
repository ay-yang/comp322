#include <iostream>

template <class T> class DynamicArray;
template <class T> class DynamicArrayIterator;

using namespace std;

template <class T>
class DynamicArrayIterator{
	private:
		int currentPosition;
		DynamicArray<T>* array;
		int direction;
	
	public:
		DynamicArrayIterator(DynamicArray<T>*,int,int);
		T& operator *();
		void operator ++();
		int operator == (const DynamicArrayIterator<T>&);
		int operator != (const DynamicArrayIterator<T>&);
};

template <class T>
DynamicArrayIterator<T>::DynamicArrayIterator(DynamicArray<T>* pointer, int dir, int pos){
	this->currentPosition = pos;
	if(dir == 1 || dir == -1) //just to check 
		this->direction = dir;
	this->array = pointer;
}

template <class T>
T& DynamicArrayIterator<T>::operator*(){
	return (*(this->array))[this->currentPosition]; 
	//return this->array->test(this->currentPosition); <---old version
}

template <class T>
void DynamicArrayIterator<T>::operator ++(){
	//increments or decrements currentPosition depending on direction set
	if(this->direction == 1)
		this->currentPosition++;
	else if(this->direction == -1)
		this->currentPosition--;
}

template <class T>
int DynamicArrayIterator<T>::operator ==(const DynamicArrayIterator<T>& other){
	return (this->currentPosition == other.currentPosition && this->array == other.array);
}

template <class T>
int DynamicArrayIterator<T>::operator !=(const DynamicArrayIterator<T>& other){
	//Basically, does the opposite of == operator
	int temp = this->currentPosition == other.currentPosition && this->array == other.array;
	if(temp == 0)
		return -1;
	return 0;
}

//--------------------------------------------------------------------------------

template <class T>
class DynamicArray{
	private:
		T* array;
		int capacity;
		int current;
		int size;
	
	public: 
		DynamicArray();
		~DynamicArray();

		int getSize();
		void add(T const&);
		T remove(int);
		T& operator [](int); 
		T& test(int);

		DynamicArrayIterator<T> begin();
		DynamicArrayIterator<T> end();
		DynamicArrayIterator<T> r_begin();
		DynamicArrayIterator<T> r_end();
};

template <class T>
DynamicArray<T>::DynamicArray(){
	this->array = new T[10];
	this->array[0] = '\0'; //appoints the null character manually
	this->capacity = 10;
	this->current = 0;
	this->size = 10;	
}

template <class T>
DynamicArray<T>::~DynamicArray(){
	delete [] this->array;
}

//Counts the number of occupied slots
template <class T>
int DynamicArray<T>::getSize(){
	this->size =0;

	for (int i = 0; i < this->capacity; i++){
		if (array[i] != '\0')
			this->size++;
		else i = this->capacity;
	}

	return this->size;

}

template <class T>
void DynamicArray<T>::add(T const& item){
	
	//cout << "current: " << current << " ";
	//cout << "cap: " << this->capacity << "\n";
	
	if(current < this->capacity){
		this->array[current] = item;
		if (current < this->capacity-1)
			this->array[current+1] = '\0'; //Again, to make sure null character is present in the end
	}
	else{
		//creates a new array with twice the capacity as the current one
		T* newArray = new T[(this->capacity)*2];
		for(int i =0; i<this->capacity; i++){
			newArray[i] = array[i];
		}
		newArray[this->capacity] = item;
		newArray[this->capacity+1] = '\0';
		
		delete [] this->array; //sayonara, old array
		this->array = newArray; //hello, newly created array
		
		int temp = this->capacity; 
		this->capacity = temp*2; //updates capacity
	}
	this->current++;
}

template <class T>
T DynamicArray<T>::remove(int i){
	if (i >= getSize() || i < 0)
		cout << "error, index " << i << " is either out of scope or contains nothing." << endl;

	else{
		if(i < this->size-1){
			this->array[i] = this->array[i+1]; //copies the next value onto current index, overriding current index value

			//move everything back by one index
			for (int pos = i+1; pos < this->size; pos++){
				this->array[pos] = this->array[pos+1];
			}
		}
		else 
			this->array[this->size-1] = '\0';
			
		this->current--; //decreases current index
	}
}

//template <class T>
template <typename T>
T& DynamicArray<T>::operator [](int index){
	return this->array[index];	
}

//template <class T>
//T& DynamicArray<T>::test(int index){
	//return this->array[index];
//}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::begin(){
	//DynamicArrayIterator<T> forwardStart = DynamicArrayIterator<T>(this, 1, 0);
	return DynamicArrayIterator<T>(this, 1, 0);
}

template <class T> 
DynamicArrayIterator<T> DynamicArray<T>::end(){
	//DynamicArrayIterator<T> endStart = DynamicArrayIterator<T>(this, 1, this->getSize());
	return DynamicArrayIterator<T>(this, 1, this->getSize());
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::r_begin(){
	return DynamicArrayIterator<T>(this, -1, this->getSize()-1);
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::r_end(){
	return DynamicArrayIterator<T>(this, -1, -1);
}

//-------------------------------------------------------------------------------------------------------

int main() {
	DynamicArray<int> foo;
	foo.add(1);
	foo.add(2);
	foo.add(4);
	foo.add(5);
	foo.add(7);
	foo.add(8);
	foo.add(9);
	foo.add(10);
	foo.add(11);
	foo.add(12);
	foo.add(15);
	
	foo.remove(8);
	foo.add(16);
	//cout << foo[7] << " " << foo[8] << " " << foo[9] << "size: " << foo.getSize() << endl;
	foo[1] = 10;
	
	cout << "The array: " << endl;
	for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
		cout << *a << " " << endl;
	}
	
	cout << "The reverse array: " << endl; 
	for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
		cout << *a << " " << endl;
	}
}


