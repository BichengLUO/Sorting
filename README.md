Sorting Algorithms
==========================

The project just contains some common sorting algorithms. When you don't remember some sorting algorithms and don't wanna use other heavy libraries like `std::sort`, you can easily copy the code here and modified the code so as to achieve your targets.

The sorting algorithms I implemented are:

### Insertion Sort
```C++
void insertion_sort(unsigned *a, long length);
```
### Quick Sort
```C++
void quick_sort(unsigned *a, long length);
```
### Merge Sort
```C++
void merge_sort(unsigned *a, long length);
```
### Counting Sort
```C++
void radix_counting_sort(unsigned *input, long length, long radix, long len);
```
> **Note:**
> - **length** means the length of input array
> - **radix** means which segment of the number should be chosen as the key
> - **len** means how long a segment should be
> If you want to simply call radix_counting_sort to sort an array, pass parameters like this:`radix_counting_sort(input, length, 0, 32)`. It means consider a 32bit integer as a segment and choose the first and the only segment as the key.

### Radix Sort
```C++
void radix_sort(unsigned *a, long length, long r = 4);
```
> **Note:**
> - **length** means the length of input array
> - **r** means how many bits of the number should be considered as a segment
