#ifndef ButtonsMap_H
#define ButtonsMap_H
#define Lights
//#define Shutters

String lightingTopic = "LightSystem/"; //nie dzialajace piny button: A0, 0, 1, 33, 50, 27
String shuttersTopic = "Shutters/"; //nie dzialajace piny button: A1, A2, 16, 17, 18, 20, 21, 30, 36, 38, 42, 43

//taken pins (DONT USE!):
//A0 its just broken for me
//10-13; 51, 52 taken by Ethernet shield
Switch *LightSwitches[] =
{
    #ifdef Lights
        new LightSwitch((int[]){40}, 1, (int[]){15}, 1, lightingTopic + "Ganek"),
        new LightSwitch((int[]){A1, 0, 1}, 3, (int[]){39}, 1, lightingTopic + "Wiatrolap"),
        new LightSwitch((int[]){A2, 2, 3}, 3, (int[]){38}, 1, lightingTopic + "Wiatrolap_Ambient"),
        new LightSwitch((int[]){A3}, 1, (int[]){37}, 1, lightingTopic + "Maszynownia"),
        new LightSwitch((int[]){A4}, 1, (int[]){36}, 1, lightingTopic + "Lazienka_Parter"),
        new LightSwitch((int[]){A5, 5}, 2, (int[]){35, 26}, 2, lightingTopic + "Korytarz_Parter"),
        new LightSwitch((int[]){A6}, 1, (int[]){34}, 1, lightingTopic + "Kuchnia"),
        new LightSwitch((int[]){A7}, 1, (int[]){28}, 1, lightingTopic + "Kuchnia_Blaty"),
        new LightSwitch((int[]){A8}, 1, (int[]){32}, 1, lightingTopic + "Kuchnia_Barek"),
        new LightSwitch((int[]){A9}, 1, (int[]){31}, 1, lightingTopic + "Kuchnia_Ambient"),
        new LightSwitch((int[]){A10}, 1, (int[]){30}, 1, lightingTopic + "Jadalnia"),
        //new LightSwitch((int[]){A11}, 1, (int[]){29}, 1, lightingTopic + "Jadalnia"),
        //new LightSwitch((int[]){A12}, 1, (int[]){33}, 1, lightingTopic + "Salon_1"),
        new LightSwitch((int[]){A13}, 1, (int[]){33}, 1, lightingTopic + "Salon"),
        //new LightSwitch((int[]){A14}, 1, (int[]){26}, 1, lightingTopic + "Salon_Ambient"),
        new LightSwitch((int[]){A15}, 1, (int[]){25}, 1, lightingTopic + "Schody"),
        new LightSwitch((int[]){49}, 1, (int[]){24}, 1, lightingTopic + "Korytarz_Pietro"),
        new LightSwitch((int[]){48}, 1, (int[]){23}, 1, lightingTopic + "Pokoj_1"),
        new LightSwitch((int[]){47}, 1, (int[]){22}, 1, lightingTopic + "Pokoj_2"),
        new LightSwitch((int[]){46}, 1, (int[]){21}, 1, lightingTopic + "Pokoj_3"),
        new LightSwitch((int[]){45}, 1, (int[]){20}, 1, lightingTopic + "Pokoj_4"),
        new LightSwitch((int[]){44}, 1, (int[]){19}, 1, lightingTopic + "Pralnia"),
        new LightSwitch((int[]){43}, 1, (int[]){18}, 1, lightingTopic + "Lazienka_Pietro"),
        new LightSwitch((int[]){42}, 1, (int[]){17}, 1, lightingTopic + "Lazienka_Pietro_Ambient"),
        new LightSwitch((int[]){41}, 1, (int[]){16}, 1, lightingTopic + "Lazienka_Pietro_Lustra")
    #endif
    #ifdef Shutters
        new ShutterSwitch((int[]){A0, A3}, (int[]){47, 46}, 1700000, shuttersTopic + "Salon_Zaluzja"),
        new ShutterSwitch((int[]){A4, A5}, (int[]){45, 44}, 1700000, shuttersTopic + "Jadalnia_Zaluzja"),
        new ShutterSwitch((int[]){A6, A7}, (int[]){41, 40}, 230000, shuttersTopic + "Jadalnia_Roleta"),
        new ShutterSwitch((int[]){A8, A9}, (int[]){39, 37}, 230000, shuttersTopic + "Kuchnia_Roleta_Wsch"),
        new ShutterSwitch((int[]){A10, A11}, (int[]){35, 34}, 230000, shuttersTopic + "Kuchnia_Roleta_Ganek"),
        new ShutterSwitch((int[]){A12, A13}, (int[]){33, 32}, 3000000, shuttersTopic + "Pokoj_1_Zaluzja"),
        new ShutterSwitch((int[]){A14, A15}, (int[]){31, 29}, 3000000, shuttersTopic + "Pokoj_2_Zaluzja")
    #endif
};

//Size of the above array
#ifdef Lights
    const int LightSwitchesCount = 22;
#endif
#ifdef Shutters
    const int LightSwitchesCount = 7;
#endif

#endif
