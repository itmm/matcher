APP = t_matcher

include Makefile.base

matcher.c: matcher.h log.h
t_matcher.c: test.h matcher.h
