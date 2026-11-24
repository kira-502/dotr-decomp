#!/usr/bin/env python3
"""tools/perm/run.py DIR [permuter args]: the toolchain's decomp-permuter with one change: its extract_fn keeps the
other function bodies in base.c (tools/perm/strip.py has already cut base.c down to the ones MWCC needs; it reads a
static callee's body when compiling the caller, even when it doesn't inline it)."""
import os, sys
P = os.path.join(os.environ["DK_TOOLCHAIN"], "src/decomp-permuter")
sys.path.insert(0, P)
from src import ast_util
from src.error import CandidateConstructionFailure
from perm_pycparser import c_ast as ca


def extract_fn(ast, fn_name):
    ret = [(n, i) for i, n in enumerate(ast.ext) if isinstance(n, ca.FuncDef) and n.decl.name == fn_name]
    if len(ret) != 1:
        raise CandidateConstructionFailure(f"{len(ret)} copies of function {fn_name} in base.c.")
    return ret[0]


ast_util.extract_fn = extract_fn
from src.main import main
main()
