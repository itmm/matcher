#include "test.h"
#include "matcher.h"

#define MATCH_FULL(STR, PATTERN) { \
    matcher_t matcher; \
    TEST_EQ(init_matcher(&matcher, PATTERN), &matcher); \
    const char begin[] = STR; \
    const char *end = begin + sizeof(begin) - 1; \
    TEST_EQ(match_input(&matcher, begin, end), end); \
    TEST(is_matcher_valid(&matcher)); \
    TEST(is_matcher_complete(&matcher)); \
}

#define NO_MATCH(STR, PATTERN) { \
    matcher_t matcher; \
    TEST_EQ(init_matcher(&matcher, PATTERN), &matcher); \
    const char begin[] = STR; \
    const char *end = begin + sizeof(begin) - 1; \
    TEST_EQ(match_input(&matcher, begin, end), NULL); \
}

#define INCOMPLETE_MATCH(STR, PATTERN, MATCHED) { \
    matcher_t matcher; \
    const char pattern[] = PATTERN; \
    TEST_EQ(init_matcher(&matcher, pattern), &matcher); \
    const char begin[] = STR; \
    const char end = begin + sizeof(begin) - 1; \
    TEST_EQ(match_input(&matcher, begin, end), end); \
    TEST(is_matcher_valid(&matcher)); \
    TEST_FALSE(is_matcher_complete(&matcher)); \
    TEST_EQ(&matcher, pattern + MATCHED); \
}

int main() {
    TEST_INIT();

    MATCH_FULL("abc", "abc");
    MATCH_FULL("aa", ".*");
    MATCH_FULL("aaa", "a*");
    MATCH_FULL("", ".*");
    MATCH_FULL(".a", "\\.a");
    MATCH_FULL("abb", "ab*");
    MATCH_FULL("a", "ab*");

    NO_MATCH("ab", "aa");
    NO_MATCH("a", "b*");

    INCOMPLETE_MATCH("", "abc", 0);
    INCOMPLETE_MATCH("ab", "abc", 2);
    INCOMPLETE_MATCH("aaa", "a*b", 0);

    TEST_SUMMARY();
}
