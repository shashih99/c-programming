#define _POSIX_C_SOURCE 200809L  /* for getline() under -std=c11 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * 193. Valid Phone Numbers
 *
 * Given a text file file.txt that contains a list of phone numbers (one per
 * line), print all valid phone numbers.
 *
 * A valid phone number must appear in one of two formats:
 *   (xxx) xxx-xxxx   or   xxx-xxx-xxxx      (x means a digit)
 *
 * Each line has no leading or trailing white space.
 *
 * Algorithm (template matching):
 * 1. Describe each valid format as a template where 'd' stands for "any digit"
 *    and every other character must match literally.
 * 2. A line is valid if it has exactly the template's length and every
 *    position matches the template.
 * 3. Read the file line by line and print the lines that match either
 *    template.
 *
 * Time Complexity: O(total characters in the file)
 * Space Complexity: O(longest line) - the getline buffer
 */

static const char* const FORMATS[] = {
    "ddd-ddd-dddd",
    "(ddd) ddd-dddd",
};
#define NUM_FORMATS (sizeof(FORMATS) / sizeof(FORMATS[0]))

/**
 * Check whether s matches template fmt exactly ('d' = any digit).
 */
static bool matchesFormat(const char* s, const char* fmt) {
    for (; *fmt; s++, fmt++) {
        if (*s == '\0') {
            return false;  // s is shorter than the template
        }
        if (*fmt == 'd') {
            // cast to unsigned char: passing a negative char to ctype is undefined
            if (!isdigit((unsigned char)*s)) {
                return false;
            }
        } else if (*s != *fmt) {
            return false;
        }
    }
    return *s == '\0';  // reject anything longer than the template
}

/**
 * @param s: one line, without its trailing newline
 * @return: true if s is in one of the valid phone number formats
 */
bool isValidPhoneNumber(const char* s) {
    for (size_t i = 0; i < NUM_FORMATS; i++) {
        if (matchesFormat(s, FORMATS[i])) {
            return true;
        }
    }
    return false;
}

/**
 * Print every valid phone number in the file (the actual LeetCode task).
 * @return: 0 on success, -1 if the file could not be opened
 */
int printValidPhoneNumbers(const char* path) {
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        perror(path);
        return -1;
    }

    char* line = NULL;
    size_t cap = 0;
    ssize_t len;
    while ((len = getline(&line, &cap, fp)) != -1) {
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (isValidPhoneNumber(line)) {
            printf("%s\n", line);
        }
    }

    free(line);
    fclose(fp);
    return 0;
}

/**
 * Run one test case and report PASS/FAIL against the expected result
 */
void runTest(const char* name, const char* s, bool expected) {
    bool result = isValidPhoneNumber(s);
    printf("%-32s \"%s\" -> %s (expected %s) %s\n",
           name, s,
           result ? "valid" : "invalid",
           expected ? "valid" : "invalid",
           result == expected ? "PASS" : "FAIL");
}

int main(int argc, char* argv[]) {
    const char* path = argc > 1 ? argv[1] : "file.txt";

    printf("Valid Phone Numbers\n");
    printf("===================\n\n");

    printf("Output for %s:\n", path);
    if (printValidPhoneNumbers(path) != 0) {
        return 1;
    }

    printf("\nLine Checks:\n\n");

    // LeetCode example
    runTest("Example: dashes", "987-123-4567", true);
    runTest("Example: spaces", "123 456 7890", false);
    runTest("Example: parentheses", "(123) 456-7890", true);

    // Edge cases
    runTest("Missing space after ')'", "(123)456-7890", false);
    runTest("Mixed formats", "(123)-456-7890", false);
    runTest("Too short", "123-45-6789", false);
    runTest("Too long", "123-456-78901", false);
    runTest("Trailing space", "123-456-7890 ", false);
    runTest("Leading space", " 123-456-7890", false);
    runTest("Letter instead of digit", "12a-456-7890", false);
    runTest("No separators", "1234567890", false);
    runTest("Empty line", "", false);

    return 0;
}
