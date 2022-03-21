MODULE Module1
    PERS jointtarget jHome := [[0,0,0,0,60,0],[9E+9,9E+9,9E+9,9E+9,9E+9,9E+9]];
	PERS jointtarget jPreLeftStart:=[[25.0261,32.6283,8.19303,-80.2544,80.3488,126.325],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
    
    !PERS robtarget pHome :=[[397.64,0,569.39],[0.23701,0,0.97151,0],[0,0,-1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    
!    PROC udp_test1()
!        VAR egmident egmID1;
!        EGMGetId egmID1;
!        !EGMSetupUC ROB_1,egmID1,"default","UCdevice"\Pose;
!        EGMSetupUC ROB_1,egmID1,"default","UCdevice"\Joint;
        
!        EGMStreamStart egmID1\SampleRate:=4;
        
!        MoveAbsJ jHome,v100,z20,tool0;
!        MoveAbsJ jPreLeftStart,v100,fine,tool0;
        
!        EGMStreamStop egmID1;
!        EGMReset egmID1;
!    ENDPROC
    
    
    PROC udp_test2()
        VAR egmident egmID1;
        VAR egmstate egmST1;
        CONST egm_minmax lin1 :=[-1,1];! pos lim
        CONST egm_minmax rot1 :=[-0.5,0.5];! orient lim
        VAR pose corr_frame_offs := [[0,0,0],[1,0,0,0]];  

        MoveAbsJ jHome ,v100,fine,tool0\WObj:=wobj0;
        

        ! test uc 
        EGMReset egmID1;  ! egm state is 0
        WaitTime 1;
        EGMGetId egmID1;  ! egm state is 1
        egmST1 := EGMGetState(egmID1);
        TPWrite "EGM State "\Num:=egmST1;
        IF egmST1 <= EGM_STATE_CONNECTED THEN
            EGMSetupUC ROB_1,egmID1,"default","UCdevice"\Pose\CommTimeout:=WAIT_MAX;
        ENDIF
        
     
        EGMActPose egmID1\Tool:=tool0,corr_frame_offs,EGM_FRAME_WORLD,
            corr_frame_offs,EGM_FRAME_WORLD
            \x:=lin1\y:=lin1\z:=lin1
            \rx:=rot1\ry:=rot1\rz:=rot1
            \LpFilter:=20\MaxSpeedDeviation:=40;
        WHILE TRUE DO
            EGMRunPose egmID1,EGM_STOP_HOLD
                \x\y\z\rx\ry\rz\CondTime:=2\RampInTime:=0.05;  ! wait here,robot just move in x and y direction.
        ENDWHILE
            
        egmST1 := EGMGetState(egmID1);
        IF egmST1=EGM_STATE_CONNECTED THEN
            TPWrite "Reset EGM instance emgID1";
            EGMReset egmID1;
        ENDIF    
        TPWrite "finish";
        
    ENDPROC
    
    
    
    
    
    PROC main()
        
        !udp_test1;
        udp_test2;
        
    ENDPROC
ENDMODULE

