# OSLab
Operation Systems Lab Exercises 
EXR 01:
p1 > pipe > p2 > FIFO > P3
hello > > HELLO >  > HeLlo
#quic use
in linux terminal cd to project path:
* first Run client program
```
g++ fifoClient.c -o fifoClient.o 
./fifoClient.o 
```
* After run client, we run server FIFO:

```
g++ pipe-ServerFIFO.c -o pipe-ServerFIFO.o
./pipe-ServerFIFO.o
```
