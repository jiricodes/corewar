.name "substance"
.comment "there was an attempt"

init:
	sti r1, %:uploop, %1
	sti r1, %:downloop, %1
	sti r1, %:gener1, %1
	sti r1, %:gener2, %1
	sti r1, %:gener3, %1
	sti r1, %:liveloop, %1
	ld %57672191, r2
	ld %57671952, r3
	fork %:livespam

init_g:
	and r1, %0, r3
gener1:
	live %1
	fork %:updef

gener2:
	live %1
	fork %:downdef

gener3:
	live %1
	fork %:init_g
	zjmp %:gener1

updef:
	and r1, %0, r4
uploop:
	live %1
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	st r2, -400
	zjmp %:uploop

livespam:
	and r1, %0, r4
liveloop:
	live %1
	zjmp %:liveloop

downdef:
	and r1, %0, r4
downloop:
	live %1
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	st r3, 400
	zjmp %:downloop
