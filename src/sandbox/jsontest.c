#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

const char *JSON_STRING =
    "{\"user\":\"johndoe\", \"admin\": false, \"uid\":1000,\n "
    "\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
            strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
    return -1;
}

char[] concata(char*  a[], char* b[]) {
    /*Out put of concat operation*/
    char* c;

    /* Elements in a and b */
    int aelems = sizeof(a) / sizeof(a[0]);
    int belems = sizeof(a) / sizeof(b[0]);

    /* Make space for c*/
    c = malloc( sizeof(a)+sizeof(b) );
    printf("%d bytes alloced for concat");//debug

    int ai;
    for(ai = 0; ai < aelems; ai++)
        c[ai] = a[ai];

    for(int bi = 0; bi < belems; bi++)
        c[ai+bi] = b[bi];

    return c;
}

int main (int args, char* argc[]) {
    int i;
    int r;
    jsmn_parser p;
    jsmntok_t t[128];

    if( args > 1 ) {
        FILE* ptr_file;
        char buf[1000];
        char* built_str;

        built_str = malloc(0);


        ptr_file = fopen(argc[1], "r");
        if( !ptr_file ) return -1;

        while (fgets(buf, 1000, ptr_file) != NULL ) {
            printf("%s", buf);
            concata(built_str, buf);
        }
        fclose(ptr_file);
        return 0;
    }

    jsmn_init(&p);
    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        printf("Failed to Parse JSON: %d\n", r);
        return r;
    }

    /* the top level object should be an object */
    if ( r < 1 || t[0].type != JSMN_OBJECT) {
        printf("object expected\n");
        return 1;
    }

    for (i = 1; i < r; i++) {
        if (jsoneq(JSON_STRING, &t[i], "user") == 0) {
            printf("- User: %.*s\n", t[i+1].end-t[i+1].start,
                    JSON_STRING + t[i+1].start);
            i++;
        }
        else if (jsoneq(JSON_STRING, &t[i], "admin") == 0) {
            printf("- Admin: %.*s\n", t[i+1].end-t[i+1].start,
                    JSON_STRING + t[i+1].start);
            i++;
        }
        else if (jsoneq(JSON_STRING, &t[i], "uid") == 0) {
            printf("- Uid: %.*s\n", t[i+1].end-t[i+1].start,
                    JSON_STRING + t[i+1].start);
            i++;
        }
        else if (jsoneq(JSON_STRING, &t[i], "groups") == 0) {
            int j;
            printf("- Groups\n");
            if (t[i+1].type != JSMN_ARRAY) {
                continue;
            }
            for ( j = 0; j < t[i+1].size; j++) {
                jsmntok_t *g = &t[i+j+2];
                printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
            }
            i += t[i+1].size + 1;
        }
        else {
            printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
                    JSON_STRING + t[i].start);
        }
    }
    return 0;
}
