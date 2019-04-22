cd ..
make
cd bin/
valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./main