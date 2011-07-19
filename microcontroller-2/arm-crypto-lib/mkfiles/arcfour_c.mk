# Makefile for ARCFOUR (RC4 compatible)
ALGO_NAME := ARCFOUR_C

# comment out the following line for removement of ARCFOUR from the build process
STREAM_CIPHERS += $(ALGO_NAME)

$(ALGO_NAME)_DIR      := arcfour/
$(ALGO_NAME)_INCDIR   := memxor/ scal/
$(ALGO_NAME)_OBJ      := arcfour.o
$(ALGO_NAME)_TEST_BIN := main-arcfour-test.o scal_arcfour.o $(CLI_STD) $(SCAL_STD)
$(ALGO_NAME)_NESSIE_TEST      := "nessie"
$(ALGO_NAME)_PERFORMANCE_TEST := "performance"

