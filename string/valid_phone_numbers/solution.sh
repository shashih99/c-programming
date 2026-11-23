#!/bin/bash
# 193. Valid Phone Numbers — the one-liner LeetCode expects.
# A valid line is either "xxx-xxx-xxxx" or "(xxx) xxx-xxxx" and nothing else.
grep -E '^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$' "${1:-file.txt}"
