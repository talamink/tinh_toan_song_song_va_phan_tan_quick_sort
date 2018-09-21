#include <iostream>
#include <omp.h> // code song song
#include <stdio.h>
#include <conio.h>
#include <algorithm> // lay swap
using namespace std;

int partition(int arr[], int left, int right)
{
	int pivot = arr[left];
	while (left != right)
	{
		if (arr[left] > arr[right])
		{
			std::swap(arr[left], arr[right]);
		}
		if (pivot == arr[left])
			right--;
		else // Pivot == arr[right]
			left++;
	}
	return left;
}

void quickSort_parallel_omp(int arr[], int low, int high)
{
	int pi;
	if (low < high)
	{
		pi = partition(arr, low, high);
		cout << "\nthread" << omp_get_thread_num() << "\n";
#pragma omp parallel sections
		{
#pragma omp section
			{
				quickSort_parallel_omp(arr, low, pi - 1);
				cout << "\nthread"<< omp_get_thread_num()<<"\n";
			}
#pragma omp section
			{	quickSort_parallel_omp(arr, pi + 1, high);
				cout << "\nthread"<< omp_get_thread_num()<<"\n";
			}
		}
	}
}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main(){
	int arr[] = { 10, 7, 2, 9, 1, 5, 6, 8, 0, 0 };
	int n = sizeof(arr) / sizeof(arr[0]); // tinh kich co cua mang

	cout << "TINH TOAN SONG SONG VA PHAN TAN - Quicksort\n";


	cout << "Chuoi truoc khi sap xep:\n";
	printArray(arr, n);
	cout << "\n";

	quickSort_parallel_omp(arr, 0, n - 1);

	cout << "Chuoi sau khi sap xep:\n";
	printArray(arr, n);
	cout << "\n";

	_getch();
	return 0;
}