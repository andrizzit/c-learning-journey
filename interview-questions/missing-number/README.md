# Missing Number in Consecutive Array

## Problem Statement

You are given an array of consecutive integers, which has at most one missing number. Write a function which returns the missing number.

**Examples:**

```
Input: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
Output: No missing number

Input: [0,1,2,3,5,6,7,8,9,10,11,12,13,14,15]
Output: 4

Input: [0,1,2,3,4,5,6,7,8,9,10,11,12,14,15]
Output: 13
```

## Key Discussion Points & Hints

- **Algorithm Choice**: Can you do better than O(n)? Binary search is optimal here.
- **Edge Cases**: What about empty arrays? Missing first/last element? No missing number?
- **Return Value Design**: Should the function return the number directly or use a pointer? How to indicate "no missing"?
- **Input Validation**: Always check for NULL pointers and invalid sizes.
- **Integer Overflow**: Use `start + (end - start) / 2` instead of `(start + end) / 2`.

## Follow-up Questions

1. **What if the array doesn't start at 0?** How would you modify the solution?
2. **What if there are multiple missing numbers?** How would the approach change?
3. **What if the array is not sorted?** Would you sort first or use a different approach?
4. **Memory constraints**: What if you can't use extra space? (This solution already uses O(1))

## Red Flags to Watch For

- **Brute force O(n) solution** without considering binary search optimization
- **No edge case handling** (NULL checks, empty array, single element)
- **Printing inside the function** instead of returning/using output parameters
- **Magic numbers** without explanation (e.g., hardcoded assumptions)
- **No input validation** or assumptions not stated
- **Poor variable naming** (e.g., `i`, `j`, `k` without context)
- **Not testing the solution** with provided examples

## Complexity Analysis

- **Time Complexity**: O(log n) - Binary search
- **Space Complexity**: O(1) - No extra space needed
