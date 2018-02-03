      .text                     ;.text (program) section
      .global normalize         ;define global function normalize
      
normalize:                      ;(label for normalize)
      movw r18, r24             ;move r25:r24 into r19:r18
      sub r18, r22              ;subtract r25:r24 with low byte of r23:r22
      sbc r19, r23              ;subtract high byte (setup for br command)
      brlt skip1                ;go to skip1 if A < B
      movw r24, r22             ;move r23:r22 into r25:r24
      ret                       ;we can return if call is proper (i.e. B > C)

skip1:
      movw r18, r24             ;again move r25:r24 into r19:r18
      sub r18, r20              ;subtract low bytes
      sbc r19, r21              ;subtract high bytes
      brge skip2                ;go to skip2 if C <= A
      movw r24, r20             ;move r21:r20 into r25:r24

skip2:
      ret
