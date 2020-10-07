	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 4
	.globl	_bench_time_sub         ## -- Begin function bench_time_sub
	.p2align	4, 0x90
_bench_time_sub:                        ## @bench_time_sub
Lfunc_begin0:
	.file	1 "/Users/sandermertens/GitHub/SanderMertens/flecs-projects/ecs_benchmark/bench_common" "./src/main.c"
	.loc	1 11 0                  ## ./src/main.c:11:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -32(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -48(%rbp)
	movq	%rcx, -40(%rbp)
Ltmp0:
	.loc	1 13 12 prologue_end    ## ./src/main.c:13:12
	movq	-24(%rbp), %rax
	.loc	1 13 20 is_stmt 0       ## ./src/main.c:13:20
	cmpq	-40(%rbp), %rax
Ltmp1:
	.loc	1 13 9                  ## ./src/main.c:13:9
	jl	LBB0_2
## %bb.1:
Ltmp2:
	.loc	1 14 29 is_stmt 1       ## ./src/main.c:14:29
	movq	-24(%rbp), %rax
	.loc	1 14 37 is_stmt 0       ## ./src/main.c:14:37
	subq	-40(%rbp), %rax
	.loc	1 14 24                 ## ./src/main.c:14:24
	movq	%rax, -8(%rbp)
	.loc	1 15 28 is_stmt 1       ## ./src/main.c:15:28
	movq	-32(%rbp), %rax
	.loc	1 15 35 is_stmt 0       ## ./src/main.c:15:35
	subq	-48(%rbp), %rax
	.loc	1 15 23                 ## ./src/main.c:15:23
	movq	%rax, -16(%rbp)
	.loc	1 16 5 is_stmt 1        ## ./src/main.c:16:5
	jmp	LBB0_3
Ltmp3:
LBB0_2:
	.loc	1 17 29                 ## ./src/main.c:17:29
	movq	-24(%rbp), %rax
	.loc	1 17 37 is_stmt 0       ## ./src/main.c:17:37
	subq	-40(%rbp), %rax
	.loc	1 17 50                 ## ./src/main.c:17:50
	addq	$1000000000, %rax       ## imm = 0x3B9ACA00
	.loc	1 17 24                 ## ./src/main.c:17:24
	movq	%rax, -8(%rbp)
	.loc	1 18 28 is_stmt 1       ## ./src/main.c:18:28
	movq	-32(%rbp), %rax
	.loc	1 18 35 is_stmt 0       ## ./src/main.c:18:35
	subq	-48(%rbp), %rax
	.loc	1 18 47                 ## ./src/main.c:18:47
	subq	$1, %rax
	.loc	1 18 23                 ## ./src/main.c:18:23
	movq	%rax, -16(%rbp)
Ltmp4:
LBB0_3:
	.loc	1 20 5 is_stmt 1        ## ./src/main.c:20:5
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	popq	%rbp
	retq
Ltmp5:
Lfunc_end0:
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__literal8,8byte_literals
	.p2align	3               ## -- Begin function bench_time_toDouble
LCPI1_0:
	.quad	4741671816366391296     ## double 1.0E+9
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_bench_time_toDouble
	.p2align	4, 0x90
_bench_time_toDouble:                   ## @bench_time_toDouble
Lfunc_begin1:
	.loc	1 25 0                  ## ./src/main.c:25:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movsd	LCPI1_0(%rip), %xmm0    ## xmm0 = mem[0],zero
	movq	%rdi, -16(%rbp)
	movq	%rsi, -8(%rbp)
Ltmp6:
	.loc	1 27 14 prologue_end    ## ./src/main.c:27:14
	cvtsi2sdq	-16(%rbp), %xmm1
	.loc	1 27 12 is_stmt 0       ## ./src/main.c:27:12
	movsd	%xmm1, -24(%rbp)
	.loc	1 28 15 is_stmt 1       ## ./src/main.c:28:15
	cvtsi2sdq	-8(%rbp), %xmm1
	.loc	1 28 33 is_stmt 0       ## ./src/main.c:28:33
	divsd	%xmm0, %xmm1
	.loc	1 28 12                 ## ./src/main.c:28:12
	addsd	-24(%rbp), %xmm1
	movsd	%xmm1, -24(%rbp)
	.loc	1 29 12 is_stmt 1       ## ./src/main.c:29:12
	movsd	-24(%rbp), %xmm0        ## xmm0 = mem[0],zero
	.loc	1 29 5 is_stmt 0        ## ./src/main.c:29:5
	popq	%rbp
	retq
Ltmp7:
Lfunc_end1:
	.cfi_endproc
                                        ## -- End function
	.globl	_bench_time_get         ## -- Begin function bench_time_get
	.p2align	4, 0x90
_bench_time_get:                        ## @bench_time_get
Lfunc_begin2:
	.loc	1 34 0 is_stmt 1        ## ./src/main.c:34:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
Ltmp8:
	.loc	1 38 28 prologue_end    ## ./src/main.c:38:28
	callq	_mach_host_self
	.loc	1 38 5 is_stmt 0        ## ./src/main.c:38:5
	movl	%eax, %edi
	movl	$1, %esi
	leaq	-12(%rbp), %rdx
	callq	_host_get_clock_service
	.loc	1 39 20 is_stmt 1       ## ./src/main.c:39:20
	movl	-12(%rbp), %edi
	.loc	1 39 5 is_stmt 0        ## ./src/main.c:39:5
	leaq	-24(%rbp), %rsi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_clock_get_time
	movq	_mach_task_self_@GOTPCREL(%rip), %rcx
	.loc	1 40 26 is_stmt 1       ## ./src/main.c:40:26
	movl	(%rcx), %edi
	.loc	1 40 44 is_stmt 0       ## ./src/main.c:40:44
	movl	-12(%rbp), %esi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	.loc	1 40 5                  ## ./src/main.c:40:5
	callq	_mach_port_deallocate
	.loc	1 41 20 is_stmt 1       ## ./src/main.c:41:20
	movl	-24(%rbp), %esi
	movl	%esi, %ecx
	.loc	1 41 5 is_stmt 0        ## ./src/main.c:41:5
	movq	-8(%rbp), %rdx
	.loc	1 41 18                 ## ./src/main.c:41:18
	movq	%rcx, (%rdx)
	.loc	1 42 21 is_stmt 1       ## ./src/main.c:42:21
	movslq	-20(%rbp), %rcx
	.loc	1 42 5 is_stmt 0        ## ./src/main.c:42:5
	movq	-8(%rbp), %rdx
	.loc	1 42 19                 ## ./src/main.c:42:19
	movq	%rcx, 8(%rdx)
	.loc	1 48 1 is_stmt 1        ## ./src/main.c:48:1
	addq	$32, %rsp
	popq	%rbp
	retq
Ltmp9:
Lfunc_end2:
	.cfi_endproc
                                        ## -- End function
	.globl	_bench_time_measure     ## -- Begin function bench_time_measure
	.p2align	4, 0x90
_bench_time_measure:                    ## @bench_time_measure
Lfunc_begin3:
	.loc	1 52 0                  ## ./src/main.c:52:0
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -8(%rbp)
Ltmp10:
	.loc	1 54 5 prologue_end     ## ./src/main.c:54:5
	leaq	-24(%rbp), %rdi
Ltmp11:
	##DEBUG_VALUE: bench_time_measure:stop <- [$rdi+0]
	callq	_bench_time_get
Ltmp12:
	.loc	1 55 12                 ## ./src/main.c:55:12
	movq	-24(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -32(%rbp)
	.loc	1 56 34                 ## ./src/main.c:56:34
	movq	-8(%rbp), %rax
	.loc	1 56 12 is_stmt 0       ## ./src/main.c:56:12
	movq	-24(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	(%rax), %rdx
	movq	8(%rax), %rcx
	callq	_bench_time_sub
	movq	%rax, -56(%rbp)
	movq	%rdx, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc	1 57 6 is_stmt 1        ## ./src/main.c:57:6
	movq	-8(%rbp), %rax
	.loc	1 57 14 is_stmt 0       ## ./src/main.c:57:14
	movq	-40(%rbp), %rcx
	movq	%rcx, (%rax)
	movq	-32(%rbp), %rcx
	movq	%rcx, 8(%rax)
	.loc	1 58 12 is_stmt 1       ## ./src/main.c:58:12
	movq	-24(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	_bench_time_toDouble
	.loc	1 58 5 is_stmt 0        ## ./src/main.c:58:5
	addq	$64, %rsp
	popq	%rbp
	retq
Ltmp13:
Lfunc_end3:
	.cfi_endproc
                                        ## -- End function
	.file	2 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/i386" "_types.h"
	.file	3 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types" "_timespec.h"
	.file	4 "/Users/sandermertens/GitHub/SanderMertens/flecs-projects/ecs_benchmark/bench_common" "./include/bench_common.h"
	.file	5 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys" "_types.h"
	.file	6 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/_types" "_mach_port_t.h"
	.file	7 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach" "mach_types.h"
	.file	8 "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/mach" "clock_types.h"
	.section	__DWARF,__debug_str,regular,debug
Linfo_string:
	.asciz	"Apple clang version 11.0.3 (clang-1103.0.32.62)" ## string offset=0
	.asciz	"src/main.c"            ## string offset=48
	.asciz	"/Users/sandermertens/GitHub/SanderMertens/flecs-projects/ecs_benchmark/bench_common" ## string offset=59
	.asciz	"double"                ## string offset=143
	.asciz	"bench_time_sub"        ## string offset=150
	.asciz	"bench_time_toDouble"   ## string offset=165
	.asciz	"bench_time_get"        ## string offset=185
	.asciz	"bench_time_measure"    ## string offset=200
	.asciz	"bench_time_t"          ## string offset=219
	.asciz	"timespec"              ## string offset=232
	.asciz	"tv_sec"                ## string offset=241
	.asciz	"__darwin_time_t"       ## string offset=248
	.asciz	"long int"              ## string offset=264
	.asciz	"tv_nsec"               ## string offset=273
	.asciz	"t1"                    ## string offset=281
	.asciz	"t2"                    ## string offset=284
	.asciz	"result"                ## string offset=287
	.asciz	"t"                     ## string offset=294
	.asciz	"time"                  ## string offset=296
	.asciz	"cclock"                ## string offset=301
	.asciz	"clock_serv_t"          ## string offset=308
	.asciz	"mach_port_t"           ## string offset=321
	.asciz	"__darwin_mach_port_t"  ## string offset=333
	.asciz	"__darwin_mach_port_name_t" ## string offset=354
	.asciz	"__darwin_natural_t"    ## string offset=380
	.asciz	"unsigned int"          ## string offset=399
	.asciz	"mts"                   ## string offset=412
	.asciz	"mach_timespec_t"       ## string offset=416
	.asciz	"mach_timespec"         ## string offset=432
	.asciz	"clock_res_t"           ## string offset=446
	.asciz	"int"                   ## string offset=458
	.asciz	"start"                 ## string offset=462
	.asciz	"stop"                  ## string offset=468
	.asciz	"temp"                  ## string offset=473
	.section	__DWARF,__debug_abbrev,regular,debug
Lsection_abbrev:
	.byte	1                       ## Abbreviation Code
	.byte	17                      ## DW_TAG_compile_unit
	.byte	1                       ## DW_CHILDREN_yes
	.byte	37                      ## DW_AT_producer
	.byte	14                      ## DW_FORM_strp
	.byte	19                      ## DW_AT_language
	.byte	5                       ## DW_FORM_data2
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	16                      ## DW_AT_stmt_list
	.byte	23                      ## DW_FORM_sec_offset
	.byte	27                      ## DW_AT_comp_dir
	.byte	14                      ## DW_FORM_strp
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	2                       ## Abbreviation Code
	.byte	36                      ## DW_TAG_base_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	62                      ## DW_AT_encoding
	.byte	11                      ## DW_FORM_data1
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	3                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	64                      ## DW_AT_frame_base
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	25                      ## DW_FORM_flag_present
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	4                       ## Abbreviation Code
	.byte	5                       ## DW_TAG_formal_parameter
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	5                       ## Abbreviation Code
	.byte	52                      ## DW_TAG_variable
	.byte	0                       ## DW_CHILDREN_no
	.byte	2                       ## DW_AT_location
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	6                       ## Abbreviation Code
	.byte	46                      ## DW_TAG_subprogram
	.byte	1                       ## DW_CHILDREN_yes
	.byte	17                      ## DW_AT_low_pc
	.byte	1                       ## DW_FORM_addr
	.byte	18                      ## DW_AT_high_pc
	.byte	6                       ## DW_FORM_data4
	.byte	64                      ## DW_AT_frame_base
	.byte	24                      ## DW_FORM_exprloc
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	39                      ## DW_AT_prototyped
	.byte	25                      ## DW_FORM_flag_present
	.byte	63                      ## DW_AT_external
	.byte	25                      ## DW_FORM_flag_present
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	7                       ## Abbreviation Code
	.byte	22                      ## DW_TAG_typedef
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	8                       ## Abbreviation Code
	.byte	19                      ## DW_TAG_structure_type
	.byte	1                       ## DW_CHILDREN_yes
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	11                      ## DW_AT_byte_size
	.byte	11                      ## DW_FORM_data1
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	9                       ## Abbreviation Code
	.byte	13                      ## DW_TAG_member
	.byte	0                       ## DW_CHILDREN_no
	.byte	3                       ## DW_AT_name
	.byte	14                      ## DW_FORM_strp
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	58                      ## DW_AT_decl_file
	.byte	11                      ## DW_FORM_data1
	.byte	59                      ## DW_AT_decl_line
	.byte	11                      ## DW_FORM_data1
	.byte	56                      ## DW_AT_data_member_location
	.byte	11                      ## DW_FORM_data1
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	10                      ## Abbreviation Code
	.byte	15                      ## DW_TAG_pointer_type
	.byte	0                       ## DW_CHILDREN_no
	.byte	73                      ## DW_AT_type
	.byte	19                      ## DW_FORM_ref4
	.byte	0                       ## EOM(1)
	.byte	0                       ## EOM(2)
	.byte	0                       ## EOM(3)
	.section	__DWARF,__debug_info,regular,debug
Lsection_info:
Lcu_begin0:
.set Lset0, Ldebug_info_end0-Ldebug_info_start0 ## Length of Unit
	.long	Lset0
Ldebug_info_start0:
	.short	4                       ## DWARF version number
.set Lset1, Lsection_abbrev-Lsection_abbrev ## Offset Into Abbrev. Section
	.long	Lset1
	.byte	8                       ## Address Size (in bytes)
	.byte	1                       ## Abbrev [1] 0xb:0x1e4 DW_TAG_compile_unit
	.long	0                       ## DW_AT_producer
	.short	12                      ## DW_AT_language
	.long	48                      ## DW_AT_name
.set Lset2, Lline_table_start0-Lsection_line ## DW_AT_stmt_list
	.long	Lset2
	.long	59                      ## DW_AT_comp_dir
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset3, Lfunc_end3-Lfunc_begin0     ## DW_AT_high_pc
	.long	Lset3
	.byte	2                       ## Abbrev [2] 0x2a:0x7 DW_TAG_base_type
	.long	143                     ## DW_AT_name
	.byte	4                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	3                       ## Abbrev [3] 0x31:0x44 DW_TAG_subprogram
	.quad	Lfunc_begin0            ## DW_AT_low_pc
.set Lset4, Lfunc_end0-Lfunc_begin0     ## DW_AT_high_pc
	.long	Lset4
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	150                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	8                       ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	303                     ## DW_AT_type
                                        ## DW_AT_external
	.byte	4                       ## Abbrev [4] 0x4a:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	96
	.long	281                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	9                       ## DW_AT_decl_line
	.long	303                     ## DW_AT_type
	.byte	4                       ## Abbrev [4] 0x58:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	80
	.long	284                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	10                      ## DW_AT_decl_line
	.long	303                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0x66:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	112
	.long	287                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	12                      ## DW_AT_decl_line
	.long	303                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	3                       ## Abbrev [3] 0x75:0x36 DW_TAG_subprogram
	.quad	Lfunc_begin1            ## DW_AT_low_pc
.set Lset5, Lfunc_end1-Lfunc_begin1     ## DW_AT_high_pc
	.long	Lset5
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	165                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	23                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	42                      ## DW_AT_type
                                        ## DW_AT_external
	.byte	4                       ## Abbrev [4] 0x8e:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	112
	.long	294                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	24                      ## DW_AT_decl_line
	.long	303                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0x9c:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	104
	.long	287                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	26                      ## DW_AT_decl_line
	.long	42                      ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	6                       ## Abbrev [6] 0xab:0x40 DW_TAG_subprogram
	.quad	Lfunc_begin2            ## DW_AT_low_pc
.set Lset6, Lfunc_end2-Lfunc_begin2     ## DW_AT_high_pc
	.long	Lset6
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	185                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	32                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
                                        ## DW_AT_external
	.byte	4                       ## Abbrev [4] 0xc0:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	120
	.long	296                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.long	365                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0xce:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	116
	.long	301                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	36                      ## DW_AT_decl_line
	.long	370                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0xdc:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	104
	.long	412                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	37                      ## DW_AT_decl_line
	.long	432                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	3                       ## Abbrev [3] 0xeb:0x44 DW_TAG_subprogram
	.quad	Lfunc_begin3            ## DW_AT_low_pc
.set Lset7, Lfunc_end3-Lfunc_begin3     ## DW_AT_high_pc
	.long	Lset7
	.byte	1                       ## DW_AT_frame_base
	.byte	86
	.long	200                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	50                      ## DW_AT_decl_line
                                        ## DW_AT_prototyped
	.long	42                      ## DW_AT_type
                                        ## DW_AT_external
	.byte	4                       ## Abbrev [4] 0x104:0xe DW_TAG_formal_parameter
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	120
	.long	462                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	51                      ## DW_AT_decl_line
	.long	365                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0x112:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	104
	.long	468                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	314                     ## DW_AT_type
	.byte	5                       ## Abbrev [5] 0x120:0xe DW_TAG_variable
	.byte	2                       ## DW_AT_location
	.byte	145
	.byte	88
	.long	473                     ## DW_AT_name
	.byte	1                       ## DW_AT_decl_file
	.byte	53                      ## DW_AT_decl_line
	.long	314                     ## DW_AT_type
	.byte	0                       ## End Of Children Mark
	.byte	7                       ## Abbrev [7] 0x12f:0xb DW_TAG_typedef
	.long	314                     ## DW_AT_type
	.long	219                     ## DW_AT_name
	.byte	4                       ## DW_AT_decl_file
	.byte	12                      ## DW_AT_decl_line
	.byte	8                       ## Abbrev [8] 0x13a:0x21 DW_TAG_structure_type
	.long	232                     ## DW_AT_name
	.byte	16                      ## DW_AT_byte_size
	.byte	3                       ## DW_AT_decl_file
	.byte	33                      ## DW_AT_decl_line
	.byte	9                       ## Abbrev [9] 0x142:0xc DW_TAG_member
	.long	241                     ## DW_AT_name
	.long	347                     ## DW_AT_type
	.byte	3                       ## DW_AT_decl_file
	.byte	35                      ## DW_AT_decl_line
	.byte	0                       ## DW_AT_data_member_location
	.byte	9                       ## Abbrev [9] 0x14e:0xc DW_TAG_member
	.long	273                     ## DW_AT_name
	.long	358                     ## DW_AT_type
	.byte	3                       ## DW_AT_decl_file
	.byte	36                      ## DW_AT_decl_line
	.byte	8                       ## DW_AT_data_member_location
	.byte	0                       ## End Of Children Mark
	.byte	7                       ## Abbrev [7] 0x15b:0xb DW_TAG_typedef
	.long	358                     ## DW_AT_type
	.long	248                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	120                     ## DW_AT_decl_line
	.byte	2                       ## Abbrev [2] 0x166:0x7 DW_TAG_base_type
	.long	264                     ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	8                       ## DW_AT_byte_size
	.byte	10                      ## Abbrev [10] 0x16d:0x5 DW_TAG_pointer_type
	.long	303                     ## DW_AT_type
	.byte	7                       ## Abbrev [7] 0x172:0xb DW_TAG_typedef
	.long	381                     ## DW_AT_type
	.long	308                     ## DW_AT_name
	.byte	7                       ## DW_AT_decl_file
	.byte	138                     ## DW_AT_decl_line
	.byte	7                       ## Abbrev [7] 0x17d:0xb DW_TAG_typedef
	.long	392                     ## DW_AT_type
	.long	321                     ## DW_AT_name
	.byte	6                       ## DW_AT_decl_file
	.byte	50                      ## DW_AT_decl_line
	.byte	7                       ## Abbrev [7] 0x188:0xb DW_TAG_typedef
	.long	403                     ## DW_AT_type
	.long	333                     ## DW_AT_name
	.byte	5                       ## DW_AT_decl_file
	.byte	69                      ## DW_AT_decl_line
	.byte	7                       ## Abbrev [7] 0x193:0xb DW_TAG_typedef
	.long	414                     ## DW_AT_type
	.long	354                     ## DW_AT_name
	.byte	5                       ## DW_AT_decl_file
	.byte	68                      ## DW_AT_decl_line
	.byte	7                       ## Abbrev [7] 0x19e:0xb DW_TAG_typedef
	.long	425                     ## DW_AT_type
	.long	380                     ## DW_AT_name
	.byte	2                       ## DW_AT_decl_file
	.byte	50                      ## DW_AT_decl_line
	.byte	2                       ## Abbrev [2] 0x1a9:0x7 DW_TAG_base_type
	.long	399                     ## DW_AT_name
	.byte	7                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	7                       ## Abbrev [7] 0x1b0:0xb DW_TAG_typedef
	.long	443                     ## DW_AT_type
	.long	416                     ## DW_AT_name
	.byte	8                       ## DW_AT_decl_file
	.byte	65                      ## DW_AT_decl_line
	.byte	8                       ## Abbrev [8] 0x1bb:0x21 DW_TAG_structure_type
	.long	432                     ## DW_AT_name
	.byte	8                       ## DW_AT_byte_size
	.byte	8                       ## DW_AT_decl_file
	.byte	61                      ## DW_AT_decl_line
	.byte	9                       ## Abbrev [9] 0x1c3:0xc DW_TAG_member
	.long	241                     ## DW_AT_name
	.long	425                     ## DW_AT_type
	.byte	8                       ## DW_AT_decl_file
	.byte	62                      ## DW_AT_decl_line
	.byte	0                       ## DW_AT_data_member_location
	.byte	9                       ## Abbrev [9] 0x1cf:0xc DW_TAG_member
	.long	273                     ## DW_AT_name
	.long	476                     ## DW_AT_type
	.byte	8                       ## DW_AT_decl_file
	.byte	63                      ## DW_AT_decl_line
	.byte	4                       ## DW_AT_data_member_location
	.byte	0                       ## End Of Children Mark
	.byte	7                       ## Abbrev [7] 0x1dc:0xb DW_TAG_typedef
	.long	487                     ## DW_AT_type
	.long	446                     ## DW_AT_name
	.byte	8                       ## DW_AT_decl_file
	.byte	56                      ## DW_AT_decl_line
	.byte	2                       ## Abbrev [2] 0x1e7:0x7 DW_TAG_base_type
	.long	458                     ## DW_AT_name
	.byte	5                       ## DW_AT_encoding
	.byte	4                       ## DW_AT_byte_size
	.byte	0                       ## End Of Children Mark
Ldebug_info_end0:
	.section	__DWARF,__debug_macinfo,regular,debug
Ldebug_macinfo:
	.byte	0                       ## End Of Macro List Mark
	.section	__DWARF,__apple_names,regular,debug
Lnames_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	4                       ## Header Bucket Count
	.long	4                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	0                       ## Bucket 0
	.long	-1                      ## Bucket 1
	.long	3                       ## Bucket 2
	.long	-1                      ## Bucket 3
	.long	728977180               ## Hash in Bucket 0
	.long	1367113316              ## Hash in Bucket 0
	.long	-1263452784             ## Hash in Bucket 0
	.long	728963602               ## Hash in Bucket 2
.set Lset8, LNames0-Lnames_begin        ## Offset in Bucket 0
	.long	Lset8
.set Lset9, LNames3-Lnames_begin        ## Offset in Bucket 0
	.long	Lset9
.set Lset10, LNames1-Lnames_begin       ## Offset in Bucket 0
	.long	Lset10
.set Lset11, LNames2-Lnames_begin       ## Offset in Bucket 2
	.long	Lset11
LNames0:
	.long	150                     ## bench_time_sub
	.long	1                       ## Num DIEs
	.long	49
	.long	0
LNames3:
	.long	200                     ## bench_time_measure
	.long	1                       ## Num DIEs
	.long	235
	.long	0
LNames1:
	.long	165                     ## bench_time_toDouble
	.long	1                       ## Num DIEs
	.long	117
	.long	0
LNames2:
	.long	185                     ## bench_time_get
	.long	1                       ## Num DIEs
	.long	171
	.long	0
	.section	__DWARF,__apple_objc,regular,debug
Lobjc_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_namespac,regular,debug
Lnamespac_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	1                       ## Header Bucket Count
	.long	0                       ## Header Hash Count
	.long	12                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	1                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.long	-1                      ## Bucket 0
	.section	__DWARF,__apple_types,regular,debug
Ltypes_begin:
	.long	1212240712              ## Header Magic
	.short	1                       ## Header Version
	.short	0                       ## Header Hash Function
	.long	15                      ## Header Bucket Count
	.long	15                      ## Header Hash Count
	.long	20                      ## Header Data Length
	.long	0                       ## HeaderData Die Offset Base
	.long	3                       ## HeaderData Atom Count
	.short	1                       ## DW_ATOM_die_offset
	.short	6                       ## DW_FORM_data4
	.short	3                       ## DW_ATOM_die_tag
	.short	5                       ## DW_FORM_data2
	.short	4                       ## DW_ATOM_type_flags
	.short	11                      ## DW_FORM_data1
	.long	0                       ## Bucket 0
	.long	-1                      ## Bucket 1
	.long	-1                      ## Bucket 2
	.long	1                       ## Bucket 3
	.long	4                       ## Bucket 4
	.long	5                       ## Bucket 5
	.long	-1                      ## Bucket 6
	.long	7                       ## Bucket 7
	.long	9                       ## Bucket 8
	.long	-1                      ## Bucket 9
	.long	10                      ## Bucket 10
	.long	12                      ## Bucket 11
	.long	-1                      ## Bucket 12
	.long	13                      ## Bucket 13
	.long	14                      ## Bucket 14
	.long	-1937529961             ## Hash in Bucket 0
	.long	501551718               ## Hash in Bucket 3
	.long	-1880351968             ## Hash in Bucket 3
	.long	-1863999343             ## Hash in Bucket 3
	.long	-243996567              ## Hash in Bucket 4
	.long	1754681015              ## Hash in Bucket 5
	.long	-1304652851             ## Hash in Bucket 5
	.long	567385087               ## Hash in Bucket 7
	.long	-1164513309             ## Hash in Bucket 7
	.long	193495088               ## Hash in Bucket 8
	.long	614278765               ## Hash in Bucket 10
	.long	-520515531              ## Hash in Bucket 10
	.long	-602271305              ## Hash in Bucket 11
	.long	-113419488              ## Hash in Bucket 13
	.long	1256548394              ## Hash in Bucket 14
.set Lset12, Ltypes8-Ltypes_begin       ## Offset in Bucket 0
	.long	Lset12
.set Lset13, Ltypes0-Ltypes_begin       ## Offset in Bucket 3
	.long	Lset13
.set Lset14, Ltypes13-Ltypes_begin      ## Offset in Bucket 3
	.long	Lset14
.set Lset15, Ltypes6-Ltypes_begin       ## Offset in Bucket 3
	.long	Lset15
.set Lset16, Ltypes1-Ltypes_begin       ## Offset in Bucket 4
	.long	Lset16
.set Lset17, Ltypes9-Ltypes_begin       ## Offset in Bucket 5
	.long	Lset17
.set Lset18, Ltypes3-Ltypes_begin       ## Offset in Bucket 5
	.long	Lset18
.set Lset19, Ltypes11-Ltypes_begin      ## Offset in Bucket 7
	.long	Lset19
.set Lset20, Ltypes14-Ltypes_begin      ## Offset in Bucket 7
	.long	Lset20
.set Lset21, Ltypes5-Ltypes_begin       ## Offset in Bucket 8
	.long	Lset21
.set Lset22, Ltypes4-Ltypes_begin       ## Offset in Bucket 10
	.long	Lset22
.set Lset23, Ltypes7-Ltypes_begin       ## Offset in Bucket 10
	.long	Lset23
.set Lset24, Ltypes10-Ltypes_begin      ## Offset in Bucket 11
	.long	Lset24
.set Lset25, Ltypes12-Ltypes_begin      ## Offset in Bucket 13
	.long	Lset25
.set Lset26, Ltypes2-Ltypes_begin       ## Offset in Bucket 14
	.long	Lset26
Ltypes8:
	.long	333                     ## __darwin_mach_port_t
	.long	1                       ## Num DIEs
	.long	392
	.short	22
	.byte	0
	.long	0
Ltypes0:
	.long	219                     ## bench_time_t
	.long	1                       ## Num DIEs
	.long	303
	.short	22
	.byte	0
	.long	0
Ltypes13:
	.long	264                     ## long int
	.long	1                       ## Num DIEs
	.long	358
	.short	36
	.byte	0
	.long	0
Ltypes6:
	.long	380                     ## __darwin_natural_t
	.long	1                       ## Num DIEs
	.long	414
	.short	22
	.byte	0
	.long	0
Ltypes1:
	.long	248                     ## __darwin_time_t
	.long	1                       ## Num DIEs
	.long	347
	.short	22
	.byte	0
	.long	0
Ltypes9:
	.long	354                     ## __darwin_mach_port_name_t
	.long	1                       ## Num DIEs
	.long	403
	.short	22
	.byte	0
	.long	0
Ltypes3:
	.long	399                     ## unsigned int
	.long	1                       ## Num DIEs
	.long	425
	.short	36
	.byte	0
	.long	0
Ltypes11:
	.long	232                     ## timespec
	.long	1                       ## Num DIEs
	.long	314
	.short	19
	.byte	0
	.long	0
Ltypes14:
	.long	308                     ## clock_serv_t
	.long	1                       ## Num DIEs
	.long	370
	.short	22
	.byte	0
	.long	0
Ltypes5:
	.long	458                     ## int
	.long	1                       ## Num DIEs
	.long	487
	.short	36
	.byte	0
	.long	0
Ltypes4:
	.long	446                     ## clock_res_t
	.long	1                       ## Num DIEs
	.long	476
	.short	22
	.byte	0
	.long	0
Ltypes7:
	.long	321                     ## mach_port_t
	.long	1                       ## Num DIEs
	.long	381
	.short	22
	.byte	0
	.long	0
Ltypes10:
	.long	432                     ## mach_timespec
	.long	1                       ## Num DIEs
	.long	443
	.short	19
	.byte	0
	.long	0
Ltypes12:
	.long	143                     ## double
	.long	1                       ## Num DIEs
	.long	42
	.short	36
	.byte	0
	.long	0
Ltypes2:
	.long	416                     ## mach_timespec_t
	.long	1                       ## Num DIEs
	.long	432
	.short	22
	.byte	0
	.long	0

.subsections_via_symbols
	.section	__DWARF,__debug_line,regular,debug
Lsection_line:
Lline_table_start0:
