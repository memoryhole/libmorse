#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "data.h"

#define TREE_LEN 64

typedef struct tree {
    uint8_t data[TREE_LEN];
    uint8_t len;
} tree;

void dump_tree(tree tree);

void die(const char *msg) {
    fputs(msg, stderr);
    abort();
}

tree create_tree(void) {
    tree tree;
    memset(&tree, 0, sizeof(tree));

    uint8_t max_offset = 0;

    for (uint8_t i = 0; i < morse_codes_len; i++) {
        const char *code = morse_codes[i];
        const uint8_t code_len = strlen(code);

        const char value = i + 'A';

        printf("Inserting %c = %s\n", value, code);

        uint8_t *pos = tree.data;
        uint8_t offset = 0;

        for (uint8_t j = 0; j < code_len; j++) {
            if (code[j] == '.') {
                offset = 2 * offset + 1;
            } else {
                offset = 2 * offset + 2;
            }
        }
        pos = tree.data + offset;

        *pos = value;

        if (offset > max_offset) {
            max_offset = offset;
        }
    }

    tree.len = max_offset;

    return tree;
}

void dump_node(tree tree, uint8_t i, uint8_t offset) {
    if (i < tree.len) {
        printf("%2d %*s", i, offset, "");

        if (i == 0) {
            printf("ROOT");

        } else if (i % 2) {
            printf(".");
        } else {
            printf("-");
        }

        if (tree.data[i] != 0) {
            printf(" [%c]\n", tree.data[i]);
        } else {
            printf(" [ ]\n");
        }

        dump_node(tree, 2 * i + 1, offset + 1);
        dump_node(tree, 2 * i + 2, offset + 1);
    }
} 

void dump_tree(tree tree) {
    printf("Tree has %d nodes\n", tree.len);
    dump_node(tree, 0, 0);
}

void usage(void) {
    fprintf(stderr, "usage: buildtree <outputfile>\n");
}

int main(int argc, char **argv) {

    if (argc < 2) {
        usage();
        exit(EXIT_FAILURE);
    } else if (strncmp(argv[0], "-h", 2) == 0 || strncmp(argv[0], "--help", 6) == 0) {
        usage();
        exit(EXIT_FAILURE);
    }

    tree tree = create_tree();
    dump_tree(tree);

    FILE *output = fopen(argv[1], "w");
    if (!output) {
        die("failed to open outputfile");
    }

    int result = fwrite(tree.data, sizeof(uint8_t), tree.len, output);
    if (result != tree.len) {
        die("failed to write outputfile");
    }
    fclose(output);

    exit(EXIT_SUCCESS);
}
