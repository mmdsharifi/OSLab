# OSLab
Operation Systems Lab Exercises 
###EXR 01:
```
p1 > pipe > p2 > FIFO > P3
hello > > HELLO >  > HeLlo
```
#Quick use
in linux terminal cd to project path:
* first Run client program
```{r, engine='bash', count_lines}
g++ fifoClient.c -o fifoClient.o 
./fifoClient.o 
```
* After run client, we run server FIFO:

```{r, engine='bash', count_lines}
g++ pipe-ServerFIFO.c -o pipe-ServerFIFO.o
./pipe-ServerFIFO.o
```
