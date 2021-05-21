#
# Copyright (c) 2021 Lab5e AS
#

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(CozIR)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/cozir.c)
target_sources(app PRIVATE src/modeminfo.c)
target_sources(app PRIVATE src/message.c)


