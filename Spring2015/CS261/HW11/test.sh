#!/bin/bash
./sort | ./bert/cache -s4096 -b1
./sort | ./bert/cache -s8192 -b1
./sort | ./bert/cache -s16384 -b1
./sort | ./bert/cache -s32768 -b1
./sort | ./bert/cache -s65536 -b1
./sort | ./bert/cache -s4096 -b2
./sort | ./bert/cache -s8192 -b2
./sort | ./bert/cache -s16384 -b2
./sort | ./bert/cache -s32768 -b2
./sort | ./bert/cache -s65536 -b2
./sort | ./bert/cache -s4096 -b4
./sort | ./bert/cache -s8192 -b4
./sort | ./bert/cache -s16384 -b4
./sort | ./bert/cache -s32768 -b4
./sort | ./bert/cache -s65536 -b4
./sort | ./bert/cache -s4096 -b8
./sort | ./bert/cache -s8192 -b8
./sort | ./bert/cache -s16384 -b8
./sort | ./bert/cache -s32768 -b8
./sort | ./bert/cache -s65536 -b8