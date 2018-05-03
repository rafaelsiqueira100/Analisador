Program Prog1;
    Var a, b: Integer;

    Procedure Proc1 (Boolean b);
        Var a, c: Boolean;        
    Begin
        If (b)
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
    
    Function Func1 (Integer a): Integer;
        Var b, d: Integer;

        Procedure P2018(Boolean a, Integer b, Boolean c, Boolean d);
            Var e, f: Boolean;
            Var g,h : Integer;
        
        Begin
            e := true;
            f := false;
            
            if(e and f)
                g := 1012;
            else
                g := -900;
            if(e or f)
                h := g+3*4+(5/2*7);
            else
                h := g-3+5*((h*3)-(3*g)/4)/7
            Write(g+h);
        End
    Begin
        b := 2*a-1;

        While (b>0) Do
        Begin
            d := b;
            b := 2*d-1;
        End

        Func1 := (b+d)/2;
        P2018();
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
