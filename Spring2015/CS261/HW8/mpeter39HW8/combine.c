/****************************
| Name1:Maxwell Petersen    |
| NetID1: mpeter39          |
****************************/
#include "combine.h"

/* Combining functions */

char inner1_descr[] = "inner1: original loop no unrolling";
/* $begin inner1 */
void inner1(vec_ptr u, vec_ptr v, data_t *dest)
{
    long int i;
    int length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    for (i=0;i<length;i++){
        sum = sum + udata[i] * vdata[i];
    }
    *dest = sum;
}


char inner2_descr[] = "inner2: unroll 2x and 2 accumulators"; 
/* $begin inner2 */
void inner2(vec_ptr u, vec_ptr v, data_t *dest)
{
    long int i;
    int length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    for (i=0;i<length;i+=2){
        sum += udata[i] * vdata[i];
        sum += udata[i+1] * vdata[i+1];
    }
    for (i; i<length; i++){

        sum += udata[i] * vdata[i];

    }

    *dest = sum;
}


char inner4_descr[] = "inner4: unroll 4x and 4 accumulators"; 
/* $begin inner4 */
void inner4(vec_ptr u, vec_ptr v, data_t *dest)
{
    long int i;
    int length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    for (i=0;i<length;i+= 4){
        sum = sum + udata[i] * vdata[i];
        sum = sum + udata[i + 1] * vdata[i + 1];
        sum = sum + udata[i + 2] * vdata[i + 2];
        sum = sum + udata[i + 3] * vdata[i + 3];
    }

    for (i; i<length; i++){

        sum += udata[i] * vdata[i];

    }

    *dest = sum;
}

char inner8_descr[] = "inner8: unroll 8x and 8 accumulators"; 
/* $begin inner8 */
void inner8(vec_ptr u, vec_ptr v, data_t *dest)
{
    long int i;
    int length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    for (i=0;i<length;i+=8){
        sum = sum + udata[i] * vdata[i];
        sum = sum + udata[i + 1] * vdata[i + 1];
        sum = sum + udata[i + 2] * vdata[i + 2];
        sum = sum + udata[i + 3] * vdata[i + 3];
        sum = sum + udata[i + 4] * vdata[i + 4];
        sum = sum + udata[i + 5] * vdata[i + 5];
        sum = sum + udata[i + 6] * vdata[i + 6];
        sum = sum + udata[i + 7] * vdata[i + 7];
    }

    for (i; i<length; i++){

        sum += udata[i] * vdata[i];

    }
    
    *dest = sum;
}




void register_combiners(void)
{
    add_combiner(inner1, inner1, inner1_descr);
    add_combiner(inner2, inner1, inner2_descr);
    add_combiner(inner4, inner1, inner4_descr);
    add_combiner(inner8, inner1, inner8_descr);
}

/****************************************************************************************************\
| Results:                                                                                           |
| -------|---------------------|---------------------|------------------------|----------------------|
|        | INT ORIG |  INT 2X  |  INT 4X  |  INT 8X  | FLOAT ORIG | FLOAT 2X  | FLOAT 4X  | FLOAT 8X |
| -------|---------------------|---------------------|------------------------|----------------------|
| 32 BIT | 8.52 CPE | 6.01 CPE | 6.07 CPE | 6.00 CPE | 10.00 CPE  | 10.00 CPE | 10.02 CPE | 9.98 CPE |
| -------|---------------------|---------------------|------------------------|----------------------|
| 64 BIT | 8.05 CPE | 6.03 CPE | 6.04 CPE | 6.00 CPE | 10.01 CPE  | 10.01 CPE | 10.03 CPE | 9.96 CPE |
| -------|---------------------|---------------------|------------------------|----------------------|
|                                                                                                    |
| Extra Problems:                                                                                    |
| 1.How much benifit was seen going from the original code to your modified code?                    |
|        For the intager data type the improvements were very noticable because every step up in     |
|        loop unrolling decteased the CPE down to 6.XX from 8.XX but slowed to hardly a noticable    |
|        difference from the varying loop unrolls (2x 4x 8x). The float data type is seen to have    |
|        little to no improvements as the loop unrolls increased.                                    |
|                                                                                                    |
| 2.What limits the improvements as the amount of loop unrolling increases?                          |
|        The amount of work that is done in the loop itself before actually looping around quickly   |
|        overcomes the amount of work saved by increasing what is done in the loop.                  |
|                                                                                                    |
\****************************************************************************************************/

