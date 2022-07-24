/*
** For voice dictation/speech-to-text, lower case and remove punctuation.
** Tip of the hat to Ben "Yahtzee" Croshaw ;-)
*/

#include <pebble.h>

/*
** Logical thing to do is include ctype and then use tolower() and ispunct()
** but get link errors, as original binary did not use those headers,
** nor link in required externs :-( Create own routines, use
** non-conflicting names to avoid confusing compiler.
*/

static int my_isupper(int c) {
    return (unsigned)c - 'A' < 26;
}

static unsigned char my_tolower(unsigned char c) {
    if(my_isupper(c))
        return c | 32;
    return c;
}


static int my_isalpha(unsigned char c) {
    return ((unsigned)c | 32) - 'a' < 26;
}
static int my_isdigit(unsigned char c) {
    return (unsigned)c - '0' < 10;
}
static int my_isalnum(unsigned char c) {
    return my_isalpha(c) || my_isdigit(c);
}
static int my_isgraph(unsigned char c) {
    return (unsigned)c - 0x21 < 0x5e;
}
static int my_ispunct(unsigned char c) {
    return my_isgraph(c) && !my_isalnum(c);
}

// Assuming PBL_MICROPHONE...

/*
** Remove punctuation from string, while at it also lower case
** src and dst can be the same string since the destination will never be larger than the source.
** Why? See https://www.reddit.com/r/pebble/comments/j33pnk/rebble_please_tweak_the_handling_of_punctuation/ https://www.reddit.com/r/pebble/comments/t1ja4z/does_ifttt_still_work_with_snowy/
*/
void clean_dictation_string(char *src, char *dst) {
    for (; *src; ++src)
        if (!my_ispunct((unsigned char) *src))
            *dst++ = my_tolower((unsigned char) *src);
    *dst = 0;
}

static DictationSessionStatusCallback real_dictation_session_callback=NULL;

static void lowercase_no_punctuation__dictation_session_callback(DictationSession *session, DictationSessionStatus status, char *transcription, void *context) {
    if (real_dictation_session_callback) {
        clean_dictation_string(transcription, transcription);
        return real_dictation_session_callback(session, status, transcription, context);
    }
}

DictationSession *dictation_session_create__patch(  uint32_t buffer_size,
                                                   DictationSessionStatusCallback callback,
                                                   void *callback_context) {
    real_dictation_session_callback = callback;
    return dictation_session_create(buffer_size, lowercase_no_punctuation__dictation_session_callback, callback_context);
}



