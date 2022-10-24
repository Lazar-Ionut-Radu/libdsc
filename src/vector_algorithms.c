#include "vector_algorithms.h"

int v_binary_search(Vector *vector, int (*cmp)(void *, void *), void *data)
{
    // Set the search space to all the array.
    int low = 0, high = vector->size - 1;
    int mid; 

    // Iteratively half the search space until it contains at most 2 values.
    while (high - low > 1) {
        mid = (high + low) / 2;
        if (cmp(vector->data[mid], data) == -1)
            low = mid + 1;
        else 
            high = mid;
    }
    // When the search space has at most 2 elements look at them.
    if (cmp(vector->data[low], data) == 0)
        return low;
    else if (cmp(vector->data[high], data) == 0)
        return high;
    
    // If not found return -1.
    return -1;
}

void v_bubble_sort(Vector *vector, int (*cmp)(void *, void *))
{
    // Swaps adjacent element until: the first is placed corectly, the second 
    // one is placed corectly and so on. 
    for (int i = vector->size - 1; i >= 0; i--)
        for (int j = 0; j < i; j++) 
            if (cmp(vector->data[j] , vector->data[j + 1]) == 1)
                swap(vector->data[j], vector->data[j+1], vector->data_size);
}

void v_insertion_sort(Vector *vector, int (*cmp)(void *, void *))
{
    // Alloc auxiliary memory.
    void *key = malloc(vector->data_size);
    if (key == NULL)
        return;
    
    int j;
    // Insert the i-th element into the (previously sorted) [0, i-1] vector.
    for (int i = 1; i < vector->size; i++) {

        memmove(key, vector->data[i], vector->data_size);
        j = i - 1;

        // Move elements to the right until the good spot is found to insert
        // into.
        while (j >= 0 && cmp(vector->data[j], key) == 1)
        {
            memmove(vector->data[j + 1], vector->data[j], vector->data_size);
            j = j - 1;
        }
        // Move the element on the good spot.
        memmove(vector->data[j + 1], key, vector->data_size);
    }

    // Free auxilairy memory.
    free(key);
}

// Takes the last element as pivot, places the pivot element ar its correct
// position in the sorted vector and places the all smaller elements 
// (than pivot) to the left and all greater elements to the right.
// Does this on the [low, high] vector.
// Returns the position of the pivot. 
int _v_qs_partition(Vector *vector, int (*cmp)(void *, void *), int low, int high)
{
    // Alloc auxiliary memory, to save the value of the pivot.
    void *key = malloc(vector->data_size);
    if (key == NULL)
        return -1;
    memmove(key, vector->data[high], vector->data_size);

    // Place the elements smaller than the pivot to at the beginning of the vector
    int pos = low - 1;
    for (int i = low; i <= high - 1; i++) {
        if (cmp(vector->data[i], key) == -1) {
            pos++;
            swap(vector->data[pos], vector->data[i], vector->data_size);
        }
    }
    // Place the pivot in its right position.
    swap(vector->data[pos + 1], vector->data[high], vector->data_size);

    // Free auxiliary memory.
    free(key);

    // Return the position of the pivot.
    return pos + 1;
}

void v_quick_sort(Vector *vector, int (*cmp)(void *, void *), int low, int high)
{
    // Recursively find the pivot, place it in the right place, then do the same
    // for the lower and upper vectors.
    if (low < high) {
        // After this the pivot will be in the right (sorted) position
        int pivot = _v_qs_partition(vector, cmp, low, high);
        // Do the same for lower and upper vectors.
        v_quick_sort(vector, cmp, low, pivot - 1);
        v_quick_sort(vector, cmp, pivot + 1, high);
    }
}

void _v_merge(Vector *vector, int (*cmp)(void *, void *), int left, int mid, int right)
{
    // Copy the 2 halves of the array.
    Vector *left_vector = v_create(vector->data_size, vector->free_func);
    void *element = malloc(vector->data_size);
    for (int i = 0; i < mid - left + 1; i++) {
        element = memmove(element, vector->data[i + left], vector->data_size);
        v_push_back(left_vector, element);  
    }

    Vector *right_vector = v_create(vector->data_size, vector->free_func);
    for (int i = 0; i < right - mid; i++) {
        element = memmove(element, vector->data[i + mid + 1], vector->data_size);
        v_push_back(right_vector, element);  
    }

    // Merge the temp arrays back into [left, right].
    // Compare the elements of the sorted left and right vectors and place
    // them in order.
    int index_left = 0;
    int index_right = 0;
    int index_merged = left;
    while ((index_left < mid - left + 1) && (index_right < right - mid)) {
        if (cmp(left_vector->data[index_left], right_vector->data[index_right]) == -1) {
            memmove(vector->data[index_merged], left_vector->data[index_left], vector->data_size);
            index_left++;
        }
        else {
            memmove(vector->data[index_merged], right_vector->data[index_right], vector->data_size);
            index_right++;
        }
        index_merged++;
    }

    // Place the remaining elements if any.
    while (index_left < mid - left + 1) {
        memmove(vector->data[index_merged], left_vector->data[index_left], vector->data_size);
        index_left++;
        index_merged++;
    }

    while (index_left < right - mid) {
        memmove(vector->data[index_merged], right_vector->data[index_right], vector->data_size);
        index_right++;
        index_merged++;
    }

    // Free the additional memoty.
    v_free(left_vector);
    v_free(right_vector);
    free(element);
}

void v_merge_sort(Vector *vector, int (*cmp)(void *, void *), int left, int right)
{
    // A vector with one element is already sorted, so this is the end of
    // the recursion.
    if (left >= right)
        return;

    // Sort the two halves of the vector recursively.
    int mid = (left + right) / 2;
    v_merge_sort(vector, cmp, left, mid);
    v_merge_sort(vector, cmp, mid + 1, right);
    
    // And merge them together.
    _v_merge(vector, cmp, left, mid, right);
}