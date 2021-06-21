# Monte Carlo MPI

PI computation employing Monte Carlo method with MPI.

## Requirements

Scripts written in linux environment (Ubuntu **18.x** and **20.x**).

- gcc compiler.
```bash
$> sudo apt install gcc 
```
- build-essential package.
```bash
$> sudo apt install build-essential 
```
- MPI
```bash
$> sudo apt update
$> sudo apt install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi-dev
```
- make.
```bash
$> sudo apt install make 
```

## How to build

- Run make.
```bash
$> make
```
- Run app.
```bash
$> make run
```

## Authors
- David Costa
    - [ds.costa@unesp.br](mailto:ds.costa@unesp.br)
- Murilo Carvalho 
    - [murilo.ignacio@unesp.br](mailto:murilo.ignacio@unesp.br)

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the [LICENSE](LICENSE) file for more details.