# minishell
:(
valgrind -s -q --suppressions=readline.supp --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --show-below-main=no ./minishell