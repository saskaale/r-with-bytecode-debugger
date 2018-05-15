1619,1621d1630
<     if(R_BCtmpBreakpoints)
<       FORWARD_NODE(*R_BCtmpBreakpoints);   /* R_NilValue or vector
<                     of positions of temporary breakpoints inside bcbody */
1660,1663d1668
<   if(ctxt->bctmpbreakpoints)
<     FORWARD_NODE(*(ctxt->bctmpbreakpoints));   /* R_NilValue or vector *
<                   of positions of temporary breakpoints inside bcbody */
<
2114c2117
<     R_BCNodeStackTop = R_BCNodeStackFnBase = R_BCNodeStackBase;
---
>     R_BCNodeStackTop = R_BCNodeStackBase;
