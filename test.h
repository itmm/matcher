#pragma once

#include "log.h"

typedef struct {
    int count;
    int failed;
} test_state;

#define _TEST_TAG "testing"

#define TEST_INIT() test_state _test_state = { 0, 0 }
#define TEST_SUMMARY() if (_test_state.failed) { \
        LOG_E(_TEST_TAG, "%d of %d tests failed", _test_state.failed, _test_state.count); \
    } else { \
        LOG_I(_TEST_TAG, "%d tests passed", _test_state.count); \
    }

#define _INC_FAILED ++_test_state.failed
#define _INC_COUNT ++_test_state.count

#define _TEST(COND, PREFIX, ...) if (! COND) { \
    _INC_FAILED; LOG_E(_TEST_TAG, PREFIX, # __VA_ARGS__); \
} _INC_COUNT

#define TEST(COND, ...) _TEST(COND, "! " #COND, __VA_ARGS__)
#define TEST_FALSE(COND, ...) _TEST(! COND, #COND, # __VA_ARGS__)

#define TEST_EQ(A, B, ...) _TEST((A) == (B), #A " != " #B, # __VA_ARGS__)
#define TEST_NE(A, B, ...) _TEST((A) != (B), #A " == " #B, # __VA_ARGS__)
#define TEST_LT(A, B, ...) _TEST((A) < (B), #A " >= " #B, # __VA_ARGS__)
#define TEST_LE(A, B, ...) _TEST((A) <= (B), #A " > " #B, # __VA_ARGS__)
#define TEST_GT(A, B, ...) _TEST((A) > (B), #A " <= " #B, # __VA_ARGS__)
#define TEST_GE(A, B, ...) _TEST((A) >= (B), #A " < " #B, # __VA_ARGS__)

#define TEST_EQ_STR(A, B, ...) _TEST(strcmp(A, B) == 0, #A " != " #B, # __VA_ARGS__)
#define TEST_NE_STR(A, B, ...) _TEST(strcmp(A, B) != 0, #A " == " #B, # __VA_ARGS__)
#define TEST_LT_STR(A, B, ...) _TEST(strcmp(A, B) < 0, #A " >= " #B, # __VA_ARGS__)
#define TEST_LE_STR(A, B, ...) _TEST(strcmp(A, B) <= 0, #A " > " #B, # __VA_ARGS__)
#define TEST_GT_STR(A, B, ...) _TEST(strcmp(A, B) > 0, #A " <= " #B, # __VA_ARGS__)
#define TEST_GE_STR(A, B, ...) _TEST(strcmp(A, B) >= 0, #A " < " #B, # __VA_ARGS__)

