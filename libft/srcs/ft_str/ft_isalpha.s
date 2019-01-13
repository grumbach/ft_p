; **************************************************************************** ;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isalpha.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2018/05/18 04:07:59 by agrumbac          #+#    #+#              ;
;    Updated: 2018/05/18 06:24:04 by agrumbac         ###   ########.fr        ;
;                                                                              ;
; **************************************************************************** ;

section .text
	global _ft_isalpha

_ft_isalpha:
	push rbp
	mov rbp, rsp

	mov rax, 0

	cmp rdi, 65
	jl _is_not_alpha
	cmp rdi, 91
	jl _is_alpha

	cmp rdi, 97
	jl _is_not_alpha
	cmp rdi, 122
	jg _is_not_alpha

_is_alpha:
	mov rax, 1
_is_not_alpha:
	leave
	ret
