#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <Windows.h>

void insertion_sort(unsigned *a, long length);

void quick_sort(unsigned *a, long length);
void quick_sort_rec(unsigned *a, long l, long r);
void swap(unsigned &a, unsigned &b);

void merge_sort(unsigned *a, long length);
void merge_sort_rec(unsigned *a, long l, long r);
void merge_sort_merge(unsigned *a, long l, long middle, long r);

void radix_sort(unsigned *a, long length, long r = 4);
void radix_counting_sort(unsigned *input, long length, long radix, long len);

void random_fill(unsigned *a, long length);
void print_array(unsigned *a, long length);
void print_array_to_file(unsigned *a, long length, std::ofstream &file);
bool check_correction(unsigned *a1, unsigned *a2, unsigned *a3, unsigned *a4, long length);

unsigned *temp;
unsigned *temp2;

long main()
{
	srand(time(NULL));
	long length = 10000;
	std::cout << "Enter the number you need to generate:";
	std::cin >> length;
	temp = new unsigned[length];
	temp2 = new unsigned[length];

	unsigned *input = new unsigned[length];
	std::ofstream file("output.txt", std::ofstream::out);

	std::cout << "Input size: " << length << std::endl;

	//Using high precision time calculation method that Win32 API provides
	LARGE_INTEGER Beglongime;
	LARGE_INTEGER EndTime;
	LARGE_INTEGER Frequency;

	//*******************************Insertion Sort**************************************
	file << "Insertion Sort:\nSource: ";
	random_fill(input, length);
	print_array_to_file(input, length, file);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Beglongime);
	insertion_sort(input, length);
	QueryPerformanceCounter(&EndTime);
	float tm1 = (float)(EndTime.QuadPart - Beglongime.QuadPart) / Frequency.QuadPart;
	std::cout << "Insertion Sort\ttime elapsed: " << tm1 << " secs." << std::endl;
	file << "Result: ";
	print_array_to_file(input, length, file);

	//*******************************Quick Sort**************************************
	file << "Quick Sort:\nSource: ";
	random_fill(input, length);
	print_array_to_file(input, length, file);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Beglongime);
	quick_sort(input, length);
	QueryPerformanceCounter(&EndTime);
	float tm2 = (float)(EndTime.QuadPart - Beglongime.QuadPart) / Frequency.QuadPart;
	std::cout << "Quick Sort\ttime elapsed: " << tm2 << " secs." << std::endl;
	file << "Result: ";
	print_array_to_file(input, length, file);

	//*******************************Merge Sort**************************************
	file << "Merge Sort:\nSource: ";
	random_fill(input, length);
	print_array_to_file(input, length, file);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Beglongime);
	merge_sort(input, length);
	QueryPerformanceCounter(&EndTime);
	float tm3 = (float)(EndTime.QuadPart - Beglongime.QuadPart) / Frequency.QuadPart;
	std::cout << "Merge Sort\ttime elapsed: " << tm3 << " secs." << std::endl;
	file << "Result: ";
	print_array_to_file(input, length, file);

	//*******************************Radix Sort**************************************
	//test different r values to show the efficiency
	for (long r = 1; r <= 20; r++)
	{
		file << "Radix Sort (r = " << r << "):\nSource: ";
		random_fill(input, length);
		print_array_to_file(input, length, file);
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&Beglongime);
		radix_sort(input, length, r);
		QueryPerformanceCounter(&EndTime);
		float tm4 = (float)(EndTime.QuadPart - Beglongime.QuadPart) / Frequency.QuadPart;
		std::cout << "Radix Sort\tr = " << r << " time elapsed: " << tm4 << " secs." << std::endl;
		file << "Result: ";
		print_array_to_file(input, length, file);
	}
	std::cout << "All test arrays has been saved to output.txt!" << std::endl;
	delete[] input;

	delete[] temp;
	delete[] temp2;
	return 0;
}

//Check whether the results of 4 sorting algorithms equal to each other
bool check_correction(unsigned *a1, unsigned *a2, unsigned *a3, unsigned *a4, long length)
{
	for (long i = 0; i < length; i++)
	{
		if (!(a1[i] == a2[i] &&
			a2[i] == a3[i] &&
			a3[i] == a4[i]))
			return false;
	}
	return true;
}

//Insertion sort
void insertion_sort(unsigned *a, long length)
{
	for (long i = 1; i < length; i++)
	{
		long b = a[i];
		long j;
		for (j = i - 1; j >= 0; j--)
		{
			if (a[j] > b) a[j + 1] = a[j];
			else break;
		}
		a[j + 1] = b;
	}
}

//Quick sort
void quick_sort(unsigned *a, long length)
{
	quick_sort_rec(a, 0, length - 1);
}

//Quick sort recursion function
//using bi-directional scanning to swap values
void quick_sort_rec(unsigned *a, long l, long r)
{
	if (l < r)
	{
		int i = l, j = r;
		unsigned p = l + rand() % (r - l + 1);
		unsigned v = a[p];
		do
		{
			//Bi-directional scanning
			while (a[i] < v) i++;
			while (a[j] > v) j--;
			if (i <= j)
			{
				swap(a[i], a[j]);
				i++;
				j--;
			}
		} while (i <= j);
		quick_sort_rec(a, l, j);
		quick_sort_rec(a, i, r);
	}
}

//Fast swap using exclusive OR
inline void swap(unsigned &a, unsigned &b)
{
	if (a != b)
	{
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

//Merge sort
void merge_sort(unsigned *a, long length)
{
	merge_sort_rec(a, 0, length - 1);
}

//Merge sort recursion function
void merge_sort_rec(unsigned *a, long l, long r)
{
	if (l < r)
	{
		long middle = (l + r) / 2;
		merge_sort_rec(a, l, middle);
		merge_sort_rec(a, middle + 1, r);
		merge_sort_merge(a, l, middle, r);
	}
}

//Merge one sorted array from l to middle
//with another sorted array from middle+1 to r
//into a sorted one together
void merge_sort_merge(unsigned *a, long l, long middle, long r)
{
	long i = l;
	long j = middle + 1;
	unsigned *c = temp;
	long k = 0;
	while (i <= middle && j <= r)
	{
		if (a[i] < a[j]) c[k++] = a[i++];
		else c[k++] = a[j++];
	}
	while (i <= middle)
	{
		c[k++] = a[i++];
	}
	while (j <= r)
	{
		c[k++] = a[j++];
	}
	for (k = 0; k <= r - l; k++)
		a[l + k] = c[k];
}

//Radix sort
void radix_sort(unsigned *a, long length, long r)
{
	for (long i = 0; i * r < 32; i++)
		radix_counting_sort(a, length, i, r);
}

//Counting sort for radix sort
//radix means which segment should be chosen as the key
//len means how long a segment should be
void radix_counting_sort(unsigned *input, long length, long radix, long len)
{
	unsigned *a = temp;
	long range = 1 << len;
	for (long i = 0; i < length; i++)
		a[i] = (input[i] >> radix * len) & (range - 1);
	unsigned *b = new unsigned[1 << len];
	memset(b, 0, sizeof(unsigned)*range);
	unsigned *c = temp2;
	for (long i = 0; i < length; i++)
		b[a[i]]++;
	for (long i = 1; i < range; i++)
		b[i] = b[i - 1] + b[i];
	for (long i = length - 1; i >= 0; i--)
	{
		c[b[a[i]] - 1] = input[i];
		b[a[i]]--;
	}
	memcpy(input, c, sizeof(unsigned) * length);
	delete[] b;
}

//Fill an array with randomized numbers
void random_fill(unsigned *a, long length)
{
	for (long i = 0; i < length; i++)
	{
		//Get an randomized number using bit operation
		//in order to exceed the limitation of RAND_MAX
		a[i] = rand() << 16 | rand();
	}
}

//Print the array
void print_array(unsigned *a, long length)
{
	for (long i = 0; i < length; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}

//Print the array to file
void print_array_to_file(unsigned *a, long length, std::ofstream &file)
{
	for (long i = 0; i < length; i++)
		file << a[i] << " ";
	file << std::endl;
}