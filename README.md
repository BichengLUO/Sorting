Sorting Algorithms
==========================

The project just contains some common sorting algorithms. When you don't remember some sorting algorithms and don't wanna use other heavy libraries like `std::sort`, you can easily copy the code here and modified the code so as to achieve your targets.

The sorting algorithms I implemented are:

### Insertion Sort
```
void insertion_sort(unsigned *a, long length);
```
### Quick Sort
```
void quick_sort(unsigned *a, long length);
```
### Merge Sort
```
void merge_sort(unsigned *a, long length);
```
### Counting Sort
```
void radix_counting_sort(unsigned *input, long length, long radix, long len);
```
> **Note:**
> - **length** means the length of input array
> - **radix** means which segment of the number should be chosen as the key
> - **len** means how long a segment should be

### Radix Sort
```
void radix_sort(unsigned *a, long length, long r = 4);
```
> **Note:**
> - **length** means the length of input array
> - **r** means how many bits of the number should be considered as a segment
