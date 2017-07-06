#define N_EIG 6
#define e_EIG 1e-12
#define L_EIG 5000

unsigned char eigcal(const float matrix_in[N_EIG*N_EIG], float eigvalue[N_EIG], float eigvector[N_EIG*N_EIG]);
