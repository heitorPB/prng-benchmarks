import click

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


@click.command()
@click.argument('infile', type=click.File('r'))
@click.option('--output', type=click.File('w'), default="results",
              help="Name of output file")
def main(infile, output):
    data = pd.read_csv(infile, sep="; ")
    fig, axes = plt.subplots()

    benchmarks = data['benchmark_name'].unique()
    PRNGs = data['PRNG'].unique()

    # coordinates of each bar group
    x = np.arange(len(PRNGs))
    width = 1 / (len(benchmarks) + 1.5)

    for i, benchmark in enumerate(benchmarks):
        y = data.loc[data['benchmark_name'] == benchmark]['average (ns)']
        dy = data.loc[data['benchmark_name'] == benchmark]['variance (ns^2)']
        bars = axes.bar(x + i*width, y, yerr=dy, width=width, label=benchmark)
        # hopefully the order of the PRNGs is not changed.

    axes.set_title("PRNG benchmarks")
    axes.set_ylabel("Time (ns)")
    axes.grid(which="both", axis="y", alpha=.3, linestyle="--")
    axes.set_xticks(x + width*(len(benchmarks)-1)/2)
    axes.set_xticklabels(PRNGs)
    axes.tick_params(axis='x', labelrotation=90)
    axes.set_yscale('log')
    axes.set_ylim(1e-0)
    axes.legend()

    #plt.tight_layout(pad=0, w_pad=0, h_pad=0)
    plt.show()

    # TODO
    # - save png
    # - one png for each benchmark


if __name__ == '__main__':
    main()
