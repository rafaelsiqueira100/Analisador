Program Prog1;
    Var a, b: Integer;

    Procedure Proc1 (Boolean b);
        Var a, c: Boolean;

        Function Func1 (Integer a): Integer;
            Var b, d: Integer;
			
			Procedure P2018 (Boolean a, Integer b, Boolean c, Boolean d);
                Var e, f: Boolean;
                Var g,h : Integer;
                
                Procedure P3018(Boolean a, Boolean b);
                    Var e,f : Boolean;
                    Var g,h : Integer;
                    Var i : Boolean;
                
				Begin
					e := not a;
					if b then
						g := 12;
					else
						g:= -12;
					i := e and (b or e);
					h := g * 3 * (g+3);
				End
			Begin
				if(e and f)then
					g:= 1012;
				else
					g:= -900;
				if(e or f)then
					h:= g+3*4+(5/2*7);
				else
					h:= g-3+5*((h*3)-(3*g)/4)/7;
				Write(g);
			End
        Begin
            b := 2*0-1;

            While (b>0) Do
            Begin
                d := b;
                b := 2*d-1;
            End

            Func1 := (b+d)/2;
			P2018();
        End
    Begin
        If (Func1(5)/2 >7)
        Then Begin
            a := true;
            c := not b;
        End
        Else Begin
            a := not b;
            c := false;
        End

        If (a and b or c) Then
            Write ('COTUCA');
        Else
            Write ('UNICAMP');
    End
Begin
    a := 5;
    b := 7;

    While (a<b or (a>500 and b>700)) Do
    Begin
        Proc1(a<b);
        a := a+2;
        b := 2*b;
    End

    Write (a);
    Write (b);
End.
