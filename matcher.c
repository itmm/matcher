#include "matcher.h"

#include "log.h"

static const char TAG[] = "matcher";

matcher_t *init_matcher(matcher_t *matcher, const char *pattern) {
    if (matcher) { *matcher = pattern; } else { LOG_E(TAG, "no matcher"); }
    return matcher;
}

matcher_t *clear_matcher(matcher_t *matcher) {
    return init_matcher(matcher, NULL);
}

static const char *match_next(matcher_t *matcher, const char *begin) {
    if (*begin == **matcher) {
        if ((*matcher)[1] != '*') { *matcher += 1; }
        return begin + 1;
    } else if ((*matcher)[1] == '*') {
        *matcher += 2;
        return begin;
    } else {
        return NULL;
    }
}

const char *match_input(matcher_t *matcher, const char *begin, const char *end) {
    if (! matcher) { LOG_E(TAG, "no matcher"); begin = NULL; }

    while (begin && begin < end) {
        if (! *matcher || ! **matcher) { 
            begin = NULL;
        } else if (**matcher == '.') {
            ++begin;
            if ((*matcher)[1] != '*') { *matcher += 1; }
        } else if (**matcher == '\\') {
            *matcher += 1;
            if (begin < end) {
                begin = match_next(matcher, begin);
            } else { LOG_E(TAG, "dangling \\"); begin = NULL; }
        } else { begin = match_next(matcher, begin); } 
    }

    return begin;
}

bool is_matcher_valid(matcher_t *matcher) {
    return matcher && *matcher;
}

bool is_matcher_complete(matcher_t *matcher) {
    return matcher && *matcher && (! **matcher || ((*matcher)[1] == '*' && (*matcher)[2] == 0));
}

