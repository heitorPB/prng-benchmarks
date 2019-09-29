import click
import matplotlib.pyplot as plt
import pandas as pd


@click.command()
@click.argument('infile', type=click.File('r'))
@click.option('--output', type=click.File('w'), default="results",
              help="Name of output file")
def main(infile, output):
    data = pd.read_csv(infile, sep="; ")#, engine="python")
    ax = data.plot.bar(x="PRNG", y="average (ns)",
                       yerr="deviation (ns)",
                       logy=True)
    ax.set_ylabel("Time (ns)")
    ax.set_title("PRNG Benchmark")
    ax.grid(which="both", axis="y", alpha=.2, linestyle="--")
    plt.show()


if __name__ == '__main__':
    main()
