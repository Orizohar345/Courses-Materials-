	.file	"try.c"
	.intel_syntax noprefix
        .text
        .globl	_main
        .def	_main;	.scl	2;	.type	32;	.endef
_main:
        lea     ecx, [esp+4]
        and     esp, -16
        push    DWORD PTR [ecx-4]
        push    ebp
        mov     ebp, esp
        push    ecx

        push 0x0       		# pushing null
	push 0x41797261		# pushing A,y,r,a
	push 0x7262694c		# pushing r,b,i,L
	push 0x64616f4c		# pushing d,a,o,L
	push esp            # push pointer for "LoadLibraryA"

	call FindFunction   # call FindFunction("LoadLibraryA")
	add esp, 0x14       # clear stack

	push 0x00006c6c		# pushing null,l,l
	push 0x642e7472		# pushing d,#,t,r
	push 0x6376736d		# pushing c,v,s,m
	push esp

	call eax            # call LoadLibrary("msvcrtdll")
	add esp, 0x0c       # clear stack (note arguments are cleared already)

	push eax            # store module handle for msvcrt
	push 0x00007373		# pushing null,s,s
	push 0x65726464		# pushing e,r,d,d
	push 0x41636f72		# pushing A,c,o,r
	push 0x50746547		# pushing P,t,e,G
	push esp            # push pointer for "GetProcAddress"

	call FindFunction   # call FindFunction("GetProcAddress")
	add esp, 0x14       # clear stack
	pop ebx             # restore module handle for msvcrt

	push 0x00006674		# pushing null,f,t
	push 0x6e697270		# pushing n,i,r,p
	push esp            # push pointer for "printf"
	push ebx            # push module handle for msvcrt

	mov esi, eax
	call esi            # call GetProcAddress(msvcrt, "printf")
	mov edi, eax       # printf in edi
	add esp, 0x08       # clear stack (note arguments are cleared already)

	push 0x00000066		# pushing null,f
	push 0x6e616373		# pushing n,a,c,s
	push esp            # push pointer for "scanf"
	push ebx            # push module handle for msvcrt

	call esi            # call GetProcAddress(msvcrt, "scanf")
	mov esi, eax       # scanf in esi
	add esp, 0x08       # clear stack (note arguments are cleared already)

        sub     esp, 52
        mov     DWORD PTR [ebp-36], 0
        mov     DWORD PTR [ebp-32], 0
        mov     DWORD PTR [ebp-28], 0
        mov     DWORD PTR [ebp-24], 0
        mov     DWORD PTR [ebp-20], 0
.L8:
        mov     DWORD PTR [ebp-48], 0
        mov     DWORD PTR [ebp-44], 0
        mov     DWORD PTR [ebp-40], 0
        sub     esp, 8
        lea     eax, [ebp-48]
        push    0x00007325	# pushing null,s,%
	mov     ebx, esp	# pointer to the string in ebx
        push    eax
        push    ebx             # pushing string pointer to stack
        call    esi             # calling scanf (in esi)
        add     esp, 16
        add     esp, 4          # clear string from stack
        mov     DWORD PTR [ebp-16], eax
        cmp     DWORD PTR [ebp-16], -1
        jne     .L2
        mov     DWORD PTR [ebp-12], 0
        jmp     .L3
.L2:
        movzx   eax, BYTE PTR [ebp-48]
        cmp     al, 114
        jne     .L4
        mov     eax, DWORD PTR [ebp-36]
        add     eax, 1
        mov     DWORD PTR [ebp-36], eax
        mov     eax, DWORD PTR [ebp-32]
        add     eax, 1
        mov     DWORD PTR [ebp-32], eax
        jmp     .L8
.L4:
        movzx   eax, BYTE PTR [ebp-48]
        cmp     al, 115
        jne     .L6
        mov     eax, DWORD PTR [ebp-36]
        add     eax, 1
        mov     DWORD PTR [ebp-36], eax
        mov     eax, DWORD PTR [ebp-32]
        add     eax, 1
        mov     DWORD PTR [ebp-32], eax
        mov     eax, DWORD PTR [ebp-28]
        add     eax, 1
        mov     DWORD PTR [ebp-28], eax
        mov     eax, DWORD PTR [ebp-24]
        add     eax, 1
        mov     DWORD PTR [ebp-24], eax
        jmp     .L8
.L6:
        movzx   eax, BYTE PTR [ebp-48]
        cmp     al, 99
        jne     .L7
        mov     eax, DWORD PTR [ebp-24]
        add     eax, 2
        mov     DWORD PTR [ebp-24], eax
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 3
        mov     DWORD PTR [ebp-20], eax
        jmp     .L8
.L7:
        movzx   eax, BYTE PTR [ebp-48]
        cmp     al, 100
        jne     .L8
        mov     eax, DWORD PTR [ebp-28]
        add     eax, 1
        mov     DWORD PTR [ebp-28], eax
        mov     eax, DWORD PTR [ebp-24]
        add     eax, 1
        mov     DWORD PTR [ebp-24], eax
        mov     eax, DWORD PTR [ebp-20]
        add     eax, 1
        mov     DWORD PTR [ebp-20], eax
        jmp     .L8
.L3:
        cmp     DWORD PTR [ebp-12], 3
        jg      .L9
        mov     eax, DWORD PTR [ebp-12]
        mov     eax, DWORD PTR [ebp-36+eax*4]
        cmp     eax, 100
        jle     .L10
        sub     esp, 12
        push    0x00203939	#pushing "99 "
	push    esp		#pushing pointer to "99 "
        call    edi             #call printf (in edi)
        add     esp, 16
        add     esp, 4          #clear stack
        jmp     .L11
.L10:
        mov     eax, DWORD PTR [ebp-12]
        mov     eax, DWORD PTR [ebp-36+eax*4]
        sub     esp, 8
        push    0x00000020      #pushing " "
	push    0x64323025      #pushing d,2,0,%
	mov     ebx, esp        #copy pointer
        push    eax
        push    ebx             #push string pointer to stack
        call    edi             #call printf (in edi)
        add     esp, 16
        add     esp, 8          #clear stack
.L11:
        add     DWORD PTR [ebp-12], 1
        jmp     .L3
.L9:
        mov     eax, DWORD PTR [ebp-20]
        cmp     eax, 100
        jle     .L12
        sub     esp, 12
        push    0x000A3939	#pushing "99\n"
	push    esp		#pushing pointer to "99\n"
        call    edi             #call printf (in edi)
        add     esp, 16
        add     esp, 4          #clear stack
        jmp     .L13
.L12:
        mov     eax, DWORD PTR [ebp-20]
        sub     esp, 8
        push    0x0000000A	#pushing "\n"
	push    0x64323025	#pushing d,2,0,%
	mov     ebx, esp	#copy pointer
        push    eax
        push    ebx             #push string pointer to stack
        call    edi             #call printf (in edi)
        add     esp, 16
        add     esp, 8          #clear stack
.L13:
        mov     eax, 0
        mov     ecx, DWORD PTR [ebp-4]
        leave
        lea     esp, [ecx-4]
        ret
FindFunction:
