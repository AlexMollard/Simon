#pragma once
#include <memory.h>

template<typename T>
class DynamicArray
{
public:
	DynamicArray(int initialSize = 0) //Constructor
	{
		int nSize;
		nSize = initialSize;
		if (nSize < 1)
			nSize = 1;

		_data = new T[nSize];
		_totalSize = nSize;
		_usedData = 0;
		_swaps = 0;
	}

	~DynamicArray() //Destructor
	{
		delete[] _data;
	}

	//--------------------------------------
	// Array access Functions
	//--------------------------------------

	void PushBack(T data) //Adds element to end of array
	{
		Resize();
		_data[_usedData] = data;
		_usedData++;
	}

	void PushFront(T data) //Adds element to front of array
	{
		Resize();
		int buffer = _data[_totalSize - 1], buffer2;


		for (int i = 0; i < _totalSize; i++)
		{
			buffer2 = _data[i];
			_data[i] = buffer;
			buffer = buffer2;
		}

		_data[0] = data;

		_usedData++;
	}

	void Insert(int dataPos, T newData)	//Overwrites element choosen by postion in array
	{
		Resize();
		_data[dataPos] = newData;
	}

	T GetData(T input) //Gets element choosen by postion in array
	{
		return _data[input];
	}

	int Count() //Get total size of elements that could fit in the array
	{
		return _totalSize;
	}

	void clear() //Puts array writing point to 0 (Making it seem like the array has been erased)
	{
		_usedData = 0;
	}

	void erase(int dataPos) //Removes element from postion choosen
	{
		for (int i = dataPos; i < _usedData; i++)
		{
			_data[i] = _data[i + 1];
		}
		_usedData--;
	}

	int GetUsedData() //Gets number of data used in array
	{
		return _usedData;
	}

	void PopBack() //Deletes element at the end of array
	{
		_usedData--;
	}

	void PopFront() //Deletes element from the start of array
	{
		for (int i = 0; i < _usedData; i++)
		{
			_data[i] = _data[i + 1];
		}

		_usedData--;
	}

	T first() //Gets the first element
	{
		if (_usedData <= 0)
		{
			std::cout << "There is no first element" << std::endl;
			return 0;
		}
		return _data[0];
	}

	T last() //Gets the last elements
	{
		if (_usedData <= 0)
		{
			std::cout << "There is no last element" << std::endl;
			return 0;
		}
		return _data[_usedData - 1];
	}

	bool empty() //Test if array is empty
	{
		if (_usedData > 0)
		{
			std::cout << "Not Empty" << std::endl;
		}
		else
		{
			std::cout << "Empty" << std::endl;
		}
		return _usedData > 0;
	}

	void Remove(T value) //Removes all elements with matching data
	{
		for (int i = 0; i < _usedData; i++)
		{
			if (_data[i] == value)
			{
				for (int x = i; x < _usedData; x++)
				{
					_data[x] = _data[x + 1];
				}

				_usedData--;
				i--;
			}
		}
	}

	void DisplayAll() //Displays all elements in array
	{
		for (int i = 0; i < GetUsedData(); i++)
		{
			std::cout << _data[i] << " ";
		}
		std::cout << std::endl;
	}

	//--------------------------------------
	// Sorting Functions
	//--------------------------------------

	void ResetSwaps() //Resets swaps
	{
		_swaps = 0;
	}

	void Swap(T *xp, T *yp)//Swaps elements
	{
		_swaps++;
		T temp = *xp;
		*xp = *yp;
		*yp = temp;
	}

	int Partition(int low, int high)//Used in Quick Sort to split array up into sections
	{
		int pivot = _data[high / 2];
		int i = (low - 1);

		for (int j = low; j <= high - 1; j++)
		{

			if (_data[j] <= pivot)
			{
				i++;
				Swap(&_data[i], &_data[j]);
			}
		}
		Swap(&_data[i + 1], &_data[high]);
		return (i + 1);
	}

	int QuickSort(int low, int high) //Quick Sort elements (Lowest element postion [0], Second highest element postion [_usedData - 1])
	{
		if (low < high)
		{
			int pi = Partition(low, high);

			QuickSort(low, pi - 1);
			QuickSort(pi + 1, high);
		}
		return _swaps;
	}

	int InsertionSort() //Insertion sort elements
	{
		int key, j;
		for (int i = 1; i < _usedData; i++)
		{
			key = _data[i];
			j = i - 1;

			while (j >= 0 && _data[j] > key)
			{
				_swaps++;
				_data[j + 1] = _data[j];
				j = j - 1;
			}
			_data[j + 1] = key;
		}
		return _swaps;
	}

	int BubbleSort() //Bubble Sort elements
	{
		for (int i = 0; i < _usedData - 1; i++)
		{

			for (int j = 0; j < _usedData - i - 1; j++)
			{
				if (_data[j] > _data[j + 1])
				{
					Swap(&_data[j], &_data[j + 1]);

				}
			}
		}
		return _swaps;
	}

	//--------------------------------------
	// Operator
	//--------------------------------------

	T& operator[](int index) //Allows the use of [] on objects
	{
		return _data[index];
	}

private:
	void Resize() //Resizes array if to many elements are added
	{
		//If array is full
		if (_usedData >= _totalSize)
		{
			//Construct new object to store _data array
			T* biggerArray = new T[_totalSize * 2];

			//Copy _data array to biggerArray 
			memcpy_s(biggerArray, sizeof(T) * _totalSize * 2, _data, sizeof(T) * _totalSize);

			//Delete _data array
			delete[] _data;

			//Increase array size
			_totalSize *= 2;

			//Assigns biggerArray to _data 
			_data = biggerArray;
		}
	}

	//Varibles
	T* _data; //Array name

	int _totalSize; //Total space in array

	int _usedData; //Total elements in array + 1

	int _swaps; //Total swaps
};