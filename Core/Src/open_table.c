/*==============================================================================
 Name        : open_table.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/

#include "open_table.h"
#include "common.h"  // For Heap_Malloc and Heap_Free
#include <stdio.h>   // For printf
#include <assert.h>  // For assert

/**=============================================================================
 Function:   open_table_init

 Purpose:    Initializes the open_table structure.

 Parameters: table: open_table structure pointer.
             tbsize: size of the hash table, should be a prime number.
             h1: primary hash function.
             h2: secondary hash function (can be the same as h1).

==============================================================================*/
void table_init(open_table* table, const size_t tbsize, size_t(*h1)(double), size_t(*h2)(double)) 
{
    table->buckets = (double**)Heap_Malloc(tbsize * sizeof(double*));
    for (size_t i = 0; i < tbsize; ++i) {
        table->buckets[i] = NULL; // Initialize all buckets to NULL
    }
    table->size = tbsize;
    table->count = 0;
    table->collisions = 0;
    table->dupes = 0;
    table->hash1 = h1;
    table->hash2 = h2;
}

/**=============================================================================
 Function:   open_table_destroy

 Purpose:    Destroys the open_table structure and frees memory.

 Parameters: table: open_table structure pointer.

==============================================================================*/
void table_destroy(open_table* table) {
    for (size_t i = 0; i < table->size; ++i) {
        if (table->buckets[i] != NULL) {
            Heap_Free(table->buckets[i]);
        }
    }
    Heap_Free(table->buckets);
    table->buckets = NULL;
    table->size = 0;
    table->count = 0;
    table->collisions = 0;
    table->hash1 = NULL;
    table->hash2 = NULL;
}

/**=============================================================================
 Function:   open_table_insert

 Purpose:    Inserts a double value into the hash table.

 Parameters: table: open_table structure pointer.
             value: value to insert.

 Returns:    enum state indicating INSERTED, EXISTS, or TABLEFULL.

==============================================================================*/
#include <math.h>  // For fabs

#define EPSILON 1e-9

enum state table_insert(open_table* table, double value) {
    size_t index = table->hash1(value) % table->size;
    size_t step = table->hash2(value) % table->size;

    for (size_t i = 0; i < table->size; ++i) {
        if (table->buckets[index] == NULL) {
            table->buckets[index] = (double*)Heap_Malloc(sizeof(double));
            *table->buckets[index] = value;
            table->count++;
            return INSERTED;
        }
        else if (fabs(*table->buckets[index] - value) < EPSILON) {
            table->dupes++;
            return EXISTS;
        }
        table->collisions++;
        index = (index + step) % table->size;
    }
    return TABLEFULL;
}

/**=============================================================================
 Function:   analyze_clusters

 Purpose:    Analyzes and prints the cluster information of the hash table.

 Parameters: table: const open_table structure pointer.

==============================================================================*/
void analyze_clusters(const open_table* table) 
{
    size_t cluster_size = 0;
    size_t cluster_count = 0;
    size_t total_cluster_length = 0;
    size_t largest_cluster_size = 0;
    
    for (int i = 0; i < table->size; i++) {
        if (table->buckets[i] == NULL) {
            printf("%s ", "_");
        }
        else {
            printf("%s ", "F");
        }
    }
    for (size_t i = 0; i < table->size; ++i) {
        if (table->buckets[i] != NULL) {
            cluster_size++;
        }
        else if (cluster_size > 0) {
            cluster_count++;
            total_cluster_length += cluster_size;
            if (cluster_size > largest_cluster_size) {
                largest_cluster_size = cluster_size;
            }
            cluster_size = 0;
        }
    }

    // Check for a cluster at the end of the table
    if (cluster_size > 0) {
        cluster_count++;
        total_cluster_length += cluster_size;
        if (cluster_size > largest_cluster_size) {
            largest_cluster_size = cluster_size;
        }
    }

    double average_cluster_length = cluster_count ? (double)total_cluster_length / cluster_count : 0.0;
    printf("Table size: %u\n", table->size);
    printf("Number of elements: %u\n", table->count);
    printf("Number of duplicate attempts: %u\n", table->dupes);
    printf("Number of collisions: %u\n", table->collisions);
    printf("Cluster count: %zu\n", cluster_count);
    printf("Total cluster length: %u\n", total_cluster_length);
    printf("Largest cluster size: %u\n", largest_cluster_size);
    printf("Average cluster length: %.2f\n", average_cluster_length);
}
/**=============================================================================
 Function:   hash1

 Purpose:    Primary hash function.

 Parameters: value: double value to hash.

 Returns:    Hash value as size_t.

==============================================================================*/
size_t hash1(double value) 
{
    size_t val = 0;
    size_t tmp = 0;
    unsigned char* ptr = (unsigned char*)&value;
    for (size_t i = 0; i < sizeof(double); ++i) {
        val = (val << 4) + ptr[i];
        if ((tmp = (val & 0xf0000000))) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
    }
    return val;
}

/**=============================================================================
 Function:   hash2

 Purpose:    Secondary hash function.

 Parameters: value: double value to hash.

 Returns:    Hash value as size_t.

==============================================================================*/
size_t hash2(double value) {
    return (size_t)value / 2 + 1; // Simple secondary hash function
}
