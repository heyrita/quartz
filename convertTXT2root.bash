#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Thu Oct  3 22:09:56 CEST 2019                                        #
# Autor: Rita Kvitochka                                                #
#                                                                      #
# File description:                                                    #
#                  This script runs convertTXT2root.                   #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function convertTXT2root_bash {
    make clean;
    make;
    
    ./convertTXT2root 0 ../data/11.txt ../root/11.root 

}

convertTXT2root_bash
