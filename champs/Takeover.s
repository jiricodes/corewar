.name "Takeover"
.comment "Yup, it's pretty hostile"

start:								#attack sequence
		ld %57672193, r2			#03700201 == st, r2, 2...
		ld %4278415362, r3			#ff037002 == ...56 st r2...
		ld %33489776, r4			#01ff0370 == ...256 st...
		ld %33685251, r5			#0201ff03 == ...r2, 256 st...
		ld %1879179775, r6			#700201ff == ...r2, 256
		ld %151060480, r7			#zjmp %256 (length of our sequence)
		ld %251658240, r8			#load lfork for defence 251658240 == 0f000000
		st r8, -511					#write lfork in case of infiltrator
		ld %0, r15					#carry = 1
erase:
		zjmp %:begin

defend:
		live %1
		st r8, -400
		st r8, -350
		st r8, -300
		zjmp %:defend

corelive:
		sti r1, %:zork, %1
corelive2:
		sti r1, %:defend, %1
		st r8, :corelive			#remove id write so infiltrators cant copy their own
		st r8, :corelive2			#same as above

core:
		live %1
		fork %:defend
		live %1
		fork %:attack
		live %1
		fork %:zork
		zjmp %:core

begin:
		sti r8, %:erase, %-1		#write lfork on zjmp so we can't be followed
		fork %:attack
		live %1
		zjmp %:corelive

attack:								#commence attack sequence
		st r2, 511
		st r3, 510
		st r4, 509
		st r5, 508
		st r6, 507
		st r2, 506
		st r3, 505
		st r4, 504
		st r5, 503
		st r6, 502
		st r2, 501
		st r3, 500
		st r4, 499
		st r5, 498
		st r6, 497
		st r2, 496
		st r3, 495
		st r4, 494
		st r5, 493
		st r6, 492
		st r2, 491
		st r3, 490
		st r4, 489
		st r5, 488
		st r6, 487
		st r2, 486
		st r3, 485
		st r4, 484
		st r5, 483
		st r6, 482
		st r2, 481
		st r3, 480
		st r4, 479
		st r5, 478
		st r6, 477
		st r2, 476
		st r3, 475
		st r4, 474
		st r5, 473
		st r6, 472
		st r2, 471
		st r3, 470
		st r4, 469
		st r5, 468
		st r6, 467
		st r2, 466
		st r3, 465
		st r4, 464
		st r5, 463
		st r6, 462
		st r2, 461
		st r3, 460
		st r4, 459
		st r5, 458
		st r6, 457
		st r2, 456
		st r3, 455
		st r4, 454
		st r5, 453
		st r6, 452
		st r2, 451
		st r3, 450
		st r4, 449
		st r5, 448
		st r6, 447
		st r7, 446					#write our zjmp %256 to the end of sequence
		live %1
		zjmp %176

zork:								#zork is here for protection
		live %1
		zjmp %:zork
