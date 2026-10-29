# c-programming

C programming exercises organized by concept. Each folder contains self-contained problems with source, `Makefile`, and `README`.

## Structure

| Folder | Concept | Problems |
|--------|---------|----------|
| [array/](array/) | Array manipulation, two pointers | `merge_sorted_array`, `remove_element`, `remove_duplicate_arr`, `two_sum`, `plus_one`, `pascal_triangle`, `pascal_triangle_ii` |
| [linked_list/](linked_list/) | Singly linked lists | `merge_two_sorted_lists`, `remove_duplicates_sorted_list` |
| [tree/](tree/) | Binary trees | `binary_tree_traversals`, `same_tree`, `minimum_depth_of_binary_tree`, `path_sum` |
| [stack/](stack/) | Stack | `valid_parentheses` |
| [binary_search/](binary_search/) | Binary search | `sqrt_x`, `search_insert_position` |
| [dynamic_programming/](dynamic_programming/) | Dynamic programming | `climbing_stairs` |
| [string/](string/) | String processing | `add_binary`, `longest_common_prefix`, `length_of_last_word`, `find_first_occurrence`, `roman_to_integer` |
| [math/](math/) | Number / math | `palindrom` |

## Build and run

From any problem directory:

```bash
make
make run
```

## Debug (F5)

Debugging always uses the **currently open `.c` file** — no per-problem launch config needed.

1. Open the problem `.c` file (e.g. `array/pascal_triangle_ii/pascal_triangle_ii.c`)
2. In **Run and Debug**, select **Debug current program** (default)
3. Press `F5`

That runs `make debug` in the file’s folder, then starts gdb on:

`${fileDirname}/build/Debug/${fileBasenameNoExtension}`
