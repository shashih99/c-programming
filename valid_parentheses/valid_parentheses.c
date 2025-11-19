#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 10000  // Based on constraint: s.length <= 10^4

// Stack structure
typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Check if stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Push character onto stack
bool push(Stack* stack, char c) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        return false;  // Stack overflow
    }
    stack->data[++stack->top] = c;
    return true;
}

// Pop character from stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';  // Stack underflow
    }
    return stack->data[stack->top--];
}

// Peek at top of stack without popping
char peek(Stack* stack) {
    if (isEmpty(stack)) {
        return '\0';
    }
    return stack->data[stack->top];
}

// Check if two brackets form a matching pair
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// Check if character is an opening bracket
bool isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

// Check if character is a closing bracket
bool isClosingBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

/**
 * Determine if the input string is valid
 * 
 * @param s: Input string containing only '()[]{}'
 * @param sLength: Length of the string
 * @return: true if valid, false otherwise
 */
bool isValid(char* s, int sLength) {
    if (s == NULL || sLength == 0) {
        return true;  // Empty string is considered valid
    }
    
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; i < sLength; i++) {
        char c = s[i];
        
        if (isOpeningBracket(c)) {
            // Push opening bracket onto stack
            if (!push(&stack, c)) {
                return false;  // Stack overflow
            }
        } else if (isClosingBracket(c)) {
            // Check if stack is empty (no matching opening bracket)
            if (isEmpty(&stack)) {
                return false;
            }
            
            // Check if top of stack matches current closing bracket
            char top = peek(&stack);
            if (isMatchingPair(top, c)) {
                pop(&stack);
            } else {
                return false;  // Mismatched brackets
            }
        }
        // Ignore any other characters (though problem states only parentheses)
    }
    
    // String is valid if stack is empty (all brackets matched)
    return isEmpty(&stack);
}

/**
 * Test function with the provided examples
 */
int main() {
    printf("Valid Parentheses Problem\n");
    printf("========================\n\n");
    
    // Example 1: s = "()"
    char* s1 = "()";
    bool result1 = isValid(s1, strlen(s1));
    printf("Example 1:\n");
    printf("Input: s = \"%s\"\n", s1);
    printf("Output: %s\n\n", result1 ? "true" : "false");
    
    // Example 2: s = "()[]{}"
    char* s2 = "()[]{}";
    bool result2 = isValid(s2, strlen(s2));
    printf("Example 2:\n");
    printf("Input: s = \"%s\"\n", s2);
    printf("Output: %s\n\n", result2 ? "true" : "false");
    
    // Example 3: s = "(]"
    char* s3 = "(]";
    bool result3 = isValid(s3, strlen(s3));
    printf("Example 3:\n");
    printf("Input: s = \"%s\"\n", s3);
    printf("Output: %s\n\n", result3 ? "true" : "false");
    
    // Example 4: s = "([])"
    char* s4 = "([])";
    bool result4 = isValid(s4, strlen(s4));
    printf("Example 4:\n");
    printf("Input: s = \"%s\"\n", s4);
    printf("Output: %s\n\n", result4 ? "true" : "false");
    
    // Example 5: s = "([)]"
    char* s5 = "([)]";
    bool result5 = isValid(s5, strlen(s5));
    printf("Example 5:\n");
    printf("Input: s = \"%s\"\n", s5);
    printf("Output: %s\n\n", result5 ? "true" : "false");
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test: Empty string
    char* s6 = "";
    bool result6 = isValid(s6, strlen(s6));
    printf("Empty string: \"%s\" -> %s\n", s6, result6 ? "true" : "false");
    
    // Test: Single opening bracket
    char* s7 = "(";
    bool result7 = isValid(s7, strlen(s7));
    printf("Single '(': \"%s\" -> %s\n", s7, result7 ? "true" : "false");
    
    // Test: All opening brackets
    char* s8 = "(((";
    bool result8 = isValid(s8, strlen(s8));
    printf("All opening: \"%s\" -> %s\n", s8, result8 ? "true" : "false");
    
    // Test: All closing brackets
    char* s9 = ")))";
    bool result9 = isValid(s9, strlen(s9));
    printf("All closing: \"%s\" -> %s\n", s9, result9 ? "true" : "false");
    
    // Test: Alternating valid brackets
    char* s10 = "()()()";
    bool result10 = isValid(s10, strlen(s10));
    printf("Alternating: \"%s\" -> %s\n", s10, result10 ? "true" : "false");
    
    // Test: Deeply nested
    char* s11 = "((((()))))";
    bool result11 = isValid(s11, strlen(s11));
    printf("Deeply nested: \"%s\" -> %s\n", s11, result11 ? "true" : "false");
    
    // Test: Complex nested
    char* s12 = "({[()]})";
    bool result12 = isValid(s12, strlen(s12));
    printf("Complex nested: \"%s\" -> %s\n", s12, result12 ? "true" : "false");
    
    return 0;
}

