#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
    --track-origins=yes --trace-children=yes --suppressions=readline.supp "$@"