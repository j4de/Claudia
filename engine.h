/***************************************************************************************
* Copyright (c) 2014, Antonio Garro.                                                   *
* All rights reserved                                                                  *
*                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are *
* permitted provided that the following conditions are met:                            *
*                                                                                      *
* 1. Redistributions of source code must retain the above copyright notice, this list  *
* of conditions and the following disclaimer.                                          *
*                                                                                      *
* 2. Redistributions in binary form must reproduce the above copyright notice, this    *
* list of conditions and the following disclaimer in the documentation and/or other    *
* materials provided with the distribution.                                            *
*                                                                                      *
* 3. Neither the name of the copyright holder nor the names of its contributors may be *
* used to endorse or promote products derived from this software without specific      *
* prior written permission.                                                            *
*                                                                                      * 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"          *
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE            *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE           *
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE            *
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL    *
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR           *
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER           *
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     *
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF        *
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                    *
***************************************************************************************/

#ifndef ENGINEH
#define ENGINEH

#include <time.h>
#include "board.h"
#include "book.h"

enum commands {COM_INVALID, COM_QUIT, COM_MOVE, COM_GO, COM_STOP, COM_PERFT, COM_POSITION,
                COM_UCI, COM_IS_READY, COM_SETOPTION};
enum subcommands {GO_INFINITE, GO_DEPTH, GO_TIME, W_TIME, B_TIME, W_INC, B_INC};

struct CONTROL {
    int wtime, btime, wtime_inc, btime_inc;
    clock_t init_time, wish_time, max_time;
    unsigned int max_depth;
    unsigned long long node_count;
    char uci, stop;
};
extern struct CONTROL control;

void IterativeDeep();
int AlphaBeta(const unsigned int, int, const int, const int);
int Quiescent(int, const int);
int RetrievePV(move*, const unsigned int);

int ParseInput(char*);
int ParseGoParams(char*);
int Command(char *);

static void ManageTimes()
{
    if(board.white_to_move){
        control.wish_time = control.wtime/30 + control.wtime_inc;
        control.max_time = control.wtime;
    }
    else{
        control.wish_time = control.btime/30 + control.btime_inc;
        control.max_time = control.btime;
    }
}

static void ResetTimes()
{
    control.wtime = 0; control.btime = 0;
    control.wtime_inc = 0; control.btime_inc = 0;
}

static void think(void *pparams)
{
    if(PolyglotChooseMove(PolyglotKey())) return;
    IterativeDeep();
    return;
}

#endif
