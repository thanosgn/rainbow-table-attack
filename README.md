# A SHA-3 finalist hash reversal using rainbow tables.

This repo is my solution to a university project in wich I was supposed to reverse a SHA-3 finalist hash function, in order to retrieve a hashed 6-character password.

## Description
The hash function targeted is [BLAKE](https://en.wikipedia.org/wiki/BLAKE_(hash_function)) and more specifically BLAKE-256. The BLAKE-256 C implementation was taken from [this GitHub repo](https://github.com/veorq/BLAKE). A combination of [MurMurHash3](https://en.wikipedia.org/wiki/MurmurHash#MurmurHash3) and [Base64](https://en.wikipedia.org/wiki/Base64) encoding was used as a reduction function. The keyspace of the password the desired password is the following 64-character alphabet: `ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@`

The computed rainbow tables are written in tab separated `.csv` files and contain the start and the end of multiple chains. They have the following form:
```
@QCfu8  0115c9318cf3b7ca742da7a01d0a49c117d629dc1716ca22aae9df05d1e89883
iorjQN  3c438fda70700c32b35d8721794f2e8f13f28d992ac4308dfca764b2402468ed
KqTDyo  c893d71c773bba3521384f9cc3d9d9d6b563da639640463683f735e1e1585561
...
!McSE1  0f38495590921cfc0527ff23dbe51580c4b7e43331ca5e924d969cfeb8dda520```

The `build_rainbow_table` executable is responsible for the building of a rainbow table. It takes an integer argument to indicate the filename of the output `.csv` file. (E.g. `./build_rainbow_table 1` will result in creating `table1.csv`). The `build.sh` bash script takes an integer argument, and invokes `build_rainbow_table` as many times as indicated by the argument  (E.g. `./build.sh 4` will result in creating 4 rainbow tables in 4 `.csv` files, namely `table1.csv`, ..., `table4.csv`).

The `attack.sh` bash script uses `rainbow_attack` executable to crack a ciphertext that is read from the standard input. It takes an integer as an argument indicating the amount of ranbow tables to be used for reverting the ciphertext.  (E.g. `./attack.sh 4` will use `table1.csv`, ..., `table4.csv`).

## Compilation
```
make
```


## Execution
```
./build.sh NUM
./attack.sh NUM
```

There is also a python script for intercepting the ciphertext (hashed password) from a [D-BUS](https://en.wikipedia.org/wiki/D-Bus) signal sent between two services.
