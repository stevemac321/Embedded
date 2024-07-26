#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>  // For size_t

    enum state { INSERTED, EXISTS, TABLEFULL };

    typedef struct open_table {
        double** buckets;   // Pointer to an array of pointers to double
        size_t size;        // Total size of the table
        size_t count;       // Number of elements inserted
        size_t collisions;  // Number of collisions during insertions
        size_t dupes;
        size_t(*hash1)(double);
        size_t(*hash2)(double);
    } open_table;

    // Function prototypes
    void table_init(open_table* table, const size_t tbsize, size_t(*h1)(double), size_t(*h2)(double));
    void table_destroy(open_table* table);
    enum state table_insert(open_table* table, double value);
    void analyze_clusters(const open_table* table);
    size_t hash1(double value);
    size_t hash2(double value);

#ifdef __cplusplus
}
#endif