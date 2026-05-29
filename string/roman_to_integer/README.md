# Roman to Integer Problem

## Problem Description

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

| Symbol | Value |
|--------|-------|
| I      | 1     |
| V      | 5     |
| X      | 10    |
| L      | 50    |
| C      | 100   |
| D      | 500   |
| M      | 1000  |

For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

- I can be placed before V (5) and X (10) to make 4 and 9.
- X can be placed before L (50) and C (100) to make 40 and 90.
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

**Constraints:**
- `1 <= s.length <= 15`
- `s` contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
- It is guaranteed that `s` is a valid roman numeral in the range [1, 3999].

## Examples

### Example 1:
```
Input: s = "III"
Output: 3
Explanation: III = 3.
```

### Example 2:
```
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
```

### Example 3:
```
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

## Solution Approach

### Method: Left-to-Right with Lookahead (Current Implementation)

**Algorithm:**
1. Iterate through the Roman numeral string from left to right
2. For each character, get its value
3. Check if the current value is less than the next value
   - If yes, this is a subtraction case (e.g., IV, IX, XL, XC, CD, CM)
   - Subtract current from next and add the result
   - Skip the next character as it's already processed
4. Otherwise, add the current value to the result
5. Return the accumulated result

**Time Complexity:** O(n) - where n is the length of the string
- We iterate through each character exactly once
- Each character is processed in constant time

**Space Complexity:** O(1) - only using a few variables (result, current, next)
- No additional data structures required
- Constant space regardless of input size

**Advantages:**
- Simple and intuitive approach
- Easy to understand and implement
- Constant space complexity
- Handles all subtraction cases correctly
- Single pass through the string

**Disadvantages:**
- Requires lookahead (checking next character)
- Slightly more complex than right-to-left approach

### Alternative Method: Right-to-Left (Alternative)

**Algorithm:**
1. Start from the rightmost character
2. Keep track of the previous value
3. If current value is less than previous, subtract it
4. Otherwise, add it
5. Update previous value and move left

**Time Complexity:** O(n) - same as current method
**Space Complexity:** O(1) - same as current method

**Advantages:**
- No need for lookahead
- Can be slightly more intuitive (process from right)

**Disadvantages:**
- Requires tracking previous value
- Slightly different logic flow

**Alternative Implementation (Pseudo-code):**
```c
int romanToInt(char *s) {
    int result = 0;
    int prev = 0;
    
    for (int i = strlen(s) - 1; i >= 0; i--) {
        int current = getValue(s[i]);
        if (current < prev) {
            result -= current;
        } else {
            result += current;
        }
        prev = current;
    }
    
    return result;
}
```

## Questions & Analysis

### 1. Why do we subtract in certain cases?
In Roman numerals, when a smaller value appears before a larger value, it means subtraction. This is a historical convention to make writing more compact. For example:
- IV = 4 (instead of IIII)
- IX = 9 (instead of VIIII)
- XL = 40 (instead of XXXX)
- XC = 90 (instead of LXXXX)
- CD = 400 (instead of CCCC)
- CM = 900 (instead of DCCCC)

### 2. How do we identify subtraction cases?
We check if the current character's value is less than the next character's value. If so, we subtract the current from the next. The valid subtraction pairs are:
- I before V or X (IV=4, IX=9)
- X before L or C (XL=40, XC=90)
- C before D or M (CD=400, CM=900)

### 3. Why is the input guaranteed to be valid?
The problem constraints state that the input is guaranteed to be a valid Roman numeral. This means:
- No invalid characters
- Proper ordering (largest to smallest, except for subtraction cases)
- No invalid subtraction pairs (e.g., IL, IC, ID, IM are invalid)
- Within the range [1, 3999]

### 4. What is the maximum value we can represent?
The maximum value is 3999 (MMMCMXCIX). This is because:
- M = 1000, so MMM = 3000
- CM = 900
- XC = 90
- IX = 9
- Total: 3000 + 900 + 90 + 9 = 3999

### 5. Edge Cases to Consider:
- [x] Single character (e.g., "I", "V", "X")
- [x] Simple addition (e.g., "III", "XX", "CC")
- [x] Single subtraction (e.g., "IV", "IX", "XL", "XC", "CD", "CM")
- [x] Mixed addition and subtraction (e.g., "MCMXCIV")
- [x] Maximum value (e.g., "MMMCMXCIX" = 3999)
- [x] Minimum value (e.g., "I" = 1)
- [x] All subtraction cases (IV, IX, XL, XC, CD, CM)

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./roman_to_integer
```

### Expected Output

```
Example 1:
Input: s = "III"
Output: 3
Explanation: III = 3.

Example 2:
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V = 5, III = 3.

Example 3:
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

Additional test cases:
s = "I": 1
s = "IV": 4
s = "IX": 9
s = "XL": 40
s = "XC": 90
s = "CD": 400
s = "CM": 900
s = "MMMCMXCIX": 3999
s = "XIV": 14
s = "XXVII": 27
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: All subtraction cases
printf("s = \"IV\": %d\n", romanToInt("IV"));      // Expected: 4
printf("s = \"IX\": %d\n", romanToInt("IX"));      // Expected: 9
printf("s = \"XL\": %d\n", romanToInt("XL"));     // Expected: 40
printf("s = \"XC\": %d\n", romanToInt("XC"));     // Expected: 90
printf("s = \"CD\": %d\n", romanToInt("CD"));     // Expected: 400
printf("s = \"CM\": %d\n", romanToInt("CM"));     // Expected: 900

// Test case: Maximum value
printf("s = \"MMMCMXCIX\": %d\n", romanToInt("MMMCMXCIX")); // Expected: 3999

// Test case: Minimum value
printf("s = \"I\": %d\n", romanToInt("I"));       // Expected: 1
```

### Test Cases Checklist

- [x] Basic addition (Example 1: "III")
- [x] Mixed addition (Example 2: "LVIII")
- [x] Complex with multiple subtractions (Example 3: "MCMXCIV")
- [x] Single character ("I", "V", "X", "L", "C", "D", "M")
- [x] All subtraction cases (IV, IX, XL, XC, CD, CM)
- [x] Maximum value ("MMMCMXCIX" = 3999)
- [x] Minimum value ("I" = 1)
- [x] Simple cases ("II", "XX", "CC", "MM")
- [x] Mixed cases ("XIV", "XXVII", "MCMXCIV")

### Performance Testing

To test performance:

1. **Time the execution:**
```bash
time ./roman_to_integer
```

2. **Test with different string lengths:**
   - Short (1-3 characters): Very fast
   - Medium (4-8 characters): Fast
   - Long (9-15 characters): Still fast (linear complexity)

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./roman_to_integer
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
int romanToInt(char *s);
```

**Parameters:**
- `s`: Roman numeral string (guaranteed to be valid, length 1-15)

**Returns:**
- Integer value of the Roman numeral (range: 1-3999)

## Algorithm Details

### Step-by-Step Example: Converting "MCMXCIV"

1. **Input:** s = "MCMXCIV"
2. **Initialize:** result = 0
3. **Iteration 1:** i=0, current='M' (1000)
   - Next='C' (100), 1000 >= 100, so add 1000
   - result = 1000
4. **Iteration 2:** i=1, current='C' (100)
   - Next='M' (1000), 100 < 1000, so subtract: 1000 - 100 = 900
   - result = 1000 + 900 = 1900
   - Skip next character (i becomes 3)
5. **Iteration 3:** i=3, current='X' (10)
   - Next='C' (100), 10 < 100, so subtract: 100 - 10 = 90
   - result = 1900 + 90 = 1990
   - Skip next character (i becomes 5)
6. **Iteration 4:** i=5, current='I' (1)
   - Next='V' (5), 1 < 5, so subtract: 5 - 1 = 4
   - result = 1990 + 4 = 1994
   - Skip next character (loop ends)
7. **Return:** 1994

### Step-by-Step Example: Converting "LVIII"

1. **Input:** s = "LVIII"
2. **Initialize:** result = 0
3. **Iteration 1:** i=0, current='L' (50)
   - Next='V' (5), 50 >= 5, so add 50
   - result = 50
4. **Iteration 2:** i=1, current='V' (5)
   - Next='I' (1), 5 >= 1, so add 5
   - result = 55
5. **Iteration 3:** i=2, current='I' (1)
   - Next='I' (1), 1 >= 1, so add 1
   - result = 56
6. **Iteration 4:** i=3, current='I' (1)
   - Next='I' (1), 1 >= 1, so add 1
   - result = 57
7. **Iteration 5:** i=4, current='I' (1)
   - No next character, so add 1
   - result = 58
8. **Return:** 58

### Step-by-Step Example: Converting "III"

1. **Input:** s = "III"
2. **Initialize:** result = 0
3. **Iteration 1:** i=0, current='I' (1)
   - Next='I' (1), 1 >= 1, so add 1
   - result = 1
4. **Iteration 2:** i=1, current='I' (1)
   - Next='I' (1), 1 >= 1, so add 1
   - result = 2
5. **Iteration 3:** i=2, current='I' (1)
   - No next character, so add 1
   - result = 3
6. **Return:** 3

## Roman Numeral Reference

### Basic Symbols
- I = 1
- V = 5
- X = 10
- L = 50
- C = 100
- D = 500
- M = 1000

### Subtraction Cases
- IV = 4 (I before V)
- IX = 9 (I before X)
- XL = 40 (X before L)
- XC = 90 (X before C)
- CD = 400 (C before D)
- CM = 900 (C before M)

### Common Examples
- 1 = I
- 2 = II
- 3 = III
- 4 = IV
- 5 = V
- 6 = VI
- 7 = VII
- 8 = VIII
- 9 = IX
- 10 = X
- 14 = XIV
- 27 = XXVII
- 58 = LVIII
- 1994 = MCMXCIV
- 3999 = MMMCMXCIX

## Additional Resources

- [LeetCode Roman to Integer Problem](https://leetcode.com/problems/roman-to-integer/)
- Roman numeral system history
- String processing techniques in C
- Time complexity analysis

