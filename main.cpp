#include <vector>

// Compiler: x86-64 gcc 12.2
// Compiler flags: -O2 -c -masm=intel
int sum(const std::vector<int> &v) {
  int result {0};
  for (size_t i {0}; i < v.size(); ++i) {
    result += v[i];
  }
  return result;
}

/* ----------------------------------------------------

sum(std::vector<int, std::allocator<int> > const&):
        mov     rax, QWORD PTR [rdi+8]
        mov     rcx, QWORD PTR [rdi]
        mov     rsi, rax
        sub     rsi, rcx
        sar     rsi, 2
        cmp     rax, rcx
        je      .L4
        xor     eax, eax
        xor     edx, edx
.L3:
        add     edx, DWORD PTR [rcx+rax*4]
        add     rax, 1
        cmp     rax, rsi
        jb      .L3
        mov     eax, edx
        ret
.L4:
        xor     edx, edx
        mov     eax, edx
        ret

---------------------------------------------------- */

// Compiler: x86-64 gcc 12.2
// Compiler flags: -O2 -c -masm=intel
int sum(const std::vector<int> &v) {
  int result {0};
  for (int i : v) {
    result += i;
  }
  return result;
}

/* ----------------------------------------------------

sum(std::vector<int, std::allocator<int> > const&):
        mov     rax, QWORD PTR [rdi]
        mov     rcx, QWORD PTR [rdi+8]
        xor     edx, edx
        cmp     rcx, rax
        je      .L1
.L3:
        add     edx, DWORD PTR [rax]
        add     rax, 4
        cmp     rax, rcx
        jne     .L3
.L1:
        mov     eax, edx
        ret

---------------------------------------------------- */

// https://godbolt.org/z/nzqW6bnPv
