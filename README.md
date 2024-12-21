
## Getting started

- Make sure you have python3 installed
- Use this for creating the venv: [https://code.visualstudio.com/docs/python/environments](https://code.visualstudio.com/docs/python/environments)

Open a terminal in VSCode for this project and then:

```
source .venv/bin/activate
```

```
pip3 install -r ./requirements.txt
```

Once the installation is complete, run the following command to confirm the installation:

```
python3 -c "import flask; print(flask.__version__)"
```

## Running the app

- Follow VSCode's guide to debugging/running a Flask app locally: [https://code.visualstudio.com/docs/python/tutorial-flask#_run-the-app-in-the-debugger](https://code.visualstudio.com/docs/python/tutorial-flask#_run-the-app-in-the-debugger)

## About the algorithm

to start, we generate a binary structure that maps each dictionary word to a 32-bit binary representation of itself:

```
tac (example word from dict)
19 0 2
00000010000000000000000000000101
```

with the given letters and the required letter we create a solution cypher:

```
cats (letters given, c is the required letter)
2 0 18 19 (n-th bit positions starting from right to left)
00000011000000000000000000000101

!cats
11111100111111111111111111111010
```

compare the solution cypher to each word in our binary structure we generated with a two step verification process:

- tac && !cats = 0
- then check if the position at the required bit is 1

usage to generate the binary:

```
gcc struct.c
./a.out
```

note: the binary structure is created once! we re-use it against any combination of words and required letter provided.

If you want to just solve it locally, you can use my separate C program.

```
gcc struct.c
./a.out
gcc solve.c cats c
./a.out2
```
