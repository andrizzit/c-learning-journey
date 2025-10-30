#include <stdio.h>
#include <stdbool.h>

/**
 * Finds the missing number in an array of consecutive integers.
 * 
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 * 
 * @param numbers Array of integers
 * @param size Size of the array
 * @param missing Pointer to store the missing number
 * @return true if missing number found, false otherwise
 */
bool find_missing_number(const int numbers[], int size, int *missing) {
    if (numbers == NULL || size == 0 || missing == NULL) {
        return false;
    }
    
    // Check if first number is missing
    if (numbers[0] != 0) {
        *missing = 0;
        return true;
    }
    
    // Check if no number is missing
    if (numbers[size - 1] == size) {
        return false;
    }
    
    // Binary search for missing number
    int start = 0;
    int end = size - 1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        
        if (numbers[mid] == mid) {
            start = mid + 1;
        } else {
            if (mid == 0 || numbers[mid - 1] == mid - 1) {
                *missing = mid;
                return true;
            }
            end = mid - 1;
        }
    }
    
    *missing = start;
    return true;
}

int main(void) {
    int missing;
    
    // Test: No missing number
    int test1[] = {0, 1, 2, 3, 4};
    printf("No missing: %s\n", 
           find_missing_number(test1, 5, &missing) ? "FAIL" : "PASS");
    
    // Test: Missing at start
    int test2[] = {1, 2, 3, 4};
    find_missing_number(test2, 4, &missing);
    printf("Missing at start (0): %s\n", missing == 0 ? "PASS" : "FAIL");
    
    // Test: Missing in middle
    int test3[] = {0, 1, 2, 4, 5};
    find_missing_number(test3, 5, &missing);
    printf("Missing in middle (3): %s\n", missing == 3 ? "PASS" : "FAIL");
    
    // Test: Missing at end
    int test4[] = {0, 1, 2, 3};
    find_missing_number(test4, 4, &missing);
    printf("Missing at end (4): %s\n", missing == 4 ? "PASS" : "FAIL");
    
    return 0;
}
