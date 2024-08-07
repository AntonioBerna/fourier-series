# fourier-series

## demo

https://github.com/AntonioBerna/fourier-series/assets/60107274/16c3fe8f-530a-4e4e-9533-81c4f845d15c

> [!NOTE]
> For more information about the Fourier series click [here](https://en.wikipedia.org/wiki/Fourier_series#Convergence). While, for more information about the Gibbs phenomenon click [here](https://en.wikipedia.org/wiki/Gibbs_phenomenon).

## mini docs

To use my software you will first have to clone the repository using the following command:

```shell
git clone https://github.com/AntonioBerna/fourier-series.git
```

now using the `cd fourier-series/` command first and then the `ls` command you will notice the presence of the `build.sh` file. You will need this file to compile the program, and in particular you can use one of the following two commands:

```shell
# Release mode
./build.sh

# Debug mode
./build.sh debug

# Clean
./build.sh clean
```

> [!NOTE]
> For more information you can directly consult the `build.sh` file with your favorite text editor.

Finally you can run the program using the following command:

```shell
./build/fourier
```

That's it.
