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
