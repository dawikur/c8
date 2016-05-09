// Copyright 2016 Dawid Kurek. All Rights Reserved.

#include "chip/executor.hpp"

#include <cstring>
#include <cstddef>

#include "chip/memory.hpp"
#include "random.hpp"


namespace chip {

Executor::Executor() : _lookupTable {

#define Operation(id, name)  [](Opcode const O, Memory& M, GetKey const& getKey)
#define Switch(id, ww, body) Operation(id, id) { switch (O. ww ) { body } }
#define Case(cc, name, body) case cc : { body ; } ; break

  Switch   (0, kk,   {
    Case(0xE0, CLR,    memset(M.Display, 0, sizeof (M.Display))    );
    Case(0xEE, RET,    M.PC = M.Stack[M.SP % 0xF]; --M.SP          );
  }),
  Operation(1, JP)   { M.PC = O.nnn;                               },
  Operation(2, CALL) { ++M.SP; M.SP %= 0xF;
                       M.Stack[M.SP] = M.PC;
                       M.PC = O.nnn;
  },
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
                       M.V[O.x] = static_cast<Byte>(ret); }
    );
    Case( 0x5, SUB,  { M.VF = (M.V[O.x] > M.V[O.y] ? 0x01 : 0x00);
                       M.V[O.x] = M.V[O.x] - M.V[O.y]; }
    );
    Case( 0x6, SHR,  { M.VF = (M.V[O.x] & 0x01);
                       M.V[O.x] >>= 1; }
    );
    Case( 0x7, SUBN, { M.VF = (M.V[O.y] > M.V[O.x] ? 0x01 : 0x00);
                       M.V[O.x] = M.V[O.x] - M.V[O.y]; }
    );
    Case( 0xE, SHL,  { M.VF = (M.V[O.x] & 0x80 ? 0x01 : 0x00);
                       M.V[O.x] <<= 1; }
    );
  }),
  Operation(9, SNE)  { if (M.V[O.x] != M.V[O.y]) { M.PC += 2; }    },
  Operation(A, LD)   { M.I = O.nnn;                                },
  Operation(B, JP)   { M.PC = O.nnn + M.V[0];                      },
  Operation(C, RND)  { M.V[O.x] = Random::get() & O.kk;            },
  Operation(D, DRW)  {
    auto const put = [&M](Byte const a, Byte const b) {
      return ((M.Display[a] ^= b) ^ b) & b;
    };
    Byte kk= 0;
    Byte p = O.n;
    for (auto x = M.V[O.x], y = M.V[O.y]; p--; ) {
        kk |= put( ((x)%64 + (y+p)%32 * 64) / 8, M.Raw[M.I+p] >> (x%8) )
           |  put( ((x+7)%64 + (y+p)%32 * 64) / 8, M.Raw[M.I+p] << (8 - x%8) );
    }
    M.VF = (kk != 0);
  },
  Switch   (E, kk,   {
    Case(0x9E, SKP,    if ( M.Keypad[M.V[O.x]]) { M.PC += 2; }     );
    Case(0xA1, SKNP,   if (!M.Keypad[M.V[O.x]]) { M.PC += 2; }     );
  }),
  Switch   (F, kk,   {
    Case(0x07, LD,     M.V[O.x] = M.DT                             );
    Case(0x0A, LD,     M.V[O.x] = getKey();                        );
    Case(0x15, LD,     M.DT = M.V[O.x]                             );
    Case(0x18, LD,     M.ST = M.V[O.x]                             );
    Case(0x1E, ADD,    M.I = M.I + M.V[O.x]                        );
    Case(0x29, LD,     M.I = offsetof(Memory, Font) + (M.V[O.x] * 5)  );
    Case(0x33, LD,   { M.Raw[M.I+0] = (M.V[O.x] / 100) % 10;
                       M.Raw[M.I+1] = (M.V[O.x] /  10) % 10;
                       M.Raw[M.I+2] = (M.V[O.x] /   1) % 10; }
    );
    Case(0x55, LD,   { for (int i = 0; i <= O.x; ++i) {
                         M.Raw[M.I+i] = M.V[i];
                       } }
    );
    Case(0x65, LD,   { for (int i = 0; i <= O.x; ++i) {
                         M.V[i] = M.Raw[M.I+i];
                       } }
    );
  })

#undef Case
#undef Switch
#undef Operation

} {}

void Executor::operator()(Opcode const opcode,
                          Memory &memory,
                          GetKey const &getKey) {
  _lookupTable[opcode.id](opcode, memory, getKey);
}

}  // namespace chip
