#define INST_R(x) { _inst_p = &(x); cout.write((const char *)(&_inst_p), sizeof _inst_p); }
#define INST_W(x) { _inst_p = &(x); cout.write((const char *)(&_inst_p), sizeof _inst_p); }
void *_inst_p;    
