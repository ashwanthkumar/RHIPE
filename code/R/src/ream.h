#ifndef	__ream_h
#define	__ream_h

#include <iostream>
#include <vector>
#include <map>

#include <google/protobuf/stubs/common.h>
#include <rexp.pb.h>

#include <stdint.h>
#include <sys/types.h>	
#include <sys/time.h>	
#include <time.h>	
#include <errno.h>
#include <fcntl.h>	
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
using namespace std;

#define R_NO_REMAP
#define R_INTERFACE_PTRS 1
#define CSTACK_DEFNS 1 

#include <Rversion.h>
#include <R.h>
#include <Rdefines.h>
/* #include <Rinternals.h> */
#include <Rinterface.h>
#include <Rembedded.h>
#include <R_ext/Boolean.h>
#include <R_ext/Parse.h>
#include <R_ext/Rdynload.h>
extern map<string, vector<string> > map_output_buffer;
extern uint32_t spill_size;
extern uint32_t total_count;
/* extern SEXP comb_pre_red,comb_do_red,comb_post_red; */
extern  char* REDUCESETUP;
extern  char* REDUCEPREKEY;
extern  char* REDUCE;
extern  char* REDUCEPOSTKEY ;
extern  char* REDUCECLEANUP;
extern bool combiner_inplace;

#define DLEVEL -9

#ifdef FILEREADER
extern FILE *FILEIN;
#endif

#ifdef RHIPEDEBUG
#define LOGG(...) logg(__VA_ARGS__)
#else
#define LOGG(...)
#endif

#ifdef USETIMER
#include "time.h"
#include <sys/time.h>
extern long int collect_total;
extern long int collect_buffer_total;
extern long int time_in_reval;
extern long int collect_spill_total;
extern long int time_in_reduce_reval;
SEXP TIMER_REDUCE_R_tryEval(SEXP, SEXP, int *);
SEXP TIMER_R_tryEval(SEXP, SEXP, int *);

#define WRAP_R_EVAL TIMER_R_tryEval
#define WRAP_R_EVAL_FOR_REDUCE TIMER_REDUCE_R_tryEval
#else
#define WRAP_R_EVAL R_tryEval
#define WRAP_R_EVAL_FOR_REDUCE R_tryEval
#endif

/* extern void (*ptr_R_ShowMessage)(const char *); */
/* extern void (*ptr_R_WriteConsole)(const char *, int); */
/* extern int  (*ptr_R_ReadConsole)(char *, unsigned char *, int, int); */
/* extern void (*ptr_R_WriteConsoleEx)(const char *, int , int ); */
/* extern FILE* R_Consolefile; */
/* extern FILE* R_Outputfile;  */
extern FILE* LOG;
extern int _STATE_;
SEXP rexpress(const char*);
void rexp2message(REXP *, const SEXP);
void fill_rexp(REXP *, const SEXP );
SEXP message2rexp(const REXP&);






/*********
 * Utility
 *********/
/* void CaptureLog(LogLevel , const char* , int ,const string& ) ; */
/* void CaptureLogInLibrary(LogLevel , const char* , int ,const string& ) ; */

uint32_t nlz(const int64_t);
uint32_t getVIntSize(const int64_t) ;
uint32_t isNegativeVInt(const int8_t);
uint32_t decodeVIntSize(const int8_t);
uint32_t reverseUInt (uint32_t );
void writeVInt64ToFileDescriptor( int64_t , FILE* );
int64_t readVInt64FromFileDescriptor(FILE* );
int64_t readVInt64FromFD(int );

int32_t readJavaInt(FILE* );

/************************
 * Signal Handler Related
 ************************/
typedef void Sigfunc(int);
Sigfunc *signal(int , Sigfunc *);
Sigfunc *Signal(int , Sigfunc *);
void sigHandler(int );


/*************
 ** Tests
 ************/
void doTest_Serialize2String(char *,const int );
void doTest_Serialize2Char(char *,const int);
void doTest_Serialize2FD(char *,const int );



/*****************
 ** File Pointers
 ****************/
struct Streams {
  FILE* BSTDERR,*BSTDIN,*BSTDOUT;
  int NBSTDERR,NBSTDIN,NBSTDOUT;
};
extern Streams *CMMNC;
int setup_stream(Streams *);


/*****************
 ** writen,Readn
 ****************/
ssize_t readn(int , void *, size_t );
ssize_t Readn(int , void *, size_t);
ssize_t writen(int , const void *, int );
void do_unser(void);
/******************
 ** Map & Reduce
 *****************/
const int mapper_run2(void);
const int mapper_run(void);
const int mapper_setup(void);
const int reducer_run(void);
const int reducer_setup(void);

/*****************
 ** Displays
 *****************/
void Re_ShowMessage(const char*);
void Re_WriteConsoleEx(const char *, int , int );
void merror(const char *, ...);
void mmessage(char *fmt, ...);
void logg(int , const char *, ...);

/******************
 ** Counter/Collect
 *****************/
SEXP counter(SEXP );
SEXP status(SEXP );
SEXP collect(SEXP ,SEXP );
SEXP collect_buffer(SEXP ,SEXP );
SEXP readFromHadoop(const uint32_t,int* );
SEXP readFromMem(void * ,uint32_t );
SEXP persUnser(SEXP);
SEXP dbgstr(SEXP);
void spill_to_reducer(void);
void mcount(char *,char*, uint32_t);


extern  R_CallMethodDef callMethods[];



#endif
