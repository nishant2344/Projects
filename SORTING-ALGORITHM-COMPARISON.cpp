#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void mergeSort(int arr[], int left, int right);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int left, int mid, int right);
int partition(int arr[], int low, int high);
void printTable(double bubble, double selection, double insertion, double merge, double quick);

void generateRandomArray(int arr[], int size, bool sorted);

int main() {
    int size;
    char type;

    cout << "Enter the size of the array: ";
    cin >> size;
    cout << "Enter 'r' to generate random array or 's' to generate sorted array: ";
    cin >> type;

    int arr[size];
    generateRandomArray(arr, size, type == 's');

    int arr1[size], arr2[size], arr3[size], arr4[size];
    for (int i = 0; i < size; i++) {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        arr4[i] = arr[i];
    }

    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr1, size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> bubble_duration = end - start;

    start = chrono::high_resolution_clock::now();
    selectionSort(arr2, size);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> selection_duration = end - start;

    start = chrono::high_resolution_clock::now();
    insertionSort(arr3, size);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> insertion_duration = end - start;

    start = chrono::high_resolution_clock::now();
    mergeSort(arr4, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> merge_duration = end - start;

    start = chrono::high_resolution_clock::now();
    quickSort(arr4, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> quick_duration = end - start;

    printTable(bubble_duration.count(), selection_duration.count(), insertion_duration.count(), merge_duration.count(), quick_duration.count());

    double times[] = {bubble_duration.count(), selection_duration.count(), insertion_duration.count(), merge_duration.count(), quick_duration.count()};
    const char* names[] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"};
    double min_time = times[0];
    const char* fastest_algorithm = names[0];

    for (int i = 1; i < 5; i++) {
        if (times[i] < min_time) {
            min_time = times[i];
            fastest_algorithm = names[i];
        }
    }

    cout << "\nThe fastest sorting algorithm is: " << fastest_algorithm << " with time: " << min_time << " seconds." << endl;

    return 0;
}

void generateRandomArray(int arr[], int size, bool sorted) {
    if (sorted) {
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }
    } else {
        srand(time(0));
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 10000;
        }
    }
}

// Bubble Sort
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

// Insertion Sort
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printTable(double bubble, double selection, double insertion, double merge, double quick) {
    cout << "\nSorting Algorithm Comparison (Time in seconds):\n";
    cout << "---------------------------------------------------\n";
    cout << "Algorithm         | Time (seconds)\n";
    cout << "---------------------------------------------------\n";
    cout << "Bubble Sort       | " << bubble << "\n";
    cout << "Selection Sort    | " << selection << "\n";
    cout << "Insertion Sort    | " << insertion << "\n";
    cout << "Merge Sort        | " << merge << "\n";
    cout << "Quick Sort        | " << quick << "\n";
    cout << "---------------------------------------------------\n";
}
