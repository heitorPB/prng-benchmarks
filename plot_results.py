import click

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


@click.command()
@click.argument('infile', type=click.File('r'))
def main(infile):
    data = pd.read_csv(infile, sep="; ", engine='python')
    fig, axes = plt.subplots(figsize=(16,9))

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
    axes.set_ylim(0.5, 400) # in nanoseconds
    axes.legend()

    fig.savefig(f'benchmark.pdf',
                bbox_inches='tight')


if __name__ == '__main__':
    main()
