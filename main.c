// CS Amusement Park
// main.c
// Written by Jonathan Sun, z5689744
// on 20/04/2025
//
// Create a program that designs and simulates the operations of a 
// bustling amusement park to ensure all visitors leave with a smile.

#include <stdio.h>

#include "amusement_park.h"

int main(void) {
    // Welcome message
    printf("Welcome to CS Amusement Park!\n");
    
    // NOTE: The printing of the ascii park will fail `1511 style`. 
    // You will not be marked on this.
    printf(
        "                                           o\n"
        "                                         o |\n"
        "                                         |\n"
        "      .       .           ._._.    _                     .===.\n"
        "      |`      |`        ..'\\ /`.. |H|        .--.      .:'   `:.\n"
        "     //\\-...-/|\\         |- o -|  |H|`.     /||||\\     ||     ||\n"
        " ._.'//////,'|||`._.    '`./|\\.'` |\\\\||:. .'||||||`.   `:.   .:'\n"
        " ||||||||||||[ ]||||      /_T_\\   |:`:.--'||||||||||`--..`=:='...\n\n"
    );

    printf("Enter the name of the park: ");
    char name[MAX_SIZE];
    scan_name(name);
    struct park *park = initialise_park(name);


    // Command loop
    command_loop(park);

    // End message
    printf("\nGoodbye!\n");

    return 0;
}