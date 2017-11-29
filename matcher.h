#pragma once

#include <stdbool.h>

typedef const char *matcher_t;

matcher_t *init_matcher(matcher_t *matcher, const char *pattern);
matcher_t *clear_matcher(matcher_t *matcher);

const char *match_input(matcher_t *matcher, const char *begin, const char *end);

bool is_matcher_valid(matcher_t *matcher);
bool is_matcher_complete(matcher_t *matcher);

