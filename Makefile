CXX=clang++

CXXFLAGS=-std=c++17 -Wall -Wextra -Werror

BINARIES=testBloomFilter

all: ${BINARIES}

tests: ${BINARIES}
	./PA1.out setup.txt input.txt successfulSearch.txt failedSearch.txt remove.txt

clean: 
	/bin/rm -f ${BINARIES} *.o PA1.out

testBloomFilter: testBloomFilter.o bloomFilter.o hashTable.o api.o
	${CXX} ${CXXFLAGS} $^ -o PA1.out 
