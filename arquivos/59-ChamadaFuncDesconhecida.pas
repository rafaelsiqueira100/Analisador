Program Prog1;
    Var a, b: Integer;

    Procedure Proc1 (Boolean b);
        Var a, c: Boolean;
        Function Func2 (): Boolean;
        Begin
            Func2 := false;
        End
        Function Func1 (Integer a): Integer;
            Var b, d: Integer;
            Function Func3():Boolean;
            Begin
                Func3 := Func2();
            End
        Begin
            b := 2*a-1;

            While (b>0) Do
            Begin
                d := b;
                b := 2*d-1;
            End

            Func1 := (b+d)/2;
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
