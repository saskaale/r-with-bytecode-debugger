893c882
< static void loadNamespace(const char* name)
---
> static void loadCompilerNamespace(void)
898c887
<     PROTECT(arg = mkString(name));
---
>     PROTECT(arg = mkString("compiler"));
901d889
< //    eval(expr, R_BaseEnv);
948c936
<     loadNamespace("compiler");
---
> 	loadCompilerNamespace();
1427c1413
< {
---
> {do
1433,1434c1419,1420
<         loadNamespace("compiler");
<     checkCompilerOptions(new);
---
> 	    loadCompilerNamespace();
> 	checkCompilerOptions(new);
1447c1433
<     loadNamespace("compiler");
---
> 	loadCompilerNamespace();
1489,1723d1474
< #if defined(__GNUC__) && ! defined(BC_PROFILING) && (! defined(NO_THREADED_CODE))
< # define THREADED_CODE
< #endif
<
<
< enum {
<   BCMISMATCH_OP,
<   RETURN_OP,
<   GOTO_OP,
<   BRIFNOT_OP,
<   POP_OP,
<   DUP_OP,
<   PRINTVALUE_OP,
<   STARTLOOPCNTXT_OP,
<   ENDLOOPCNTXT_OP,
<   DOLOOPNEXT_OP,
<   DOLOOPBREAK_OP,
<   STARTFOR_OP,
<   STEPFOR_OP,
<   ENDFOR_OP,
<   SETLOOPVAL_OP,
<   INVISIBLE_OP,
<   LDCONST_OP,
<   LDNULL_OP,
<   LDTRUE_OP,
<   LDFALSE_OP,
<   GETVAR_OP,
<   DDVAL_OP,
<   SETVAR_OP,
<   GETFUN_OP,
<   GETGLOBFUN_OP,
<   GETSYMFUN_OP,
<   GETBUILTIN_OP,
<   GETINTLBUILTIN_OP,
<   CHECKFUN_OP,
<   MAKEPROM_OP,
<   DOMISSING_OP,
<   SETTAG_OP,
<   DODOTS_OP,
<   PUSHARG_OP,
<   PUSHCONSTARG_OP,
<   PUSHNULLARG_OP,
<   PUSHTRUEARG_OP,
<   PUSHFALSEARG_OP,
<   CALL_OP,
<   CALLBUILTIN_OP,
<   CALLSPECIAL_OP,
<   MAKECLOSURE_OP,
<   UMINUS_OP,
<   UPLUS_OP,
<   ADD_OP,
<   SUB_OP,
<   MUL_OP,
<   DIV_OP,
<   EXPT_OP,
<   SQRT_OP,
<   EXP_OP,
<   EQ_OP,
<   NE_OP,
<   LT_OP,
<   LE_OP,
<   GE_OP,
<   GT_OP,
<   AND_OP,
<   OR_OP,
<   NOT_OP,
<   DOTSERR_OP,
<   STARTASSIGN_OP,
<   ENDASSIGN_OP,
<   STARTSUBSET_OP,
<   DFLTSUBSET_OP,
<   STARTSUBASSIGN_OP,
<   DFLTSUBASSIGN_OP,
<   STARTC_OP,
<   DFLTC_OP,
<   STARTSUBSET2_OP,
<   DFLTSUBSET2_OP,
<   STARTSUBASSIGN2_OP,
<   DFLTSUBASSIGN2_OP,
<   DOLLAR_OP,
<   DOLLARGETS_OP,
<   ISNULL_OP,
<   ISLOGICAL_OP,
<   ISINTEGER_OP,
<   ISDOUBLE_OP,
<   ISCOMPLEX_OP,
<   ISCHARACTER_OP,
<   ISSYMBOL_OP,
<   ISOBJECT_OP,
<   ISNUMERIC_OP,
<   VECSUBSET_OP,
<   MATSUBSET_OP,
<   VECSUBASSIGN_OP,
<   MATSUBASSIGN_OP,
<   AND1ST_OP,
<   AND2ND_OP,
<   OR1ST_OP,
<   OR2ND_OP,
<   GETVAR_MISSOK_OP,
<   DDVAL_MISSOK_OP,
<   VISIBLE_OP,
<   SETVAR2_OP,
<   STARTASSIGN2_OP,
<   ENDASSIGN2_OP,
<   SETTER_CALL_OP,
<   GETTER_CALL_OP,
<   SWAP_OP,
<   DUP2ND_OP,
<   SWITCH_OP,
<   RETURNJMP_OP,
<   STARTSUBSET_N_OP,
<   STARTSUBASSIGN_N_OP,
<   VECSUBSET2_OP,
<   MATSUBSET2_OP,
<   VECSUBASSIGN2_OP,
<   MATSUBASSIGN2_OP,
<   STARTSUBSET2_N_OP,
<   STARTSUBASSIGN2_N_OP,
<   SUBSET_N_OP,
<   SUBSET2_N_OP,
<   SUBASSIGN_N_OP,
<   SUBASSIGN2_N_OP,
<   LOG_OP,
<   LOGBASE_OP,
<   MATH1_OP,
<   DOTCALL_OP,
<   COLON_OP,
<   SEQALONG_OP,
<   SEQLEN_OP,
<   BASEGUARD_OP,
<   BREAKPOINT0_OP,
<   BREAKPOINT1_OP,
<   BREAKPOINT2_OP,
<   BREAKPOINT3_OP,
<   BREAKPOINT4_OP,
<   OPCOUNT
< };
<
<
<
< #ifdef THREADED_CODE
< typedef union { void *v; int i; } BCODE;
<
< /* Declare opinfo volatile to prevent gcc 6 from making a local copy
<    in bcEval stack frames and thus increasing stack usage
<    dramatically */
< volatile
< static struct { void *addr; int argc; char *instname; } opinfo[OPCOUNT];
<
< #define OP(name,n) \
<   case name##_OP: opinfo[name##_OP].addr = (__extension__ &&op_##name); \
<     opinfo[name##_OP].argc = (n); \
<     opinfo[name##_OP].instname = #name; \
<     goto loop; \
<     op_##name
<
< #define OP_ARGCNT(o) opinfo[o].argc
<
< #define BEGIN_MACHINE  NEXT(); init: { loop: switch(which++)
< #define LASTOP } retvalue = R_NilValue; goto done
< #define INITIALIZE_MACHINE() if (body == NULL) goto init
<
< #define NEXT() (__extension__ ({currentpc = pc; goto *(*pc++).v;}))
< #define GETOP() (*pc++).i
< #define SKIP_OP() (pc++)
<
< #define BCCODE(e) ((BCODE *) INTEGER(BCODE_CODE(e)))
< #define BCCODE_ORIG(e) ((BCODE *) INTEGER(BCODE_CODE_UNBREAKPOINT(e)))
< #else
< typedef int BCODE;
<
< #define OP(name,argc) case name##_OP
<
< static char argcnt_cache[OPCOUNT];
< static Rboolean argcnt_inited = FALSE;
< static inline int OP_ARGCNT(int o){
<     SEXP compilersym, bcOpArgCntsym, fcall, fcall2, res;
<     int i;
<
<     loadNamespace("compiler");
<
<     if( !argcnt_inited ){
<         PROTECT(compilersym = install("compiler"));
<         PROTECT(bcOpArgCntsym = install("bcOpArgCnt"));
<         PROTECT(fcall = lang3(R_TripleColonSymbol, compilersym, bcOpArgCntsym));
<         PROTECT(fcall2 = lang1(fcall));
<         res = eval(fcall2, R_GlobalEnv);
<         UNPROTECT(4);
<
<         if(OPCOUNT > XLENGTH(res))
<             error(_("Not enough instruction argument count provided by compiler::bcOpArgCnt"));
<
<         for(i = 0; i < XLENGTH(res); i++){
<             argcnt_cache[i] = INTEGER(res)[i];
<         }
<         argcnt_inited = TRUE;
<     }
<
<     if(o >= OPCOUNT)
<         error(_("Instruction out of range"));
<
<     return argcnt_cache[o];
< }
<
< #ifdef BC_PROFILING
< #define BEGIN_MACHINE  loop: currentpc = pc; current_opcode = *pc; jmp_opcode = *pc++; do_instruction: switch(jmp_opcode)
< #else
< #define BEGIN_MACHINE  loop: currentpc = pc; jmp_opcode = *pc++; do_instruction: switch(jmp_opcode)
< #endif
< #define LASTOP  default: error(_("bad opcode"))
< #define INITIALIZE_MACHINE()
<
< #define NEXT() goto loop
< #define GETOP() *pc++
< #define SKIP_OP() (pc++)
<
< #define BCCODE(e) INTEGER(BCODE_CODE(e))
< #define BCCODE_ORIG(e) INTEGER(BCODE_CODE_UNBREAKPOINT(e))
< #endif
<
<
< /*
< #define CallDebugBrowser(call, body, rho) do { \
<   RCNTXT cntxt;\
<   begincontext(&cntxt, CTXT_BREAKPOINT, body, rho, \
<    R_BaseEnv,  R_NilValue, R_NilValue); \
<   do_browser(call, body, R_NilValue, rho); \
<   endcontext(&cntxt); \
< }while(0)
< */
<
< #define CallDebugBrowser(call, body, rho) do { \
<   do_browser(call, body, R_NilValue, rho); \
< }while(0)
<
1806,1807d1556
< static Rboolean canDebugBC(SEXP body);
<
1841,1853c1590,1596
<     Rprintf("debugging in: ");
<     PrintCall(call, rho);
<
<     if(!R_is_bc_debug_enabled()
<             || (R_is_bc_debug_enabled() && !canDebugBC(body)) ){
<         body = bytecodeExpr(body);
<     }
<
<     SrcrefPrompt("debug", R_Srcref);
<     PrintValue( TYPEOF(body) == BCODESXP ? bytecodeExpr(body) : body);
<
<     CallDebugBrowser(call, op, newrho);
<
---
> 	if (TYPEOF(body) == BCODESXP)
> 	    body = bytecodeExpr(body);
> 	Rprintf("debugging in: ");
> 	PrintCall(call, rho);
> 	SrcrefPrompt("debug", R_Srcref);
> 	PrintValue(body);
> 	do_browser(call, op, R_NilValue, newrho);
1860,1864c1603,1610
< 	if (! cntxt.jumptarget /* ignores intermediate jumps for on.exits */
< 	    && R_ReturnedValue == R_RestartToken) {
< 	    cntxt.callflag = CTXT_RETURN;  /* turn restart off */
< 	    R_ReturnedValue = R_NilValue;  /* remove restart token */
< 	    cntxt.returnValue = eval(body, newrho);
---
> 	if (!cntxt.jumptarget) {
> 	    /* ignores intermediate jumps for on.exits */
> 	    if (R_ReturnedValue == R_RestartToken) {
> 		cntxt.callflag = CTXT_RETURN;  /* turn restart off */
> 		R_ReturnedValue = R_NilValue;  /* remove restart token */
> 		cntxt.returnValue = eval(body, newrho);
> 	    } else
> 		cntxt.returnValue = R_ReturnedValue;
2179c1924
<   CallDebugBrowser(call, op, rho);
---
> 	do_browser(call, op, R_NilValue, rho);
2334c2079
<       CallDebugBrowser(call, op, rho);
---
> 	    do_browser(call, op, R_NilValue, rho);
2376c2121
<     CallDebugBrowser(call, op, rho);
---
> 		do_browser(call, op, R_NilValue, rho);
2383c2128
<     CallDebugBrowser(call, op, rho);
---
> 		do_browser(call, op, R_NilValue, rho);
2448c2193
<     CallDebugBrowser(call, op, rho);
---
> 		do_browser(call, op, R_NilValue, rho);
3755a3501,3504
> #if defined(__GNUC__) && ! defined(BC_PROFILING) && (! defined(NO_THREADED_CODE))
> # define THREADED_CODE
> #endif
>
3796a3546,3673
> enum {
>   BCMISMATCH_OP,
>   RETURN_OP,
>   GOTO_OP,
>   BRIFNOT_OP,
>   POP_OP,
>   DUP_OP,
>   PRINTVALUE_OP,
>   STARTLOOPCNTXT_OP,
>   ENDLOOPCNTXT_OP,
>   DOLOOPNEXT_OP,
>   DOLOOPBREAK_OP,
>   STARTFOR_OP,
>   STEPFOR_OP,
>   ENDFOR_OP,
>   SETLOOPVAL_OP,
>   INVISIBLE_OP,
>   LDCONST_OP,
>   LDNULL_OP,
>   LDTRUE_OP,
>   LDFALSE_OP,
>   GETVAR_OP,
>   DDVAL_OP,
>   SETVAR_OP,
>   GETFUN_OP,
>   GETGLOBFUN_OP,
>   GETSYMFUN_OP,
>   GETBUILTIN_OP,
>   GETINTLBUILTIN_OP,
>   CHECKFUN_OP,
>   MAKEPROM_OP,
>   DOMISSING_OP,
>   SETTAG_OP,
>   DODOTS_OP,
>   PUSHARG_OP,
>   PUSHCONSTARG_OP,
>   PUSHNULLARG_OP,
>   PUSHTRUEARG_OP,
>   PUSHFALSEARG_OP,
>   CALL_OP,
>   CALLBUILTIN_OP,
>   CALLSPECIAL_OP,
>   MAKECLOSURE_OP,
>   UMINUS_OP,
>   UPLUS_OP,
>   ADD_OP,
>   SUB_OP,
>   MUL_OP,
>   DIV_OP,
>   EXPT_OP,
>   SQRT_OP,
>   EXP_OP,
>   EQ_OP,
>   NE_OP,
>   LT_OP,
>   LE_OP,
>   GE_OP,
>   GT_OP,
>   AND_OP,
>   OR_OP,
>   NOT_OP,
>   DOTSERR_OP,
>   STARTASSIGN_OP,
>   ENDASSIGN_OP,
>   STARTSUBSET_OP,
>   DFLTSUBSET_OP,
>   STARTSUBASSIGN_OP,
>   DFLTSUBASSIGN_OP,
>   STARTC_OP,
>   DFLTC_OP,
>   STARTSUBSET2_OP,
>   DFLTSUBSET2_OP,
>   STARTSUBASSIGN2_OP,
>   DFLTSUBASSIGN2_OP,
>   DOLLAR_OP,
>   DOLLARGETS_OP,
>   ISNULL_OP,
>   ISLOGICAL_OP,
>   ISINTEGER_OP,
>   ISDOUBLE_OP,
>   ISCOMPLEX_OP,
>   ISCHARACTER_OP,
>   ISSYMBOL_OP,
>   ISOBJECT_OP,
>   ISNUMERIC_OP,
>   VECSUBSET_OP,
>   MATSUBSET_OP,
>   VECSUBASSIGN_OP,
>   MATSUBASSIGN_OP,
>   AND1ST_OP,
>   AND2ND_OP,
>   OR1ST_OP,
>   OR2ND_OP,
>   GETVAR_MISSOK_OP,
>   DDVAL_MISSOK_OP,
>   VISIBLE_OP,
>   SETVAR2_OP,
>   STARTASSIGN2_OP,
>   ENDASSIGN2_OP,
>   SETTER_CALL_OP,
>   GETTER_CALL_OP,
>   SWAP_OP,
>   DUP2ND_OP,
>   SWITCH_OP,
>   RETURNJMP_OP,
>   STARTSUBSET_N_OP,
>   STARTSUBASSIGN_N_OP,
>   VECSUBSET2_OP,
>   MATSUBSET2_OP,
>   VECSUBASSIGN2_OP,
>   MATSUBASSIGN2_OP,
>   STARTSUBSET2_N_OP,
>   STARTSUBASSIGN2_N_OP,
>   SUBSET_N_OP,
>   SUBSET2_N_OP,
>   SUBASSIGN_N_OP,
>   SUBASSIGN2_N_OP,
>   LOG_OP,
>   LOGBASE_OP,
>   MATH1_OP,
>   DOTCALL_OP,
>   COLON_OP,
>   SEQALONG_OP,
>   SEQLEN_OP,
>   BASEGUARD_OP,
>   OPCOUNT
> };
>
4675a4577,4620
> #ifdef THREADED_CODE
> typedef union { void *v; int i; } BCODE;
>
> /* Declare opinfo volatile to prevent gcc 6 from making a local copy
>    in bcEval stack frames and thus increasing stack usage
>    dramatically */
> volatile
> static struct { void *addr; int argc; char *instname; } opinfo[OPCOUNT];
>
> #define OP(name,n) \
>   case name##_OP: opinfo[name##_OP].addr = (__extension__ &&op_##name); \
>     opinfo[name##_OP].argc = (n); \
>     opinfo[name##_OP].instname = #name; \
>     goto loop; \
>     op_##name
>
> #define BEGIN_MACHINE  NEXT(); init: { loop: switch(which++)
> #define LASTOP } retvalue = R_NilValue; goto done
> #define INITIALIZE_MACHINE() if (body == NULL) goto init
>
> #define NEXT() (__extension__ ({currentpc = pc; goto *(*pc++).v;}))
> #define GETOP() (*pc++).i
> #define SKIP_OP() (pc++)
>
> #define BCCODE(e) (BCODE *) INTEGER(BCODE_CODE(e))
> #else
> typedef int BCODE;
>
> #define OP(name,argc) case name##_OP
>
> #ifdef BC_PROFILING
> #define BEGIN_MACHINE  loop: currentpc = pc; current_opcode = *pc; switch(*pc++)
> #else
> #define BEGIN_MACHINE  loop: currentpc = pc; switch(*pc++)
> #endif
> #define LASTOP  default: error(_("bad opcode"))
> #define INITIALIZE_MACHINE()
>
> #define NEXT() goto loop
> #define GETOP() *pc++
> #define SKIP_OP() (pc++)
>
> #define BCCODE(e) INTEGER(BCODE_CODE(e))
> #endif
5730,5772d5680
<
< static void modifybcbreakpoint(SEXP bc, int pos, Rboolean setTo);
< static void printBCStatus();
<
< #define DO_SET_ALL_TMP_BREAKPOINTS(body, tmplist, is) do { \
<         if((tmplist) && !isNull((tmplist))) {\
<             for (int i = 0; i < length((tmplist)); i++) { \
<                 modifybcbreakpoint((body), INTEGER((tmplist))[i], is); \
<             } \
<         }\
<     } while (0)
<
< #define DO_REMOVE_OLD_BREAKPOINTS(body, tmplist) \
<   DO_SET_ALL_TMP_BREAKPOINTS(body, tmplist, FALSE)
< #define DO_RESTORE_OLD_BREAKPOINTS(body, tmplist) \
<   DO_SET_ALL_TMP_BREAKPOINTS(body, tmplist, TRUE)
<
<
< #ifdef THREADED_CODE
< #define BREAKPOINT_GOTO_ORIGIN_OP(inst) do{ \
<         __extension__ ({goto *(*(inst)).v;}); \
<     } while(0)
< #else
< #define BREAKPOINT_GOTO_ORIGIN_OP(inst) do{ \
<         jmp_opcode = *(inst); \
<         goto do_instruction; \
<     } while(0)
< #endif
<
< static int findOp(void *addr);
<
< #ifdef THREADED_CODE
< static int getCurOp(ptrdiff_t diff) {
<     BCODE *codebase = BCCODE(R_BCbody);
<     return findOp(codebase[diff].v);
< }
< #else
< static int getCurOp(ptrdiff_t diff) {
<     BCODE *codebase = BCCODE(R_BCbody);
<     return findOp(codebase[diff]);
< }
< #endif
<
5843,5873d5750
< Rboolean canDebugBC(SEXP body){
<     if(TYPEOF(body) != BCODESXP)
<         return FALSE;
<
<     if(R_DebugVerbose)
<         return TRUE;
<     SEXP constants = BCCONSTS(body);
<     SEXP srcrefs = findLocTable(constants, "srcrefsIndex");
<     SEXP expressions = findLocTable(constants, "expressionsIndex");
<     Rboolean can = srcrefs != R_NilValue && expressions != R_NilValue;
<     return can;
< }
<
< /*
< void checkMissingSrcRefs(SEXP body){
<     if(TYPEOF(body) == BCODESXP){
<
<     SEXP constants = BCCONSTS(body);
<     SEXP ltable = findLocTable(constants, "srcrefsIndex");
<     if(ltable == R_NilValue){
<         int i = 0;
<         i++;
<     }
<  //       error(_("OOPS ltable is error"));
<     }
< }
< */
<
<
<
<
5884,5918d5760
< static SEXP R_findBCInterpreterLastExpressionForSrcref(){
<     SEXP body = R_BCbody;
<     if (body == NULL)
<     /* This has happened, but it is not clear how. */
<     /* (R_Srcref == R_InBCInterpreter && R_BCbody == NULL) */
<     return R_NilValue;
<
<     SEXP constants = BCCONSTS(body);
<     SEXP lexprtable = findLocTable(constants, "expressionsIndex");
<     if (lexprtable == R_NilValue)
<     /* location table not available */
<     return R_NilValue;
<     SEXP lsrcreftable = findLocTable(constants, "srcrefsIndex");
<     if (lsrcreftable == R_NilValue)
<     /* location table not available */
<     return R_findBCInterpreterExpression();
<
<     BCODE *codebase = BCCODE(body);
<     BCODE * pc = ((BCODE *) INTEGER(BCODE_CODE(body)));
<     ptrdiff_t relpc = (*((BCODE **)(R_BCpc))) - codebase;
<     SEXP srcref = getLocTableElt(relpc, lsrcreftable, constants);
<     SEXP retexpr;
<     do{
<         retexpr = getLocTableElt(relpc, lexprtable, constants);
< #ifdef THREADED_CODE
<         int op = findOp(pc[relpc].v);
< #else
<         int op = pc[relpc];
< #endif
<         relpc += opinfo[op].argc + 1;
<     } while (relpc < XLENGTH(BCODE_CODE(body)) && getLocTableElt(relpc, lsrcreftable, constants) == srcref);
<
<     return retexpr;
< }
<
5927,5994d5768
<
< /* At the beginning it removes the all previously setted temporary
<    breakpoints. Then prints current state of the bytecode
<    interpreter ( bytecode + stack ). At the end it calls the
<    original bytecode instruction which is shadowed by this
<    breakpoint. */
<
< /*
< begincontext(&cntxt, CTXT_BUILTIN, R_NilValue, \
<          R_BaseEnv, R_BaseEnv, R_NilValue, R_NilValue); \
< */
<
< static SEXP SRC_OR_EXPRREF() {
<     SEXP srcref = R_findBCInterpreterSrcref(NULL);
<     if(!isNull(srcref))
<         return srcref;
<     return R_findBCInterpreterExpression(NULL);
< }
<
< #define CHECK_ADD_BREAKPOINT(pcdiff) do { \
<     if(RDEBUG(rho)){ \
<       ptrdiff_t diff = *((BCODE**)R_BCpc) - codebase - 1; \
<       *((BCODE**)R_BCpc) = BCCODE(R_BCbody) + diff + 1; \
<       codebase = BCCODE(R_BCbody); \
<       constants = BCCONSTS(R_BCbody); \
<       pc = *((BCODE**)R_BCpc) + pcdiff + 1; \
<    } \
< } while(0)
<
< #define DO_BREAKPOINT() do { \
<         R_RemoveBCtmpBreakpoints(R_BCbody, *R_BCtmpBreakpoints); \
<         *R_BCtmpBreakpoints = R_NilValue; \
<         ptrdiff_t diff = pc - codebase - 1; \
<         if(!R_GlobalContext->browserfinish) { \
<             SEXP cursrcref = SRC_OR_EXPRREF(); \
<             /*if(isNull(cursrcref)) myBP();*/ \
<             int op = getCurOp(diff); \
<             \
<             if(R_DebugVerbose || \
<                 ( oldbreakpointexpr != cursrcref && op != POP_OP && op != GOTO_OP ) \
<             ) { \
<                 oldbreakpointexpr = cursrcref; \
<                 SrcrefPrompt("debugBC", R_findBCInterpreterSrcref(NULL)); \
<                 if(!R_DebugVerbose) \
<                     PrintValue(R_findBCInterpreterLastExpressionForSrcref()); \
<                 else \
<                     Rprintf("\n"); \
<                 if(R_DebugVerbose) printBCStatus(); \
<                 CallDebugBrowser(CALL_FRAME_FUN(), body, rho); \
<                 if(RDEBUG(rho)) \
<                   Rf_breakOnNextBCInst(body, R_BCpc, R_BCtmpBreakpoints); \
<             }else{ \
<                 Rf_breakOnNextBCInst(body, R_BCpc, R_BCtmpBreakpoints); \
<             } \
<         }else{ \
<             oldbreakpointexpr = R_NilValue;\
<         }\
<         if(RDEBUG(rho) && R_BrowserLastCommand == 'f'){ \
<               Rf_breakOnNextBCInst(body, R_BCpc, R_BCtmpBreakpoints); \
<         } \
<         \
<         codebase = BCCODE(R_BCbody);\
<         constants = BCCONSTS(R_BCbody);\
<         pc = codebase + diff + 1; \
<         \
<         BREAKPOINT_GOTO_ORIGIN_OP( (BCODE*)BCCODE_ORIG(body) + diff ); \
<     } while (0)
<
6143,6146d5925
<   static int evalcount = 0;
< #ifndef THREADED_CODE
<   int jmp_opcode;
< #endif
6147a5927
>   static int evalcount = 0;
6151d5930
<   SEXP* oldtmpbreakpoints = R_BCtmpBreakpoints;
6154d5932
<   SEXP oldbreakpointexpr = R_NilValue;
6165a5944,5945
>   BC_CHECK_SIGINT();
>
6166a5947,5948
>   codebase = pc = BCCODE(body);
>   constants = BCCONSTS(body);
6172,6191d5953
<   /* duplicate body in case this function has modified */
<   if(BCODE_HAS_TMPBREAKPOINTS(body)){
<     SEXP expr = TAG(body);
<     body = CONS(BCODE_CODE_UNBREAKPOINT(body), BCODE_CONSTS(body));
<     SET_TAG(body, expr);
<     SET_TYPEOF(body, BCODESXP);
<   }
<
<   /* satisfy GC */
<   BCNPUSH(body); /* pushing body is neccesary just in case of
<     duplicated, but pushing even unchanged one is easier for code
<     readability */
<   BCNPUSH(R_NilValue);  /* new  are stored on stack
<     R_BCtmpBreakpoints */
<   R_BCtmpBreakpoints = &(GETSTACK_SXPVAL_PTR(R_BCNodeStackTop -1));
<
<
<   codebase = pc = BCCODE(body);
<   constants = BCCONSTS(body);
<
6219,6220d5978
<   R_bcstack_t *oldfnbase = R_BCNodeStackFnBase;
<   R_BCNodeStackFnBase = R_BCNodeStackTop;
6223,6231d5980
<
<   if(RDEBUG(rho)){
<       ptrdiff_t diff = pc - codebase;
<       Rf_breakOnNextBCInst(body, R_BCpc, R_BCtmpBreakpoints);
<       codebase = BCCODE(body);
<       constants = BCCONSTS(body);
<       pc = codebase + diff;
<   }
<
6711,6713c6458,6459
<     POP_CALL_FRAME(value);
<     CHECK_ADD_BREAKPOINT(OP_ARGCNT(CALL_OP));
<     NEXT();
---
> 	POP_CALL_FRAME(value);
> 	NEXT();
6742d6487
<   CHECK_ADD_BREAKPOINT(OP_ARGCNT(CALLBUILTIN_OP));
6763,6764d6506
<
<   CHECK_ADD_BREAKPOINT(OP_ARGCNT(CALLSPECIAL_OP));
7073,7074c6820
<   CHECK_ADD_BREAKPOINT(OP_ARGCNT(SETTER_CALL_OP));
<     NEXT();
---
> 	NEXT();
7115,7116c6861
<   CHECK_ADD_BREAKPOINT(OP_ARGCNT(GETTER_CALL_OP));
<     NEXT();
---
> 	NEXT();
7232,7236d6976
<     OP(BREAKPOINT0, 0): DO_BREAKPOINT(); NEXT();
<     OP(BREAKPOINT1, 1): DO_BREAKPOINT(); NEXT();
<     OP(BREAKPOINT2, 2): DO_BREAKPOINT(); NEXT();
<     OP(BREAKPOINT3, 3): DO_BREAKPOINT(); NEXT();
<     OP(BREAKPOINT4, 4): DO_BREAKPOINT(); NEXT();
7241,7243d6980
<   BCNPOP_IGNORE_VALUE(); /* body */
<
<
7247d6983
<   R_BCtmpBreakpoints = oldtmpbreakpoints;
7250d6985
<   R_BCNodeStackFnBase = oldfnbase;
7564,7576d7296
< /*SEXP do_setCode(SEXP call, SEXP op, SEXP args, SEXP rho)
< {
<     SEXP fun, newcode, ans;
<
<     checkArity(op, args);
<
<     fun = CAR(args);
<     newcode = CADR(args);
<
<
< }
< */
<
7622d7341
<   SEXP code_orig = !isNull(BCODE_CODE_UNBREAKPOINT(bc)) ? BCODE_CODE_UNBREAKPOINT(bc) : code;
7627,7636d7345
<   PROTECT(ans = allocVector(VECSXP, expr != R_NilValue ? 5 : 4));
<   SET_VECTOR_ELT(ans, 0, install(".Code"));
<   SET_VECTOR_ELT(ans, 1, R_bcDecode(code));
<   SET_VECTOR_ELT(ans, 2, R_bcDecode(code_orig));
<   SET_VECTOR_ELT(ans, 3, allocVector(VECSXP, nc));
<   if (expr != R_NilValue)
<       SET_VECTOR_ELT(ans, 4, duplicate(expr));
<
<   dconsts = VECTOR_ELT(ans, 3);
< /*
7645c7354
< */  for (i = 0; i < nc; i++) {
---
>   for (i = 0; i < nc; i++) {
7973,8062d7681
< #ifdef THREADED_CODE
< #define getBCVal(pc,pos) (pc)[pos].i
< #define getBCInstr(pc,pos) findOp((pc)[pos].v)
< #define setBCInstr(pc,pos,val) (pc)[pos].v = opinfo[val].addr
< #else
< #define getBCVal(pc,pos) (pc)[pos]
< #define getBCInstr(pc,pos) (pc)[pos]
< #define setBCInstr(pc,pos,v) (pc)[pos] = v
< #endif
<
< /*
<  * Set or unset breakpoint for bc at position pos
<  * unset if setTo is FALSE, othervise set
<  */
< void modifybcbreakpoint(SEXP bc, int pos, Rboolean setTo){
<     if (pos <= 0 || pos >= LENGTH(bc))
<         error(_("Breapoint position out of bytecode range"));
<
<     int val;
<     SEXP newbccode, ans;
<     BCODE* pc;
<
<     /* save copy of original bytecode
<          we have to save this copy because the evaluated bytecode array
<          would be modified by replacing instructions with breakpoint
<          when evaluating, the breakpoint instruction will have to look into this array
<          to evaluate old intruction */
<     if(isNull(BCODE_CODE_UNBREAKPOINT(bc))){
<         //duplicate original code buffer
<         PROTECT(newbccode = duplicate(BCODE_CODE(bc)));
<         SEXP oldbcode = BCODE_CODE(bc);
<
<         //save it as third element into function structure list
<         // function structure is now ( code -> constants -> original code )
<         PROTECT(ans = CONS(CDR(bc), oldbcode));
<         SETCDR(bc, ans);
<         SETCAR(bc, newbccode);
<
<         UNPROTECT(2);
<     }
<
<     pc = ((BCODE *) INTEGER(BCODE_CODE(bc)));
<
<     if(setTo){  //enable breakpoint
<         val = getBCInstr(pc,pos);
<         switch(OP_ARGCNT(val)){
<             case 0: val = BREAKPOINT0_OP; break;
<             case 1: val = BREAKPOINT1_OP; break;
<             case 2: val = BREAKPOINT2_OP; break;
<             case 3: val = BREAKPOINT3_OP; break;
<             case 4: val = BREAKPOINT4_OP; break;
<             default:
<                 error(_("Opcode argument count mismatch"));
<         }
<         setBCInstr(pc,pos,val);
<     }else{  //disable breakpoint
<         #ifdef THREADED_CODE
<             pc[pos].v = ((BCODE *) INTEGER(BCODE_CODE_UNBREAKPOINT(bc)))[pos].v;
<         #else
<             pc[pos] = ((BCODE *) INTEGER(BCODE_CODE_UNBREAKPOINT(bc)))[pos];
<         #endif
<     }
< }
<
< /*
<  * R function wrapper over the modifybcbreakpoint
<  * 3 arguments,
<  *      bytecode,
<  *      position,
<  *      setTo ( TRUE - set breajpoint, FAKSE unset)
<  * returns back bytecode ( first argument )
<  */
< SEXP attribute_hidden do_modifybcbreakpoint(SEXP call, SEXP op, SEXP args, SEXP rho)
< {
<     int pos;
<     SEXP bc;
<     Rboolean setTo;
<     checkArity(op, args);
<     bc = CAR(args);
<     if (TYPEOF(CAR(args)) == CLOSXP)
<         bc = BODY(bc);
<
<     pos = asInteger(CADR(args));                //2nd argument
<     setTo = asLogical(CADDR(args));             //3rd agument
<
<     modifybcbreakpoint(bc, pos, setTo);
<
<     return CAR(args);
< }
<
8078,8268d7696
< }
<
< void R_RemoveBCtmpBreakpoints(SEXP body, SEXP tmplist){
<     DO_REMOVE_OLD_BREAKPOINTS(body, tmplist);
< }
<
<
< void Rf_restoreAllBrowserBreakpoints(SEXP body, SEXP tmplist){
<     DO_RESTORE_OLD_BREAKPOINTS(body, tmplist);
< }
<
<
< void Rf_breakOnNextBCInst(SEXP R_BCbody, void** R_BCpc, SEXP* R_BCtmpBreakpoints) {
<     int inst;
<     if( (*(BCODE**)R_BCpc) ) {     //already inside BC
<         inst = (*(BCODE**)R_BCpc) - BCCODE(R_BCbody) + 1;
<     } else {            //currently in the beginning of (bcEva
<         inst = 0;
<     }
<
<     RCNTXT cntxt;
<
<     begincontext(&cntxt, CTXT_BUILTIN, R_NilValue,
<              R_BaseEnv, R_BaseEnv, R_NilValue, R_NilValue);
<
<     loadNamespace("compiler");
<
<     /* equivalent to compiler::bcSetNextBreakpoint( quote(fun), inst, skipCall ) */
<     SEXP compilersym, bcSetNextBreakpointsym, possym, quotesym, qexpr, fcall, fcall2, ret;
<
<     PROTECT(compilersym = install("compiler"));
<     PROTECT(bcSetNextBreakpointsym = install("bcSetNextBreakpoint"));
<     PROTECT(quotesym = install("quote"));
<     PROTECT(possym = ScalarInteger(inst));
<     PROTECT(qexpr = lang2(quotesym, R_BCbody));
<     PROTECT(fcall = lang3(R_TripleColonSymbol, compilersym, bcSetNextBreakpointsym));
<     PROTECT(fcall2 = lang3(fcall, qexpr, possym));
<
<     ret = eval(fcall2, R_GlobalEnv);
<
<     UNPROTECT(7);
<
<     endcontext(&cntxt);
<
<     *R_BCtmpBreakpoints = ret;
< }
<
< void R_printCurrentBCbody(SEXP body, void* pc, Rboolean peephole, int verboselvl) {
<     SEXP compilersym, disasmsym, quotesym, bctoolssym, printdisasmsym;
<     SEXP prefixstr, verbose, zero, peepholeexpr ,instexpr;
<     SEXP qexpr, disasmcall, fcall, fcall2;
<     RCNTXT cntxt;
<
<     begincontext(&cntxt, CTXT_BUILTIN, R_NilValue,
<              R_BaseEnv, R_BaseEnv, R_NilValue, R_NilValue);
<     loadNamespace("bctools");
<     loadNamespace("compiler");
<
<     PROTECT(bctoolssym = install("bctools"));
<     PROTECT(compilersym = install("compiler"));
<     PROTECT(disasmsym = install("disassemble"));
<     PROTECT(printdisasmsym = install("print"));
<     PROTECT(quotesym = install("quote"));
<
<     PROTECT(fcall = lang3(R_TripleColonSymbol, compilersym, disasmsym));
<     PROTECT(qexpr = lang2(quotesym, body));
<     PROTECT(disasmcall = lang2(fcall, qexpr));
<     PROTECT(prefixstr = mkString("        "));
<     PROTECT(verbose = ScalarInteger(verboselvl));
<     PROTECT(zero = ScalarInteger(0));
<     PROTECT(peepholeexpr = ScalarLogical(peephole));
<     //current evaluating instruction if body equals to NULL
<     PROTECT(instexpr =
<                 pc
<                     ? ScalarInteger((*(BCODE**)pc) - BCCODE(body))
<                     : R_NilValue);
<
<     /* equivalent to print(
<      *      compiler::disassemble(
<      *                  quote(call),
<      *                  prefix,
<      *                  verbose = 1,
<      *                  maxdepth = 0,
<      *                  curdepth = 0,
<      *                  select = inst,
<      *                  peephole=peephole)
<      *       )
<      */
<     PROTECT(fcall2 = lang8(printdisasmsym, disasmcall, prefixstr, verbose, zero, zero, instexpr, peepholeexpr));
<     eval(fcall2, R_GlobalEnv);
<     UNPROTECT(14);
<
<     endcontext(&cntxt);
< }
<
< void R_printCurrentBCstack(void* startVoid, void* curVoid) {
<     int i,j,size,opts;
<     SEXP canPrint, printval;
<     R_bcstack_t* start = (R_bcstack_t*) startVoid;
<     R_bcstack_t* cur = (R_bcstack_t*) curVoid;
<
<     #ifdef CACHE_ON_STACK
<         /* binding cache on stack */
<         R_len_t n = LENGTH(BCCONSTS(R_BCbody));
<         #ifdef CACHE_MAX
<             if (n > CACHE_MAX) { n = CACHE_MAX; }
<         #endif
<         start += n;
<     #else
<         /* binding cache in separated vector */
<         start += 1;
<     #endif
<
<     if(cur - 1 < start){
<         Rprintf("       stack is empty\n");
<     }
<
<     /* information if stack at position i from start contains printable value */
<     PROTECT(canPrint = allocVector(LGLSXP, cur-start));
<
<     /*
<      * go through whole stack because we need to mark pieces which are
<      *  RAWMEM so we wouldn't print them
<      */
<     for(i = 0 ; i < cur-start ; i++){
<         LOGICAL(canPrint)[i] = TRUE;
<         #ifdef TYPED_STACK
<             if((start+i)->tag == RAWMEM_TAG){
<                 size = (start+i)->u.ival;
<                 /*set next cnt following elements to FALSE so we don't
<                  *  print em
<                  */
<                 for(j = 0; j < size; j++){
<                     LOGICAL(canPrint)[++i] = FALSE;
<                 }
<             }
<         #endif
<     }
<
<     /* print stack from the top */
<     while(--cur >= start){
<         if(!LOGICAL(canPrint)[cur-start])
<             continue;
<
<         Rprintf("       %p: ", cur);
< #ifdef TYPED_STACK
<         if(cur->tag == RAWMEM_TAG){
<             Rprintf("<rawmem of size %d>\n", cur->u.ival);
<         }else{
< #endif
<             /* We cannot use default dput setting,
<              * because we don't want to evaluate promises */
<             opts = SHOWATTRIBUTES | DELAYPROMISES;
<             printval = deparse1(GETSTACK_PTR(cur), 0, opts);
<             for (i = 0; i < LENGTH(printval); i++)
<                 Rprintf("%s\n", CHAR(STRING_ELT(printval, i)));
< #ifdef TYPED_STACK
<         }
< #endif
<     }
<
<     UNPROTECT(1); /* canPrint */
< }
<
< void printBCStatus(){
<     Rprintf("     --- Evaluating bytecode --- \n");
<     R_printCurrentBCbody(R_BCbody, R_BCpc, TRUE, 1);
<     Rprintf("     -------- Stack dump ------- \n");
<     R_printCurrentBCstack(R_BCNodeStackFnBase, R_BCNodeStackTop);
< }
<
< SEXP attribute_hidden do_breakpoint(SEXP call, SEXP op, SEXP args, SEXP rho)
< {
<     Rboolean oldrdebug;
<     oldrdebug = RDEBUG(rho);
<     SET_RDEBUG(rho, 1);
<     R_GlobalContext->browserfinish = 0;
<     R_BrowserLastCommand = 'n';
<
<     if(!R_is_bc_debug_enabled() && R_BCIntActive)
<   warning(_("Calling breakpoint in the BC while bytecode debugger disabled"));
<
<     /* Support for bytecode debugger */
<     if(R_BCIntActive && !oldrdebug){
<       R_RemoveBCtmpBreakpoints(
<           R_BCbody, *R_BCtmpBreakpoints);
<       Rf_breakOnNextBCInst(
<           R_BCbody, R_BCpc, R_BCtmpBreakpoints);
<     }
<
<     return R_NilValue;
