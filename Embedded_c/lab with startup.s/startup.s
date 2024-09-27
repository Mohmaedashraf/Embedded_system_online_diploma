/*startup_cortexM3.s
eng.mohamed
*/
.section .vector
.word 0x20001000  /*stack top address*/
.word _reset 	/*reset*/
.word vector_handler	/* NMI */
.word vector_handler	/* HARD FALUT */
.word vector_handler	/* MM FALUT */
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler
.word vector_handler

.section .text

_reset:
	bl main
	b .
.thumb_func
vector_handler:
	b _reset	