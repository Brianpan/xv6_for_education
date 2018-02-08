# XV6 Source Code
FileName | Status
kalloc.c | ok

# Simple Linker Script Example
// kernel.ld
https://sourceware.org/binutils/docs/ld/Simple-Example.html

SECTIONS
{
	// location counter
	// if not set, the value is the current value of the location counter
	. = 0x100000;
	// declare output section .text
	// *(.text) names of input section 
	// * wildcard
	// *(.text) means all input sections in all input files
	.text : {*(.text)};
	// The linker put data output section at 0x8000000
	. = 0x8000000;
	.data : { *(.data) }
}

https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/4/html/Using_ld_the_GNU_Linker/assignments.html
SECTIONS
{
  .text :
    {
      *(.text)
      _etext = .;
      // define a symbol that is not included in any object
      PROVIDE(etext = .);
    }
}

SECTIONS { ❶
        . = 0x00000000; ❷
        .text : { ❸
                abc.o (.text);
                def.o (.text);
        } ❹
}
3, 4 -> This part of the script specifies that, the .text section from the input files abc.o and def.o should go to the .text section of the output file.

- Entry Point
https://sourceware.org/binutils/docs/ld/Entry-Point.html#Entry-Point

First instruction to execute in a program is called the entry point.
Can use ENTRY(symbol) to set the entry point

- Section Types
1. .text : program code
2. .rdata: read only data
3. .data : read-write initialized data
4. .bss  : read-write initialized data


