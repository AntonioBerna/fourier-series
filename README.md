# fourier-series

![GitHub License](https://img.shields.io/github/license/antonioberna/fourier-series)
![GitHub repo size](https://img.shields.io/github/repo-size/antonioberna/fourier-series)
![GitHub Created At](https://img.shields.io/github/created-at/antonioberna/fourier-series)

## demo

https://github.com/AntonioBerna/fourier-series/assets/60107274/16c3fe8f-530a-4e4e-9533-81c4f845d15c

> [!NOTE]
> For more information about the Fourier series click [here](https://en.wikipedia.org/wiki/Fourier_series#Convergence). While, for more information about the Gibbs phenomenon click [here](https://en.wikipedia.org/wiki/Gibbs_phenomenon).

## mini docs

To use my software you will first have to clone the repository using the following command:

```
git clone https://github.com/AntonioBerna/fourier-series.git
```

now using the `cd fourier-series/` command first and then the `ls` command you will notice the presence of the `Makefile` file. You will need this file to compile the program, and in particular if you want to compile the program  you can use the following command:

```
make
```

If you want to clean the program you can use the following command:

```
make clean
```

> [!NOTE]
> For more information you can directly consult the `Makefile` file with your favorite text editor.

Finally you can run the program using the following command:

```
make run
```

That's it.

Below is a table of supported commands:

| Command                           | Description                     |
| :---:                             | :---:                           |
| <kbd>UP</kbd>                     | Increase the $n$ terms          |
| <kbd>DOWN</kbd>                   | Decrease the $n$ terms          |
| <kbd>LEFT</kbd>, <kbd>RIGHT</kbd> | Change wave of Gibbs phenomenon |