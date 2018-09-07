gcc -o m64_int.out -D INT -D USE_UNI *.c
gcc -o m64_float.out -D FLOAT -D USE_UNI *.c
gcc -m32 -o m32_float.out -D FLOAT -D USE_UNI *.c
gcc -m32 -o m32_int.out -D INT -D USE_UNI *.c
./m64_int.out
./m64_float.out
./m32_int.out
./m32_float.out
