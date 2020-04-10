#!/bin/bash
gcc -o mykernel shell.c helper.c interpreter.c memorymanager.c shellmemory.c kernel.c cpu.c pcb.c ram.c ready_queue.c
