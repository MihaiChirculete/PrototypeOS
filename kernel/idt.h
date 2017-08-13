#ifndef __IDT_H
#define __IDT_H

/* IDT.C */
extern void _idt_load();
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();

#endif


/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr _idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void _idt_load();


/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
   	/* Assign the base values */
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	/* Set the other fields */
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;

}

/* Installs the IDT */
void idt_install()
{
	// debug messages
	char idt_setup[] = "Interrupt Descriptor Table setup started...\n";
	char idt_pointer_and_limit[] = "IDT pointer and limit set!\n";
	char idt_flushed[] = "IDT flushed!\n";

	write(idt_setup, WHITE_ON_BLACK);

    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    _idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    _idtp.base = (addr)&idt;

    write(idt_pointer_and_limit, LIGHTGREEN_ON_BLACK);

    /* Clear out the entire IDT, initializing it to zeros */
    memset((void*)&idt, 0, sizeof(struct idt_entry) * 256);

    write(idt_flushed, LIGHTGREEN_ON_BLACK);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    _idt_load();
}
