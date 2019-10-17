#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Thu Oct 26 16:24:03 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script prints list the functions in a shared   #
# library.                                            #
#                                                                      #
# Input paramete:                                                      #
# NON.                                                #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function analyzer_sh {

    make clean
    make
    ./analyzer rootfiles/list.txt  hist.root

}

analyzer_sh



