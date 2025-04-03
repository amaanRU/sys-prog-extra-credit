#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Notes:
- Must have function with the following signature, void kmeans_clustering(float* pixels, int num_pixels, int num_centroids, int max_iters, int seed, float* centroids, int* labels)

*/

// Euclidean distance is the metric used ( i.e. sqrt((red1-red2)^2 + (green1-green2) + (blue1-blue2)^2). 
float distance(float* a, float* b) {
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]));
}

void kmeans_clustering(float* pixels, int num_pixels, int num_centroids, int max_iters, int seed, float* centroids, int* labels) {
    srand(seed); 

    // Initialize each centroid with a random pixel
    for (int i = 0; i < num_centroids; i++) {
        int randomPixel = rand() % num_pixels;

        centroids[i * 3] = pixels[randomPixel * 3];
        centroids[i * 3 + 1] = pixels[randomPixel * 3 + 1];
        centroids[i * 3 + 2] = pixels[randomPixel * 3 + 2];
    }

    // Handle each iteration
    for (int iter = 0; iter < max_iters; iter++) {
        for (int i = 0; i < num_pixels; i++) {
            int best_cluster = 0;
            float min_dist = distance(&pixels[i * 3], &centroids[0]);
            
            for (int j = 1; j < num_centroids; j++) {
                float dist = distance(&pixels[i * 3], &centroids[j * 3]);

                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }

            labels[i] = best_cluster;
        }

        int* counts = (int*)calloc(num_centroids, sizeof(int));
        float* new_centroids = (float*)calloc(num_centroids * 3, sizeof(float));

        for (int i = 0; i < num_pixels; i++) {
            int cluster = labels[i];

            new_centroids[cluster * 3] += pixels[i * 3];
            new_centroids[cluster * 3 + 1] += pixels[i * 3 + 1];
            new_centroids[cluster * 3 + 2] += pixels[i * 3 + 2];

            counts[cluster]++;
        }

        for (int j = 0; j < num_centroids; j++) {
            if (counts[j] > 0) {
                centroids[j * 3] = new_centroids[j * 3] / counts[j];
                centroids[j * 3 + 1] = new_centroids[j * 3 + 1] / counts[j];
                centroids[j * 3 + 2] = new_centroids[j * 3 + 2] / counts[j];
            }
        }

        // Free memory
        free(counts);
        free(new_centroids);
    }
}
