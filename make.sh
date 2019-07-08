#!/bin/bash

./zokrates compile -i eq.code
./zokrates setup
./zokrates compute-witness -a 
./zokrates generate-proof
./zokrates export-verifier
