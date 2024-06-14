#include <stdio.h>
#include <stdlib.h>
#include "8085assembler.h"
int getNumber(FILE * , char * );
int cmpstr(char * , char * );
char MOV(char * );
char MVI(char);
char LXI(char * );
char DAD(char * );
char INX(char * );
char DCX(char * );
char PUSH(char * );
char POP(char * );
char ADD(char);
char ANA(char);
char ORA(char);
char CMP(char);
char XRA(char);
char INR(char);
char DCR(char);
char ADC(char);
char SUB(char);
char SBB(char);

char * lower(char * );
char * capital(char*);
int power(int, int);
int stringNum(char * );
void error(FILE * , FILE * );
void printLabels();
void clearMem();

struct labels *head = NULL, *last = NULL, *temp = NULL;
void main(int argc, char ** argv) {
  head = calloc(1, sizeof(struct labels));
  last = head;
  FILE * file, * binFile;
  char c;
  int n;
  long bytenum = 0;
  char instruct[6];
  char argument[20];
  if (argc <= 1) {
    printf("[-] No file as argument\n");
    return;
  }
  file = fopen(argv[1], "r");
  binFile = fopen("a.bin", "wb");
  if (file == NULL) {
    printf("[-] Couldn't open the file '%s'\n", argv[1]);
    return;
  }
  while ((c = fgetc(file)) != EOF) {
    if (c == ' ') continue;
    if (c == ';') {
      while ((c = fgetc(file)) != '\n');
      continue;
    }
    if ((c < 91 && c > 64) || (c > 96 && c < 123)) {
      int k = 0;
      do {
        if (c == EOF || c == '\n' || c == ';') break;
        instruct[k] = c;
        (last -> name)[k] = c;
        k++;
        if (k-1 >= 4) {
          while ((c = fgetc(file)) != ':') {
            (last -> name)[k] = c;
            k++;
            if ((c == '\n') || (k > MAXLABELNAME - 2) || (c == ' ')) {
              error(file, binFile);
              return;
            }
          }
        }
        if (c == ':') {
          (last->name)[k] = 0;
          (last -> address) = bytenum;
          last -> next = calloc(1, sizeof(struct labels));
          last = last -> next;
          break;
        }
      } while ((c = fgetc(file)) != ' ');

      instruct[k] = 0;
      if (c == ':') continue;
      // printf("Instruction found: %s\n", instruct);
      if (c == ';' || c == EOF || c == '\n') {
        if (cmpstr(capital(instruct), "XCHG")) {
          // printf("%x\n", XCHG);
          bytenum += 1;
          fputc(XCHG, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "DAA")) {
          bytenum += 1;
          fputc(DAA, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "CMA")) {
          bytenum += 1;
          fputc(CMA, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "CMC")) {
          bytenum += 1;
          fputc(CMC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "STC")) {
          bytenum += 1;
          fputc(STC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RLC")) {
          bytenum += 1;
          fputc(RLC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RRC")) {
          bytenum += 1;
          fputc(RRC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RAL")) {
          printf("%x\n", RAL);
          continue;
        }
        if (cmpstr(capital(instruct), "RAR")) {
          bytenum += 1;
          fputc(RAR, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RET")) {
          bytenum += 1;
          fputc(RET, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RNZ")) {
          bytenum += 1;
          fputc(RNZ, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RZ")) {
          bytenum += 1;
          fputc(RZ, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RNC")) {
          bytenum += 1;
          fputc(RNC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RC")) {
          bytenum += 1;
          fputc(RC, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RPO")) {
          bytenum += 1;
          fputc(RPO, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RPE")) {
          bytenum += 1;
          fputc(RPE, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RP")) {
          bytenum += 1;
          fputc(RP, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RM")) {
          bytenum += 1;
          fputc(RM, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "PCHL")) {
          bytenum += 1;
          fputc(PCHL, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "XTHL")) {
          bytenum += 1;
          fputc(XTHL, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "SPHL")) {
          bytenum += 1;
          fputc(SPHL, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "EI")) {
          bytenum += 1;
          fputc(EI, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "DI")) {
          bytenum += 1;
          fputc(DI, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "RIM")) {
          bytenum += 1;
          fputc(RIM, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "SIM")) {
          bytenum += 1;
          fputc(SIM, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "NOP")) {
          bytenum += 1;
          fputc(NOP, binFile);
          continue;
        }
        if (cmpstr(capital(instruct), "HLT")) {
          bytenum += 1;
          fputc(HLT, binFile);
          continue;
        }
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        if (c == EOF) break;
      }

      if (c == ';' || c == '\n' || c == EOF) {
        error(file, binFile);
        return;
      }
      if (cmpstr(capital(instruct), "MOV")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        while ((c = fgetc(file)) == ' ');
        if (c == ',') {
          while ((c = fgetc(file)) == ' ');
          argument[k] = c;
          k++;
          argument[k] = 0;
        } else {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(MOV(argument), binFile);
        // printf("%x\n", MOV(argument));
        continue;
      }
      if (cmpstr(capital(instruct), "MVI")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(MVI(argument[0]), binFile);
        // printf("%x", MVI(argument[0]));
        while ((c = fgetc(file)) == ' ');
        if (c == ',') {
          n = getNumber(file, argument);
          if (n == -1) {
            error(file, binFile);
            return;
          }
          // printf(" %x\n",(char)n);
          bytenum += 1;
          fputc((char) n, binFile);
          continue;
        } else {
          error(file, binFile);
          return;
        }
        continue;
      }

      if (cmpstr(capital(instruct), "LXI")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'P') {
          argument[k] = c;
          k++;
        }
        if (c != ',')
          while ((c = fgetc(file)) == ' ');
        if (c == ',') {
          n = getNumber(file, argument + k);
          if (n == -1) {
            error(file, binFile);
            return;
          }

          // printf("%x %s\n", LXI(argument), argument+k);
          bytenum += 1;
          fputc(LXI(argument), binFile);
          bytenum += 1;
          fputc((char)(n), binFile);
          bytenum += 1;
          fputc((char)(n >> 8), binFile);
          continue;
        } else {
          error(file, binFile);
          return;
        }
        continue;
      }

      if (cmpstr(capital(instruct), "LDAX")) {
        while ((c = fgetc(file)) == ' ');
        if (c == 'B') {
          bytenum += 1;
          fputc(LDAXB, binFile);
        } else if (c == 'D') {
          bytenum += 1;
          fputc(LDAXD, binFile);
        } else {
          error(file, binFile);
          return;
        }
        continue;
      }
      if (cmpstr(capital(instruct), "STAX")) {
        while ((c = fgetc(file)) == ' ');
        if (c == 'B') {
          bytenum += 1;
          fputc(STAXB, binFile);
        } else if (c == 'D') {
          bytenum += 1;
          fputc(STAXD, binFile);
        } else {
          error(file, binFile);
          return;
        }
        continue;
      }
      if (cmpstr(capital(instruct), "LDA")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(LDA, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "STA")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(STA, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ADD")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(ADD(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ADC")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(ADC(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "SUB")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(SUB(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "SBB")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(SBB(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ADI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(ADI, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ACI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(ACI, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "SUI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(SUI, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "SBI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(SBI, binFile);
        bytenum += 1;
        fputc((char)(n), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "DAD")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'P') {
          argument[k] = c;
          k++;
        }
        bytenum += 1;
        fputc(DAD(argument), binFile);
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        continue;
      }
      if (cmpstr(capital(instruct), "INR")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(INR(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "DCR")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(DCR(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "INX")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'P') {
          argument[k] = c;
          k++;
        }
        bytenum += 1;
        fputc(INX(argument), binFile);
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        continue;
      }
      if (cmpstr(capital(instruct), "DCX")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'P') {
          argument[k] = c;
          k++;
        }
        bytenum += 1;
        fputc(DCX(argument), binFile);
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        continue;
      }
      if (cmpstr(capital(instruct), "ANA")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(ANA(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ORA")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(ORA(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "XRA")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(XRA(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CMP")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        bytenum += 1;
        fputc(CMP(argument[0]), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ANI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(ANI, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "XRI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(XRI, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "ORI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(ORI, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CPI")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CPI, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "IN")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(IN, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "OUT")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(OUT, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "PUSH")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'S') {
          argument[k] = c;
          k++;
          if ((c = fgetc(file)) == 'W') {
            argument[k] = c;
            k++;
          }
        }
        bytenum += 1;
        fputc(PUSH(argument), binFile);
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        continue;
      }
      if (cmpstr(capital(instruct), "POP")) {
        while ((c = fgetc(file)) == ' ');
        k = 0;
        argument[k] = c;
        k++;
        if ((c = fgetc(file)) == 'S') {
          argument[k] = c;
          k++;
          if ((c = fgetc(file)) == 'W') {
            argument[k] = c;
            k++;
          }
        }
        bytenum += 1;
        fputc(POP(argument), binFile);
        if (c == ';')
          while ((c = fgetc(file)) != '\n');
        continue;
      }
      if (cmpstr(capital(instruct), "JMP")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JMP, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JNZ")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JNZ, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JZ")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JZ, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JNC")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JNC, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JC")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JC, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JPO")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JPO, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JPE")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JPE, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JP")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JP, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "JM")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(JM, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CALL")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CALL, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CNZ")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CNZ, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CZ")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CZ, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CNC")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CNC, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CC")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CC, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CPO")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CPO, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CPE")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CPE, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CP")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CP, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }
      if (cmpstr(capital(instruct), "CM")) {
        n = getNumber(file, argument);
        if (n == -1) {
          error(file, binFile);
          return;
        }
        bytenum += 1;
        fputc(CM, binFile);
        bytenum += 1;
        fputc((char) n, binFile);
        bytenum += 1;
        fputc((char)(n >> 8), binFile);
        continue;
      }

      while ((c = fgetc(file)) != '\n') {
        if (c == EOF) break;
      }
      continue;
    }

    // printf("%c", c);
  }
  clearMem();
  fclose(file);
  fclose(binFile);
}
void clearMem(){
  temp = head;
  while(temp->next != 0){
    last = temp;
    temp = temp->next;
    free(last);
  }
  free(temp);
}

void printLabels() {
  temp = head;
  while (temp -> next != 0) {
    printf("%s - %d\n", temp -> name, temp -> address);
    temp = temp -> next;
  }
}
int stringNum(char * s) {
  unsigned int n = 0, len = 0;
  s = lower(s);
  for (len = 0; s[len] != 0; len++);
  if ((s[0] == '0') && (s[1] == 'x')) {
    for (int i = len - 1; i > 1; i--) {
      if ((s[i] < 58) && (s[i] > 47)) {
        n = n | ((s[i] - '0') << ((len - i - 1) * 4));
      } else if ((s[i] > 96) && (s[i] < 103)) {
        n = n | ((s[i] - 87) << ((len - i - 1) * 4));
      } else {
        return -1;
      }

    }
    return n;
  }
  if (s[len - 1] == 'h') {
    for (int i = len - 2; i > 0; i--) {
      if ((s[i] < 58) && (s[i] > 47)) {
        n = n | ((s[i] - '0') << ((len - i - 2) * 4));
      } else if ((s[i] > 96) && (s[i] < 103)) {
        n = n | ((s[i] - 87) << ((len - i - 2) * 4));
      } else {
        return -1;
      }

    }
    return n;
  }
  if (s[len - 1] == 'b') {
    for (int i = len - 2; i > 0; i--) {
      if ((s[i] == '0') || (s[i] == '1')) n = n | (((s[i] - '0') << (len - 2 - i)));
      else return -1;
    }
    return n;
  }
  if (s[len - 1] == 'd') {
    for (int i = len - 2; i >= 0; i--) {
      if ((s[i] >= '0') && (s[i] <= '9')) {
        n += ((s[i] - '0') * power(10, len - 2 - i));
      } else return -1;
      // if((len-2-i)>=5) return n;
    }
    // printf("%d\n", n);
    return n;
  } else {
    for (int i = len - 1; i >= 0; i--) {
      if ((s[i] >= '0') && (s[i] <= '9')) {
        n += ((s[i] - '0') * power(10, len - 1 - i));
      } else return -1;
      // if((len-1-i)>=5) return n;
    }
    // printf("%d\n", n);
    return n;
  }
}
void error(FILE * file, FILE * binFile) {
  printf("[-] Error\n");
  fclose(file);
  fclose(binFile);
}
int power(int x, int n) {
  if (n == 0)
    return 1;
  int ans = x;
  for (int i = 1; i < n; i++) ans *= x;
  return ans;
}
int getNumber(FILE * file, char * argument) {
  char c;
  int k = 0;
  while ((c = fgetc(file)) == ' ');
  while (1) {
    if (c == ' ' || c == '\n') break;
    if (c == ';') {
      while ((c = fgetc(file)) != '\n');
      break;
    }
    argument[k] = c;
    k++;
    c = fgetc(file);
  }
  argument[k] = 0;
  if(head!=NULL){
    temp = head;
    while(temp->next != 0){
      if(cmpstr(temp->name, argument)) return temp->address;
      temp = temp->next;
    }
  }
  return stringNum(argument);
}
char * lower(char * s) {
  for (int i = 0; s[i] != 0; i++) {
    if ((s[i] > 64) && (s[i] < 91)) s[i] += 32;
  }
  return s;
}
char * capital(char * s) {
  for (int i = 0; s[i] != 0; i++) {
    if ((s[i] > 96) && (s[i] < 123)) s[i] -= 32;
  }
  return s;
}
int cmpstr(char * s1, char * s2) {
  int i;
  for (i = 0; s1[i] != 0 && s2[i] != 0; i++) {
    if (s1[i] != s2[i]) return 0;
  }
  if (s1[i] == 0 && s2[i] == 0) return 1;
  return 0;
}
char LXI(char * arg) {
  switch (arg[0]) {
  case 'B':
    return LXIB;
  case 'D':
    return LXID;
  case 'H':
    return LXIH;
  case 'S':
    if (arg[1] == 'P') {
      return LXISP;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char DAD(char * arg) {
  switch (arg[0]) {
  case 'B':
    return DADB;
  case 'D':
    return DADD;
  case 'H':
    return DADH;
  case 'S':
    if (arg[1] == 'P') {
      return DADSP;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char INX(char * arg) {
  switch (arg[0]) {
  case 'B':
    return INXB;
  case 'D':
    return INXD;
  case 'H':
    return INXH;
  case 'S':
    if (arg[1] == 'P') {
      return INXSP;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char DCX(char * arg) {
  switch (arg[0]) {
  case 'B':
    return DCXB;
  case 'D':
    return DCXD;
  case 'H':
    return DCXH;
  case 'S':
    if (arg[1] == 'P') {
      return DCXSP;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char PUSH(char * arg) {
  switch (arg[0]) {
  case 'B':
    return PUSHB;
  case 'D':
    return PUSHD;
  case 'H':
    return PUSHH;
  case 'P':
    if ((arg[1] == 'S') && (arg[2] == 'W')) {
      return PUSHPSW;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char POP(char * arg) {
  switch (arg[0]) {
  case 'B':
    return POPB;
  case 'D':
    return POPD;
  case 'H':
    return POPH;
  case 'P':
    if ((arg[1] == 'S') && (arg[2] == 'W')) {
      return POPPSW;
    } else return 0xFF;
  default:
    return 0xFF;
  }
}
char ADD(char c) {
  switch (c) {
  case 'A':
    return ADDA;
  case 'B':
    return ADDB;
  case 'C':
    return ADDC;
  case 'D':
    return ADDD;
  case 'E':
    return ADDE;
  case 'H':
    return ADDH;
  case 'L':
    return ADDL;
  case 'M':
    return ADDM;
  default:
    return 0xFF;
  }
}
char ANA(char c) {
  switch (c) {
  case 'A':
    return ANAA;
  case 'B':
    return ANAB;
  case 'C':
    return ANAC;
  case 'D':
    return ANAD;
  case 'E':
    return ANAE;
  case 'H':
    return ANAH;
  case 'L':
    return ANAL;
  case 'M':
    return ANAM;
  default:
    return 0xFF;
  }
}
char ORA(char c) {
  switch (c) {
  case 'A':
    return ORAA;
  case 'B':
    return ORAB;
  case 'C':
    return ORAC;
  case 'D':
    return ORAD;
  case 'E':
    return ORAE;
  case 'H':
    return ORAH;
  case 'L':
    return ORAL;
  case 'M':
    return ORAM;
  default:
    return 0xFF;
  }
}
char XRA(char c) {
  switch (c) {
  case 'A':
    return XRAA;
  case 'B':
    return XRAB;
  case 'C':
    return XRAC;
  case 'D':
    return XRAD;
  case 'E':
    return XRAE;
  case 'H':
    return XRAH;
  case 'L':
    return XRAL;
  case 'M':
    return XRAM;
  default:
    return 0xFF;
  }
}
char CMP(char c) {
  switch (c) {
  case 'A':
    return CMPA;
  case 'B':
    return CMPB;
  case 'C':
    return CMPC;
  case 'D':
    return CMPD;
  case 'E':
    return CMPE;
  case 'H':
    return CMPH;
  case 'L':
    return CMPL;
  case 'M':
    return CMPM;
  default:
    return 0xFF;
  }
}
char INR(char c) {
  switch (c) {
  case 'A':
    return INRA;
  case 'B':
    return INRB;
  case 'C':
    return INRC;
  case 'D':
    return INRD;
  case 'E':
    return INRE;
  case 'H':
    return INRH;
  case 'L':
    return INRL;
  case 'M':
    return INRM;
  default:
    return 0xFF;
  }
}
char DCR(char c) {
  switch (c) {
  case 'A':
    return DCRA;
  case 'B':
    return DCRB;
  case 'C':
    return DCRC;
  case 'D':
    return DCRD;
  case 'E':
    return DCRE;
  case 'H':
    return DCRH;
  case 'L':
    return DCRL;
  case 'M':
    return DCRM;
  default:
    return 0xFF;
  }
}
char SBB(char c) {
  switch (c) {
  case 'A':
    return SBBA;
  case 'B':
    return SBBB;
  case 'C':
    return SBBC;
  case 'D':
    return SBBD;
  case 'E':
    return SBBE;
  case 'H':
    return SBBH;
  case 'L':
    return SBBL;
  case 'M':
    return SBBM;
  default:
    return 0xFF;
  }
}
char SUB(char c) {
  switch (c) {
  case 'A':
    return SUBA;
  case 'B':
    return SUBB;
  case 'C':
    return SUBC;
  case 'D':
    return SUBD;
  case 'E':
    return SUBE;
  case 'H':
    return SUBH;
  case 'L':
    return SUBL;
  case 'M':
    return SUBM;
  default:
    return 0xFF;
  }
}
char ADC(char c) {
  switch (c) {
  case 'A':
    return ADCA;
  case 'B':
    return ADCB;
  case 'C':
    return ADCC;
  case 'D':
    return ADCD;
  case 'E':
    return ADCE;
  case 'H':
    return ADCH;
  case 'L':
    return ADCL;
  case 'M':
    return ADCM;
  default:
    return 0xFF;
  }
}
char MVI(char c) {
  switch (c) {
  case 'A':
    return MVIA;
  case 'B':
    return MVIB;
  case 'C':
    return MVIC;
  case 'D':
    return MVID;
  case 'E':
    return MVIE;
  case 'H':
    return MVIH;
  case 'L':
    return MVIL;
  case 'M':
    return MVIM;
  default:
    return 0xFF;
  }
}
char MOV(char * arg) {
  switch (arg[0]) {
  case 'A':
    switch (arg[1]) {
    case 'A':
      return MOVAA;
    case 'B':
      return MOVAB;
    case 'C':
      return MOVAC;
    case 'D':
      return MOVAD;
    case 'E':
      return MOVAE;
    case 'H':
      return MOVAH;
    case 'L':
      return MOVAL;
    case 'M':
      return MOVAM;
    default:
      return 0xFF;
    }
  case 'B':
    switch (arg[1]) {
    case 'A':
      return MOVBA;
    case 'B':
      return MOVBB;
    case 'C':
      return MOVBC;
    case 'D':
      return MOVBD;
    case 'E':
      return MOVBE;
    case 'H':
      return MOVBH;
    case 'L':
      return MOVBL;
    case 'M':
      return MOVBM;
    default:
      return 0xFF;
    }
  case 'C':
    switch (arg[1]) {
    case 'A':
      return MOVCA;
    case 'B':
      return MOVCB;
    case 'C':
      return MOVCC;
    case 'D':
      return MOVCD;
    case 'E':
      return MOVCE;
    case 'H':
      return MOVCH;
    case 'L':
      return MOVCL;
    case 'M':
      return MOVCM;
    default:
      return 0xFF;
    }
  case 'D':
    switch (arg[1]) {
    case 'A':
      return MOVDA;
    case 'B':
      return MOVDB;
    case 'C':
      return MOVDC;
    case 'D':
      return MOVDD;
    case 'E':
      return MOVDE;
    case 'H':
      return MOVDH;
    case 'L':
      return MOVDL;
    case 'M':
      return MOVDM;
    default:
      return 0xFF;
    }
  case 'E':
    switch (arg[1]) {
    case 'A':
      return MOVEA;
    case 'B':
      return MOVEB;
    case 'C':
      return MOVEC;
    case 'D':
      return MOVED;
    case 'E':
      return MOVEE;
    case 'H':
      return MOVEH;
    case 'L':
      return MOVEL;
    case 'M':
      return MOVEM;
    default:
      return 0xFF;
    }
  case 'H':
    switch (arg[1]) {
    case 'A':
      return MOVHA;
    case 'B':
      return MOVHB;
    case 'C':
      return MOVHC;
    case 'D':
      return MOVHD;
    case 'E':
      return MOVHE;
    case 'H':
      return MOVHH;
    case 'L':
      return MOVHL;
    case 'M':
      return MOVHM;
    default:
      return 0xFF;
    }
  case 'L':
    switch (arg[1]) {
    case 'A':
      return MOVLA;
    case 'B':
      return MOVLB;
    case 'C':
      return MOVLC;
    case 'D':
      return MOVLD;
    case 'E':
      return MOVLE;
    case 'H':
      return MOVLH;
    case 'L':
      return MOVLL;
    case 'M':
      return MOVLM;
    default:
      return 0xFF;
    }
  case 'M':
    switch (arg[1]) {
    case 'A':
      return MOVMA;
    case 'B':
      return MOVMB;
    case 'C':
      return MOVMC;
    case 'D':
      return MOVMD;
    case 'E':
      return MOVME;
    case 'H':
      return MOVMH;
    case 'L':
      return MOVML;
    default:
      return 0xFF;
    }
  default:
    return 0xFF;
  }
}