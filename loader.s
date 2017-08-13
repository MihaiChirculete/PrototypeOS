global outb 	; make the label outb visible outside this file
; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
; [esp + 4] the I/O port
;[esp] return address

outb:
	mov al, [esp + 8] 	; move the data to be sent into the al register
	mov dx, [esp + 4] 	; move the address of the I/O port into the dx register
	out dx, al 			; send the data to the I/O port
	ret 				; return to the calling function

global inb
; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;[esp] The return address
inb:
	mov dx, [esp + 4] 	; move the address of the I/O port to the dx register
	in al, dx	; read a byte from the I/O port and store it in the al register
	ret 	; return the read byte


global loader	; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002		; define the magic number constant
FLAGS equ 0x0 					; multiboot flags
CHECKSUM equ -MAGIC_NUMBER		; calculate the checksum
								; (magic number + checksum + flags should equal 0)

KERNEL_STACK_SIZE equ 4096 ; size of stack in bytes

section .bss
	align 4							; align at 4 bytes					
	kernel_stack:					; label points to beginning of memory
		resb KERNEL_STACK_SIZE		; reserve stack for the kernel



section .text:			; start of the text (code) section
	align 4				; the code must be 4 byte aligned
	dd MAGIC_NUMBER		; write the magic number to the machine code,
	dd FLAGS 			; the flags,
	dd CHECKSUM 		; and the checksum

loader: 					; the loader label (defined as entry point in linker script)

	mov esp, kernel_stack + KERNEL_STACK_SIZE	; point esp to the start of the
												; stack (end of memory area)

extern kmain 	; the main function of the kernel
call kmain 		; call the main function of the kernel

.loop:
	jmp .loop				; loop forever


; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global gdt_flush     ; Allows the C code to link to this
extern _gp            ; Says that '_gp' is in another file
gdt_flush:
    lgdt [_gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               ; Returns back to the C code!