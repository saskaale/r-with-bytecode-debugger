686,688c694
< #define BCODE_CONSTS(x) ( TYPEOF(CDR(x))==LISTSXP ? CADR(x) : CDR(x))
< #define BCODE_HAS_TMPBREAKPOINTS(x) ( TYPEOF(CDR(x))==LISTSXP )
< #define BCODE_CODE_UNBREAKPOINT(x) ( BCODE_HAS_TMPBREAKPOINTS(x) ? CDDR(x) : R_NilValue )
---
> #define BCODE_CONSTS(x) CDR(x)
991,992d993
< void R_printCurrentBCbody(SEXP body, void* pc, Rboolean peephole, int verbose);
< void R_printCurrentBCstack(void* fnbase, void* top);
998,1000d998
< void Rf_breakOnNextBCInst(SEXP body, void** pc, SEXP* tmplist);
< void R_RemoveBCtmpBreakpoints(SEXP body, SEXP tmplist);
< void Rf_restoreAllBrowserBreakpoints(SEXP body, SEXP tmplist);
1407d1404
< SEXP	 Rf_lang7(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
