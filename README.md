# PRNG Benchmarks

Simple benchmarks for the common C++ Pseudo Random Number Generators.


## Results

On my laptop with Intel(R) Core(TM) i5-4210H CPU @ 2.90GHz, clang++ 8.0.1:

![](benchmarks-clang++.png)

Smaller time means faster, but does not necessarily mean better. You should
also consider the period of each generator and and its "randomness quality".


## Compilation and usage

Requirements:
- a C++ compiler that implements C++17
- boost libraries 1.69 (or newer?)
- make

To compile the code, use the `Makefile`:

``` bash
$ make
$ ./benchmarks
```

The plotting script uses python3, matplotlib and pandas. The simplest way to run it is with the Makefile:
``` bash
$ make plots
```


## Contributing

Fork this repo, make your changes and open a Pull Request :)

Some ideas:
- benchmark more generators
- improve the plotting script
- add another benchmark


## License

This project is licensed under GLP3 License - see the [LICENSE](LICENSE) file
for more details.