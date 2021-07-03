#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include "src/montecarlo.h"
#include "src/timer.h"
#include <unistd.h>
#include <math.h>

#define SERVER_RANK 0

int main (int argc, char* argv[]) {

    MPI_Status status;
    
    pid_t process_rank;
    int src_rank;
    int number_of_processes;
    int msg_tag;
    int n = 100000000;

    double buffer = 0;
    double pi = 0;
    double sum = 0;

    Timer timer = {
        .start = {0, 0},
        .end = {0, 0},
        .start_ns = 0,
        .end_ns = 0,
        .elapsed_time = 0
    }; 
    
    
    srand(time(NULL));
    MPI_Init (&argc, &argv);

    MPI_Comm_size (MPI_COMM_WORLD, &number_of_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &process_rank);

    if(process_rank == SERVER_RANK) {
        clock_gettime(CLOCK_MONOTONIC, &timer.start);
    }

    // Server broadcast
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_rank == SERVER_RANK) {
        for (src_rank = 1; src_rank < number_of_processes; src_rank++) {
            msg_tag = 0;
            MPI_Recv(&buffer, 1, MPI_DOUBLE, src_rank, msg_tag, MPI_COMM_WORLD, &status);
            sum += buffer;
        }
    } 
    else { //clients
        msg_tag = 0;
        pi = monte_carlo_pi(n);
        MPI_Send(&pi, 1, MPI_DOUBLE, SERVER_RANK, msg_tag, MPI_COMM_WORLD);
    }
        
    if(process_rank == SERVER_RANK) {

        pi = sum / (number_of_processes - 1);
        
        clock_gettime(CLOCK_MONOTONIC, &timer.end);

        timer.start_ns = tm_timespec_to_nanosconds(timer.start);
        timer.end_ns = tm_timespec_to_nanosconds(timer.end);
        timer.elapsed_time = timer.end_ns - timer.start_ns;
        
        printf("server(monte_carlo: elapsed_time)> %ldns\n", timer.elapsed_time);
        printf("server(pi: aproximation)> %.10lf\n", pi);
        printf("server(pi: error)> %g\n", fabs(M_PI - pi));
    }


    MPI_Finalize();

    return 0;
}
