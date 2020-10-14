#!/usr/bin/env bash

COMPILERS=("g++" "clang++")

for compiler in ${COMPILERS[@]}
do
	echo -e "Compiling with $compiler"
	make clean
	CXX=${compiler} make

	echo -e "Running code"
	./benchmark > results-${compiler}.csv

	echo -e "Ploting"
	python plot_results.py results-${compiler}.csv
	mv benchmark.pdf benchmarks-${compiler}.pdf
	convert -density 300 benchmarks-${compiler}.pdf benchmarks-${compiler}.png

	echo -e "\n"
done