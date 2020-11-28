#include <stdio.h>

int main() {
    printf(" Welcome to                                                                                 \n");
    printf("                                       ##   ##                                              \n");
    printf("                                       ##   ##  ##      ##                                  \n");
    printf(" ########               ########  ##   ##   ##   ##    ##                                   \n");
    printf("   #####                 #####         ##   ##    ##  ##                                    \n");
    printf("     ###                 ###      ##   ##   ##     ####                                     \n");
    printf("      ###       #       ###       ##   ##   ##      ##                                      \n");
    printf("      ###      ###      ###       ##   ###  ###    ##         ##                    ###                 \n");
    printf("       ###    #####    ###                        ##          ##                    ###                 \n");
    printf("       ###   ### ###   ###     #####    ## ####  ##  ######   ##  ##   ##       ##    #   #####         \n");
    printf("        ### ###   ### ###          ##   ###   ##    ##   ##   #####     ##     ##    #   ##             \n");
    printf("        #####      #####       ######   ##    ##   ##    ##   #####      ##   ##          ####          \n");
    printf("         ###        ###       ##   ##   ##    ##    ##   ##   ##  ##       ####              ##         \n");  
    printf("          #          #         ######   ##    ##     ######   ##   ##       ##           #####          \n");
    printf("                                                         ##                ##                           \n");
    printf("                                                    ##  ##                ##                            \n");
    printf("                                                     ####                ##                             \n");
    printf("                                                                                                                \n");
    printf("   # # #                   # # #    # # # # # #     # # # # # #      # # #         # # # # #        # # # #     \n");
    printf("   #    #                 #    #   #           #    #          #     #   #         #        #       #     #     \n");
    printf("    #    #       #       #    #   #    # # #    #   #   # # #   #    #   #         #   # #   #      #     #     \n");
    printf("     #    #     # #     #    #    #    #   #    #   #   #    #   #   #   #         #   #  #   #     #     #     \n");
    printf("      #    #   #   #   #    #     #    #   #    #   #   # # #   #    #   #         #   #   #   #    #     #     \n");
    printf("       #    # #     # #    #      #    #   #    #   #          #     #   #         #   #   #   #     #   #      \n");
    printf("        #    #   #   #    #       #    #   #    #   #   #     #      #   #         #   #  #   #       # #       \n");
    printf("         #      # #      #        #    # # #    #   #   # #    #     #   # # # #   #   # #   #                  \n");
    printf("          #    #   #    #          #           #    #   #  #    #    #         #   #        #         # #       \n");
    printf("           #  #     #  #            # # # # # #     # # #   # #  #   # # # # # #   # # # # #          # #       \n");
    printf("\n");
    printf(" MAIN MENU:     \n");
    printf("  1. NEW GAME   \n");
    printf("  2. LOAD GAME  \n");
    printf("  3. QUIT GAME  \n");

    int opsiMenu;
    
    scanf("%d", opsiMenu);
    // Input menu tidak valid
    while (opsiMenu < 1 || opsiMenu > 3) {
        printf("Menu is not available. Try again!\n");
    }
    
    // Input menu valid
    if (opsiMenu == 1) {
        printf("Starting new game...\n");
        printf("Please enter your name: ");
    }
    
    return 0;
}
