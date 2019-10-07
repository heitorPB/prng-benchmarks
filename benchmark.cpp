/*
 * PRNG Benchmarks
 * Copyright (C) 2019 Heitor Pascoal de Bittencourt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/taus88.hpp>


/* TODO
 *
 * Separate in main.cpp and benchmark.{cpp,h}
 * Add docs. Sphinx + Doxygen?
 */

template<class PRNG>
std::chrono::duration<double, std::nano>
naive_benchmark_(PRNG& generator, int count = 1<<10)
{
	std::uint_fast64_t number;

	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < count; i++)
		number = generator();
	auto stop = std::chrono::high_resolution_clock::now();

	number += 1; // just to get rid of -Wunused warning

	auto duration = std::chrono::duration<double, std::nano>(stop - start);
	duration /= count;

	return duration;
}


template<class PRNG>
std::vector<std::chrono::duration<double, std::nano>>
naive_benchmark(PRNG& generator, int count = 1<<14)
{
	std::vector<std::chrono::duration<double, std::nano>> durations;

	for(int i = 0; i < count; i++)
		durations.push_back(naive_benchmark_(generator));

	return durations;
}


template<class PRNG>
std::chrono::duration<double, std::nano>
uniform_int_distribution_(PRNG& generator, int count = 1<<10)
{
	std::uint_fast64_t number;
	std::uniform_int_distribution<int> dist(0, 1<<20);

	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < count; i++)
		number = dist(generator);
	auto stop = std::chrono::high_resolution_clock::now();

	number += 1; // just to get rid of -Wunused warning

	auto duration = std::chrono::duration<double, std::nano>(stop - start);
	duration /= count;

	return duration;
}


template<class PRNG>
std::vector<std::chrono::duration<double, std::nano>>
uniform_int_distribution_benchmark(PRNG& generator, int count = 1<<14)
{
	std::vector<std::chrono::duration<double, std::nano>> durations;

	for(int i = 0; i < count; i++)
		durations.push_back(uniform_int_distribution_(generator));

	return durations;
}



void print_statistics(std::string name,
                      std::string benchmark_name,
                      std::vector<std::chrono::duration<double, std::nano>>& timings)
{
	std::chrono::duration<double, std::nano> zero = std::chrono::nanoseconds(0);

	auto sum = std::accumulate(timings.begin(), timings.end(), zero);
	auto average = sum.count() / timings.size();

	double squares = 0;
	for (auto t: timings)
		squares += t.count() * t.count();

	double variance = squares/timings.size() - average*average;
	double std_deviation = std::sqrt(variance);

	std::cout << name << "; "
	          << benchmark_name << "; "
	          << average << "; "
	          << std_deviation  << "; "
	          << variance << std::endl;
}


template<class PRNG>
void benchmarks(PRNG& generator, std::string name)
{
	auto naive_timings = naive_benchmark(generator);
	print_statistics(name, "Naive benchmark", naive_timings);

	auto int_dist = uniform_int_distribution_benchmark(generator);
	print_statistics(name, "std::uniform_int_distribution", int_dist);
}


int main()
{
	std::cout << "PRNG; benchmark_name; average (ns); deviation (ns); variance (ns^2)"
	          << std::endl;

	//benchmarks(std::rand, "std::rand - C library");

	std::minstd_rand minst;
	benchmarks(minst, "std::minst_rand");

	std::mt19937 mersenne;
	benchmarks(mersenne, "std::mt19937");

	std::mt19937_64 mersenne64;
	benchmarks(mersenne64, "std::mt19937_64");

	std::ranlux24_base ranlux24_base;
	benchmarks(ranlux24_base, "std::ranlux24_base");

	std::ranlux48_base ranlux48_base;
	benchmarks(ranlux48_base, "std::ranlux48_base");

	std::ranlux24 ranlux24;
	benchmarks(ranlux24, "std::ranlux24");

	std::ranlux48 ranlux48;
	benchmarks(ranlux48, "std::ranlux48");

	std::knuth_b knuth_b;
	benchmarks(knuth_b, "std::knuth_b");

	boost::random::mt19937 b_mt19937;
	benchmarks(b_mt19937, "boost::random::mt19937");

	boost::random::mt19937_64 b_mt19937_64;
	benchmarks(b_mt19937_64, "boost::random::mt19937_64");

	boost::random::mt11213b b_mt11213b;
	benchmarks(b_mt11213b, "boost::random::mt1213b");

	boost::random::taus88 b_taus;
	benchmarks(b_taus, "boost::random::taus88");

	// TODO add more boost generators
	// https://www.boost.org/doc/libs/1_71_0/doc/html/boost_random/reference.html#boost_random.reference.generators
	return 0;
}