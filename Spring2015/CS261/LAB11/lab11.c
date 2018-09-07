long proc(long  a1, long  *a1p,
          int   a2, int   *a2p,
          short a3, short *a3p,
          char  a4, char  *a4p,
          long	x, 	long *resultp) {
	  *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;

    if (x <= 1)
        *resultp = 1;
    else {
        long nresult;
        proc(a1, a1p, a2, a2p, a3, a3p, a4, a4p, x-1, &nresult);
        *resultp = (a1+a2)*(a3-a4);
    } 

    return *resultp;
}


long main() {
	long x1 = 1;
	int x2 = 2;
	short x3 = 3; 
	char x4 = 4;
	long x = 5;
	long result;

	proc(x1, &x1, x2, &x2, x3, &x3, x4, &x4, x, &result); 
	return result;
}
