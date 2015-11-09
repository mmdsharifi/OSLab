# OSLab
Operation Systems Lab Exercises
###EXR 02:

```
Shared Memory
1 Server create a data and 10 client use it.
```

#Quick use
in linux terminal cd to project path:
* first Run Producer program
```{r, engine='bash', count_lines}
g++ Producer.c -o Producer.o
./Producer.o
```
*  run client :

```{r, engine='bash', count_lines}
g++ -std=c++0x -pthread -o Consumer.o Consumer.c

./Consumer.o
```
