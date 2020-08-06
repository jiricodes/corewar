.name "wrong op"
.comment "sd command"

l2:		sti r1, %:error, %1		#wrong label
		and r1, %0, r1

live:	live %1
		zjmp %:live
