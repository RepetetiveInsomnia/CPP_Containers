GCC=g++
SRC=./source
TEST_SRC=./tests/all_tests.cc
CFLAGS=-Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest -lgcov -lm
GCOVFLAGS=--coverage
OS = $(shell uname)


all: clean test

clean:
	rm -rf *.o *.a *.so *.out *.info *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test:  clean
	$(GCC) $(CFLAGS) $(TEST_SRC) -lgtest -pthread
	./a.out

gcov_report: clean

	$(GCC) $(CFLAGS) $(GCOVFLAGS) $(TEST_SRC) -lgtest -pthread -o report.out
	./report.out
	lcov -t "report" -o report.info --no-external -c -d .
	genhtml -o ./report report.info
	rm -rf *.gcda *.gcno *.info

docker-build-run : clean
	docker build -t s21_containers . -f ./docker/Dockerfile
	docker run -d s21_containers
docker-artifacts-copy:
	docker run -d s21_containers
	docker cp $(shell docker ps -alq):/project/report/ .
	docker stop $(shell docker ps -alq)
docker-tests: docker-build-run docker-artifacts-copy

check:
	clang-format -style="{BasedOnStyle: Google}" -i ./tests/all_tests.cc ./source/*.h ./*.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config ./tests/all_tests.cc ./source/*.h ./*.h
ifeq ($(OS), Darwin)
	leaks --atExit -- ./*.out
else
	touch valgrind.txt
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./*.out > valgrind.txt
	mv valgrind.txt ./report
endif