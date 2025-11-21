# DNA Sequence Composition Problem

## Problem Statement

Given a large list of DNA sequences (strings containing only A, T, G, C). Some sequences are composite sequences formed by concatenating other complete sequences from the list. Write a method that finds all sequences that can be decomposed into two or more other sequences from the same list and return all valid decompositions.

**Examples:**

```
Input:
["ATGC", "AT", "GC", "GCTA", "TA", "ATGCTA", "CTAGC", "CT", "AGC", "CTAGCTA"]

Output:
ATGC = ["AT", "GC"]
GCTA = ["GC", "TA"]
ATGCTA = ["AT", "GC", "TA"]
ATGCTA = ["ATGC", "TA"]
CTAGC = ["CT", "AGC"]
CTAGCTA = ["CT", "AGC", "TA"]
CTAGCTA = ["CTAGC", "TA"]
```

## Key Discussion Points & Hints

- **Recursive Decomposition**: Use backtracking to try all possible prefix splits at each step.
- **Self-Exclusion**: A sequence cannot be decomposed using itself as a component.
- **Minimum Parts**: Only show decompositions with at least 2 parts.
- **Multiple Decompositions**: A sequence may have multiple valid decompositions.
- **String Matching**: Check if each prefix exists in the original list before recursing.
- **Optimization Opportunity**: Consider using a Trie or hash set for faster prefix lookups.
- **Dynamic Programming**: Memoization could avoid redundant computations.

## Approaches

### 1. Recursive Backtracking (Current Implementation)

- For each sequence, try all possible prefix lengths
- If prefix exists in list (and isn't the original), recurse on remainder
- Base case: when remainder is empty, print if we have ≥2 parts
- **Time**: O(2^n × m) worst case - n = sequence length, m = list size for lookups
- **Space**: O(n) for recursion stack depth

### 2. Dynamic Programming (Optimized)

- Use memoization to cache decompositions for substrings
- Build solutions bottom-up from smaller substrings
- **Time**: O(n² × m) where n = max sequence length, m = list size
- **Space**: O(n²) for memoization table

### 3. Trie-Based Approach (Advanced)

- Build a Trie of all sequences for O(k) prefix lookup
- Use DP with Trie for efficient substring checking
- **Time**: O(n² × k) where k = average prefix length
- **Space**: O(total characters) for Trie + O(n²) for DP

## Follow-up Questions

1. **What if sequences can contain lowercase letters?** Would you normalize input?
2. **How would you handle very large sequence lists?** Consider memory-efficient data structures.
3. **What if you only need to find ONE decomposition per sequence?** Can you optimize by stopping early?
4. **How would you handle circular sequences?** (e.g., "ATGC" could be viewed as "GCTA" rotated)
5. **What about overlapping decompositions?** Should "ATAT" decompose as ["AT", "AT"] or treat duplicate usage differently?
6. **Memory constraints**: What if the sequence list doesn't fit in memory?

## Red Flags to Watch For

- **Not excluding self** when checking if a prefix exists in the list
- **Missing base case** in recursion (empty remainder check)
- **Not requiring minimum 2 parts** (a sequence alone isn't a decomposition)
- **Inefficient lookup** using linear search through the list repeatedly
- **Buffer overflow** when copying strings (not checking bounds)
- **No NULL termination** when using `strncpy`
- **Not handling empty strings** or NULL pointers
- **Stack overflow** with very long sequences (deep recursion)
- **Memory leaks** if using dynamic allocation
- **Not printing all decompositions** when multiple exist

## Implementation Notes

### Current Implementation (Basic)

The provided solution uses:

- **Recursive backtracking** to explore all possible decompositions
- **Linear search** to check if a prefix exists in the sequence list
- **Global arrays** for storing sequences (simpler but less flexible)
- **Direct printing** instead of storing results

### Potential Improvements

1. **Use a hash set** for O(1) prefix existence checks instead of O(m) linear search
2. **Add memoization** to avoid recomputing decompositions for the same substring
3. **Dynamic allocation** instead of fixed-size arrays for flexibility
4. **Return results** in a data structure instead of printing directly
5. **Implement iterative DP** solution to avoid deep recursion stacks

## Complexity Analysis

### Current Implementation

- **Time Complexity**: O(n × 2^L × m) where:
  - n = number of sequences
  - L = average length of sequences
  - m = number of sequences (for existence check)
  - Exponential due to trying all prefix combinations
- **Space Complexity**: O(L) for recursion stack depth

### With Hash Set Optimization

- **Time Complexity**: O(n × 2^L) - Same exponential behavior but O(1) lookups
- **Space Complexity**: O(n × L) for hash set + O(L) for recursion

### With DP + Hash Set

- **Time Complexity**: O(n × L²) - Polynomial time with memoization
- **Space Complexity**: O(n × L²) for memoization table

## Testing Strategy

**Test Cases to Cover:**

1. **No decomposable sequences** - all sequences are atomic
2. **Simple 2-part decomposition** - "ATGC" = ["AT", "GC"]
3. **Multiple decompositions** - "ATGCTA" = ["AT","GC","TA"] or ["ATGC","TA"]
4. **Long chains** - sequences decomposed into 3+ parts
5. **Edge cases**:
   - Empty list
   - Single sequence (no decomposition possible)
   - All sequences of length 1
   - Duplicate sequences in list
6. **Self-reference** - ensure a sequence doesn't use itself in decomposition
