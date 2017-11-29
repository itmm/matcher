#pragma once

/**
 * \file log.h
 * \brief basic logging functionality
 */

#include <stdio.h>

#if !defined(LOG_MIN_LEVEL)
    /// minimal level of logging
	#define LOG_MIN_LEVEL 1
#endif

#define LOGGING_E (LOG_MIN_LEVEL <= 3)
#define LOGGING_W (LOG_MIN_LEVEL <= 2)
#define LOGGING_I (LOG_MIN_LEVEL <= 1)
#define LOGGING_D (LOG_MIN_LEVEL <= 0)

#define _LOG_COLOR(COLOR) "\033[0;" COLOR "m"
#define _LOG_COLOR_RED _LOG_COLOR("31")
#define _LOG_COLOR_GREEN _LOG_COLOR("32")
#define _LOG_COLOR_BROWN _LOG_COLOR("33")
#define _LOG_RESET_COLOR "\033[0m"

#define LOG_MESSAGE(SHOULD_LOG, OUTPUT, PREFIX, SUFFIX, FILE, LINE, FN, TAG, FMT, ...) \
    if (SHOULD_LOG) { \
    	fprintf( \
    		OUTPUT, \
    		PREFIX "%s:%d (%s) %s: " FMT SUFFIX "\n", \
    		FILE, \
    		LINE, \
    		FN, \
    		TAG, \
    		## __VA_ARGS__ \
    	); \
    }

#define LOG_E(TAG, FMT, ...) LOG_MESSAGE( \
    LOGGING_E, \
    stderr, \
    _LOG_COLOR_RED "E ", \
    _LOG_RESET_COLOR, \
    __FILE__, \
    __LINE__, \
    __FUNCTION__, \
    TAG, \
    FMT, \
    ## __VA_ARGS__ \
)

#define LOG_W(TAG, FMT, ...) LOG_MESSAGE( \
	LOGGING_W, \
	stderr, \
	_LOG_COLOR_BROWN "W ", \
	_LOG_RESET_COLOR, \
	__FILE__, \
	__LINE__, \
	__FUNCTION__, \
	TAG, \
	FMT, \
	## __VA_ARGS__ \
)

#define LOG_I(TAG, FMT, ...) LOG_MESSAGE( \
	LOGGING_I, \
	stdout, \
	_LOG_COLOR_GREEN "I ", \
	_LOG_RESET_COLOR, \
	__FILE__, \
	__LINE__, \
	__FUNCTION__, \
	TAG, \
	FMT, \
	## __VA_ARGS__ \
)

#define LOG_D(TAG, FMT, ...) LOG_MESSAGE( \
	LOGGING_D, \
	stdout, \
	"", \
	"", \
	__FILE__, \
	__LINE__, \
	__FUNCTION__, \
	TAG, \
	FMT, \
	## __VA_ARGS__ \
)
