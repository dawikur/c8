// Copyright 2016 Dawid Kurek. All Rights Reserved.

#ifndef SRC_EXECUTOR_HPP_
#define SRC_EXECUTOR_HPP_

#include <cstddef>
#include <cstring>
#include <random>

#include "memory.hpp"
#include "opcode.hpp"

class random {
 public:
  static Byte get() {
    static random r;
    return r.distribution(r.generator);
  }

 private:
  random() : randomDevice{}, generator{randomDevice()}, distribution{} {}

  std::random_device randomDevice;
  std::mt19937 generator;
  std::uniform_int_distribution<Byte> distribution;
};

class Executor {
 public:
  Executor()
    : lookupTable {

#define Operation(id, name)  [](Opcode const O, Memory& M, bool& waitForKey)
#define Switch(id, ww, body) Operation(id, id) { switch (O. ww ) { body } }
#define Case(cc, name, body) case cc : { body ; } ; break

      Switch   (0, kk,   {
        Case(0xE0, CLR,    memset(M.Display, 0, sizeof (M.Display))    );
        Case(0xEE, RET,    M.PC = M.Stack[M.SP]; --M.SP                );
      }),
      Operation(1, JP)   { M.PC = O.nnn;                               },
      Operation(2, CALL) { ++M.SP; M.Stack[M.SP] = M.PC; M.PC = O.nnn; },
      Operation(3, SE)   { if (M.V[O.x] == O.kk)     { M.PC += 2; }    },
      Operation(4, SNE)  { if (M.V[O.x] != O.kk)     { M.PC += 2; }    },
      Operation(5, SE)   { if (M.V[O.x] == M.V[O.y]) { M.PC += 2; }    },
      Operation(6, LD)   { M.V[O.x] = O.kk;                            },
      Operation(7, ADD)  { M.V[O.x] = M.V[O.x] + O.kk;                 },
      Switch   (8, n,    {
        Case( 0x0, LD,     M.V[O.x] = M.V[O.y]                         );
        Case( 0x1, OR,     M.V[O.x] = M.V[O.x] | M.V[O.y]              );
        Case( 0x2, AND,    M.V[O.x] = M.V[O.x] & M.V[O.y]              );
        Case( 0x3, XOR,    M.V[O.x] = M.V[O.x] ^ M.V[O.y]              );
        Case( 0x4, ADD,  { Word ret = M.V[O.x] + M.V[O.y];
                           M.VF = (ret > 255 ? 0x01 : 0x00);
                           M.V[O.x] = ret;          }                  );
        Case( 0x5, SUB,  { M.VF = (M.V[O.x] > M.V[O.y] ? 0x01 : 0x00);
                           M.V[O.x] = M.V[O.x] - M.V[O.y]; }           );
        Case( 0x6, SHR,  { M.VF = (M.V[O.x] & 0x01);
                           M.V[O.x] >>= 1; }                           );
        Case( 0x7, SUBN, { M.VF = (M.V[O.y] > M.V[O.x] ? 0x01 : 0x00);
                           M.V[O.x] = M.V[O.x] - M.V[O.y]; }           );
        Case( 0xE, SHL,  { M.VF = (M.V[O.x] & 0x80 ? 0x01 : 0x00);
                           M.V[O.x] <<= 1; }                           );
      }),
      Operation(9, SNE)  { if (M.V[O.x] != M.V[O.y]) { M.PC += 2; }    },
      Operation(A, LD)   { M.I = O.nnn;                                },
      Operation(B, JP)   { M.PC = O.nnn + M.V[0];                      },
      Operation(C, RND)  { M.V[O.x] = random::get() & O.kk;            },
      Operation(D, DRW)  { M.VF = 0;
                           Byte dst = M.V[O.x] + M.V[O.y]; // hmm, what and where is stride?
                           for (auto p = 0; p < O.n; ++p) {
                             Byte const byte = M.V[M.I + p];
                             Byte const before = M.Display[dst + p];
                             M.Display[dst + p] ^= byte;
                             if (before != M.Display[dst + p]) {
                               M.VF = 1;
                             }
                           }                                           },
      Switch   (E, kk,   {
        Case(0x9E, SKP,    if ( M.Keypad[M.V[O.x]]) { M.SP += 2; }     );
        Case(0xA1, SKNP,   if (!M.Keypad[M.V[O.x]]) { M.SP += 2; }     );
      }),
      Switch   (F, kk,   {
        Case(0x07, LD,     M.V[O.x] = M.DT                             );
        Case(0x0A, LD,     waitForKey = true;                          );
        Case(0x15, LD,     M.DT = M.V[O.x]                             );
        Case(0x18, LD,     M.ST = M.V[O.x]                             );
        Case(0x1E, ADD,    M.I = M.I + M.V[O.x]                        );
        Case(0x29, LD,     M.I = offsetof(Memory, Keypad) + (O.x * 5)  );
        Case(0x33, LD,   { auto const Vx = M.V[O.x];
                           M.Raw[M.I+0] = (Vx / 10) % 10;
                           M.Raw[M.I+1] = (Vx / 10) % 10;
                           M.Raw[M.I+2] = (Vx / 1 ) % 10; }            );
      })

#undef Case
#undef Switch
#undef Operation

    } {}

  void operator()(Opcode const opcode, Memory &memory) {
    bool dummy;
    (*this)(opcode, memory, dummy);
  }

  void operator()(Opcode const opcode, Memory &memory, bool &waitForKey) {
    waitForKey = false;
    lookupTable[opcode.id](opcode, memory, waitForKey);
  }

 private:

  void (*lookupTable[16])(Opcode const, Memory&, bool &waitForKey);
};

#endif  // SRC_EXECUTOR_HPP_
