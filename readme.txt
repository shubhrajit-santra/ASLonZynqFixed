
*************** Subset + Arm-Learning Algorithm Implementation on Zynq ***************

--> This repository contains all the source codes and a block diagram of the architecture for the Zynq implementation of the multi-armed bandit (MAB) subset + arm-learning algorithm.
--> This implementation is for four arms with a minimum subset size of two, that is, N = 4 and K = 2.
--> The .cpp files are the main files and the testbench files that have been used for generating the HLS IPs usign Vivado HLS.
--> The variables used in the Vivado HLS codes are of fixed-point type.
--> The mtwist.h file is a helper file for generating the pseudo-random number generator (PRNG) inside the "inform_ls" or "lite_to_stream" HLS IP.
--> The .png file is a snapshot of the block diagram generated in Vivado IPI.
--> The "helloworld_sdk" file is the C code used to generate the baremetal application in Vivado SDK (Software Development Kit).
--> The "helloworld_arm" file is the C code for implementing the entire algorithm in the ARM processor itself using Vivado SDK.