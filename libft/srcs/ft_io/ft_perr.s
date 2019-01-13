; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_perr.s                                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2018/05/19 12:54:14 by agrumbac          #+#    #+#              ;
;    Updated: 2018/06/21 16:24:43 by agrumbac         ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

%define MACH_SYSCALL(n)    0x2000000 | n
%define WRITE              4
%define STDERR             2

section .text
	global _ft_perr
	extern _ft_strlen

_ft_perr:
	push rbp
	mov rbp, rsp

	mov rsi, rdi

	call _ft_strlen
	mov rdx, rax

	mov rdi, STDERR
	mov rax, MACH_SYSCALL(WRITE)
	syscall

	leave
	ret
