
#include <stdio.h>
#define MAX_POSITION 20

//--- Data Representation ---//
struct Particle {

    char name[20];

    double mass;          // MeV/c^2
    int charge;           // Electric charge in units of e

    int lepton_number;
    int baryon_number;
};

//--- Particle Datasets ---//
struct Particle electron = {
    "Electron", 0.511, -1, 1, 0
};

struct Particle proton = {
    "Proton", 938.272, 1, 0, 1
};

struct Particle neutron = {
    "Neutron", 939.565, 0, 0, 1
};

struct Particle neutrino_e = {
    "Electron Nu", 0.0, 0, 1, 0
};

struct Particle neutrino_m = {
    "Muon Nu", 0.0, 0, 1, 0
};

struct Particle neutrino_t = {
    "Tau Nu", 0.0, 0, 1, 0
};

//--- Antiparticle Datasets ---//
struct Particle positron = {
    "Positron", 0.511, 1, -1, 0
};

struct Particle antiproton = {
    "Antiproton", 938.272, -1, 0, -1
};

struct Particle antineutron = {
    "Antineutron", 939.565, 0, 0, -1
};

struct Particle antineutrino_e = {
    "Electron AntiNu", 0.0, 0, -1, 0
};

struct Particle antineutrino_m = {
    "Muon AntiNu", 0.0, 0, -1, 0
};

struct Particle antineutrino_t = {
    "Tau AntiNu", 0.0, 0, -1, 0
};

//--- Insert Element ---//
int insert_element(struct Particle array[], int count, struct Particle particle)
{
    if (count >= MAX_POSITION)
    {
        printf("Error: Array is full!\n");
        return -1;
    }

    array[count] = particle;

    return count + 1;
}

//--- conservation calculation ---//
int check_conservation(struct Particle initial[], int size_initial, struct Particle final[], int size_final)
{
    int total_charge = 0;
    int total_baryon = 0;
    int total_lepton = 0;

    int initial_charge = 0;
    int initial_baryon = 0;
    int initial_lepton = 0;

    for(int j = 0; j < size_initial; j++)
    {
        initial_charge += initial[j].charge;
        initial_baryon += initial[j].baryon_number;
        initial_lepton += initial[j].lepton_number;
    }

    for(int i = 0; i < size_final; i++)
    {
        total_charge += final[i].charge;
        total_baryon += final[i].baryon_number;
        total_lepton += final[i].lepton_number;
    }

    if(initial_baryon == total_baryon && initial_charge == total_charge && initial_lepton == total_lepton)
    {
        printf("The decay is valid!\n");
        return 0;
    }

    else
    {
        printf("Decay is invalid!\n");
        return -1;
    }
}

//--- particle interaction examples ---//
int beta_decay()
{
    struct Particle initial[MAX_POSITION];
    struct Particle final[MAX_POSITION];

    int size_initial = 0;
    int size_final = 0;

    //Initial particles
    size_initial = insert_element(initial, size_initial, neutron);

    //Final particles
    size_final = insert_element(final, size_final, proton);
    size_final = insert_element(final, size_final, electron);
    size_final = insert_element(final, size_final, antineutrino_e);

    if(size_initial < 0 || size_final < 0)
    {
        return -1;
    }

    return check_conservation(initial, size_initial, final, size_final);
}

int test_interaction()
{
    struct Particle initial[MAX_POSITION];
    struct Particle final[MAX_POSITION];

    int size_initial = 0;
    int size_final = 0;

    //Initial particles
    size_initial = insert_element(initial, size_initial, antineutrino_t);

    //Final particles
    size_final = insert_element(final, size_final, antiproton);
    size_final = insert_element(final, size_final, electron);
    size_final = insert_element(final, size_final, antineutrino_m);

    if(size_initial < 0 || size_final < 0)
    {
        return -1;
    }

    return check_conservation(initial, size_initial, final, size_final);

}

int main(void)
{

    beta_decay();
    test_interaction();
    return 0;
}
